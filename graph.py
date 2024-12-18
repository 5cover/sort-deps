import json
import re
from collections import defaultdict

Graph = dict[str, set[str]]

SEP = '-->'

def empty() -> Graph: return defaultdict(set)

def from_json(fp) -> Graph:
    return {name: {*deps} for name, deps in json.load(fp).items()}


def parse(input: str) -> Graph:
    graph: Graph = empty()
    for nodes in (line.split(SEP) for line in re.findall(rf'^(?:[\w-]+)(?:{SEP}[\w-]+)+$', input, re.M)):
        for i in range(1, len(nodes)):
            dependent = nodes[i - 1]
            dependency = nodes[i]
            graph[dependent].add(dependency)
            graph[dependency]  # Make sure we get empty arrays for leafs

    return graph

def dependent_count(graph: Graph, item: str):
    """The number of items that depend on the item of this name"""
    return sum(item in dependencies for dependencies in graph.values())