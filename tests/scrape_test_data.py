#!/usr/bin/env python3.9
"""*
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file trace_stats.py
 *
 * @brief A utility to extract the test data from the resulting files form running a test
 *        generated with the gen_test_scripts.py.
 *        It produces a single tsv with all of the run data for easier Processing latter
 *
 * @date 2023/01/07
 * @version 0.3
 *"""

import pandas as pd
from sys import argv
import re
import os
from pathlib import Path
from math import inf
import concurrent.futures as cf
from multiprocessing import cpu_count
from trace_stats import (ModelResult, ModelResults, TraceData, fs_DFS,
                         process_data as process_trace_dir, genTraceData as genRompTraceData,
                         process_data_parallel as process_trace_dir_parallel)
from gen_test_scripts import ROMP_CONFIGS, CMURPHI_CONFIGS, RUMUR_CONFIGS, INIT_TIME_STR
import logging as log

DEBUG: int = 2


COLS=["Model_name",
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

ENABLE_ROMP_SCRAPE_TRACE_PARALLEL: bool = True


TIME_PATTERN = re.compile(r"TIME_NS=(?P<time_ns>\d+)")

ROMP_PATTERN = re.compile(r"""(?:.|\s)+
(?P<bfs>\033\[1;4mBFS SUMMARY:\033\[0m
\s*States Found: (?P<bfs_states>\d+)
\s*Rules Applied: (?P<bfs_rules>\d+)
\s*(?:Actual|BFS) Runtime: (?P<bfs_time>[^\n]+)
)?(?:.|\s)*
(?P<completed>\033\[1;4mRW SUMMARY:\033\[0m
\s*issues found: n=(?:\033\[30;1;4m|\033\[32;1m)?(?P<errors>\d+)(?:\033\[0m)? \(\|n\|=(?:\033\[30;1;4m|\033\[32;1m)?(?P<abs_errors>\d+)(?:\033\[0m)?)
\s*total rules applied: (?P<total_rules>\d+)
\s*avg rules applied: (?P<avg_rules>\d+(?:\.\d*)?
)?(?:.|\s)*
TIME_NS=(?P<time_ns>\d+)
""")


def romp(f,data_dir) -> dict:
    filepath = Path(f)
    tmp = str(filepath.stem).split('-')
    index, run = int(tmp[0]), int(tmp[1].split('__')[0])
    config_gen = ROMP_CONFIGS[index]
    config = config_gen.config
    model = str(config_gen.model.stem)
    data = {
        "ModelChecker": 'romp',
        "Model_name": model,
        "Config_details": config,
        "Config_index": index,
        "Config_run_index": run
    }
    content = ""
    with open(f, 'r') as file:
        content = file.read()
    if content == "":
        raise Exception(f"File Contents unreadable ({index}-{run}: {f!s})")
    # Extract the relevant information using regular expressions
    '''searching for a pattern in string
        if found
            get capture group
            re.search() --gets match obj'''
    t = TIME_PATTERN.search(content)
    if t is None:
        log.error(f"[ERROR] Could not match TIME pattern ({index}-{run}: {f!s})")
        data.update({'Time': inf})
    else:
        data.update({'Time': int(t.group('time_ns')) if t.group('time_ns') is not None else None})
    m = RUMUR_PATTERN.search(content)
    if m is None:
        log.error(f"[ERROR] Could not match RUMUR pattern ({index}-{run}: {f!s})")
        for i in COLS:
            if i not in data:
                data.update({i: None})
        return data
    data.update({
        "Completed": m.group('completed') is not None,
        "Error_status": ('NO ERROR' if (m.group('errors') is not None and int(m.group('errors')) <= 0) else (
                            int(m.group('errors')) if m.group('errors') is not None else None)),
        "States Generated": None,
        "Time": int(m.group('time_ns')) if m.group('time_ns') is not None else None,
        "Transitions": None,
        "Cachegrind_data": None,
        "Misc_data": {
            'rules_fired': int(m.group('total_rules')) if m.group('total_rules') is not None else None,
            'avg_depth': float(m.group('avg_rules')) if m.group('avg_rules') is not None else None,
            'Trace_data':None,
            'BFS_data':{'enabled':False, 'states':0, 'transitions':0, 'time_str':""}
        }
    })
    if m.group('bfs') is not None:
        data["Misc_data"]['BFS_data'].update({
                'enabled': True,
                'states': int(m.group('bfs_states')),
                'transitions': int(m.group('bfs_rules')),
                'time_str': m.group('bfs_time')
            })
    #NOTE: trace dir for this model should be the `run`th dir in the `./traces/{index}/` dir
    trace_dir:str = os.listdir(f'{data_dir}/traces/{index}')[run]
    trace_results: ModelResults
    if ENABLE_ROMP_SCRAPE_TRACE_PARALLEL:
        max_threads = cpu_count() if 0 <= cpu_count() <= 3 else cpu_count()-2
        trace_results = process_trace_dir_parallel(trace_dir,max_workers=max_threads)
    else:
        trace_results = process_trace_dir(trace_dir)
    if 0 <= len(trace_results) > 1:
        print("[ERROR] rumur trace data caught multiple romp instances")
        return data
    trace_data: ModelResult = trace_results.items()[0][1]
    data.update({
        "States Generated": (trace_data.abs_unique_state_count + data['MiscData']['BFS_data']['states']),
        "Transitions": (trace_data.abs_unique_applied_transition_count + data['MiscData']['BFS_data']['transitions'])
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
    return data
#?END def romp() -> None


CMURPHI_PATTERN = re.compile(r"""(?P<completed>(?:Status|Result):
+\s*(?:(?P<no_error>No error found)|(?:(?P<errors>Invariant|Error|Assertion) \"(?:[ \w\d\_\-]*)\" failed)|(?P<deadlock>Deadlocked state found))\.
+State Space Explored:
+\s*(?P<states>\d+) states, (?P<rules>\d+) rules fired in (?:\d+(?:\.\d*)?)s\.)
+(?P<hash_compaction>\s*Omission Probabilities (caused by Hash Compaction):
+\s*Pr\[even one omitted state\]\s+<=\s+(?P<op_omitted>\d+(?:\.\d*))
+\s*Pr\[even one undetected error\]\s+<=\s+(?P<op_undetected>\d+(?:\.\d*))
+\s*Diameter of reachability graph: (?P<op_diameter>\d+(?:\.\d*))
)?""")

def cmurphi(f) -> dict:
    filepath = Path(f)
    tmp = str(filepath.stem).split('-')
    index, run = int(tmp[0]), int(tmp[1].split('__')[0])
    config_gen = CMURPHI_CONFIGS[index]
    config = config_gen.config
    model = str(config_gen.model.stem)
    data = {
        "ModelChecker": 'cmuprhi',
        "Model_name": model,
        "Config_details": config,
        "Config_index": index,
        "Config_run_index": run
    }
    content = ""
    with open(f, 'r') as file:
        content = file.read()
    if content == "":
        raise Exception(f"File Contents unreadable ({index}-{run}: {f!s})")
    # Extract the relevant information using regular expressions
    '''searching for a pattern in string
        if found
            get capture group
            re.search() --gets match obj'''
    t = TIME_PATTERN.search(content)
    if t is None:
        log.error(f"[ERROR] Could not match TIME pattern ({index}-{run}: {f!s})")
        data.update({'Time': inf})
    else:
        data.update({'Time': int(t.group('time_ns')) if t.group('time_ns') is not None else None})
    m = CMURPHI_PATTERN.search(content)
    if m is None:
        log.error(f"[ERROR] Could not match CMURPHI pattern ({index}-{run}: {f!s})")
        for i in COLS:
            if i not in data:
                data.update({i: None})
        return data
    # try:
    #     err_tmp3 = 'DEADLOCK' if m.group('deadlock') is not None else None
    #     err_tmp2 = 1 if m.group('errors') is not None else err_tmp3
    #     err_tmp1 = 'NO ERROR' if m.group('no_error') is not None else err_tmp2
    # except Exception as ex:
    #     log.error(str(ex))
    # err_tmp1= ('NO ERROR' if m.group('no_error') is not None else (
    #                         int(m.group('errors')) if m.group('errors') is not None else (
    #                         'DEADLOCK' if m.group('deadlock') is not None else None)))
    data.update({
        "Completed": m.group('completed') is not None,
        "Error_status": ('NO ERROR' if m.group('no_error') is not None else (
                            1 if m.group('errors') is not None else (
                            'DEADLOCK' if m.group('deadlock') is not None else None))),
        "States Generated": int(m.group('states')) if m.group('states') is not None else None,
        "Transitions": int(m.group('rules')) if m.group('rules') is not None else None,
        "Cachegrind_data": None,
        "Misc_data": dict()
        })
    if m.group('hash_compaction') is not None:
        data['Misc_data'].update({
            'omitted': float(m.group('op_omitted')),
            'undetected': float(m.group('op_undetected')),
            'diameter': float(m.group('op_diameter'))
        })
    if DEBUG >= 3:
        log.debug(f"[DEBUG] just finished with {f}: {data!s}")
    return data
#?END def cmurphi() -> None


RUMUR_PATTERN = re.compile(r"""(?P<completed>Status:
+\s*(?:(?P<no_error>No) error|(?P<errors>\d+) error\(s\)|(?P<deadlock>[Dd]eadlock)(?:\(s\))?) found\.
+\s*State Space Explored:
+\s*(?P<states>\d+) states, (?P<rules>\d+) rules fired in (?:\d+(?:.\d*)?)s.)""")

def rumur(f) -> dict:
    filepath = Path(f)
    tmp = str(filepath.stem).split('-')
    index, run = int(tmp[0]), int(tmp[1].split('__')[0])
    config_gen = RUMUR_CONFIGS[index]
    config = config_gen.config
    model = str(config_gen.model.stem)
    data = {
        "ModelChecker": 'rumur',
        "Model_name": model,
        "Config_details": config,
        "Config_index": index,
        "Config_run_index": run
    }
    content = ""
    with open(f, 'r') as file:
        content = file.read()
    if content == "":
        raise Exception(f"File Contents unreadable ({index}-{run}: {f!s})")
    # Extract the relevant information using regular expressions
    '''searching for a pattern in string
        if found
            get capture group
            re.search() --gets match obj'''
    t = TIME_PATTERN.search(content)
    if t is None:
        log.error(f"[ERROR] Could not match TIME pattern ({index}-{run}: {f!s})")
        data.update({'Time': inf})
    else:
        data.update({'Time': int(t.group('time_ns')) if t.group('time_ns') is not None else None})
    m = RUMUR_PATTERN.search(content)
    if m is None:
        log.error(f"[ERROR] Could not match RUMUR pattern ({index}-{run}: {f!s})")
        for i in COLS:
            if i not in data:
                data.update({i: None})
        return data
    data.update({
        "Completed": m.group('completed') is not None,
        "Error_status": ('NO ERROR' if m.group('no_error') is not None else (
                            int(m.group('errors')) if m.group('errors') is not None else (
                            'DEADLOCK' if m.group('deadlock') is not None else None))),
        "States Generated": int(m.group('states')) if m.group('states') is not None else None,
        "Transitions": int(m.group('rules')) if m.group('rules') is not None else None,
        "Cachegrind_data": None, # TODO read and extract valgrind data if it exists
        "Misc_data": dict()
        })
    return data
#?END def rumur() -> None


def read_text_file(path, df, top_dir="./") -> dict:
    '''ip-path,op-None
    '''
    if not os.path.exists(path):
        raise Exception("Path does not exist!!")
    if path.endswith(".txt"):
        if path.endswith('.ru.txt'):
            return rumur(path)
        elif path.endswith('.romp.txt'):
            return romp(path,top_dir)
        elif path.endswith('.cm.txt'):
            return cmurphi(path)
    return None
#?END def read_text_file() -> None

def scrape_data(data_dir) -> pd.DataFrame:
    #do col name to be added for cmurphi - omission prob stats required and analysis of state space  // -pr gives rules information is it required ? --todo
    #for romp only to consider text below RW results ? other in config --TOdo
    # df: pd.DataFrame = pd.DataFrame(columns=COLS)
    #created a pd dataframe with subcols each for flag + others
    # call opening file function in loop
    data_files = []
    def file_callback(path) -> None:
        if (path.endswith('.romp.txt')
                or path.endswith('.ru.txt')
                or path.endswith('.cm.txt')):
            data_files.append(path)
    def thread_work(filepath) -> dict:
        return read_text_file(filepath,data_dir)
    fs_DFS(data_dir,fileCallback=file_callback)
    if DEBUG > 0:
        print(f"[DEBUG] input file len: {len(data_files)}")
    max_threads = (cpu_count() if 0 <= cpu_count() >= 3 else cpu_count()-2) if ENABLE_ROMP_SCRAPE_TRACE_PARALLEL else (1 if DEBUG >= 3 else None)
    with cf.ThreadPoolExecutor(max_workers=max_threads) as executor:
        data = [ i for i in executor.map(thread_work, data_files)]
    if DEBUG > 0:
        print(f"[DEBUG] data len: {len(data)}")
        if DEBUG >= 1 and len(data) > 1:
            print(f"[DEBUG] data[0]: {data[0]}")
    df = pd.DataFrame(data,columns=COLS)
    return df
#?END def scrape_data() -> None

def save_data(df:pd.DataFrame,loc=f"./data/{INIT_TIME_STR}_results.tsv",fmt:str="tsv") -> None:
    _fmt = fmt.lower()
    with open(loc,'w') as file:
        if _fmt == 'tsv':
            df.to_csv(file,columns=COLS,sep='\t')
        elif _fmt == 'csv':
            df.to_csv(file,columns=COLS)
        elif _fmt == 'json':
            df.to_json(file,orient='records')
#?END def save_data(df,loc) -> None


def main()->None:
    data_dir = argv[1] if len(argv) > 1 and os.path.exists(argv[1]) else './'
    save_data(scrape_data(data_dir))
#?END def main() -> None:

if __name__ == "__main__":
    log_format = "%(asctime)s: %(message)s"
    log.basicConfig(format=log_format, level=log.INFO if DEBUG <= 0 else log.DEBUG,
                        datefmt="%H:%M:%S")
    main()
