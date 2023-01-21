#using pandas then converting it into a csv ?
import pandas as pd
import re
import os
path = "Path"
#changing the current working directory to the provided path
os.chdir(path)




def romp(f):
    '''1) read the file data 
    '''
    pass

def cmurphi(f):
    pass
import re

def rumur(f):
    lines = f.readlines()
    memory_usage = lines[0]
    progress_report = lines[1]
    status = lines[3]
    state_space_explored = lines[4]

    size_of_state = int(re.search(r'(\d+) bits', memory_usage).group(1))
    size_of_hash_table = int(re.search(r'(\d+) slots', memory_usage).group(1))

    states_explored = int(re.search(r'(\d+) states explored', progress_report).group(1))
    rules_fired = int(re.search(r'(\d+) rules fired', progress_report).group(1))
    time_taken = float(re.search(r'(\d+\.\d+)s', progress_report).group(1))

    error_status = re.search(r'Status:(.+)', status).group(1).strip()

    states = int(re.search(r'(\d+) states', state_space_explored).group(1))
    rules_fired = int(re.search(r'(\d+) rules', state_space_explored).group(1))
    time_taken = float(re.search(r'(\d+\.\d+)s', state_space_explored).group(1))

    data = {'model':'rumur', 'States_visited': states_explored, 'Rules_Fired': rules_fired, 'Time': time_taken,
            'Memory': size_of_state, 'Hashtable_Size': size_of_hash_table, 'Error_Status':error_status}

    stats_df = stats_df.append(data, ignore_index=True)

    return stats_df


def rumur(f):
    '''1)read all lines in the file 
    '''
    lines = f.readlines()
    memory_usage = lines[0]
    status = lines[2]
    state_space_explored = lines[3]

    size_of_state = int(memory_usage.split(':')[1].split()[0])
    size_of_hash_table = int(memory_usage.split(':')[2].split()[0])

    error_status = status.split(':')[1].strip()

    states = int(state_space_explored.split(':')[1].split()[0])
    rules_fired = int(state_space_explored.split(':')[1].split()[4])
    time_taken = float(state_space_explored.split(':')[1].split()[7][:-1])

    data = {'model':'rumur', 'States_visited': states_explored, 'Rules_Fired': rules_fired, 'Time': time_taken,
            'Memory': size_of_state, 'Hashtable_Size': size_of_hash_table, 'Error_Status':error_status}

    stats_df = stats_df.append(data, ignore_index=True)

    #TODO USE REGEX LIB not split of datatype
    #todo index from the model 
    #todo fsdfs use list 

'''use fsdfs to get list of files
    create the config generator objects
        iterate through each config generator obj 
            using the index to match files to configs and use regex to extract data into df
    Note :  any data that can't be gathered must have None as value 

Colsname: File_name/Model_name , config details (dict with flags mapping to its value), error_status,state generated,time,rules fired, model_checker_type,valgrind data#todo
By tomorrow: 4 PM
 1) regex
 2) cols df
 3) index
'''
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

def fs_DFS(path, dirCallback=None, fileCallback=None) -> List[str]:
    if not os.path.exists(path):
        raise Exception("Path does not exist!!")
    stack = []
    ret = []
    stack.append(path);
    while len(stack) > 0:
        tmp = stack.pop(len(stack) - 1)
        if(os.path.isdir(tmp)):
            ret.append(tmp)
            for item in os.listdir(tmp):
                stack.append(os.path.join(tmp, item))
            if dirCallback:
                dirCallback(tmp)
        elif(os.path.isfile(tmp)):
            ret.append(tmp)
            if fileCallback:
                fileCallback(tmp)
    return ret

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

    cols=["Model_name","Config_details","Error_status","States Generated","Time","Rules_Fired","ModelChecker_type","Valgrind_data"]# todo add cols name for romp and cm
    stats_df=pd.DataFrame(columns=cols)
    #created a pd dataframe with subcols each for flag + others 
    # call opening file function in loop 
    read_text_file()


if __name__ == "__main__":
    main()