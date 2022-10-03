#! /usr/bin/python3
"""*
 * @proj romp
 * @author Andrew Osterhout
 * @author Ajantha Varadharaaj
 * @org University of Utah (UofU) School of Computing (SoC)
 * @org Center for Parallel compute at Utah (CPU)
 * @org <a href="https://civic-fv.github.io">Civic-fv NSF Grant</a>
 * @org Ganesh Gopalakrishnan's Research Group
 * @file romp-rw.hpp
 *
 * @brief A utility to extract romp model-checkers (random walkers) trace files
 *         and perform some statistics on the traces.
 *
 * @date 2022/05/11
 * @version 0.1
 *"""

from concurrent.futures import process
from sys import argv
import os
from json import load as j_load, dumps as j_dump
from typing import Any, Dict, List, Sequence, Tuple, Type, Union as Un, MutableSet as Set, FrozenSet as FSet, NamedTuple, Callable
from dataclasses import dataclass, field
from math import inf, nan as NaN
from io import StringIO
import datetime
import traceback
import statistics as stats

DEBUG: bool = True

Num: Type = Un[int,float]

class StatSummary(NamedTuple):
    """a simple named tuple that holds a 5 number summary of a StatRange"""
    mean: Num
    stdev: Num
    median: Num
    min: Num
    max: Num
#? END NamedTuple Statsummary

TupleFactory: Type = Callable[[Any],Un[Tuple,NamedTuple]]
SR_SS_FACTORY: Callable[[Any],Un[Tuple,NamedTuple]] = (
    lambda x: StatSummary(x.mean,x.stdev,x.median,x.min,x.max))

# class StateSet(set):
#     def add(self,state:dict) -> None:
#         set.add(self,j_dump(state))
# #? END class StateSet

class Version(tuple):
    "Simple multi part version handler"
    def __init__(self, val:Un[str,Sequence]) -> None:
        if isinstance(val,str):
            tuple.__init__(self,Version.__parse_v_str(val))
        elif isinstance(val, Sequence):
            tuple.__init__(self,val)
        elif isinstance(val,Num):
            tuple.__init__(self,[val])
        else:
            raise Exception(f"`{type(val)!s}` is not a valid initializer for a Version")
    @staticmethod
    def __parse_v_str(val:str) -> Sequence:
        return map(int,val.split('.'))
#? END class Version

@dataclass(eq=True,frozen=True,unsafe_hash=False)
class RompID:
    """A unique identifier for a "romp" indexed by the model,
    and when it was run, also holds (but is not hashed with) the metadata of a run."""
    romp_vers: Version
    model: str
    romp_init_time: int
    root_seed: str
    metadata: dict = field(hash=False,repr=True,compare=False)
    # seed: Un[str,int]
    def __str__(self) -> str:
        time_stamp = datetime.datetime.fromtimestamp(self.romp_init_time).strftime('%y-%m-%d %H:%M:%S')
        model_name = os.path.split(self.model)[1] # .rsplit('.',1)[0]
        return f"{time_stamp} :: {model_name} w/ seed: {self.root_seed}"
    #? END def __str__(self) -> str
    @property
    def rule_count(self) -> int:
        return self.metadata['total-rule-count']
    @property
    def possible_state_count(self) -> int:
        return self.metadata['possible-state-count']
    @property
    def transition_count(self) -> int:
        return self.rule_count * self.possible_state_count
    @property
    def time_unit(self) -> str:
        if romp_vers < (0,0,3):
            return "sec"
        return "ms"
#? END @dataclass RompID

@dataclass(eq=True,frozen=True,unsafe_hash=False)
class TraceID:
    """A unique identifier for a single trace in a romp."""
    romp_id: RompID
    trace_id: int
    trace_dir: str
    file_name: str
    seed: int
    start_id: int
#? END @dataclass TraceID

class RompTraceParseError(Exception):
    pass
#? END class RompTraceParseError


SR_DEFAULT_SUMMARY_FMT_STR: str = (
    "{:>12.3g} {:^12.4g} {:>12.3g} {:>12.2g} {:>12.2g}")
SR_DEFAULT_SUMMARY_FACTORY: TupleFactory = SR_SS_FACTORY
SR_DEFAULT_SUMMARY_LABEL_STR: str = (
    f"{'mean:':->12s}-{'stdev:':-^12s}-{'median:':->12s}-{'min:':->12s}-{'max:':->12s}")
