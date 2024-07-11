#!/usr/bin/env python3

import json
import sys
from collections import defaultdict, deque
import glob
import plotly.graph_objects as go
import plotly.express as px

def _do_process(path: str):
    rule_hits = defaultdict(int)
    rule_misses = defaultdict(int)
    rule_sequence = []
    hits = 0
    misses = 0
    with open(path, 'r') as file:
        trace_file = json.load(file)

    for trace in trace_file['trace']:
        rule_type = trace['$type']
        rule_name = trace.get('rule', {}).get('label', 'unknown')

        if rule_type in {'rule-hit', 'rule-miss'}:
            rule_sequence.append(rule_name)
            if rule_type == 'rule-hit':
                rule_hits[rule_name] += 1
                hits += 1
            elif rule_type == 'rule-miss':
                rule_misses[rule_name] += 1
                misses += 1

    return rule_sequence, rule_hits, rule_misses, hits, misses

def calculate_ngrams(sequence, n):
    ngram_seq = deque(maxlen=n)
    ngrams = defaultdict(int)

    for item in sequence:
        ngram_seq.append(item)
        if len(ngram_seq) == n:
            ngrams[tuple(ngram_seq)] += 1

    # Filter out n-grams that start with 'unknown'
    filtered_ngrams = {k: v for k, v in ngrams.items() if k[0] != 'unknown'}
    
    return filtered_ngrams

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


def main(n):
    json_files = glob.glob('*.json')

    if not json_files:
        print("No JSON files found in the current directory.")
        sys.exit(1)
    
    all_rule_sequences = [] 
    all_filtered_ngrams = defaultdict(int)
    total_count = 0

    for json_file in json_files:
        rule_sequence, rule_hits, rule_misses, hits, misses = _do_process(json_file)
        all_rule_sequences.append(rule_sequence)

    for sequence in all_rule_sequences:
        filtered_ngrams = calculate_ngrams(sequence, n)
        for k, v in filtered_ngrams.items():
            all_filtered_ngrams[k] += v
            total_count += v

    avg_ngram_freqs = {k: v / len(all_rule_sequences) for k, v in all_filtered_ngrams.items()}

    for ngram, count in avg_ngram_freqs.items():
        print(f'{ngram}: {count}')
    
    plot_histogram(avg_ngram_freqs, 'Top Average N-gram Frequencies Across All Walks', 'Average Frequency', 'N-grams', 'avg_ngram_frequencies.png', top_n=20)


    # plot_histogram(all_filtered_ngrams, 'N-gram Frequencies', 'Frequency', 'N-grams', 'ngram_frequencies.png', top_n=20, min_freq=5)
    # plot_histogram(avg_ngram_freqs, 'Average N-gram Frequencies Across All Walks', 'Average Frequency', 'N-grams', 'avg_ngram_frequencies.png', top_n=20, min_freq=0.1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: ./trace_statistics.py <n>")
        sys.exit(1)

    n = int(sys.argv[1])
    main(n)
