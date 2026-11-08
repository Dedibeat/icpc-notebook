#!/usr/bin/env python3
"""Download the first-ranked accepted C++ entry from each CSES code-size queue.

Requires requests/beautifulsoup4 and a private PHPSESSID cookie file. Read-only:
never submits solutions or hacks. Entries retain their actual compiler version;
C++17 compatibility and notebook suitability are not inferred from language C++.
Usage: python3 tools/cses_shortest.py --cookie-file /private/session --all
Work: O(total downloaded HTML/source bytes), excluding network; memory O(tasks).
"""
import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
from datetime import datetime, timezone
import hashlib
import json
from pathlib import Path
import re
import sys
import threading
import time
from urllib.parse import urljoin

import requests
from bs4 import BeautifulSoup

BASE = 'https://cses.fi'
LOCAL = threading.local()


def parse_queue(source, task):
    soup = BeautifulSoup(source, 'html.parser')
    rows = []
    for row in soup.select('table tr'):
        link = row.select_one('a.details-link[href]')
        if link is None:
            continue
        cells = row.find_all('td', recursive=False)
        if len(cells) < 6:
            raise ValueError('Unexpected submission row')
        path = link['href']
        if not re.fullmatch(rf'/problemset/hack/{task}/entry/\d+/?', path):
            raise ValueError('Unexpected entry URL')
        size = re.fullmatch(r'([\d,]+)\s*ch\.', cells[4].get_text(' ', strip=True))
        if not size or cells[2].get_text(strip=True) != 'C++':
            raise ValueError('Unexpected language/size')
        if 'full' not in cells[5].get('class', []):
            raise ValueError('Queue row is not accepted')
        rows.append({'entry_id': re.search(r'/entry/(\d+)', path)[1],
                     'entry_url': urljoin(BASE, path),
                     'author': cells[1].get_text(' ', strip=True),
                     'submitted_at': cells[0].get_text(' ', strip=True),
                     'reported_characters': int(size[1].replace(',', '')),
                     'max_time': cells[3].get_text(' ', strip=True)})
    if not rows:
        raise ValueError('No accessible accepted C++ entries')
    sizes = [r['reported_characters'] for r in rows]
    if sizes != sorted(sizes):
        raise ValueError('Queue is not sorted by increasing code size')
    return rows


def parse_entry(source):
    soup = BeautifulSoup(source, 'html.parser')
    code = soup.select_one('pre.prettyprint')
    if code is None or not code.get_text().strip():
        raise ValueError('Source is missing or inaccessible')
    compiler = None
    for row in soup.select('table tr'):
        cells = row.find_all('td', recursive=False)
        if len(cells) == 4:
            compiler = cells[2].get_text(' ', strip=True)
            break
    if not compiler or not compiler.startswith('C++'):
        raise ValueError('Missing C++ compiler version')
    return compiler, code.get_text()


def get_session(cookie):
    if not hasattr(LOCAL, 'session'):
        LOCAL.session = requests.Session()
        LOCAL.session.headers['Connection'] = 'close'
        LOCAL.session.cookies.set('PHPSESSID', cookie, domain='cses.fi')
    return LOCAL.session


def fetch(url, cookie):
    for attempt in range(5):
        try:
            r = get_session(cookie).get(url, timeout=(10, 40))
            r.raise_for_status()
            if '/login' in r.url:
                raise ValueError('Session expired; login required')
            return r.text
        except requests.RequestException as error:
            status = error.response.status_code if error.response is not None else None
            if attempt == 4 or (status is not None and status < 500 and status != 429):
                raise
            header = error.response.headers.get('Retry-After', '') if error.response is not None else ''
            time.sleep(int(header) if header.isdigit() else min(2 ** attempt, 30))


