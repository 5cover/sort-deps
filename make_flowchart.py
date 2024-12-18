#!/usr/bin/env python3

"""
Reads a graph JSON and produces a Mermaid flowchart for it.
"""

import sys
import graph as g

# todo: improve canonicalization more

graph = g.from_json(sys.stdin)

print('flowchart')

done: g.Graph = g.empty()


def print_deps(node: str):
    print(node, end='')

    deps = sorted(graph[node] - done[node])
    done[node].update(deps)

    first = True
    for dep in deps:
        if first:
            first = False
            print(end='-->')
            print_deps(dep)
        else:
            print()
            print(node, end='-->')
            print_deps(dep)


root = min(graph, key=lambda item: g.dependent_count(graph, item))

print_deps(root)
