#!/usr/bin/env python3
"""Build a printable notebook from the newest substantial CSES analyses.

Input:  ~/projects/p1/cses/analyses_final/{manifest.tsv,*.html} plus the live
        CSES task pages on the first run.
Output: cses_notebook.html and cses_statements.json (Chrome can print the HTML
        to cses_notebook.pdf).

Selection is intentionally mechanical: scan numeric task ids newest-first, skip
analyses shorter than --min-chars, and keep --count entries. This removes most
one-observation introductory tasks without pretending to rank every problem.
"""

from __future__ import annotations

import argparse
import json
import html
from concurrent.futures import ThreadPoolExecutor, as_completed
from pathlib import Path
from urllib.request import Request, urlopen

from bs4 import BeautifulSoup


STYLE = r"""
@page { size: A4; margin: 13mm 14mm 15mm; }
* { box-sizing: border-box; }
body { color: #172033; font: 9.6pt/1.38 system-ui, sans-serif; margin: 0 auto;
       max-width: 185mm; }
h1 { color: #173f73; font-size: 25pt; margin: 0 0 8mm; }
.task-title { border-bottom: 1.5pt solid #2e6da4; color: #173f73; font-size: 16pt;
              line-height: 1.2; margin: 0 0 4mm; padding-bottom: 1.5mm; }
h3 { color: #245789; font-size: 11pt; line-height: 1.25; margin: 4mm 0 1mm; }
p, ul, ol { margin: 1.5mm 0; }
ul, ol { padding-left: 6mm; }
a { color: #245789; text-decoration: none; }
pre { background: #f5f7fa; border-left: 2.5pt solid #6b91b8; font: 7.2pt/1.22
      "DejaVu Sans Mono", monospace; margin: 3mm 0; padding: 2.5mm;
      tab-size: 2; white-space: pre-wrap; overflow-wrap: anywhere; }
code { font-family: "DejaVu Sans Mono", monospace; }
.cover { align-items: center; display: flex; height: 245mm; justify-content: center;
         page-break-after: always; text-align: center; }
.cover p { color: #536579; font-size: 12pt; }
.contents { page-break-after: always; }
.toc { columns: 3; column-gap: 7mm; font-size: 8.4pt; }
.toc-group { break-inside: avoid; margin: 0 0 4mm; }
.toc-group h2 { border-bottom: .8pt solid #6b91b8; color: #245789;
                font-size: 10pt; margin: 0 0 1.5mm; padding-bottom: .7mm; }
.toc-group ol { list-style: none; margin: 0; padding: 0; }
.toc li { break-inside: avoid; margin: 0 0 1.2mm; }
.analysis { break-before: page; }
.chapter-title { color: #617083; font-size: 9pt; font-weight: 700;
                 letter-spacing: .08em; margin: 0 0 2mm; text-transform: uppercase; }
.meta { color: #617083; font-size: 8.5pt; margin-bottom: 4mm; }
.statement { background: #f1f6fb; border-left: 2.5pt solid #2e6da4;
             margin: 3mm 0 5mm; padding: 2.5mm 3mm; }
.statement .statement-title { color: #245789; font-size: 10.5pt; letter-spacing: .02em;
                              margin: 0 0 1.5mm; }
.statement h1, .statement h2 { border: 0; color: #365d82; font-size: 10pt;
                               line-height: 1.25; margin: 2.5mm 0 .8mm; padding: 0; }
.statement h3, .statement h4 { color: #365d82; font-size: 9.6pt; line-height: 1.25;
                              margin: 2mm 0 .8mm; }
.statement h1, .statement h2, .statement h3, .statement h4 { break-after: avoid; }
.statement p, .statement ul, .statement ol { margin: .9mm 0; }
.statement li { margin: .3mm 0; }
.statement pre { font-size: 7pt; margin: 1.5mm 0; }
.explanation h1, .explanation h2 { border-bottom: 1pt solid #6b91b8; color: #245789;
                                  font-size: 12.5pt; line-height: 1.25;
                                  margin: 4mm 0 1.5mm; padding-bottom: .8mm; }
.explanation h3 { font-size: 10.8pt; margin: 3mm 0 1mm; }
.explanation h4 { color: #365d82; font-size: 9.8pt; margin: 2.5mm 0 .8mm; }
.explanation h1, .explanation h2, .explanation h3, .explanation h4 {
  break-after: avoid;
}
.math-display { display: block; margin: 2mm 0; overflow-wrap: anywhere; text-align: center; }
img { display: block; margin: 3mm auto; max-height: 115mm; max-width: 100%; }
table { border-collapse: collapse; width: 100%; }
td, th { border: .4pt solid #9aa8b8; padding: 1.5mm; }
@media print { a { color: inherit; } }
"""


