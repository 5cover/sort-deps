#!/usr/bin/env python3

"""
Reads a graph JSON and produces a Mermaid flowchart for it.
"""

import sys
import graph as g

# todo: improve canonicalization

graph = g.from_json(sys.stdin)

print('flowchart')

visited: set[str] = set()


def print_deps(node: str):
    for dep in sorted(graph[node]):
        if dep not in graph[node]:
            continue

        print(node, end='-->')
        graph[node].discard(dep)
        if len(graph[dep] - {dep}) == 1:
            print_deps(dep)
        else:
            print(dep)


for node in sorted(graph):
    print_deps(node)
