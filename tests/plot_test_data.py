import argparse
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np
import seaborn as sns

def violin_plot():
    #TODO

def box_plot(df_selected, model, feature):
    #TODO printing plots

def get_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("model_name",help="Provide the model_name ")
    parser.add_argument("feature", help="provide the feature")
    return parser.parse_args()

def main():
    args = get_args()
    model = args.model_name
    feature =args.feature
    df1 = pd.read_csv("./data/23-03-30_16-21-39_results.tsv",delimiter='\t')
    df2 = pd.read_csv("./data/23-03-30_16-41-54_results.tsv",delimiter='\t')
    #TODO --> add tsv of romp
    df =pd.concat([df1, df2], ignore_index=True)
    df = df.loc[df["Model_name"] == model]
    df_selected = df[["ModelChecker",feature]]
    box_plot(df_selected, model, feature)
    
if __name__ == "__main__":
    main()