class StatRange(list):
    DEFAULT_SUMMARY_FMT_STR: str = SR_DEFAULT_SUMMARY_FMT_STR
    DEFAULT_SUMMARY_LABEL_STR: str = SR_DEFAULT_SUMMARY_LABEL_STR
    DEFAULT_SUMMARY_FACTORY: TupleFactory = SR_DEFAULT_SUMMARY_FACTORY
    """A list that allows you to have easy access to statistical operations"""
    def __init__(self, *args,
                 summary_fmt_str: str = SR_DEFAULT_SUMMARY_FMT_STR,
                 summary_label_str: str = SR_DEFAULT_SUMMARY_LABEL_STR,
                 summary_factory: TupleFactory = SR_DEFAULT_SUMMARY_FACTORY,
                 **kwargs) -> None:
        list.__init__(self,*args,**kwargs)
        self.min: int = inf
        self.max: int = -inf
        self.sum: int = 0
        self.n: int = 0
        # self.__data: List[Num] = list()
        self.__median: Num = None
        self.__stdev: Num = None
        self.__mode: Num = None
        self.__summary_fmt_str: str = summary_fmt_str
        # if 'summary_fmt_str' in kwargs:
        #     self.__summary_fmt_str = kwargs['summary_fmt_str']
        self.__summary_label_str: str = summary_label_str
        # if 'summary_label_str' in kwargs:
        #     self.__summary_label_str = kwargs['summary_label_str']
        self.__summary_factory: TupleFactory = summary_factory
        # if 'summary_factory' in kwargs:
        #     self.__summary_label_str = kwargs['summary_factory']
    def append(self, data) -> None:
        self.add_data(data)
    def add_data(self,data:Un[list,List,Num]) -> None:
        self.__median = None
        self.__stdev = None
        if isinstance(data,list):
            if len(data) <= 0:
                if DEBUG:
                    print("tried to add an empty list/StatRange to a StatRange!!")
                return
            list.extend(self,data)
            self.max = max(max(data),self.max)
            self.min = min(min(data),self.min)
            self.n += len(data)
            self.sum += sum(data)
            return
        self.max = max(data,self.max)
        self.min = min(data,self.min)
        self.sum += data
        self.n += 1
        list.append(self,data)
    @property
    def mean(self) -> Num:
        if self.n <= 0:
            return NaN
        return self.sum / self.n
    def __calc_median(self) -> None:
        if self.__median is None:
            self.__median = stats.median(self)
    @property
    def median(self) -> Num:
        if self.n <= 0: 
            return NaN
        self.__calc_median()
        return self.__median # [len(self.__median)//2]
    def __calc_stdev(self) -> None:
        if self.__stdev is None:
            self.__stdev = stats.stdev(self)
    @property
    def stdev(self) -> Num:
        if self.n <= 0: return NaN
        self.__calc_stdev()
        return self.__stdev
    def __calc_mode(self) -> None:
        if self.__mode is None:
            self.__mode = stats.mode(self)
    @property
    def mode(self) -> Num:
        if self.n <= 0: return NaN
        self.__calc_mode()
        return self.__mode
    def __len__(self) -> int:
        return self.n
    # def __iadd__(self,other):
    #     self.add(other)
    #     return self
    @property
    def str_label(self) -> str:
        "a label to go above the output of a .str call"
        return self.__summary_label_str
    @property
    def summary(self) -> Un[Tuple,NamedTuple,StatSummary]:
        return self.__summary_factory(self)
    @property
    def summary_str(self) -> str:
        """get the string but pretty and ready to fit in a 80 char wide line
        with a line header/label up to 12 chars wide/long"""
        return self.__summary_fmt_str.format(*self.summary)
    def __repr__(self) -> str:
        return f"StatRange(n={self.n:d},min={self.min:.2g},mean={self.mean:.4g},stdev={self.stdev:.6g},max={self.max:.2g})"
#? END class StatRange

SR_PERCENT_FMT: dict = {'summary_fmt_str': "{:>11.3g}% {:^12.4%} {:>11.3g}% {:>11.2g}% {:>11.2g}%",
                        'summary_label_str': f"{'mean%:':->12s}-{'stdev%:':-^12s}-{'median%:':->12s}-{'min%:':->12s}-{'max%:':->12s}",
                        'summary_factory': (lambda x: tuple([x.mean*100, x.stdev, x.median*100, x.min*100,x.max*100]))}
SR_PERCENT_FMT2: dict = {'summary_fmt_str': "{:>11.3g}% {:^11.4g}% {:>11.3g}% {:>11.2g}% {:>11.2g}%",
                         'summary_label_str': f"{'mean%:':->12s}-{'stdev%:':-^12s}-{'median%:':->12s}-{'min%:':->12s}-{'max%:':->12s}",
                         'summary_factory': (lambda x: tuple([x.mean*100, x.stdev*100, x.median*100, x.min*100,x.max*100]))}
SR_PPM_FMT: dict = {'summary_fmt_str': "{:>12.3g} {:^12.4g} {:>12.3g} {:>12.2g} {:>12.2g}",
                    'summary_label_str': f"{'mean:':->12s}-{'stdev:':-^12s}-{'median:':->12s}-{'min:':->12s}-{'max:':->12s}",
                    'summary_factory': (lambda x: tuple([x.mean*10**6, x.stdev*10**6, x.median*10**6, x.min*10**6,x.max*10**6]))}

JSON_t: Type = Un[list,dict,str,Num,None,bool]
JSON_OBJ_t: Type = Dict[str,JSON_t]
STATE_t: Type = Un[tuple,str]
RULE_t: Type = str # Un[str,JSON_OBJ_t]
NormState: Type = Callable[[JSON_t],STATE_t]


