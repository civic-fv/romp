#using pandas then converting it into a csv ?
import pandas as pd
import subprocess
import re
import os
from math import inf
path = "Path" # idk what this is (@Ajantha)
from trace_stats import ModelResult, ModelResults, fs_DFS, process_data as process_trace_dir
from gen_test_scripts import ROMP_CONFIGS, CMURPHI_CONFIGS, RUMUR_CONFIGS, ROMP_TRACE_DIR_TEMPLATE
#changing the current working directory to the provided path
os.chdir(path)

#TODO: fill this in
ROMP_PATTERN = re.compile(r"""(?:.|\s)+
(?P<bfs>\033\[1;4mBFS SUMMARY:\033\[0m
\s*States Found: (?P<bfs_states>\d+)
\s*Rules Applied: (?P<bfs_rules>\d+)
\s*(?:Actual|BFS) Runtime: (?P<bfs_time>[^\n]+)
)?(?:.|\s)*
(?P<completed>\033\[1;4mRW SUMMARY:\033\[0m
\s*issues found: n=(?:\033\[30;1;4m|\033\[32;1m)?(?P<errors>\d+)(?:\033\[0m)? \(\|n\|=(?:\033\[30;1;4m|\033\[32;1m)?(?P<abs_errors>\d+)(?:\033\[0m)?)
\s*total rules applied: (?P<total_rules>\d+)
\s*avg rules applied: (?P<avg_rules>\d+(?:\.\d*)?)
)?(?:.|\s)*
TIME_NS=(?P<time_ns>\d+)
""")


def romp(f, df) -> None:
    filepath = os.path(f)
    tmp = str(filepath.stem).split('-')
    index, run = int(tmp[0]), int(tmp[1].split('__')[0])
    config_gen = ROMP_CONFIGS[index]
    config = config_gen.config
    model = str(config_gen.model.stem)
    content = ""
    with open(f, 'r') as f:
        content = f.read()
    if content == "":
        raise Exception(f"File Contents unreadable ({f})")
    # Extract the relevant information using regular expressions
    m = ROMP_PATTERN.search(content)
    data = {
        "Model_name": model,
        "Config_details": config,
        "Config_index": index,
        "Config_run_index": run,
        "Completed": m.group('completed') is not None,
        "Error_status": ('NO ERROR' if (m.group('errors') is not None and int(m.group('errors')) <= 0) else (
                            int(m.group('errors')) if m.group('errors') is not None else None)),
        "States Generated": None,
        "Time": int(m.group('time_ns')) if m.group('time_ns') is not None else None,
        "Transitions": None,
        "ModelChecker": 'romp',#TODO addition for analysis + Omission Probabilities ??
        "Cachegrind_data": None,
        "Misc_data": {
            'rules_fired': int(m.groups('total_rules')) if m.groups('total_rules') is not None else None,
            'avg_depth': float(m.groups('avg_rules')) if m.groups('avg_rules') is not None else None,
            'Trace_data':None,
            'BFS_data':{'enabled':False, 'states':0, 'transitions':0, 'time_str':""}
        }
    }
    if m.groups('bfs') is not None:
        data["Misc_data"]['BFS_data'].update({
                'enabled': True,
                'states': int(m.groups('bfs_states')),
                'transitions': int(m.groups('bfs_rules')),
                'time_str': m.groups('bfs_time')
            })
    #NOTE: trace dir for this model should be the `run`th dir in the `./traces/{index}/` dir
    trace_dir:str = os.listdir(ROMP_TRACE_DIR_TEMPLATE.format(id=index))[run]
    trace_results: ModelResults = process_trace_dir(trace_dir)
    if 0 <= len(trace_results) > 1:
        print("[ERROR] rumur trace data caught multiple romp instances")
        df.append(data, ignore_index=True)
        return
    trace_data: ModelResult = trace_results.items()[0][1]
    data.update({
        "States Generated": trace_data.abs_unique_state_count + data['MiscData']['BFS_data']['states']),
        "Transitions": trace_data.abs_unique_applied_transition_count + data['MiscData']['BFS_data']['transitions']
        })
    data["Misc_data"].update({'TraceData':{
                                'ErrorData': {
                                    'found': trace_data.errors_found,
                                    'rate': trace_data.error_detection_rate
                                },
                                'RuleData': {
                                    'tried': trace_data.unique_rule_count.summary,
                                    'applied': trace_data.unique_applied_rule_count.summary,
                                    'possible': trace_data.id.rule_count,
                                },
                                'StateData': {
                                    'found': trace_data.unique_state_count.summary,
                                    'abs_found': trace_data.abs_unique_state_count,
                                },
                                'TransitionData': {
                                    'tried': trace_data.unique_transition_count.summary,
                                    'applied': trace_data.unique_applied_transition_count.summary,
                                    'abs_tried': trace_data.abs_unique_transition_count.summary,
                                    'abs_applied': trace_data.abs_unique_applied_transition_count.summary
                                }
                            }})
    df.append(data, ignore_index=True)

