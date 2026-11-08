#!/usr/bin/env python3
"""Resumable CSES C++17 submission runner, adapted from p1/cses/fire_ac2.py
and verify_ac.py. Usage: see tools/README.cses.md. Requires requests/bs4.
No credentials are written to logs. Each task may try alternate real sources.
Work: O(source bytes + number of tasks/attempts), excluding compiler/judge time.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor
import hashlib
import json
from pathlib import Path
import re
import subprocess
import tempfile
import time
import unicodedata

import requests
from bs4 import BeautifulSoup

BASE = 'https://cses.fi'
VERDICTS = ['ACCEPTED', 'WRONG ANSWER', 'TIME LIMIT EXCEEDED',
            'MEMORY LIMIT EXCEEDED', 'RUNTIME ERROR', 'COMPILATION ERROR',
            'OUTPUT LIMIT EXCEEDED', 'COMPILATION FAILED']


def normalize(name):
    return re.sub('[^a-z0-9]', '', unicodedata.normalize('NFKD', name).encode('ascii', 'ignore').decode().lower())


def index_sources(tasks, roots):
    names = {normalize(t['title']): t['id'] for t in tasks}
    candidates = {t['id']: [] for t in tasks}
    seen = {t['id']: set() for t in tasks}
    for root in roots:
        for path in sorted(root.rglob('*.cpp')):
            if '.git' in path.parts:
                continue
            ids = re.findall(r'(?<!\d)(\d{4})(?!\d)', path.stem + ' ' + path.parent.name)
            ids = {t for t in ids if t in candidates}
            task = next(iter(ids)) if len(ids) == 1 else None
            if not ids:
                task = names.get(normalize(path.stem))
                if task is None and path.stem.lower() in ('main', 'solution'):
                    task = names.get(normalize(path.parent.name))
            if task:
                digest = hashlib.sha256(path.read_bytes()).hexdigest()
                if digest not in seen[task]:
                    candidates[task].append({'path': str(path.resolve()), 'sha256': digest})
                    seen[task].add(digest)
    return candidates


def verdict(source):
    soup = BeautifulSoup(source, 'html.parser')
    status = soup.select_one('#status')
    if status and status.get_text(strip=True) in ('COMPILE ERROR', 'COMPILATION ERROR'):
        return 'COMPILATION ERROR'
    for row in soup.select('tr'):
        cells = row.find_all(['td', 'th'], recursive=False)
        if len(cells) >= 2 and cells[0].get_text(strip=True) == 'Result:':
            value = cells[1].get_text(' ', strip=True)
            if value in VERDICTS:
                return value
    return None


def session(cookie):
    s = requests.Session()
    s.headers['Connection'] = 'close'
    s.cookies.set('PHPSESSID', cookie, domain='cses.fi')
    return s


def save_event(path, event):
    with path.open('a') as f:
        f.write(json.dumps(event) + '\n')
        f.flush()


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--cookie-file', type=Path, required=True)
    p.add_argument('--account', required=True, help='Expected CSES numeric user ID')
    p.add_argument('--tasks', type=Path, default=Path('tmp/cses-all.json'))
    p.add_argument('--sources', nargs='+', type=Path, required=True)
    p.add_argument('--state', type=Path, default=Path('tmp/cses-run'))
    p.add_argument('--rounds', type=int, default=3)
    p.add_argument('--skip-compile', action='store_true', help='Let CSES compile; fastest submission mode')
    p.add_argument('--delay', type=float, default=4, help='Seconds between submissions (default 4)')
    args = p.parse_args()
    if args.delay < 0:
        p.error('--delay must be nonnegative')
    args.state.mkdir(parents=True, exist_ok=True)
    cookie = args.cookie_file.read_text().strip()
    s = session(cookie)
    page = s.get(BASE + '/problemset/submit/1068/', timeout=30)
    page.raise_for_status()
    soup = BeautifulSoup(page.text, 'html.parser')
    if not soup.select_one(f'a[href="/user/{args.account}"]'):
        raise RuntimeError('Session expired or unexpected account; no submissions sent')
    token = soup.select_one('input[name="csrf_token"]')['value']
    identity = args.state / 'account.txt'
    if identity.exists() and identity.read_text() != args.account:
        raise RuntimeError('State belongs to another account')
    identity.write_text(args.account)
    tasks = json.loads(args.tasks.read_text())
    candidates = index_sources(tasks, args.sources)
    (args.state / 'sources.json').write_text(json.dumps(candidates, indent=2))
    baseline = args.state / 'baseline.json'
    if not baseline.exists():
        def scan(task):
            with session(cookie) as client:
                r = client.get(f'{BASE}/problemset/model/{task}/', timeout=30)
                if r.status_code not in (200, 404):
                    raise RuntimeError(f'Scan failed: {task}, HTTP {r.status_code}')
                if '/login' in r.url:
                    raise RuntimeError('Session expired')
                return task, r.status_code == 200
        with ThreadPoolExecutor(max_workers=4) as pool:
            status = dict(pool.map(scan, candidates))
        baseline.write_text(json.dumps(status, indent=2))
    accepted = {t for t, ok in json.loads(baseline.read_text()).items() if ok}
    log = args.state / 'events.jsonl'
    events = [json.loads(line) for line in log.read_text().splitlines()] if log.exists() else []
    tried = {(e['task'], e['sha256']) for e in events if e['kind'] in ('submitted', 'compile_error')}
    accepted.update(e['task'] for e in events if e.get('verdict') == 'ACCEPTED')
    print(f'Baseline/resume: {len(accepted)}/{len(tasks)} AC; source coverage: {sum(bool(v) for v in candidates.values())}', flush=True)

    def check_pending():
        nonlocal accepted, events
        completed = {e['submission'] for e in events if e['kind'] == 'verdict'}
        pending = [e for e in events if e['kind'] == 'submitted' and e['submission'] not in completed]
        for event in pending:
            result = None
            for _ in range(60):
                r = s.get(f"{BASE}/problemset/result/{event['submission']}/", timeout=30)
                r.raise_for_status()
                result = verdict(r.text)
                if result:
                    break
                time.sleep(2)
            if result is None:
                raise RuntimeError(f"Unresolved submission {event['submission']}; resume later")
            record = dict(event, kind='verdict', verdict=result)
            save_event(log, record)
            events.append(record)
            if result == 'ACCEPTED':
                accepted.add(event['task'])
            print(f"{event['task']} {result} ({len(accepted)}/{len(tasks)} AC)", flush=True)
            time.sleep(.25)

    check_pending()
    for round_id in range(args.rounds):
        submitted = 0
        for task, sources in candidates.items():
            if task in accepted:
                continue
            for source in sources:
                if (task, source['sha256']) in tried:
                    continue
                record = dict(source, task=task)
                if not args.skip_compile:
                    with tempfile.TemporaryDirectory() as directory:
                        compile_result = subprocess.run(['g++', '-std=c++17', '-DONLINE_JUDGE', '-O2', source['path'], '-o', directory + '/solution'], capture_output=True, timeout=90)
                    if compile_result.returncode:
                        record.update(kind='compile_error', error=compile_result.stderr.decode(errors='replace')[-3000:])
                        save_event(log, record)
                        tried.add((task, source['sha256']))
                        continue
                # Log each successful POST before any later network request.
                # A missing redirect is ambiguous: stop rather than duplicate it.
                r = s.post(BASE + '/course/send.php',
                           data={'csrf_token': token, 'task': task, 'type': 'course',
                                 'target': 'problemset', 'lang': 'C++', 'option': 'C++17'},
                           files={'file': (task + '.cpp', Path(source['path']).read_bytes(), 'text/plain')},
                           timeout=45, allow_redirects=False)
                for retry in range(5):
                    if r.status_code != 429:
                        break
                    header = r.headers.get('Retry-After', '')
                    wait = int(header) if header.isdigit() else min(10 * 2 ** retry, 60)
                    print(f'{task}: rate limited; backoff {wait}s (Retry-After={header or "absent"})', flush=True)
                    time.sleep(wait)
                    r = s.post(BASE + '/course/send.php',
                               data={'csrf_token': token, 'task': task, 'type': 'course',
                                     'target': 'problemset', 'lang': 'C++', 'option': 'C++17'},
                               files={'file': (task + '.cpp', Path(source['path']).read_bytes(), 'text/plain')},
                               timeout=45, allow_redirects=False)
                match = re.search(r'/result/(\d+)', r.headers.get('Location', ''))
                if not match:
                    raise RuntimeError(f'{task}: submission not confirmed (HTTP {r.status_code}); inspect before retrying')
                record.update(kind='submitted', submission=match[1])
                save_event(log, record)
                events.append(record)
                tried.add((task, source['sha256']))
                submitted += 1
                print(f"round {round_id+1}: {task} submitted {match[1]}", flush=True)
                time.sleep(args.delay)
                if submitted % 10 == 0:
                    check_pending()
                break
        check_pending()
        if not submitted:
            break
    remaining = [{'id': t['id'], 'title': t['title'], 'sources': len(candidates[t['id']])}
                 for t in tasks if t['id'] not in accepted]
    (args.state / 'remaining.json').write_text(json.dumps(remaining, indent=2))
    print(f'FINAL {len(accepted)}/{len(tasks)} AC; remaining: {len(remaining)}', flush=True)


if __name__ == '__main__':
    main()
