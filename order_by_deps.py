#!/usr/bin/env python3

"""
Reads a graph JSON from standard input (an object, keys are are item names, values are arrays of dependencies)

Outputs the canically ordered symbols.
"""

import sys
import json
from collections import deque

graph: dict[str, set[str]] = {name: {*deps} for name, deps in json.load(sys.stdin).items()}

kind_order = ['macro', 'typedef', 'fdecl', 'fdef']


def define_before_use(item: str):
    """If an item should come before its dependents"""
    return item.startswith('macro') or item.startswith('fdecl') or item.startswith('typedef')


def dependent_count(item: str):
    """The number of items that depend on the item of this name"""
    return sum(item in dependencies for dependencies in graph.values())


def sort_key(item: str):
    kind, name = item.split('-', 2)
    return (kind_order.index(kind), name)


def bfs_deps(root: str):
    """
    BFS with two modifications
    - Neighbors (dependencies) are sorted alphabetically
    - Items that must be defined before use come before their dependents.
    """
    f = deque()
    f.append(root)
    visited = {root}
    while f:
        s = f.popleft()
        t = graph[s] - visited
        before = sorted(filter(define_before_use, t), key=sort_key,
                        reverse=True)  # Reverse sorting counteracts extendleft appending the elements in reverse order
        if before:
            visited.update(before)
            f.appendleft(s)
            f.extendleft(before)
        else:
            yield s
        after = sorted(filter(lambda item: not define_before_use(item), t), key=sort_key)
        visited.update(after)
        f.extend(after)


root = min(graph, key=dependent_count)

for item in bfs_deps(root):
    print(item)