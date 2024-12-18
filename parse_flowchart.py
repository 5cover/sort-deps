#!/usr/bin/env python3

"""
Reads a Mermaid flowchart from standard input and turns it into a graph JSON.

Only a subset of the syntax is implemented: this program work by searching standard input for XX-->YY-->ZZ... lines
"""

import json
import sys
import graph as g

graph = g.parse(sys.stdin.read())

json.dump(graph, sys.stdout, separators=(',', ':'), default=list)
