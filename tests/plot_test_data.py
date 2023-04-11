
# %%
import pandas as pd
# import matplotlib.pyplot as plt
import numpy as np
#import seaborn as sns

#%%
def violin_plot():
    #TODO
    pass

def box_plot(df_selected):
    """
    Take in a DF selection in the form of `{'group': {'label': [data-points], more label groups ...}, more groups...}`
    
    """
    #TODO printing plots


def main():
    df_cm = pd.read_csv("./tests/data/23-03-30_16-21-39_results.tsv",delimiter='\t')
    df_ru = pd.read_csv("./tests/data/23-03-30_16-41-54_results.tsv",delimiter='\t')
    #TODO --> add tsv of romp
    df = pd.concat([df_cm, df_ru], ignore_index=True)
    models = set(df['Model_name'])
    # {} nested for how many qualifiers you want to have
    box_plot({x:{m:dfx.query(f"Model_name=='{m}'").Time.to_numpy() for m in ['ruMI','german','n_peterson_bug1']} for x,dfx in [('cmurphi',df_cm),('rumur',df_ru)]}
            )
    


#%%
if __name__ == "__main__":
    main()
