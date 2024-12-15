#!/usr/bin/env python3

"""
Reads a Mermaid flowchart from standard input and turns it into a graph JSON.

Only a subset of the syntax is implemented: this program work by searching standard input for XX-->YY lines (where XX and YY are node names)
"""

import sys
import re
import json
from collections import defaultdict

graph: defaultdict[str, list[str]] = defaultdict(list)
'item -> dependencies'

dependent_prefix=''
dependency_prefix=''

for dependent, dependency in re.findall(rf'^({dependent_prefix}[\w-]+)-->({dependency_prefix}[\w-]+)$', sys.stdin.read(), re.M):
    #print(f'{dependent}-->{dependency}', file=sys.stderr)
    graph[dependent].append(dependency)
    graph[dependency]  # Make sure we get empty arrays for leafs

json.dump(graph, sys.stdout, separators=(',', ':'))