def get_state_not_simple(json:JSON_t) -> STATE_t:
    """Handler for producing a hashable state object to work with,
    when trace is not set to simple.
    i.e. it flattens the state to the same tuple that 
    a simple trace would have."""
    def check_json_obj_type(j:JSON_t,type_str:str) -> None:
        "raises Exception if json type does not match conv"
        if not isinstance(json,JSON_OBJ_t) or (
                '$type' in j
                    and j['$type'] != type_str):
            raise Exception("State was not represented as expected !!")
    state:list = list()
    class StateParse:
        "class is just to avoid python func def needs"
        @staticmethod
        def recur_record(rec:JSON_OBJ_t) -> None:
            for val in rec['fields']:
                check_json_obj_type(val,'kv-pair')
                StateParse.proc_val(val['value'])
        @staticmethod
        def recur_enum_array(arr:JSON_OBJ_t) -> None:
            for val in arr['elements']:
                check_json_obj_type(val,'kv-pair')
                StateParse.proc_val(val['value'])
        @staticmethod
        def recur_array(arr:JSON_OBJ_t) -> None:
            for val in arr['elements']:
                StateParse.proc_val(val['value'])
        @staticmethod
        def proc_val(val:JSON_OBJ_t) -> None:
            if '$type' not in val:
                raise Exception("State json struct is broken (for NOT-simple trace) !!")
            t_str:str = val['$type']
            if t_str == "record-val":
                StateParse.recur_record(val)
            elif t_str == "enum-array-value":
                StateParse.recur_enum_array(val)
            elif t_str == "array-value":
                StateParse.recur_array(val)
            else:
                state.append(val)
    StateParse.proc_val(json)
    return tuple(state)
#? END def get_state_not_simple: NormState


def get_state_simple(json:JSON_t) -> STATE_t:
    """handler for producing a hashable state object to work with, 
    when trace is set to simple.
    i.e. turns the flat list into a immutable tuple.
    NOTE: if DEBUG is true it will also raise error is `json`/the-state is not
    a flat list in the json."""
    if DEBUG:
        if not isinstance(json,list):
            raise Exception("state was not a simple state ``list'' !!")
        for val in json:
            if isinstance(val,dict) or isinstance(val,list):
                raise Exception("simple state contained a mutable object (dict/obj or list/array)")
    return tuple(json)
#? END def get_state_simple: NormState

@dataclass()
class ModelTransition:
    "simple dataclass representing a transition in the model"
    state: STATE_t
    rule: RULE_t
#? END dataclass ModelTransition

