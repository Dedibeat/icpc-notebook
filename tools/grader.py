#!/usr/bin/env python3
"""grader.py [-v] SOL [JUDGE] — compile both and pipe SOL<->JUDGE; -v echoes the talk."""
# Input: SOL.cpp and JUDGE.cpp (default judge.cpp), using line-flushed protocols.
# Effect: compiles both, then pipes each program's stdout to the other's stdin.
# Output: judge exit status; -v copies the conversation to stderr.
# Pitfalls: no timeout while the judge runs; a program that does not flush may deadlock.
import sys, subprocess, threading

def g(s): return subprocess.run(["g++", "-std=c++17", "-O2", s + ".cpp", "-o", s]).returncode

def pump(a, b, tag):
    for line in a:
        if tag: sys.stderr.write(tag + line)
        b.write(line); b.flush()
    b.close()

a = sys.argv[1:]
v = "-v" in a
a = [x for x in a if x != "-v"]
if not a: print(__doc__); sys.exit()

sol = a[0].removesuffix(".cpp")
judge = (a[1] if len(a) > 1 else "judge").removesuffix(".cpp")
if g(sol) or g(judge): sys.exit(1)

s = subprocess.Popen(["./" + sol], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
j = subprocess.Popen(["./" + judge], stdin=subprocess.PIPE, stdout=subprocess.PIPE, text=True)
threading.Thread(target=pump, args=(j.stdout, s.stdin, "JUDGE> " if v else 0), daemon=True).start()
threading.Thread(target=pump, args=(s.stdout, j.stdin, "SOL>  " if v else 0), daemon=True).start()
j.wait()
try: s.wait(.5)
except subprocess.TimeoutExpired: s.kill()
sys.exit(j.returncode)
