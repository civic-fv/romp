#!/usr/bin/env python3

import json
import sys
from collections import defaultdict, deque
import glob
import plotly.graph_objects as go
import plotly.express as px
from math import factorial as fact


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

def create_rule_name(rule) -> str:
    res = f"{rule.get('label','<UNKNOWN>')}("
    sep = ""

    for q in rule.get('quantifiers',[]):
        if "scalarset" in q['type']:
            res += sep + q['value']['value'][6:]
        elif "range" in q['type']:
            res += sep + q['value']['value'] #TODO check how ranges are output as quantifiers
        sep = ','
    return res + ')'

def _do_process(path: str) -> set:
    with open(path,'r') as file:
        
        pass


def main(n):
    json_files = glob.glob('*.json')

    if not json_files:
        print("No JSON files found in the current directory.")
        sys.exit(1)
    
    all_rule_sequences = [] 
    all_filtered_ngrams = defaultdict(int)
    total_count = 0
    walk_count = 0

    for json_file in json_files:
        walk_Count += 1
        states |= _do_process(json_file)

    print(f"Total States: {}")


    # plot_histogram(all_filtered_ngrams, 'N-gram Frequencies', 'Frequency', 'N-grams', 'ngram_frequencies.png', top_n=20, min_freq=5)
    # plot_histogram(avg_ngram_freqs, 'Average N-gram Frequencies Across All Walks', 'Average Frequency', 'N-grams', 'avg_ngram_frequencies.png', top_n=20, min_freq=0.1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: ./trace_statistics.py <n>")
        sys.exit(1)

    n = int(sys.argv[1])
    main(n)