@dataclass(init=False)
class TraceData:
    """An immutable dataclass that takes the directory and name of a file in that dir,
    that is a either a "romp-trace" or a "romp-simple-trace"
    and extracts the relevant data from it for statistical processing."""
    id: TraceID
    romp_id: RompID
    seed: Un[str,int]
    rule_miss_streak: StatRange
    rule_hit_streak: StatRange
    state_miss_streak: StatRange
    state_hit_streak: StatRange
    depth: int
    tries: int
    is_valid: bool
    is_error: bool
    result: str
    unique_applied_rules: FSet[RULE_t]
    unique_rules: FSet[RULE_t]
    unique_applied_transitions: FSet[ModelTransition]
    unique_transitions: FSet[ModelTransition]
    unique_states: FSet[STATE_t]
    property_violated: Un[None,str,dict]
    property_violated_inside: Un[None,str,dict]
    active_time: Un[int,None]
    total_time: Un[int,None]
    def __init__(self,_trace_dir:str,_file_name:str) -> None:
        self.id: TraceID = None
        self.romp_id: RompID = None
        self.seed: Un[str,int] = None
        self.rule_miss_streak: StatRange = StatRange()
        self.rule_hit_streak: StatRange = StatRange()
        self.state_miss_streak: StatRange = StatRange()
        self.state_hit_streak: StatRange = StatRange()
        self.abs_state_miss_streak: StatRange = StatRange()
        self.abs_state_hit_streak: StatRange = StatRange()
        self.depth: int = 0
        self.tries: int = 0
        self.is_valid: bool = None
        self.is_error: bool = None
        self.result: str = None
        self.unique_applied_rules: FSet[RULE_t] = None
        self.unique_rules: FSet[RULE_t] = None
        self.unique_applied_transitions: FSet[ModelTransition] = None
        self.unique_transitions: FSet[ModelTransition] = None
        self.unique_states: FSet[STATE_t] = None
        self.property_violated: Un[None,str,dict] = None
        self.property_violated_inside: Un[None,str,dict] = None
        self.active_time: Un[int,None] = None
        self.total_time: Un[int,None] = None
        self.__process_trace_file(_trace_dir,_file_name)
    #? END def __init__()
    def __process_trace_file(self,_trace_dir:str,_file_name:str) -> None:
        with open(_trace_dir+'/'+_file_name,'r') as tf:
            json = j_load(tf)
        try :
            if json['$type'] not in ["romp-trace", "romp-simple-trace"]:
                raise Exception("Not a romp trace file")
            metadata = json['metadata']
            version = Version(json['$version'])
            self.romp_id = RompID(version,
                                metadata['model'],
                                int(metadata['romp-id']),
                                metadata['root-seed'],
                                metadata
                                )
            if version >= (0,0,2):
                self.id = TraceID(self.romp_id,
                                _trace_dir,_file_name,
                                int(json['trace-id']),
                                int(json['seed']),
                                int(json['start-id'])
                                )
            else:
                self.id = TraceID(self.romp_id,
                                _trace_dir,_file_name,
                                int(metadata['trace-id']),
                                int(metadata['seed']),
                                int(metadata['start-id'])
                                )
            get_state: NormState = get_state_simple if bool(metadata['simple-trace']) else get_state_not_simple
            rule_misses, rule_hits = 0, 0
            state_misses, state_hits = 0, 0
            abs_state_misses, abs_state_hits = 0, 0
            unique_states: Set[STATE_t] = set()
            unique_rules_applied: Set[str] = set()
            unique_applied_transitions: Set[ModelTransition] = set()
            unique_transitions: Set[ModelTransition] = set()
            unique_rules: Set[str] = set()
            state: STATE_t = get_state(json['trace'][0]['state'])
            unique_states.add(state)
            # self.depth += 1
            # self.tries += 1
            for elm in json['trace'][1:]:
                self.tries += 1
                rule = j_dump(elm['rule'])
                unique_rules.add(rule)
                unique_transitions.add(ModelTransition(state,rule))
                if elm['$type'] in ["rule-fail", "rule-miss"]: # CASE: rule miss
                    rule_misses += 1
                    if rule_hits > 0:
                        self.rule_hit_streak.add_data(rule_hits)
                        rule_hits = 0
                    # CASE: abs state miss
                    abs_state_misses += 1
                    if abs_state_hits > 0:
                        self.abs_state_hit_streak.add_data(abs_state_hits)
                        abs_state_hits = 0
                    continue
                # CASE: rule hit
                # self.depth += 1
                rule_hits += 1
                if rule_misses > 0:
                    self.rule_miss_streak.add_data(rule_misses)
                    rule_misses = 0
                unique_rules_applied.add(rule)
                state = get_state(elm['state'])
                if state in unique_states: # CASE: state miss
                    state_misses += 1
                    if state_hits > 0:
                        self.state_hit_streak.add_data(state_hits)
                        state_hits = 0
                    # CASE: abs state miss
                    abs_state_misses += 1
                    if abs_state_hits > 0:
                        self.abs_state_hit_streak.add_data(abs_state_hits)
                        abs_state_hits = 0
                    continue
                # CASE: state hit
                state_hits += 1
                if state_misses > 0:
                    self.state_miss_streak.add_data(state_misses)
                    state_misses = 0
                # CASE: abs state hit
                abs_state_hits += 1
                if abs_state_misses > 0:
                    self.abs_state_miss_streak.add_data(abs_state_misses)
                    abs_state_misses = 0
                unique_states.add(state)
                unique_applied_transitions.add(ModelTransition(state,rule))
            if rule_hits > 0:
                self.rule_hit_streak.add_data(rule_hits)
            if rule_misses > 0:
                self.rule_miss_streak.add_data(rule_misses)
            if state_hits > 0:
                self.state_hit_streak.add_data(state_hits)
            if state_misses > 0:
                self.state_miss_streak.add_data(state_misses)
            if abs_state_hits > 0:
                self.abs_state_hit_streak.add_data(abs_state_hits)
            if abs_state_misses > 0:
                self.abs_state_miss_streak.add_data(abs_state_misses)
            results = json['results']
            self.depth = int(results['depth'])
            if 'result' in results:
                self.result = results['result']
                self.is_valid = (self.result in ['COVER COMPLETE', 'MAX DEPTH REACHED', 'ATTEMPT LIMIT REACHED'])
                self.is_error = (self.result in ['PROPERTY VIOLATED', 'ASSUMPTION VIOLATED', 'ERROR STATEMENT REACHED', 'UNKNOWN ISSUE'])
            else:
                self.result = self.__patch_old_results(results)
                self.is_valid = bool(results['valid'])
                self.is_error = bool(results['is-error'])
            if results['property-violated'] is not None:
                if 'label' in results['property-violated'] :
                    self.property_violated = results['property-violated']['label']
                else: self.property_violated = j_dump(results['property-violated'])
            if results['tripped-inside'] is not None:
                if 'label' in results['tripped-inside']:
                    self.property_violated_inside = results['tripped-inside']['label']
                else: self.property_violated_inside = j_dump(results['tripped-inside'])
            self.property_violated_inside = results['tripped-inside']
            self.active_time = results['active-time']
            self.total_time = results['total-time']
            self.unique_states = frozenset(unique_states)
            self.unique_rules = frozenset(unique_rules)
            self.unique_applied_rules = frozenset(unique_rules_applied)
            self.unique_transitions = frozenset(unique_transitions)
            self.unique_applied_transitions = frozenset(unique_applied_transitions)
        except Exception as ex:
            if DEBUG:
                traceback.print_exc()
            raise RompTraceParseError(str(ex))
    #? END def __process_trace_file()
    def __patch_old_results(self,res:JSON_OBJ_t) -> str:
        if res['attempts-final'] <= 0:
            return "ATTEMPT LIMIT REACHED"
        if res['depth'] >= RompID.metadata['max-depth']:
            return "MAX DEPTH REACHED"
        if not res['valid'] and not res['is-error']:
            return "ASSUMPTION VIOLATED"
        if not res['valid'] and res['is-error']:
            return "PROPERTY VIOLATED"
        if res['valid'] and res['is-error']:
            return "ERROR REACHED"
        if ((res['valid'] and res['is-error']) and
                (res['property-violated'] is None and
                    res['tripped-inside'] is not None)):
            return "COVER COMPLETE"
        return "UNKNOWN ISSUE"
    #? END def patch_old_results(self,res:JSON_OBJ_t) -> str:
    @property
    def missed_rules(self) -> int:
        return self.tries - self.depth
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def rule_miss_rate(self) -> Num:
        return self.missed_rules / self.tries
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def rule_hit_rate(self) -> Num:
        return self.depth / self.tries
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def unique_state_count(self) -> Num:
        return len(self.unique_states)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def unique_rule_count(self) -> Num:
        return len(self.unique_rules)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def unique_applied_rule_count(self) -> Num:
        return len(self.unique_applied_rules)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def unique_tried_but_not_applied_rules(self) -> FSet[RULE_t]:
        return self.unique_rules - self.unique_applied_rules
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def unique_tried_but_not_applied_rule_count(self) -> Num:
        return len(self.unique_tried_but_not_applied_rules)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def never_tried_rule_count(self) -> Num:
        return self.romp_id.rule_count - len(self.unique_rules)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def unique_transition_count(self) -> Num:
        return len(self.unique_transitions)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def unique_applied_transition_count(self) -> Num:
        return len(self.unique_applied_transitions)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def unique_tried_but_not_applied_transitions(self) -> FSet[ModelTransition]:
        return self.unique_transitions - self.unique_applied_transitions
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def unique_tried_but_not_applied_transition_count(self) -> Num:
        return len(self.unique_tried_but_not_applied_transitions)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def never_tried_transition_count(self) -> Num:
        return self.romp_id.transition_count - len(self.unique_transitions)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def never_tried_rule_coverage(self) -> Num:
        return self.never_tried_rule_count / self.romp_id.rule_count
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def tried_but_never_applied_rule_coverage(self) -> Num:
        return self.unique_tried_but_not_applied_rule_count / self.romp_id.rule_count
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def tried_rule_coverage(self) -> Num:
        return self.unique_rule_count / self.romp_id.rule_count
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def applied_rule_coverage(self) -> Num:
        return self.unique_applied_rule_count / self.romp_id.rule_count
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def state_hit_rate(self) -> Num:
        if self.depth <= 0: return NaN
        return (self.unique_state_count-1) / (self.depth)
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def abs_state_hit_rate(self) -> Num:
        return self.unique_state_count / self.tries
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def state_miss_rate(self) -> Num:
        return 1 - self.state_hit_rate
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def abs_state_miss_rate(self) -> Num:
        return (self.tries - self.unique_state_count) / self.tries
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def state_coverage(self) -> Num:
        return self.unique_state_count / self.romp_id.possible_state_count
    #? END @property avg_miss_streak(self) -> Num:
    @property
    def start_id(self) -> int:
        return self.id.start_id
    #? END @property start_id(self) -> int:
    def __hash__(self) -> int:
        return hash(self.id)
    #? END def __hash__(self) -> int:
