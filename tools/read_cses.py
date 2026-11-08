#!/usr/bin/env python3
"""Bulk-read public CSES statements. Requires requests and beautifulsoup4.

Examples:
  python3 tools/read_cses.py 1068 1083
  python3 tools/read_cses.py --all --format json --output tmp/cses.json
  python3 tools/read_cses.py 1068 --offline

Preserves full statements, including examples and TeX. Cache entries are JSON;
failed downloads never replace good entries. Work: O(total HTML size), excluding
network latency; memory: O(total selected statement size). No login required.
"""
import argparse
from concurrent.futures import ThreadPoolExecutor, as_completed
import json
from pathlib import Path
import re
import sys
import time
from urllib.parse import urljoin

import requests
from bs4 import BeautifulSoup

BASE = 'https://cses.fi'


def fetch(url):
    """Retry transient HTTP/network errors; retain TLS verification and timeouts."""
    for attempt in range(3):
        try:
            response = requests.get(url, timeout=(10, 40))
            response.raise_for_status()
            return response.text
        except requests.RequestException as error:
            if (getattr(error, 'response', None) is not None
                    and error.response.status_code < 500
                    and error.response.status_code != 429):
                raise
            if attempt == 2:
                raise
            time.sleep(2 ** attempt)


def parse_tasks(source):
    soup = BeautifulSoup(source, 'html.parser')
    tasks = {}
    for link in soup.select('a[href]'):
        match = re.fullmatch(r'/problemset/task/(\d+)/?', link['href'])
        if match:
            tasks[match[1]] = link.get_text(' ', strip=True)
    if not tasks:
        raise ValueError('No task links found in problem set')
    return tasks


def parse_statement(task, source):
    soup = BeautifulSoup(source, 'html.parser')
    body = soup.select_one('.content .md')
    if body is None or not body.get_text(strip=True):
        raise ValueError(f'{task}: missing statement')
    title = soup.select_one('.title-block h1') or soup.select_one('h1')
    if title is None:
        raise ValueError(f'{task}: missing title')
    for image in body.select('img[src]'):
        image.replace_with(f"![{image.get('alt', 'Figure')}]({urljoin(BASE, image['src'])})")
    # Replace code blocks first: BeautifulSoup's strip=True destroys indentation.
    for pre in body.select('pre'):
        code = pre.get_text().strip('\n')
        fence = '```'
        while fence in code:
            fence += '`'
        pre.replace_with(f'\n\n{fence}\n{code}\n{fence}\n\n')
    for heading in body.select('h1,h2,h3,h4'):
        heading.replace_with('\n\n## ' + heading.get_text(' ', strip=True) + '\n\n')
    for br in body.select('br'):
        br.replace_with('\n')
    for item in body.select('li'):
        item.insert_before('\n- ')
        item.insert_after('\n')
    for para in body.select('p,ul,ol'):
        para.insert_before('\n\n')
        para.insert_after('\n\n')
    # Keep math source and text-node spacing, including inline <span> boundaries.
    text = body.get_text().strip()
    limits = soup.select_one('.task-constraints')
    return {'id': str(task), 'title': title.get_text(' ', strip=True),
            'url': f'{BASE}/problemset/task/{task}/',
            'limits': limits.get_text(' ', strip=True) if limits else '',
            'statement': text}


def read_task(task, cache, refresh=False, offline=False):
    path = cache / f'{task}.json'
    if path.exists() and (not refresh or offline):
        saved = json.loads(path.read_text())
        if saved.get('id') != task or not saved.get('statement'):
            raise ValueError(f'{task}: invalid cache entry; use --refresh')
        return saved
    if offline:
        raise ValueError(f'{task}: not cached')
    entry = parse_statement(task, fetch(f'{BASE}/problemset/task/{task}/'))
    cache.mkdir(parents=True, exist_ok=True)
    temporary = path.with_suffix('.json.tmp')
    temporary.write_text(json.dumps(entry, ensure_ascii=False, indent=2) + '\n')
    temporary.replace(path)
    return entry


def render(entries, fmt):
    if fmt == 'json':
        return json.dumps(entries, ensure_ascii=False, indent=2) + '\n'
    return '\n\n---\n\n'.join(
        f"# {e['id']}: {e['title']}\n\n{e['url']}\n\n{e['limits']}\n\n{e['statement']}"
        for e in entries) + '\n'


def main():
    parser = argparse.ArgumentParser(description=__doc__,
                                     formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('ids', nargs='*', help='CSES task IDs, space or comma separated')
    parser.add_argument('--all', action='store_true', help='Read the full current problem set')
    parser.add_argument('--cache', type=Path, default=Path('tmp/cses-statements'))
    parser.add_argument('--refresh', action='store_true')
    parser.add_argument('--offline', action='store_true', help='Only read cached data')
    parser.add_argument('--workers', type=int, default=4, choices=range(1, 9), metavar='1..8')
    parser.add_argument('--format', choices=['md', 'json'], default='md')
    parser.add_argument('--output', type=Path, help='Default: stdout; progress goes to stderr')
    args = parser.parse_args()
    ids = [part for arg in args.ids for part in arg.split(',') if part]
    if any(not re.fullmatch(r'[1-9]\d*', task) for task in ids):
        parser.error('IDs must be positive integers')
    if args.refresh and args.offline:
        parser.error('--refresh and --offline conflict')
    if args.all:
        if args.offline:
            ids += sorted((p.stem for p in args.cache.glob('*.json') if p.stem.isdigit()), key=int)
        else:
            ids += list(parse_tasks(fetch(f'{BASE}/problemset/')))
    ids = list(dict.fromkeys(ids))
    if not ids:
        parser.error('Provide task IDs or --all (offline --all requires cached tasks)')
    results, errors = {}, []
    with ThreadPoolExecutor(max_workers=args.workers) as pool:
        futures = {pool.submit(read_task, task, args.cache, args.refresh, args.offline): task
                   for task in ids}
        for future in as_completed(futures):
            task = futures[future]
            try:
                results[task] = future.result()
            except Exception as error:
                errors.append(task)
                print(f'ERROR {task}: {error}', file=sys.stderr)
            done = len(results) + len(errors)
            if done % 25 == 0:
                print(f'Progress: {done}/{len(ids)}', file=sys.stderr)
    output = render([results[task] for task in ids if task in results], args.format)
    if args.output:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(output)
    else:
        sys.stdout.write(output)
    print(f'Read {len(results)}/{len(ids)} statements; cache: {args.cache}', file=sys.stderr)
    return bool(errors)


if __name__ == '__main__':
    sys.exit(main())
