#!/usr/bin/env python3

import json
import sys
from collections import defaultdict, deque
import glob
import plotly.graph_objects as go
import plotly.express as px
from math import factorial as fact


def create_rule_name(rule) -> str:
    res = f"{rule.get('label','<UNKNOWN>')}("
    sep = ""

    for q in rule.get('quantifiers',[]):
        if "scalarsetunion" in q['value']['type']:
            res += sep + q['value']['value']['value'][6:]
        elif "scalarset" in q['value']['type']:
            res += sep + q['value']['value'][6:]
        elif "range" in q['value']['type']:
            res += sep + str(q['value']['value']['value'])
        elif "enum" in q['value']['type']:
            res += q['value']['value'][6:] #TODO check how enums are output as quantifiers
        sep = ','
    return res + ')'

def _do_process(path: str):
    rule_hits = defaultdict(int)
    rule_misses = defaultdict(int)
    rule_sequence = []
    hits = 0
    misses = 0
    with open(path, 'r') as file:
        trace_file = json.load(file)
        total_rule_count = trace_file['metadata']['total-rule-count']
        
        if not trace_file['metadata']['simple-trace']:
            rule_extractor = (lambda x: create_rule_name(x.get('rule', {})))
        else:
            rule_extractor = (lambda x: x.get('rule','<UNKNWON>'))
        for trace in trace_file['trace']:
            rule_type = trace['$type']
            rule_name = rule_extractor(trace) #this is designed for traces with simple trace disabled 

            if rule_type in {'rule-hit', 'rule-miss'}:
                rule_sequence.append(rule_name)
                if rule_type == 'rule-hit':
                    rule_hits[rule_name] += 1
                    hits += 1
                elif rule_type == 'rule-miss':
                    rule_misses[rule_name] += 1
                    misses += 1

    return rule_sequence, rule_hits, rule_misses, hits, misses, total_rule_count

def calculate_ngrams(sequence, n):
    ngram_seq = deque(maxlen=n)
    ngrams = defaultdict(int)

    for i in range(len(sequence) - n):
        ngram = tuple(sequence[i:i + n])
        if '<UNKNOWN>' not in ngram[0]:
            ngrams[ngram] += 1

    return ngrams

def plot_histogram(data, title, xlabel, ylabel, filename, top_n=20):
    # Limit to top_n data points for readability
    data = dict(sorted(data.items(), key=lambda item: item[1], reverse=True))

    labels = [str(k) for k in data.keys()]
    values = list(data.values())

    fig = go.Figure(data=[go.Bar(x=list(range(len(labels))), y=values, text=values, hovertext=labels, hoverinfo='text+y', textposition='auto')])
    fig.update_layout(
        title=title,
        xaxis_title=xlabel,
        yaxis_title=ylabel,
        xaxis=dict(tickvals=list(range(len(labels))), ticktext=['']*len(labels)),  # Use empty ticktext to hide x-axis labels
        yaxis=dict(range=[0, max(values) * 1.1]),  # Extend y-axis range to make differences more noticeable
        height=800,  # Fixed height for consistency
        width=1500,  # Fixed width for consistency
        margin=dict(b=50)  # Bottom margin to accommodate
    )
    fig.write_image(filename)
    fig.show()


def get_stats(n,dir):
    json_files = glob.glob(f"{dir}/*.json")

    if not json_files:
        print("No JSON files found in the current directory.")
        sys.exit(1)
    
    all_rule_sequences = [] 
    all_filtered_ngrams = defaultdict(int)
    total_count = 0
    walk_count = 0

    for json_file in json_files:
        walk_count += 1
        rule_sequence, rule_hits, rule_misses, hits, misses, n_rules = _do_process(json_file)
        all_rule_sequences.append(rule_sequence)

    expected_ngrams: int = (fact(n_rules)//(fact(n)*fact(n_rules-n)))  # n total, r sample size  -> n! / (r!((n-r)!))
    
    
    for sequence in all_rule_sequences:
        filtered_ngrams = calculate_ngrams(sequence, n)
        for k, v in filtered_ngrams.items():
            all_filtered_ngrams[k] += v
            total_count += v

    avg_ngram_freqs = {k: v / walk_count for k, v in all_filtered_ngrams.items()}

    for ngram, count in avg_ngram_freqs.items():
        print(f'{ngram}: {count}')
    
    plot_histogram(avg_ngram_freqs, 'Top Average N-gram Frequencies Across All Walks', 'Average Frequency', 'N-grams', 'avg_ngram_frequencies.png', top_n=20)


    # plot_histogram(all_filtered_ngrams, 'N-gram Frequencies', 'Frequency', 'N-grams', 'ngram_frequencies.png', top_n=20, min_freq=5)
    # plot_histogram(avg_ngram_freqs, 'Average N-gram Frequencies Across All Walks', 'Average Frequency', 'N-grams', 'avg_ngram_frequencies.png', top_n=20, min_freq=0.1)

def main():
    if len(sys.argv) != 3:
        print("Usage: ./trace_statistics.py <dir> <n>")
        sys.exit(1)

    n = int(sys.argv[2])
    dir = sys.argv[1]
    get_stats(n,dir)


if __name__ == "__main__":
    main()