CURATED_GROUPS = (
    ("Data Structures", (3314, 3304, 2184, 1077)),
    ("String", (3359, 2186, 1743, 1112, 1087)),
    ("Graph", (2177, 2143, 2138, 2080, 1686, 1195, 1136)),
    (
        "Math",
        (3397, 3355, 2214, 2210, 2209, 2182, 2164, 2137, 1728, 1726, 1725, 1082),
    ),
    ("Dynamic Programming", (2229, 2181, 1653)),
)


def arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser()
    parser.add_argument(
        "--source",
        type=Path,
        default=Path("~/projects/p1/cses/analyses_final").expanduser(),
    )
    parser.add_argument("--output", type=Path, default=Path("cses_notebook.html"))
    parser.add_argument("--count", type=int, default=100)
    parser.add_argument("--min-chars", type=int, default=900)
    parser.add_argument(
        "--tasks",
        help="comma-separated task ids to include, in the given order; overrides count/filter",
    )
    parser.add_argument("--label", default="", help="cover-page selection description")
    parser.add_argument(
        "--grouped",
        action="store_true",
        help="split known curated tasks into notebook-style sections",
    )
    parser.add_argument("--statement-cache", type=Path, default=Path("cses_statements.json"))
    parser.add_argument("--refresh-statements", action="store_true")
    return parser.parse_args()


def load_manifest(path: Path) -> list[tuple[int, str, int]]:
    rows = []
    for line in path.read_text().splitlines():
        task, name, chars = line.split("\t")
        rows.append((int(task), name, int(chars)))
    return rows


def analysis_body(path: Path) -> str:
    soup = BeautifulSoup(path.read_text(), "html.parser")
    body = soup.select_one("div.md")
    if body is None:
        raise ValueError(f"missing div.md in {path}")
    for tag in body.select("script, style"):
        tag.decompose()
    return body.decode_contents()


def statement_body(source: str) -> str:
    """Return the task statement through Constraints, omitting Example onward."""
    soup = BeautifulSoup(source, "html.parser")
    body = soup.select_one("div.md")
    if body is None:
        raise ValueError("missing div.md in task page")
    example = body.select_one("#example")
    if example is not None:
        for node in [example, *list(example.find_next_siblings())]:
            node.decompose()
    for tag in body.select("script, style"):
        tag.decompose()
    return body.decode_contents()


def harvest_statements(
    chosen: list[tuple[int, str, int]], cache_path: Path, refresh: bool
) -> dict[str, str]:
    cached: dict[str, str] = {}
    if cache_path.is_file() and not refresh:
        cached = json.loads(cache_path.read_text())
    pending = [row for row in chosen if refresh or str(row[0]) not in cached]

    def fetch(row: tuple[int, str, int]) -> tuple[str, str]:
        task = row[0]
        request = Request(
            f"https://cses.fi/problemset/task/{task}/",
            headers={"User-Agent": "icpc-notebook-cses-harvester/1.0"},
        )
        with urlopen(request, timeout=30) as response:
            page = response.read().decode("utf-8")
        return str(task), statement_body(page)

    if pending:
        print(f"harvesting {len(pending)} statements with 16 workers")
        with ThreadPoolExecutor(max_workers=16) as pool:
            jobs = [pool.submit(fetch, row) for row in pending]
            for job in as_completed(jobs):
                task, body = job.result()
                cached[task] = body
        cache_path.write_text(json.dumps(cached, ensure_ascii=False, indent=2) + "\n")
    missing = [str(row[0]) for row in chosen if str(row[0]) not in cached]
    if missing:
        raise SystemExit(f"missing harvested statements: {missing}")
    return cached


def choose_rows(args: argparse.Namespace) -> list[tuple[int, str, int]]:
    rows = load_manifest(args.source / "manifest.tsv")
    by_id = {task: (task, name, chars) for task, name, chars in rows}
    if args.tasks:
        ids = [int(token) for token in args.tasks.split(",") if token.strip()]
        if not ids or len(ids) != len(set(ids)):
            raise SystemExit("--tasks must contain unique comma-separated ids")
        missing = [task for task in ids if task not in by_id]
        if missing:
            raise SystemExit(f"unknown task ids: {missing}")
        return [by_id[task] for task in ids]
    return [row for row in sorted(rows, reverse=True) if row[2] >= args.min_chars][: args.count]


