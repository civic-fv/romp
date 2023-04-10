import argparse
import pandas as pd
import matplotlib.pyplot as plt


def box_plot(data,model,feature):
    print("iamhereinside plot")
    exit()
    plt.boxplot(data, labels=["Cmurphi", "Rumur"])
    plt.title("Box Plot of Model:",model)
    plt.ylabel(feature)
    plt.show()
    

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
    model_checker_groups = df_selected.groupby("ModelChecker")
    data = []
    for name, group in model_checker_groups:
        feature_values = group[feature].tolist()
        data.append([name, feature_values])
    box_plot(data,model,feature)

if __name__ == "__main__":
    main()