def download(task, title, cookie, output, refresh):
    metadata = output / f'{task}.json'
    code_path = output / f'{task}.cpp'
    if metadata.exists() and code_path.exists() and not refresh:
        entry = json.loads(metadata.read_text())
        if entry.get('sha256') != hashlib.sha256(code_path.read_bytes()).hexdigest():
            raise ValueError('Cached source hash differs; use --refresh')
        return entry
    queue_url = f'{BASE}/problemset/queue/{task}/1/?lang=3&status=2&user=&by=2&order=0'
    queue = fetch(queue_url, cookie)
    first = parse_queue(queue, task)[0]
    detail = fetch(first['entry_url'], cookie)
    compiler, code = parse_entry(detail)
    data = code.encode('utf-8')
    entry = dict(first, task=task, title=title, queue_url=queue_url,
                 compiler=compiler, status='ACCEPTED', rank=1,
                 fetched_at_utc=datetime.now(timezone.utc).isoformat(),
                 sha256=hashlib.sha256(data).hexdigest(), source_bytes=len(data),
                 source_file=str(code_path))
    # Preserve ranking and source-page evidence, without authentication forms/tokens.
    evidence = {'ranking': parse_queue(queue, task), 'compiler': compiler}
    (output / f'{task}.evidence.json').write_text(json.dumps(evidence, indent=2) + '\n')
    temporary = code_path.with_suffix('.cpp.tmp')
    temporary.write_bytes(data)
    temporary.replace(code_path)
    temporary = metadata.with_suffix('.json.tmp')
    temporary.write_text(json.dumps(entry, ensure_ascii=False, indent=2) + '\n')
    temporary.replace(metadata)
    return entry


def main():
    p = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    p.add_argument('ids', nargs='*', help='Task IDs (default with --all: every cached task)')
    p.add_argument('--all', action='store_true')
    p.add_argument('--tasks', type=Path, default=Path('tmp/cses-all.json'))
    p.add_argument('--cookie-file', required=True, type=Path)
    p.add_argument('--output', type=Path, default=Path('tmp/cses-shortest'))
    p.add_argument('--workers', type=int, choices=range(1, 9), default=4, metavar='1..8')
    p.add_argument('--refresh', action='store_true')
    args = p.parse_args()
    tasks = {str(t['id']): t['title'] for t in json.loads(args.tasks.read_text())}
    ids = list(dict.fromkeys([*(tasks if args.all else []), *args.ids]))
    if not ids or any(t not in tasks for t in ids):
        p.error('Provide known task IDs or --all; prepare --tasks with read_cses.py')
    cookie = args.cookie_file.read_text().strip()
    if not cookie or any(c.isspace() for c in cookie):
        p.error('cookie-file must contain only PHPSESSID')
    args.output.mkdir(parents=True, exist_ok=True)
    entries, errors = {}, {}
    with ThreadPoolExecutor(max_workers=args.workers) as pool:
        futures = {pool.submit(download, t, tasks[t], cookie, args.output, args.refresh): t for t in ids}
        for future in as_completed(futures):
            task = futures[future]
            try:
                entries[task] = future.result()
            except Exception as error:
                errors[task] = str(error)
                print(f'ERROR {task}: {error}', file=sys.stderr, flush=True)
            if (len(entries) + len(errors)) % 25 == 0:
                print(f'{len(entries)+len(errors)}/{len(ids)} checked; {len(entries)} downloaded', flush=True)
    manifest = {'selection': 'first accepted C++ entry in ascending reported code-size queue',
                'compiler_policy': 'all C++ versions; actual compiler recorded per entry',
                'tasks_requested': len(ids), 'downloaded': len(entries),
                'entries': [entries[t] for t in ids if t in entries], 'errors': errors}
    (args.output / 'manifest.json').write_text(json.dumps(manifest, ensure_ascii=False, indent=2) + '\n')
    print(f'DONE {len(entries)}/{len(ids)} downloaded; {len(errors)} errors', flush=True)
    return bool(errors)


if __name__ == '__main__':
    sys.exit(main())
