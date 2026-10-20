#!/usr/bin/env python3
"""Turn a build's report.json into shields.io endpoint badge files.

Usage:  python3 tools/progress_badges.py REPORT_JSON VERSION OUT_DIR

Writes OUT_DIR/VERSION_{code,functions,data}.json (see docs/github_actions.md).
"""
import json
import os
import sys

# (file suffix, label, report.json measure)
BADGES = [
    ("code", "code", "matched_code_percent"),
    ("functions", "functions", "matched_functions_percent"),
    ("data", "data", "matched_data_percent"),
]


def color(percent):
    """Red through green as the percentage climbs."""
    for limit, name in ((10, "red"), (25, "orange"), (50, "yellow"), (75, "yellowgreen"), (100, "green")):
        if percent <= limit:
            return name
    return "brightgreen"


def main():
    report, version, out = sys.argv[1:4]
    with open(report) as f:
        measures = json.load(f)["measures"]
    os.makedirs(out, exist_ok=True)
    for suffix, label, key in BADGES:
        percent = measures.get(key, 0.0)
        badge = {
            "schemaVersion": 1,
            "label": label,
            "message": "%.2f%%" % percent,
            "color": color(percent),
        }
        with open(os.path.join(out, "%s_%s.json" % (version, suffix)), "w") as f:
            json.dump(badge, f)
            f.write("\n")


if __name__ == "__main__":
    main()