def arrange_sections(
    chosen: list[tuple[int, str, int]], grouped: bool
) -> list[tuple[str, list[tuple[int, str, int]]]]:
    if not grouped:
        return [("", chosen)]
    by_id = {row[0]: row for row in chosen}
    known = {task for _, tasks in CURATED_GROUPS for task in tasks}
    missing = sorted(set(by_id) - known)
    if missing:
        raise SystemExit(f"no curated section assigned for task ids: {missing}")
    return [
        (name, [by_id[task] for task in tasks if task in by_id])
        for name, tasks in CURATED_GROUPS
        if any(task in by_id for task in tasks)
    ]


def main() -> None:
    args = arguments()
    if args.count <= 0 or args.min_chars < 0:
        raise SystemExit("--count must be positive and --min-chars nonnegative")

    chosen = choose_rows(args)
    if not args.tasks and len(chosen) != args.count:
        raise SystemExit(f"only found {len(chosen)} qualifying analyses")
    grouped_rows = arrange_sections(chosen, args.grouped)
    chosen = [row for _, rows in grouped_rows for row in rows]
    statements = harvest_statements(chosen, args.statement_cache, args.refresh_statements)

    toc_groups = []
    sections = []
    for group_name, rows in grouped_rows:
        toc = []
        for index, (task, name, chars) in enumerate(rows):
            source = args.source / f"{task}.html"
            if not source.is_file():
                raise SystemExit(f"missing analysis: {source}")
            safe_name = html.escape(name)
            toc.append(f'<li><a href="#task-{task}">{task} · {safe_name}</a></li>')
            chapter = (
                f'<p class="chapter-title">{html.escape(group_name)}</p>'
                if group_name and index == 0
                else ""
            )
            sections.append(
                f'<article class="analysis" id="task-{task}">{chapter}'
                f'<h2 class="task-title">{task} · {safe_name}</h2>'
                f'<p class="meta"><a href="https://cses.fi/problemset/task/{task}/">Task</a>'
                f' · source analysis length {chars:,} characters</p>'
                f'<section class="statement"><h3 class="statement-title">Problem statement</h3>'
                f'{statements[str(task)]}</section>'
                f'<section class="explanation">{analysis_body(source)}</section></article>'
            )
        heading = f"<h2>{html.escape(group_name)}</h2>" if group_name else ""
        toc_groups.append(
            f'<section class="toc-group">{heading}<ol>{"".join(toc)}</ol></section>'
        )

    first, last = chosen[0][0], chosen[-1][0]
    selection_label = args.label or f"{len(chosen)} selected analyses"
    if args.tasks:
        selection_note = "Curated selection; short introductory analyses are omitted."
    else:
        selection_note = (
            f"Mechanical filter: at least {args.min_chars:,} source characters.<br>"
            "Short introductory analyses are omitted."
        )
    selection_scope = (
        f"{len(chosen)} tasks in {len(grouped_rows)} sections"
        if args.grouped
        else f"tasks {first} through {last}"
    )
    document = f"""<!doctype html>
<html lang="en"><head><meta charset="utf-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<base href="https://cses.fi/">
<title>CSES Analysis Notebook</title><style>{STYLE}</style>
<script>window.MathJax={{tex:{{inlineMath:[["\\\\(","\\\\)"]],displayMath:[["\\\\[","\\\\]"]]}},svg:{{fontCache:"global"}}}};</script>
<script defer src="https://cdn.jsdelivr.net/npm/mathjax@3/es5/tex-svg.js"></script>
</head><body>
<section class="cover"><div><h1>CSES Analysis Notebook</h1>
<p>{html.escape(selection_label)} · {selection_scope}</p>
<p>{selection_note}</p></div></section>
<section class="contents"><h1>Contents</h1><div class="toc">{''.join(toc_groups)}</div></section>
{''.join(sections)}
<script>
document.querySelectorAll('.math').forEach((node) => {{
  const display = node.classList.contains('math-display');
  node.textContent = (display ? '\\\\[' : '\\\\(') + node.textContent + (display ? '\\\\]' : '\\\\)');
}});
</script></body></html>"""
    args.output.write_text(document)
    print(f"wrote {args.output}: {len(chosen)} analyses in {len(grouped_rows)} sections")


if __name__ == "__main__":
    main()
