#!/usr/bin/env python3

"""
Reads a graph JSON from standard input (an object, keys are are item names, values are arrays of dependencies)

Outputs the canically ordered symbols.
"""

import sys
from collections import deque
from typing import Any
from collections.abc import Callable
import graph as g

graph = g.from_json(sys.stdin)

def define_before_use(item: str):
    """If an item should come before its dependents"""
    return item.startswith('macro') or item.startswith('fdecl') or item.startswith('typedef')


def c_sort_key(item: str):
    kind, name = item.split('-', 2)
    return (('macro', 'typedef', 'fdecl', 'fdef').index(kind), name)


def bfs_deps(root: str, sort_key: Callable[[str], Any] | None = None):
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


root = min(graph, key=lambda item: g.dependent_count(graph, item))

for item in bfs_deps(root):
    print(item)
