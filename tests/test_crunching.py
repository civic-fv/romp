#using pandas then converting it into a csv ?
import pandas as pd
import subprocess
import re
import os
from math import inf
path = "Path"
from trace_stats import TraceData
from test_script import fs_DFS
#changing the current working directory to the provided path
os.chdir(path)

def romp(f):
    '''1) read the file data 
    '''
    pass

def cmurphi(f):
    pass

 

def rumur(f)->pd.DataFrame:
    with open(f, 'r') as f:
        content = f.read()
        # Extract the relevant information using regular expressions
        '''searching for a pattern in string
            if found 
                get capture group
                re.search() --gets match obj'''

        Model_name = '' #todo
        Config_details = ''#todomodel_name = 'rumur'
        completed = 'Yes' if 'No error found.' in content else 'No'
        completed = 'Yes' if 'No error found.' in content else 'No'
        error_status_match = re.search(r'Status:\s*(.+?)State Space Explored:', content, re.DOTALL)
        error_status = error_status_match.group(1).strip() if error_status_match is not None else None
        states_generated_match = re.search(r'State Space Explored:\s*(\d+) states,[\s\S]*', content)
        states_generated = int(states_generated_match.group(1)) if states_generated_match is not None else None
        time = #todo to be obtained using external tool
        rules_fired_match = re.search(r'State Space Explored:\s*\d+ states,\s*(\d+) rules fired', content)
        rules_fired = int(rules_fired_match.group(1)) if rules_fired_match is not None else 0
        modelchecker_type = 'Rumur'
        valgrind_data = #todo
        data = {"Model_name":,"Config_details":,"Completed":completed,"Error_status":error_status,"States Generated":states_generated,
                "Time":time,"Rules_Fired":rules_fired,"ModelChecker_type":modelchecker_type,"Valgrind_data":valgrind_data}
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
                if '__ru' in file:
                    rumur(f)
                elif '_romp' in file:
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
    file_list=fs_DFS("relative_path")
    for filename in file_list:
        read_text_file(#TODO insert the path)



if __name__ == "__main__":
    main()