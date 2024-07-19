#!/usr/bin/env python3

import json
import sys
from collections import defaultdict, deque
import glob
from multiset import FrozenMultiset


DEBUG: bool = False

def get_state_simple(json):
    """handler for producing a hashable state object to work with, 
    when trace is set to simple.
    i.e. turns the flat list into a immutable tuple.
    NOTE: if DEBUG is true it will also raise error is `json`/the-state is not
    a flat list in the json."""
    if DEBUG:
        if not isinstance(json,list):
            raise Exception("state was not a simple state ``list'' !!")
    return tuple([(FrozenMultiset([get_state_simple(j) for j in i["multiset"]]) 
                    if isinstance(i,dict)
                    else i)
                        for i in json])
#? END def get_state_simple: NormState


def _do_process(path: str) -> set:
    with open(path,'r') as file:
        trace_file = json.load(file)
        states: set = set()
        
        for trace_item in trace_file['trace']:
            trace_item_type = trace_item['$type']
            
            if trace_item_type in {'rule-hit','init'}:
                 state = get_state_simple(trace_item['state'])
                 states.add(state)
    
    return states


def main(path):
    json_files = glob.glob(f'{path}/*.json')

    if not json_files:
        print("No JSON files found in the current directory.")
        sys.exit(1)
    
    states: set = set()
    walk_Count: int = 0

    for json_file in json_files:
        walk_Count += 1
        states |= _do_process(json_file)

    print(f"Total States:  {len(states)}\n"
          f"Total Walkers: {walk_Count}\n")

    
if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: ./simple_state_count.py <path>")
        sys.exit(1)
    main(sys.argv[1])
    
    
"""

| model name   | depth | bfs states | rw states | # of rw's | rw's coverage |
| n_pete_bug1  |     8 |      316   |      192  |      32   | =(rs states)/(bfs states) |

"""