CMURPHI_PATTERN = re.compile(r"""(?:.|\s)+
(?P<completed>Status:

	(?:(?P<no_error>No) error|(?P<errors>\d+) error\(s\)|(?P<deadlock>[Dd]eadlock)(?:\(s\))?) found.

State Space Explored:

	(?P<states>\d+) states, (?P<rules>\d+) rules fired in \d+s.
)?
 
Omission Probabilities (caused by Hash Compaction):

    Pr\[even one omitted state\]\s+<=\s+\d+\.\d+\n\tPr\[even one undetected error\]\s+<=\s+\d+\.\d+\n\tDiameter of reachability graph: \d+$ #TODO

TIME_NS=(?P<time_ns>\d+)
""")

def cmurphi(f, df) -> None:
    filepath = os.path(f)
    tmp = str(filepath.stem).split('-')
    index, run = int(tmp[0]), int(tmp[1].split('__')[0])
    config_gen = CMURPHI_CONFIGS[index]
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
    m = CMURPHI_PATTERN.search(content)
    data = {
        "Model_name": model,
        "Config_details": config,
        "Config_index": index,
        "Config_run_index": run,
        "Completed": m.group('completed') is not None,
        "Error_status": ('NO ERROR' if m.group('no_error') is not None else (
                            int(m.group('errors')) if m.group('errors') is not None else (
                            'DEADLOCK' if m.group('deadlock') is not None else None))),
        "States Generated": int(m.group('states')) if m.group('states') is not None else None,
        "Time": int(m.group('time_ns')) if m.group('time_ns') is not None else None,
        "Transitions": int(m.group('rules')) if m.group('rules') is not None else None,
        "ModelChecker": 'cmuprhi',#TODO addition for analysis + Omission Probabilities ??
        "Cachegrind_data": None,
        "Misc_data": dict()
        }
    df.append(data, ignore_index=True)

RUMUR_PATTERN = re.compile(r"""(?:.|\s)+
(?P<completed>Status:

	(?:(?P<no_error>No) error|(?P<errors>\d+) error\(s\)|(?P<deadlock>[Dd]eadlock)(?:\(s\))?) found.

State Space Explored:

	(?P<states>\d+) states, (?P<rules>\d+) rules fired in \d+s.
)?
TIME_NS=(?P<time_ns>\d+)
""")

def rumur(f, df) -> None:
    filepath = os.path(f)
    tmp = str(filepath.stem).split('-')
    index, run = int(tmp[0]), int(tmp[1].split('__')[0])
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
        "Config_index": index,
        "Config_run_index": run,
        "Completed": m.group('completed') is not None,
        "Error_status": ('NO ERROR' if m.group('no_error') is not None else (
                            int(m.group('errors')) if m.group('errors') is not None else (
                            'DEADLOCK' if m.group('deadlock') is not None else None))),
        "States Generated": int(m.group('states')) if m.group('states') is not None else None,
        "Time": int(m.group('time_ns')) if m.group('time_ns') is not None else None,
        "Transitions": int(m.group('rules')) if m.group('rules') is not None else None,
        "ModelChecker": 'rumur',
        "Cachegrind_data": None, # TODO read and extract valgrind data if it exists
        "Misc_data": dict()
        }
    df.append(data, ignore_index=True)

def read_text_file(path, df) -> None:
    '''ip-path,op-None
    '''
    if not os.path.exists(path):
        raise Exception("Path does not exist!!")
    for file in os.listdir():
        if file.endswith(".txt"):
            f = os.path.join(path, file)
            if '.ru.txt' in file:
                rumur(f,df)
            elif '.romp.txt' in file:
                romp(f,df)
            else:
                cmurphi(f,df)

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
    cols=["Model_name",
          "ModelChecker",
          "Config_index",
          "Config_run_index",
          "Completed",
          "Error_status",
          "States Generated",
          "Time",
          "Transitions",
          "Config_details",
          "Misc_data",
          "Cachegrind_data"]
    #do col name to be added for cmurphi - omission prob stats required and analysis of state space  // -pr gives rules information is it required ? --todo
    #for romp only to consider text below RW results ? other in config --TOdo
    stats_df=pd.DataFrame(columns=cols)
    #created a pd dataframe with subcols each for flag + others 
    # call opening file function in loop 
    file_list=fs_DFS("TODO relative_path probs get from args")
    for filename in file_list:
        read_text_file( #TODO GET data directories
                        ,stats_df)

if __name__ == "__main__":
    main()
