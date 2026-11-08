# Bulk CSES statement reader

Install dependencies: `python3 -m pip install requests beautifulsoup4`.

```sh
# Read several complete statements in one call (Markdown on stdout).
python3 tools/read_cses.py 1068 1083 1069

# Download the current full problem set, with four concurrent readers.
python3 tools/read_cses.py --all --format json --output tmp/cses-all.json

# Read cached statements without network requests.
python3 tools/read_cses.py 1068,1083 --offline
python3 tools/read_cses.py --all --offline --output tmp/cses-all.md

# Refresh selected statements.
python3 tools/read_cses.py 1068 1083 --refresh

# Run offline regression tests.
python3 -m unittest discover -s tests -p test_cses_reader.py
```

Includes the title, source URL, limits, full statement, constraints, and examples.
Math remains in its original TeX notation; sample indentation is preserved.
The default cache is `tmp/cses-statements/` (already ignored by Git).
No CSES login or cookie is needed. TLS certificates are verified.

IDs keep their requested order and duplicates are removed. Progress and errors go
to stderr, leaving stdout suitable for piping. Failed tasks produce a nonzero
exit status; successful tasks are still cached and included in the output.
Rerunning retries only missing tasks unless `--refresh` is supplied. A failed
refresh preserves the old cache. `--all --offline` reads all cached tasks only;
it does not claim the cache covers the current problem set.

Use `--workers 1` for sequential downloads (maximum 8). Transient failures are
retried up to three times with backoff; permanent HTTP errors are not retried.
Cache entries are standalone JSON files, separate from the abbreviated HTML
cache used by `build_cses_notebook.py`. Text output preserves content rather than
reproducing the site's visual layout; figures are preserved as Markdown image links. Public statement access is read-only and submits no solutions.

# CSES submission runner

`cses.py` adapts the useful parts of `p1/cses/fire_ac2.py` and `verify_ac.py`
without their hardcoded credentials, temporary paths, or disabled TLS checks.
It indexes C++ files by task ID or normalized title, deduplicates their contents,
optionally compiles with C++17, submits sequentially, records submission IDs immediately,
and checks final verdicts. Alternate sources are tried in later rounds.

```sh
# Prepare the current task list with titles.
python3 tools/read_cses.py --all --format json --output tmp/cses-all.json

# cookie-file contains only PHPSESSID. Keep it private and outside Git.
# State is tied to the expected numeric CSES account ID.
python3 tools/cses.py --cookie-file /private/path/cses-session.txt \
  --account 503778 --sources /path/to/solutions /path/to/alternate/solutions

# Fast mode: let CSES compile, shorten the pause, retain verdict verification.
python3 tools/cses.py --cookie-file /private/path/cses-session.txt \
  --account 503778 --sources /path/to/solutions --skip-compile --delay 1.5

python3 -B -m unittest discover -s tests -p test_cses_runner.py
```

Defaults: three rounds, four-second pauses after confirmed submissions, four
concurrent read-only requests for the initial acceptance scan. HTTP 429 responses
use Retry-After when supplied, otherwise exponential backoff (10 to 60 seconds),
with at most five retries. Use --delay 5 to avoid bursts on stricter accounts. Other unconfirmed POSTs stop
the run for inspection: inspect account submissions before restarting, since a
network failure may leave the outcome uncertain. Resume with the same arguments
and state directory; do not run two writers against the same state or account.

Artifacts in `tmp/cses-run/`:

- `account.txt`: account ID guard.
- `baseline.json`: initial account acceptance scan (model-page access).
- `sources.json`: candidate file paths and SHA-256 hashes.
- `events.jsonl`: append-only compilation, submission, and verdict records.
- `remaining.json`: tasks still unaccepted after the run finishes.

Never infer acceptance from compilation, sample output, or submission redirects.
The initial scan follows the current CSES model-page access behavior; submitted
solutions require an explicit final `ACCEPTED` result. Cache/state files are
local working artifacts, not additions to the printed notebook. Source paths
must stay available for subsequent runs. Imported sources retain their authors'
licenses; this tool does not redistribute them or make correctness claims.

## Finding missing sources

Use authenticated GitHub **code** search rather than README keyword matches:
many repositories list all problems while only implementing some.

```sh
gh search code '"Sliding Window Advertisement" language:C++' \
  --limit 30 --json repository,path
gh search code '"cses.fi/problemset/task/3227"' \
  --limit 30 --json repository,path
```

Search titles, IDs, and filename variants (spaces, hyphens, underscores). Inspect
actual implementation files, pin repository revisions, and verify with the judge.
Useful discovered collections:

- <https://github.com/thehouseisonfire/material-maratona> (`cses/code/`)
- <https://github.com/khalwsh/Competitive-Programming> (`CSES-solutions/`)
- <https://github.com/Jonathan-Uy/CSES-Solutions>
- <https://github.com/TamimEhsan/CSES-Solutions>
