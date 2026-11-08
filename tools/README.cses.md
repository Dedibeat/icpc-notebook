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
