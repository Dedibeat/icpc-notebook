#!/usr/bin/env python3
"""Build the focused PDF from hack_notebook.md and its actual tested snippets.

Requires reportlab. Run from any directory; no generated code is duplicated.
Each entry must fit one A4 page or the build fails instead of clipping content.
"""
import argparse
import html
import re
from pathlib import Path

from reportlab.lib import colors
from reportlab.lib.enums import TA_LEFT
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import ParagraphStyle
from reportlab.pdfbase.pdfmetrics import stringWidth
from reportlab.pdfgen import canvas
from reportlab.platypus import Flowable, Frame, Paragraph, Spacer, Table, TableStyle

ROOT = Path(__file__).resolve().parents[1]
WIDTH, HEIGHT = A4
MARGIN = 36
BODY_WIDTH = WIDTH - 2*MARGIN
INK = colors.HexColor("#172B38")
MUTED = colors.HexColor("#475569")
ACCENT = colors.HexColor("#245B63")


def inline(text):
    """Small, intentionally restricted inline Markdown subset for this source."""
    text = html.escape(text)
    text = re.sub(r"\[([^\]]+)\]\(([^)]+)\)",
                  lambda m: ('<a href="' + m[2] + '" color="#245B63">' + m[1] + '</a>')
                  if m[2].startswith("https://") else m[1], text)
    text = re.sub(r"`([^`]+)`", r'<font name="Courier" size="8">\1</font>', text)
    return text


def para(text, size=9.5, leading=12):
    style = ParagraphStyle("body", fontName="Helvetica", fontSize=size,
                           leading=leading, textColor=INK, alignment=TA_LEFT,
                           spaceAfter=5)
    return Paragraph(text, style)


def field(label, text, small=False):
    return para(f"<b>{label}</b> {inline(text)}",
                8.5 if small else 9.5, 10.5 if small else 12)


class Code(Flowable):
    def __init__(self, source, size=9.5):
        super().__init__()
        self.lines = source.rstrip().splitlines()
        longest = max((stringWidth(s, "Courier", size) for s in self.lines), default=0)
        self.size = min(size, size*(BODY_WIDTH-18)/max(longest, 1))
        if self.size < 7.8:
            raise ValueError("Code line too long; shorten the source instead of shrinking it")
        self.leading = self.size + 1.2
        self.width = BODY_WIDTH
        self.height = len(self.lines)*self.leading+16

    def draw(self):
        c = self.canv
        c.setFillColor(colors.HexColor("#F3F5F6"))
        c.rect(0, 0, self.width, self.height, fill=1, stroke=0)
        c.setFont("Courier", self.size)
        y = self.height-8-self.size
        for line in self.lines:
            c.setFillColor(MUTED if line.lstrip().startswith("//") else colors.black)
            c.drawString(9, y, line)
            y -= self.leading


def snippet(path):
    lines = (ROOT/path).read_text().splitlines()
    while lines and (not lines[0].strip() or lines[0].startswith("//")):
        lines.pop(0)
    lines = [s for s in lines if s not in ('#include "common.hpp"', '#pragma once')]
    return "\n".join(lines).strip()


def load_entries():
    text = (ROOT/"hack_notebook.md").read_text()
    sections = re.split(r"^## (\d+\. .+)$", text, flags=re.M)
    entries = []
    for i in range(1, len(sections), 2):
        entry = {"Title": sections[i]}
        for match in re.finditer(r"^\*\*(\w+):\*\* (.+)$", sections[i+1], re.M):
            entry[match[1]] = match[2]
        required = {"Status", "Purpose", "Idea", "Code", "Complexity", "Pitfalls",
                    "Example", "Tests", "Sources"}
        if not required <= entry.keys():
            raise ValueError(f"Missing fields in {entry['Title']}: {required-entry.keys()}")
        entries.append(entry)
    if len(entries) != 12:
        raise ValueError("Expected exactly twelve algorithm entries")
    return entries


def page_header(c, title, status, page, total):
    c.setFillColor(ACCENT)
    c.setFont("Helvetica-Bold", 8)
    c.drawString(MARGIN, HEIGHT-32, "ICPC  /  PRACTICAL TRICKS  /  C++17")
    c.setFillColor(INK)
    c.setFont("Helvetica-Bold", 18)
    c.drawString(MARGIN, HEIGHT-58, title)
    c.setFont("Helvetica-Bold", 8)
    c.setFillColor(MUTED)
    c.drawString(MARGIN, HEIGHT-74, status)
    c.setStrokeColor(colors.HexColor("#CAD3D8"))
    c.line(MARGIN, 30, WIDTH-MARGIN, 30)
    c.setFont("Helvetica", 8)
    c.drawString(MARGIN, 18, "Check each entry's indexing, modulus, and output contract")
    c.drawRightString(WIDTH-MARGIN, 18, f"{page} / {total}")


