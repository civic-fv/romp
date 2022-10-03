#!/usr/bin/python3

from os import system as run_cmd, path
from sys import argv
from trace_stats import ModelResults, process_data, ModelResult
from typing import Tuple, NamedTuple, Type
from time import time


DEBUG: bool = False

class SymTestData(NamedTuple):
    """Named Tuple containing the sym and no_sym trace_stats.ModelResult objects
    from a symmetry test comparison of romp."""
    sym: ModelResult
    no_sym: ModelResult
    def print(self) -> None:
        """PrettyPrint this object to the console"""
        for l_s,l_n in zip(str(self.sym).split('\n'),str(self.no_sym).split('\n')):
            print(f"{l_s:<80s} || {l_n:<80s}")
    #? END def print(self) -> None:
#? END NamedTuple SymData





def run_tests(model_path:str, test_args:str="-s '{}' -d 2000 -w 128",
              trace_dir:str="./traces", romp_path:str="build/romp/romp",
              cc:str="g++", cc_args:str="-O2 -w"
              ) -> SymTestData:
    """Given the location of a murphi file generate a romp model-checker
    and then compile and run it with and without symmetry reduction enabled.
    Then use the trace_stats module to generate the Model results from the
    two tests and return those semi processed data bundles.

    Args:
        - model_path (str): _file path to murphi model to use for the test_
        - test_args (str, optional): _additional arguments to pass to the checker._
                                    Defaults to "-s '{}' -d 2000 -w 128".
        - trace_dir (str, optional): _the directory_.
                                    Defaults to "./traces".
        - romp_path (str, optional): _name/path to romp tool_.
                                    Defaults to "build/romp/romp".
        - cc (str, optional): _path/name of the C++ compiler to use_.
                                    Defaults to "g++".
        - cc_args (str, optional): _additional arguments to pass to the C++ compiler_.
                                    Defaults to "-O2 -w".

    Returns:
        SymTestData(sym:ModelResult,no_sym:ModelResult): _NamedTuple of the model Results \
         from the two runs._

    Throws:
        Exception: whenever a system call returns a non-zero return value, \
        signalling that something went wrong while using an external tool.
        See exception message for more details on what and where error occurred.
    """
    root_seed = f"{int(time()):x}"
    if "{}" in test_args:
        test_args = test_args.format(root_seed)
    elif "%s" in test_args:
        test_args = test_args % root_seed
    trace_dir = path.join(trace_dir,root_seed)
    # generate model checker
    ret = run_cmd(f"{romp_path} --simple-trace --do-measure "
                  f"-s -o{model_path}.sym.test.cpp {model_path}" +
                   " >/dev/null 2>&1" if not DEBUG else "")
    if ret != 0:
        raise Exception("romp failed to generate model-checker!")
    # build no sym model
    ret = run_cmd(f"{cc} {cc_args} -pthread "
                  f"-o{model_path}.nosym.test {model_path}.sym.test.cpp" +
                   " >/dev/null 2>&1" if not DEBUG else "")
    if ret != 0:
        raise Exception("`{cc}` failed to build the model-checker")
    # build sym model
    ret = run_cmd(f"{cc} {cc_args} -pthread -D__romp__ENABLE_symmetry "
                  f"-o{model_path}.sym.test {model_path}.sym.test.cpp" +
                   " >/dev/null 2>&1" if not DEBUG else "")
    if ret != 0:
        raise Exception("`{cc}` failed to build the model-checker (w/ symmetry flag)")
    sym_t_dir = path.join(trace_dir,path.basename(model_path)+'_sym')
    no_sym_t_dir = path.join(trace_dir,path.basename(model_path)+'_nsym')
    # run sym model checker
    ret = run_cmd(f"{model_path}.sym.test {test_args} -t '{sym_t_dir}' -y" +
                   " >/dev/null 2>&1"  if not DEBUG else "")
    if ret != 0:
        raise Exception("error while running symmetric model-checker")
    # run no sym model checker
    ret = run_cmd(f"{model_path}.nosym.test {test_args} -t '{no_sym_t_dir}' -y" +
                   " >/dev/null 2>&1"  if not DEBUG else "")
    if ret != 0:
        raise Exception("error while running non-symmetric model-checker")

    results = process_data(trace_dir)
    sym,no_sym = None, None
    if len(results) != 2 :
        raise Exception(f"Error :: found unexpected trace data in trace dir !! (n={len(results)})")
    for key in results:
        res = results[key]
        if res.do_symmetry:
            if sym is not None:
                raise Exception("ERROR :: more than one sym trace !!")
            sym = res
        else:
            if no_sym is not None:
                raise Exception("ERROR :: more than one no sym trace !!")
            no_sym = res
    if sym is None:
        raise Exception("ERROR :: missing sim trace data !!")
    if no_sym is None:
        raise Exception("ERROR :: missing no sim trace data !!")

    return SymTestData(sym,no_sym)
#? END def run_tests() -> SymData:



def main() -> None:
    '''do the task'''
    i = len(argv) - 1
    cc_args = '-O2 -w'
    if i == 6:
        cc_args = argv[i]
        i -= 1
    cc = 'g++'
    if i == 5:
        cc = argv[i]
        i -= 1
    romp_path = 'build/romp/romp'
    if i == 4:
        romp_path = argv[i]
        i -= 1
    trace_dir = './traces'
    if i == 3:
        trace_dir = argv[i]
        i -= 1
    romp_args = None
    if i == 2:
        romp_args = argv[i] if argv[i] != '' else None
        i -= 1
    if i == 1:
        model_path = argv[i]
    else:
        print("ERROR no model was provided!")
        return

    data = run_tests(model_path,romp_args,
                     trace_dir,romp_path,
                     cc,cc_args)
    data.print()
#? END def main() -> None


if __name__ == "__main__":
    main()



