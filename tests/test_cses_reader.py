"""Offline regression tests for the bulk statement reader."""
import importlib.util
import json
import io
from pathlib import Path
import tempfile
import unittest
from unittest.mock import patch

spec = importlib.util.spec_from_file_location('reader', Path(__file__).resolve().parents[1] / 'tools/read_cses.py')
reader = importlib.util.module_from_spec(spec)
spec.loader.exec_module(reader)
HTML = '''<div class="title-block"><h1>Example Task</h1></div><div class="content">
<ul class="task-constraints"><li>Time limit: 1 s</li></ul><div class="md">
<p>Use <span class="math">n \\le 10</span> values.</p><h1>Input</h1><p>Read n.</p>
<h1>Constraints</h1><ul><li>n &gt; 0</li></ul><h1>Example</h1>
<p>Input:</p><pre>2\n  1 2\n</pre><p>Output:</p><pre>3\n</pre></div></div>'''


class ReaderTests(unittest.TestCase):
    def test_preserves_full_statement(self):
        entry = reader.parse_statement('1068', HTML)
        self.assertEqual(entry['title'], 'Example Task')
        for text in ['n \\le 10', '## Constraints', '## Example', '2\n  1 2', 'Output:', '```\n3\n```']:
            self.assertIn(text, entry['statement'])
        self.assertIn('Time limit', entry['limits'])
        self.assertEqual(json.loads(reader.render([entry], 'json')), [entry])

    def test_missing_statement(self):
        with self.assertRaises(ValueError):
            reader.parse_statement('1068', '<h1>Login</h1>')

    def test_task_links_deduplicate(self):
        source = '<a href="/problemset/task/1068/">Weird Algorithm</a>' * 2
        source += '<a href="/problemset/result/123/">Result</a>'
        self.assertEqual(reader.parse_tasks(source), {'1068': 'Weird Algorithm'})
        with self.assertRaises(ValueError):
            reader.parse_tasks('')

    def test_cache_offline_and_failed_refresh(self):
        with tempfile.TemporaryDirectory() as directory:
            cache = Path(directory)
            with patch.object(reader, 'fetch', return_value=HTML) as fetch:
                original = reader.read_task('1068', cache)
                self.assertEqual(reader.read_task('1068', cache, offline=True), original)
                self.assertEqual(fetch.call_count, 1)
            with patch.object(reader, 'fetch', return_value='<h1>Error</h1>'):
                with self.assertRaises(ValueError):
                    reader.read_task('1068', cache, refresh=True)
            self.assertEqual(reader.read_task('1068', cache, offline=True), original)
            with self.assertRaises(ValueError):
                reader.read_task('9999', cache, offline=True)

    def test_partial_failure_outputs_success_and_nonzero_status(self):
        with tempfile.TemporaryDirectory() as directory:
            output = Path(directory) / 'results.json'
            entry = reader.parse_statement('1068', HTML)
            argv = ['read_cses.py', '1068', '9999', '--format', 'json',
                    '--output', str(output)]
            def read(task, *args):
                if task == '9999':
                    raise ValueError('missing')
                return entry
            with patch.object(reader.sys, 'argv', argv), patch.object(reader, 'read_task', side_effect=read), patch.object(reader.sys, 'stderr', io.StringIO()):
                self.assertTrue(reader.main())
            self.assertEqual(json.loads(output.read_text()), [entry])

    def test_transient_retry_and_permanent_error(self):
        response = reader.requests.Response()
        response.status_code = 404
        with patch.object(reader.requests, 'get', return_value=response) as get:
            with self.assertRaises(reader.requests.HTTPError):
                reader.fetch('https://cses.fi/missing')
            self.assertEqual(get.call_count, 1)
        good = reader.requests.Response()
        good.status_code = 200
        good._content = b'ok'
        with patch.object(reader.requests, 'get', side_effect=[reader.requests.Timeout(), good]), patch.object(reader.time, 'sleep'):
            self.assertEqual(reader.fetch('https://cses.fi/'), 'ok')


if __name__ == '__main__':
    unittest.main()
