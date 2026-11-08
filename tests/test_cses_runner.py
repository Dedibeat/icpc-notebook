import importlib.util
from pathlib import Path
import tempfile
import json
import io
from types import SimpleNamespace
from unittest.mock import patch, MagicMock
import unittest
spec=importlib.util.spec_from_file_location('cses',Path(__file__).resolve().parents[1]/'tools/cses.py')
cses=importlib.util.module_from_spec(spec);spec.loader.exec_module(cses)
class RunnerTests(unittest.TestCase):
    def test_normalize(self):
        self.assertEqual(cses.normalize('Fixed-Length Paths II'),cses.normalize('Fixed Length Paths II'))
        self.assertEqual(cses.normalize('Prüfer Code'),'prufercode')
    def test_verdict(self):
        for verdict in cses.VERDICTS:
            self.assertEqual(cses.verdict(f'<table><tr><td>Result:</td><td><span>{verdict}</span></td></tr></table>'),verdict)
        self.assertIsNone(cses.verdict('<td>ACCEPTED</td>'))
        self.assertIsNone(cses.verdict('<table><tr><td>Result:</td><td>TESTING</td></tr></table>'))
    def test_compile_error_status(self):
        self.assertEqual(cses.verdict('<span id="status">COMPILE ERROR</span>'),'COMPILATION ERROR')
    def test_matching_and_deduplication(self):
        with tempfile.TemporaryDirectory() as directory:
            p=Path(directory)
            (p/'1068 - Old Name.cpp').write_text('first')
            (p/'Weird Algorithm.cpp').write_text('first')
            (p/'Missing Number.cpp').write_text('second')
            (p/'Unknown.cpp').write_text('third')
            tasks=[{'id':'1068','title':'Weird Algorithm'},{'id':'1083','title':'Missing Number'}]
            result=cses.index_sources(tasks,[p])
            self.assertEqual([len(result[t]) for t in ['1068','1083']],[1,1])
    def test_resume_skips_accepted_submission(self):
        with tempfile.TemporaryDirectory() as directory:
            root=Path(directory); state=root/'state'; state.mkdir()
            (state/'baseline.json').write_text('{"1068": false}')
            (root/'cookie').write_text('fake-session')
            (root/'tasks.json').write_text(json.dumps([{'id':'1068','title':'Weird Algorithm'}]))
            sources=root/'sources'; sources.mkdir(); (sources/'1068.cpp').write_text('int main(){}')
            page=MagicMock();page.text='<a href="/user/503778">account</a><input name="csrf_token" value="test">'
            result=MagicMock();result.text='<table><tr><td>Result:</td><td>ACCEPTED</td></tr></table>'
            response=MagicMock();response.status_code=302;response.headers={'Location':'/problemset/result/123/'}
            client=MagicMock();client.get.side_effect=lambda url,**kw: result if '/result/' in url else page
            client.post.return_value=response
            argv=['cses.py','--cookie-file',str(root/'cookie'),'--account','503778','--tasks',str(root/'tasks.json'),'--sources',str(sources),'--state',str(state)]
            with patch.object(cses,'session',return_value=client),patch('sys.argv',argv),patch.object(cses.subprocess,'run',return_value=SimpleNamespace(returncode=0)),patch.object(cses.time,'sleep'),patch('sys.stdout',new_callable=io.StringIO):
                cses.main()
                self.assertEqual(client.post.call_count,1)
                cses.main()
                self.assertEqual(client.post.call_count,1)
            events=[json.loads(line) for line in (state/'events.jsonl').read_text().splitlines()]
            self.assertEqual([e['kind'] for e in events],['submitted','verdict'])
            self.assertEqual(events[1]['verdict'],'ACCEPTED')
            self.assertEqual(json.loads((state/'remaining.json').read_text()),[])

if __name__=='__main__':unittest.main()
