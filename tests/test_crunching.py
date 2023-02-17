#using pandas then converting it into a csv ?
import pandas as pd
import subprocess
import re
import os
from math import inf
path = "Path" # idk what this is (@Ajantha)
from trace_stats import TraceData, fs_DFS
from gen_test_scripts import ROMP_CONFIGS, CMURPHI_CONFIGS, RUMUR_CONFIGS
#changing the current working directory to the provided path
os.chdir(path)

def romp(f):
    '''1) read the file data 
    '''
    pass

def cmurphi(f):
    pass

RUMUR_PATTERN = re.compile(r"""(?:.|\s)+
(?<completed>Status:

	(?:(?<no_error>No) error|(?<errors>\d+) error\(s\)|(?<deadlock>[Dd]eadlock)(?:\(s\))?) found.

State Space Explored:

	(?<states>\d+) states, (?<rules>\d+) rules fired in \d+s.
)?
TIME_NS=(?<time_ns>\d+)
""")

def rumur(f)->pd.DataFrame:
    filepath = os.path(f)
    index = int(str(filepath.stem).split('-')[0])
    config_gen = RUMUR_CONFIGS[index]
    config = config_gen.config
    model = str(config_gen.model.stem)
    content = ""
    with open(f, 'r') as f:
        content = f.read()
    if content == "":
        raise Exception(f"File Contents unreadable ({f})")
    # Extract the relevant information using regular expressions
    '''searching for a pattern in string
        if found 
            get capture group
            re.search() --gets match obj'''
    m = RUMUR_PATTERN.search(content)
    data = {
        "Model_name": model,
        "Config_details": config,
        "Completed": m.group('completed') is not None,
        "Error_status": ('NO ERROR' if m.group('no_error') is not None else (
                            int(m.group('errors')) if m.group('errors') is not None else (
                            'DEADLOCK' if m.group('deadlock') is not None else None))),
        "States Generated": int(m.group('states')) if m.group('states') is not None else None,
        "Time": int(m.group('time_ns')) if m.group('time_ns') is not None else None,
        "Rules_Fired": int(m.group('rules')) if m.group('rules') is not None else None,
        "ModelChecker_type": 'rumur',
        "Valgrind_data": None # TODO read and extract valgrind data if it exists
        }
    stats_df = stats_df.append(data, ignore_index=True)
    return stats_df

def read_text_file(path) -> None:
    '''ip-path,op-None
    '''
    if not os.path.exists(path):
        raise Exception("Path does not exist!!")
    for file in os.listdir():
        if file.endswith(".txt"):
            full_path = os.path.join(path, file)
            with open(full_path, 'r') as f:
                if '.ru.txt' in file:
                    rumur(f)
                elif '.romp.txt' in file:
                    romp(f)
                else:
                    cmurphi(f)

def main()->None:
    '''Things to do 

    1) open the file in the path ".\relative ?"
        open all .txt files in loop
        i) check which model 
            how to do 
            after __ what it is there if ==ru rumur , romp=romp and cm= cmurphi
        ii) if it is rumur 
            what are subdata to be stored

    '''
    cols=["Model_name","Config_details","Completed","Error_status","States Generated","Time","Rules_Fired","ModelChecker_type","Valgrind_data"]# todo add cols name for romp and cm
    stats_df=pd.DataFrame(columns=cols)
    #created a pd dataframe with subcols each for flag + others 
    # call opening file function in loop 
    file_list=fs_DFS("TODO relative_path")
    for filename in file_list:
        read_text_file(#TODO insert the path)



if __name__ == "__main__":
    main()