def place(c, story, title):
    frame = Frame(MARGIN, 40, BODY_WIDTH, HEIGHT-130,
                  leftPadding=0, rightPadding=0, topPadding=0, bottomPadding=0)
    frame.addFromList(story, c)
    if story:
        raise ValueError(f"Content exceeds one page: {title}; {len(story)} blocks remain")


def build(destination):
    entries = load_entries()
    destination.parent.mkdir(parents=True, exist_ok=True)
    c = canvas.Canvas(str(destination), pagesize=A4, pageCompression=1)
    c.setTitle("ICPC Practical Tricks Notebook")
    c.setAuthor("ICPC team notebook")
    c.setSubject("Practical C++17 techniques, interpolation, and unique-centroid subtree counting")
    total = len(entries)+1
    page_header(c, "Practical tricks notebook", "QUICK INDEX + SHARED SETUP", 1, total)
    rows = [[para("<b>Technique</b>", 8, 10), para("<b>Contract</b>", 8, 10),
             para("<b>Page</b>", 8, 10)]]
    for page, entry in enumerate(entries, 2):
        status = entry["Status"].split(" / ")[0].title()
        status = status.replace(" Under Recurrence Contract", " (recurrence)")
        status = status.replace(" Under Polynomial Contract", " (polynomial)")
        rows.append([para(inline(entry["Title"]), 8.5, 10.5),
                     para(status, 8.5, 10.5), para(str(page), 8.5, 10.5)])
    table = Table(rows, colWidths=[BODY_WIDTH-177, 145, 32], hAlign="LEFT")
    table.setStyle(TableStyle([
        ("VALIGN", (0,0), (-1,-1), "TOP"),
        ("BACKGROUND", (0,0), (-1,0), colors.HexColor("#E8EEF0")),
        ("LINEBELOW", (0,0), (-1,0), .5, colors.HexColor("#CAD3D8")),
        ("ROWBACKGROUNDS", (0,1), (-1,-1), [colors.white, colors.HexColor("#F6F7F8")]),
        ("LEFTPADDING", (0,0), (-1,-1), 6),
        ("RIGHTPADDING", (0,0), (-1,-1), 6),
        ("TOPPADDING", (0,0), (-1,-1), 3),
        ("BOTTOMPADDING", (0,0), (-1,-1), 2),
    ]))
    story = [table, Spacer(1, 9),
             field("Copy once.", "Use this setup before the selected snippets. Local includes "
                   "are omitted in print. Do not use `#define int long long`. Arithmetic uses "
                   "long long; indices use int; bit operations use unsigned 64-bit words."),
             Code(snippet("sections/hacks/common.hpp")), Spacer(1, 7),
             field("RNG.", "Seed once in main, then pass rng by reference. Keep a fixed seed "
                   "for debugging; use the printed runtime seed for submission. Modular "
                   "power costs O(log e); normalization and random sampling cost O(1)."),
             field("Read the contract.", "Exact searches may take exponential time. A heuristic's "
                   "nullopt/false means NOT FOUND, not impossible. Probabilistic bounds assume "
                   "independent uniform samples on a fixed input; sum failure bounds across calls."),
             field("Validate.", "Run `bash tools/test_hack_notebook.sh`; add `SANITIZE=1` for "
                   "address/undefined-behavior checks. Fixed-seed tests do not prove reliability "
                   "on every input. Check witnesses and benchmark your problem's constraints."),
             field("Rebuild.", "`python3 tools/build_hack_notebook.py` requires reportlab. "
                   "The PDF reads actual tested snippets and the notes in hack_notebook.md.")]
    place(c, story, "setup")
    c.showPage()
    for page, entry in enumerate(entries, 2):
        page_header(c, entry["Title"], entry["Status"], page, total)
        story = [field("Purpose.", entry["Purpose"]),
                 field("Idea.", entry["Idea"]), Spacer(1, 2),
                 Code(snippet(entry["Code"])), Spacer(1, 7),
                 field("Complexity.", entry["Complexity"]),
                 field("Pitfalls.", entry["Pitfalls"]),
                 field("Example.", entry["Example"]),
                 field("Tests.", entry["Tests"], small=True),
                 field("Sources.", entry["Sources"], small=True)]
        place(c, story, entry["Title"])
        c.showPage()
    c.save()
    print(f"Built {destination} ({total} pages)")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--output", type=Path,
                        default=ROOT/"output/pdf/icpc_hack_notebook.pdf")
    build(parser.parse_args().output)