#? END @dataclass TraceData

@dataclass(init=False,eq=False,unsafe_hash=True,frozen=False)
class ModelResult:
    """A mutable dataclass that hold the data of many romp traces,
    and keeps running statistics of many of the data held within the 
    added TraceData entities.  
    (meant to be held and generated by a ModelResults class)"""
    id: RompID
    traces: Set[TraceID]
    # miss_streak: StatRange
    rule_miss_streak: StatRange
    rule_hit_streak: StatRange
    state_miss_streak: StatRange
    state_hit_streak: StatRange
    abs_state_miss_streak: StatRange
    abs_state_hit_streak: StatRange
    depth: StatRange
    missed_rules: StatRange
    tries: StatRange
    rule_hit_rate: StatRange
    rule_miss_rate: StatRange
    state_hit_rate: StatRange
    state_miss_rate: StatRange
    abs_state_hit_rate: StatRange
    abs_state_miss_rate: StatRange
    active_time: StatRange
    total_time: StatRange
    unique_state_count: StatRange
    unique_states: Set[STATE_t]
    unique_rule_count: StatRange
    unique_rules: Set[RULE_t]
    unique_applied_rule_count: StatRange
    unique_applied_rules: Set[str]
    avg_never_tried_but_never_applied_rule_count: StatRange
    unique_transition_count: StatRange
    unique_transitions: Set[ModelTransition]
    unique_applied_transition_count: StatRange
    avg_never_tried_but_never_applied_transition_count: StatRange
    unique_applied_transitions: Set[str]
    avg_never_tried_rule_count: StatRange
    avg_never_tried_but_never_applied_rule_coverage: StatRange
    avg_never_tried_rule_coverage: StatRange
    avg_tried_rule_coverage: StatRange
    avg_applied_rule_coverage: StatRange
    unique_startstates: Set[int]
    avg_state_coverage: StatRange
    properties_violated: Set[Un[None,str]]
    errors_found: int
    def __init__(self,_romp_id:RompID) -> None:
        self.id: RompID = _romp_id
        self.traces: Set[TraceID] = set()
        # self.miss_streak: StatRange = StatRange()
        self.rule_miss_streak: StatRange = StatRange()
        self.rule_hit_streak: StatRange = StatRange()
        self.state_miss_streak: StatRange = StatRange()
        self.state_hit_streak: StatRange = StatRange()
        self.abs_state_miss_streak: StatRange = StatRange()
        self.abs_state_hit_streak: StatRange = StatRange()
        self.depth: StatRange = StatRange()
        self.missed_rules: StatRange = StatRange()
        self.tries: StatRange = StatRange()
        self.rule_hit_rate: StatRange = StatRange(**SR_PERCENT_FMT)
        self.rule_miss_rate: StatRange = StatRange(**SR_PERCENT_FMT)
        self.state_hit_rate: StatRange = StatRange(**SR_PERCENT_FMT)
        self.state_miss_rate: StatRange = StatRange(**SR_PERCENT_FMT)
        self.abs_state_hit_rate: StatRange = StatRange(**SR_PERCENT_FMT)
        self.abs_state_miss_rate: StatRange = StatRange(**SR_PERCENT_FMT)
        self.active_time: Un[StatRange,None] = StatRange()
        self.total_time: Un[StatRange,None] = StatRange()
        self.unique_state_count: StatRange = StatRange()
        self.unique_states: Set[STATE_t] = set()
        self.unique_rule_count: StatRange = StatRange()
        self.unique_rules: Set[RULE_t] = set()
        self.unique_applied_rule_count: StatRange = StatRange()
        self.unique_applied_rules: Set[str] = set()
        self.avg_tried_but_never_applied_rule_count: StatRange = StatRange()
        self.unique_transition_count: StatRange = StatRange()
        self.unique_transitions: Set[ModelTransition] = set()
        self.unique_applied_transition_count: StatRange = StatRange()
        self.unique_applied_transitions: Set[str] = set()
        self.avg_tried_but_never_applied_transition_count: StatRange = StatRange()
        self.unique_startstates: Set[int] = set()
        self.avg_never_tried_rule_count: StatRange = StatRange()
        self.avg_tried_rule_coverage: StatRange = StatRange(**SR_PERCENT_FMT)
        self.avg_tried_but_never_applied_rule_coverage: StatRange = StatRange(**SR_PERCENT_FMT)
        self.avg_applied_rule_coverage: StatRange = StatRange(**SR_PERCENT_FMT)
        self.avg_never_tried_rule_coverage: StatRange = StatRange(**SR_PERCENT_FMT)
        self.avg_state_coverage: StatRange = StatRange()
        self.properties_violated: Set[Un[None,str]] = set()
        self.errors_found: int = 0
    #? END __init__()
    def add(self,trace:TraceData) -> None:
        if trace is None: 
            return None
        if not isinstance(trace, TraceData):
            raise Exception("ModelResult.add() : can only accept TraceData objects !!")
        if trace in self.traces:
            return None
        self.traces.add(trace)
        # self.miss_streak.add(trace.miss_streak.avg,trace.miss_streak.total)
        self.rule_miss_streak.add_data(trace.rule_miss_streak)
        self.rule_hit_streak.add_data(trace.rule_hit_streak)
        self.state_miss_streak.add_data(trace.state_miss_streak)
        self.state_hit_streak.add_data(trace.state_hit_streak)
        self.abs_state_miss_streak.add_data(trace.abs_state_miss_streak)
        self.abs_state_hit_streak.add_data(trace.abs_state_hit_streak)
        self.depth.add_data(trace.depth)
        self.missed_rules.add_data(trace.missed_rules)
        self.rule_hit_rate.add_data(trace.rule_hit_rate)
        self.rule_miss_rate.add_data(trace.rule_miss_rate)
        self.state_hit_rate.add_data(trace.state_hit_rate)
        self.state_miss_rate.add_data(trace.state_miss_rate)
        self.abs_state_hit_rate.add_data(trace.abs_state_hit_rate)
        self.abs_state_miss_rate.add_data(trace.abs_state_miss_rate)
        self.tries.add_data(trace.tries)
        if trace.total_time is not None:
            self.active_time.add_data(trace.active_time)
            self.total_time.add_data(trace.total_time)
        else:
            self.total_time, self.active_time = None, None
        self.unique_state_count.add_data(trace.unique_state_count)
        self.unique_states |= trace.unique_states
        self.unique_rule_count.add_data(trace.unique_rule_count)
        self.unique_rules |= trace.unique_rules
        self.unique_applied_rule_count.add_data(trace.unique_applied_rule_count)
        self.unique_applied_rules |= trace.unique_applied_rules
        self.unique_applied_transition_count.add_data(trace.unique_applied_transition_count)
        self.unique_applied_transitions |= trace.unique_applied_transitions
        self.avg_tried_but_never_applied_rule_count.add_data(trace.unique_tried_but_not_applied_rule_count)
        self.avg_never_tried_rule_count.add_data(trace.never_tried_rule_count)
        self.avg_tried_but_never_applied_transition_count.add_data(trace.unique_tried_but_not_applied_transition_count)
        self.avg_tried_transition_coverage.add_data(trace.tried_transition_coverage)
        self.avg_never_tried_transition_count.add_data(trace.never_tried_transition_count)
        self.avg_never_tried_rule_coverage.add_data(trace.never_tried_rule_coverage)
        self.avg_tried_rule_coverage.add_data(trace.tried_rule_coverage)
        self.avg_tried_but_never_applied_rule_coverage.add_data(trace.tried_but_never_applied_rule_coverage)
        self.avg_applied_rule_coverage.add_data(trace.applied_rule_coverage)
        self.avg_state_coverage.add_data(trace.state_coverage)
        self.unique_startstates.add(trace.start_id)
        if trace.property_violated is not None:
            self.properties_violated.add(trace.property_violated)
        if trace.is_error:
            self.errors_found += 1
    #? END def add() -> None:
    @property
    def trace_count(self) -> int:
        return len(self.traces)
    #? END @property trace_count() -> int:
    @property
    def abs_unique_state_count(self) -> int:
        return len(self.unique_states)
    #? END @property unique_state_count() -> int:
    @property
    def startstates_count(self) -> int:
        return len(self.unique_startstates)
    #? END @property unique_state_count() -> int:
    @property
    def abs_state_coverage(self) -> Num:
        return len(self.unique_states) / self.possible_state_count
    #? END @property unique_state_count() -> int:
    @property
    def abs_unique_rule_count(self) -> int:
        return len(self.unique_rules)
    #? END @property unique_state_count() -> int:
    @property
    def abs_unique_applied_rule_count(self) -> int:
        return len(self.unique_applied_rules)
    #? END @property unique_state_count() -> int:
    @property
    def unique_tried_but_not_applied_rules(self) -> FSet[RULE_t]:
        return frozenset(self.unique_rules - self.unique_applied_rules)
    #? END @property unique_state_count() -> int:
    @property
    def unique_tried_but_not_applied_rule_count(self) -> int:
        return len(self.unique_tried_but_not_applied_rules)
    #? END @property unique_state_count() -> int:
    @property
    def abs_never_tried_rule_count(self) -> int:
        return self.id.rule_count - len(self.unique_rules)
    #? END @property unique_state_count() -> int:
    @property
    def abs_unique_transition_count(self) -> int:
        return len(self.unique_transitions)
    #? END @property unique_state_count() -> int:
    @property
    def abs_unique_applied_transition_count(self) -> int:
        return len(self.unique_applied_transitions)
    #? END @property unique_state_count() -> int:
    @property
    def unique_tried_but_not_applied_transitions(self) -> FSet[RULE_t]:
        return frozenset(self.unique_transitions - self.unique_applied_transitions)
    #? END @property unique_state_count() -> int:
    @property
    def unique_tried_but_not_applied_transition_count(self) -> int:
        return len(self.unique_tried_but_not_applied_transitions)
    #? END @property unique_state_count() -> int:
    @property
    def abs_never_tried_transition_count(self) -> int:
        return self.id.transition_count - len(self.unique_transitions)
    #? END @property unique_state_count() -> int:
    @property
    def abs_rule_coverage(self) -> Num:
        return len(self.unique_rules) / self.id.rule_count
    #? END @property unique_state_count() -> int:
    @property
    def error_detection_rate(self) -> Num:
        return self.errors_found / len(self.traces)
    @property
    def metadata(self) -> dict:
        return self.id.metadata
    @property
    def do_symmetry(self) -> bool:
        return self.metadata['symmetry-reduction']
    @property
    def possible_state_count(self) -> bool:
        return self.metadata['possible-state-count']
    #? END @property unique_state_count() -> int:
    # def __hash__(self) -> int:
    #     return hash(self.id)
    # #? END def __hash__(self) -> int:
    # def __eq__(self,other) -> int:
    #     return isinstance(other,ModelResult) and hash(self) == hash(other)
    # #? END def __eq__(self) -> int:
    # def __ne__(self,other) -> int:
    #     return not self == other
    # #? END def __ne__(self) -> int:
    def __str__(self) -> str:
        if self.total_time is not None:
            time_label = self.total_time.str_label
            t_time = self.total_time.summary_str
            a_time = self.active_time.summary_str
        else:
            time_label = StatRange.DEFAULT_SUMMARY_LABEL_STR
            t_time = f"{'n/a':>12s} {'n/a':^12s} {'n/a':>12s} {'n/a':>12s} {'n/a':>12s}"
            a_time = t_time
        timeU = "({self.id.time_unit})"
        return (f"{'='*80}\n"
                f"  {self.id!s:^76s}  \n"
                f"  {'-'*76}  \n"
                f"      walks: {len(self.traces):<67d}\n"
                f"  max-depth: {self.metadata['max-depth']:<67d}\n"
                f"  symmetry?: {self.do_symmetry!s:<67s}\n"
                f"    {'TIME:':_^72}\n"
                f"{timeU:>11}  {time_label:-<66s}\n"
                f"     active: {a_time!s:<67s}\n"
                f"      total: {t_time!s:<67s}\n"
                f"    {'ERRORS:':_^72}\n"
                f"     #-disc: {self.errors_found:<67g}\n"
                f"       rate: {self.error_detection_rate:<67.2g}\n"
                f"    {'RULES:':_^72}\n"
                f"             {self.unique_rule_count.str_label:-<66s}\n"
                f"      tried: {self.unique_rule_count.summary_str:<67s}\n"
                f"    applied: {self.unique_applied_rule_count.summary_str:<67s}\n"
                f"    tr - ap: {self.avg_tried_but_never_applied_rule_count.summary_str:<67s}\n"
                f"      never: {self.avg_never_tried_rule_count.summary_str:<67s}\n"
                f"   possible: {self.id.rule_count:<67,d}\n"
                f"    |tried|: {self.abs_unique_rule_count:<67d}\n"
                f"  |applied|: {self.abs_unique_applied_rule_count:<67d}\n"
                f"  |tr - ap|: {self.unique_tried_but_not_applied_rule_count:<67d}\n"
                f"    |never|: {self.abs_never_tried_rule_count:<67d}\n"
                f"   COVERAGE  {self.avg_applied_rule_coverage.str_label:-<66s}\n"
                f"      tried: {self.avg_tried_rule_coverage.summary_str:<67s}\n"
                f"    applied: {self.avg_applied_rule_coverage.summary_str:<67s}\n"
                f"    tr - ap: {self.avg_tried_but_never_applied_rule_coverage.summary_str:<67s}\n"
                f"      never: {self.avg_never_tried_rule_coverage.summary_str:<67s}\n"
                f" |coverage|: {self.abs_rule_coverage:<12.2%}\n"
                f"             {self.depth.str_label:-<66s}\n"
                f"       hits: {self.depth.summary_str:<67s}\n"
                f"     misses: {self.missed_rules.summary_str:<67s}\n"
                f"      tries: {self.tries.summary_str:<67s}\n"
                f"             {self.rule_hit_rate.str_label:-<66s}\n"
                f"   hit-rate: {self.rule_hit_rate.summary_str:<67s}\n"
                f"  miss-rate: {self.rule_miss_rate.summary_str:<67s}\n"
                f"    STREAKS  {self.state_hit_streak.str_label:-<66s}\n"
                f"       hits: {self.rule_hit_streak.summary_str:<67s}\n"
                f"     misses: {self.rule_miss_streak.summary_str:<67s}\n"
                f"    {'STATES:':_^72}\n"
                f"             {self.unique_state_count.str_label:-<66s}\n"
                f"      found: {self.unique_state_count.summary_str:<67s}\n"
                f"   possible: {self.possible_state_count:<67.9g}\n"
                f"    |found|: {self.abs_unique_state_count:<67,d}\n"
                f"             {self.avg_state_coverage.str_label:-<66s}\n"
                f"   coverage: {self.avg_state_coverage.summary_str:<67s}\n"
                f" |coverage|: {self.abs_state_coverage:<12.4g}\n"
                f"             {self.state_hit_rate.str_label:-<66s}\n"
                f"   hit-rate: {self.state_hit_rate.summary_str:<67s}\n"
                f"  miss-rate: {self.state_miss_rate.summary_str:<67s}\n"
                f"    |hit-r|: {self.abs_state_hit_rate.summary_str:<67s}\n"
                f"   |miss-r|: {self.abs_state_miss_rate.summary_str:<67s}\n"
                f"    STREAKS  {self.state_hit_streak.str_label:-<66s}\n"
                f"       hits: {self.state_hit_streak.summary_str:<67s}\n"
                f"     misses: {self.state_miss_streak.summary_str:<67s}\n"
                f"     |hits|: {self.abs_state_hit_streak.summary_str:<67s}\n"
                f"   |misses|: {self.abs_state_miss_streak.summary_str:<67s}\n"
                f"    {'TRANSITIONS:':_^72}\n"
                f"             {self.unique_transition_count.str_label:-<66s}\n"
                f"      tried: {self.unique_transition_count.summary_str:<67s}\n"
                f"    applied: {self.unique_applied_transition_count.summary_str:<67s}\n"
                f"    tr - ap: {self.avg_tried_but_never_applied_transition_count.summary_str:<67s}\n"
                f"      never: {self.avg_never_tried_transition_count.summary_str:<67s}\n"
                # f"   possible: {self.id.transition_count:<67.9g}\n"
                f"    |tried|: {self.abs_unique_transition_count:<67.3g}\n"
                f"  |applied|: {self.abs_unique_applied_transition_count:<67.3g}\n"
                f"  |tr - ap|: {self.unique_tried_but_not_applied_transition_count:<67.3g}\n"
                # f"    |never|: {self.abs_never_tried_transition_count:<67.4g}\n"
                f"    {'PROPS:':_^72}\n"
                f" #-violated: {len(self.properties_violated):<67d}\n" 
            #     f"       list: " +
            #    [f"           "  for i in self.properties_violated].join('\n') +
                f"{'='*80}\n")
    #? END def __str__(self) -> str:
#? END @dataclass ModelResult

class ModelResults(Dict[RompID,ModelResult]):
    """The holder class of multiple ModelResult objects.
    Keeping track and care to not add traces not belonging to
    the same model to any existing model."""
    def add(self,trace:Un[TraceData,None]) -> None:
        if trace is None: return None
        if not isinstance(trace, TraceData):
            raise Exception("ModelResults.add() : can only accept TraceData objects !!")
        if trace.romp_id not in self:
            self.update({trace.romp_id: ModelResult(trace.romp_id)})
        self[trace.romp_id].add(trace)
    #? END def add() -> None
#? END class ModelResults


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
#? END def fs_DFS() -> List[str]

def genTraceData(path:str) -> Un[TraceData,None]:
    dir_name, file_name = os.path.split(path)
    if not file_name.endswith('.json'): return None
    try:
        return TraceData(dir_name,file_name)
    except RompTraceParseError as te:
        print(f"{path:<16s} :parse-error: {te!s}")
    except Exception as ex:
        print(f"{path:<16s} :exception: {ex!s}")
    except:
        print(f"{path:<16s} :???-error: ???")
    return None # error occurred return none
#? END def genTraceData() -> Un[TraceData,None]

def process_data(trace_dir:str) -> ModelResults:
    results = ModelResults()
    file_paths = fs_DFS(trace_dir,fileCallback=lambda p: results.add(genTraceData(p)))
    return results
#? END def process_data() -> ModelResults:
    

def print_results(results:ModelResults) -> None:
    print()
    for key in results:
        if DEBUG:
            print(tuple(results[key].depth))
            # states = list(results[key].unique_states)
            # for i in range(0,len(states)):
            #     for j in range(i+1,len(states)):
            #         if len(states[i]) != len(states[j]):
            #             print("state repr error!! (uneven lengths found)")
            #         if all(i_val==j_val for i_val,j_val in zip(states[i],states[j])):
            #             print("duplicate state found !!", states[i])
        print(results[key])
#?END def print_results() -> None:



def main() -> None:
    '''perform the functionality of the code'''
    trace_dir = "./traces"
    if (len(argv) >= 2):
        trace_dir = argv[1].strip()
        while trace_dir[-1] in '/\\':
            trace_dir = trace_dir[:len(trace_dir)-1]
    results = process_data(trace_dir)
    print_results(results)
#? END def main() -> None

if __name__ == "__main__":
    if DEBUG:
        _t = StatRange()
        if _t is None:
            print("StatRange() returns None")
        # print(repr(StatRange()))
        print(StatSummary(0,0,0,0,0))
    main()

