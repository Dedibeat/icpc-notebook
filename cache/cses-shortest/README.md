# CSES shortest accepted C++ snapshot

400 first-ranked accepted C++ sources, downloaded from CSES on 2026-11-08.
Each queue was filtered to C++ and ACCEPTED, then sorted by increasing reported
code size (`lang=3&status=2&by=2&order=0`). Ties retain CSES ordering.

- `<taskid>.cpp`: unchanged extracted source.
- `<taskid>.json`: author, source URL, queue URL, compiler, reported size, download
  timestamp and source SHA-256.
- `<taskid>.evidence.json`: first-page ranking metadata and compiler version.
- `manifest.json`: complete index with repository-relative source paths.

These are raw reference sources, separate from the printable notebook. The queue
combines C++ versions: 192 C++20, 139 C++17, 48 C++11, 15 C++23, and 6 labeled
C++. Preserve the recorded version; C++17 compatibility is not implied. Source
code may use code-golf tricks or depend on historical judge behavior. ACCEPTED
is the status shown by CSES when downloaded; no new submissions were made to
validate this snapshot. Rankings may change after the recorded timestamps.

Sources retain their authorship and applicable rights. Public visibility is not
a blanket license; this snapshot does not relicense third-party code. Attribution
and original source links are preserved in each task's metadata.

To refresh explicitly (requires a private CSES PHPSESSID file):

```sh
python3 tools/cses_shortest.py --all --cookie-file /private/session \
  --output cache/cses-shortest --refresh
```

The downloader's task index defaults to `tmp/cses-all.json`; prepare it with
`python3 tools/read_cses.py --all --format json --output tmp/cses-all.json`.
No cookies, account credentials or authentication forms are included here.
