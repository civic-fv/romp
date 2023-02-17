from os import system, makedirs, listdir
from typing import List, Union as Un, Dict
from pathlib import Path
from dataclasses import dataclass
import sys
from datetime import datetime
from random import randint
import copy

# turn on debug messages (also turns on debug messages in generated files)
DEBUG = False

# should the tests include a run of valgrind's cachegrind tool (more than doubles run time of generated test scripts)
ENABLE_CACHEGRIND = False

# set this to True if you want to just run all murphi models in the current directory
DO_ALL_MODELS = True

# this only changes file paths for debugging purposes and won't make a script that can run locally
DO_SLURM = True



@dataclass
class GeneratorConfigOption:
    value: str


@dataclass
class CompilerConfigOption:
    value: str


@dataclass
class ModelCheckerConfigOption:
    value: str


class SlurmConfigOption:
    value: str


ConfigOpt_t = Un[None, GeneratorConfigOption,
                 CompilerConfigOption, ModelCheckerConfigOption]
Params_t = Dict[str, List[ConfigOpt_t]]
Config_t = Dict[str, ConfigOpt_t]

GCO = GeneratorConfigOption
CCO = CompilerConfigOption
MCO = ModelCheckerConfigOption

# << =========================================================================================== >>
# <<                                        GLOBAL CONFIG                                        >>
# << =========================================================================================== >>

CC = "gcc"
CXX = "g++"

CXX_PARAMS = "-std=c++17 -O3 -pthread"
CC_PARAMS = "-march=native -O3 -pthread"

INIT_TIME:datetime = datetime.now() 
INIT_TIME_STR:str = INIT_TIME.strftime("%y-%m-%d_%H-%M-%S")

LOCAL_SAVE_PATH = "./test_results"
CHPC_SAVE_PATH = "/scratch/general/vast/u1350795/romp"
SAVE_PATH = Path((CHPC_SAVE_PATH if DO_SLURM else LOCAL_SAVE_PATH) + '/' + INIT_TIME_STR).absolute()
ROMP = str(Path("../build/romp/romp").absolute())
ROMP_PARAMS: Params_t = {"symmetry": [None, GCO('-s')],
                         "trace": [MCO(f'-t {SAVE_PATH}/romp/traces'), None],
                         "trace-comp": [GCO('--simple-trace-rep')],
                         "seed": [None, None, MCO('-s scrappy'), MCO('-s 1234567890'), MCO(f'{INIT_TIME_STR}'), MCO(f'{randint(0,sys.maxsize):0X}'), MCO(str(randint(0,sys.maxsize)))],
                         "walkers":[None,MCO("-w 512"),MCO("-w 1024"),MCO("-w 2048"),MCO("-w 4096"),MCO("-w 8192"), MCO("-w 16384")],
                         "depth":[None,MCO("-d 512"),MCO("-d 1024"),MCO("-d 2048"),MCO("-d 4096"),MCO("-d 8192"), MCO("-d 16384"),MCO("-d 32768")],
                         "bfs": [None,MCO("-bfs s 1"), MCO("-bfs s 16"), MCO("-bfs s 64"), MCO("-bfs s 256"),MCO("-bfs m 1"), MCO("-bfs m 16"), MCO("-bfs m 64"), MCO("-bfs m 256")],
                         "attempt-limit":[None,MCO("-ll"),MCO("-ll 4096")],
                         "launch":[MCO('-y')]}
ROMP_CONFIGS: ConfigGenerator = ConfigGenerator(ROMP, CXX, CXX_PARAMS, ROMP_PARAMS, ALL_MODELS, "romp")

CMURPHI = str(Path("../../cmurphi/src/mu").absolute())
CMURPHI_PARAMS: Params_t = {"HashCompaction": [GCO("-c"), None], "BitCompaction": [GCO("-b"), None],
                            "MemLimit":[MCO("-m10000")], "trace-DFS": [MCO("ON"), MCO("OFF")],
                            "deadlock":[GCO("--deadlock-detection "+i) for i in ["off", "stuck", "stuttering"]]}  # TODO make this option match cmurphi man/help page
CMURPHI_CONFIGS: ConfigGenerator = ConfigGenerator(CMURPHI, CXX, CXX_PARAMS, CMURPHI_PARAMS, ALL_MODELS, "cm")

RUMUR = str(Path("../../rumur/build/rumur/rumur").absolute())
RUMUR_PARAMS: Params_t = {"symmetry": [GCO("--symmetry-reduction="+i) for i in ["heuristic", "exhaustive", "off"]],
                          # TODO make this option match rumur man/help page
                          "bound": [None,GCO("--bound=4096"),GCO("--bound=8192"),GCO("--bound=16384")]}  # TODO make this option match rumur man/help page
RUMUR_CONFIGS = ConfigGenerator(RUMUR, CC, CC_PARAMS, RUMUR_PARAMS,
                                [i for i in ALL_MODELS if not (
                                    "dash.m" in i or "-flow.m" in i or "multi.m" in i)],
                                "ru")

PASSES: int = 8

SBATCH_PARMAS: str = f'''
#SBATCH -M kingspeak
#SBATCH --account=ganesh
#SBATCH --partition=kingspeak-shared
#SBATCH --nodes=4
#SBATCH -C c16
#SBATCH -c 16
#SBATCH --exclusive
#SBATCH --time=12:00:00
#SBATCH --mail-type=FAIL
#SBATCH --mail-user=ajanthav10@gmail.com '''
# SBATCH_PARMAS: str = "-M kingspeak --account=ganesh --partition=kingspeak-shared --nodes=2 --ntasks=8 -C c16 -c 16 --exclusive --time=12:00:00 --mail-type=FAIL --mail-user=ajanthav10@gmail.com"

ALL_MODELS: List[str] = [
    "./adash.m"
] if not DO_ALL_MODELS else [ Path(i) for i in listdir('./') if i[-2::] == '.m']

SLURM_TEMPLATE:str = f"""#!/usr/bin/bash
{SBATCH_PARMAS}
#SBATCH --array={{job_arr}}

_EXT="{{ext}}"
TEST_DIR="{SAVE_PATH}/$_EXT"
TEST_RUNS={PASSES}


cd "$TEST_DIR"
mkdir -p "$SLURM_JOB_ID"
cd "$SLURM_JOB_ID"

python3 "../job.py" "$SLURM_JOB_ID" "$TEST_RUNS"

cd ..
rm -rf "$SLURM_JOB_ID"
cd ..

"""

PY_JOB_TEMPLATE:str = f"""#!/usr/bin/python3

from os import system
from sys import argv
from time import perf_counter_ns

DEBUG: bool = {DEBUG!s}

ENABLE_CACHEGRIND: bool = {ENABLE_CACHEGRIND!s}

SLURM_JOB_ID: int = int(argv[1])
TEST_RUNS: int = int(argv[2])

EXT: str = "%s"
SAVE_LOC:str = "{SAVE_PATH}/"+EXT
JOBS = [
    %s
]

JOB = JOBS[SLURM_JOB_ID]

def main():
    if DEBUG:
        print('[' + str(JOB['index']) + "] GENERATING: `" + JOB['model'] + '`')
    system(JOB['gen'] + "" if DEBUG else " > /dev/null")
    if DEBUG:
        print('[' + str(JOB['index']) + "] COMPILING: `" + JOB['model'] + '`')
    system(JOB['comp'] + "" if DEBUG else " > /dev/null")
    if DEBUG:
        print('[' + str(JOB['index']) + "] RUNNING: `" + JOB['model'] + "` x" + str(TEST_RUNS))
    for i in range(TEST_RUNS):
        outfile = (SAVE_LOC + '/' + str(JOB['index']) + '-' + str(i)
                    + '__' + JOB['model'] + '.' + EXT)
        start = perf_counter_ns()
        system(JOB['run'] + ' > "' + outfile + '.txt"')
        time = start - perf_counter_ns()
        with open(outfile + '.txt','a') as file:
            file.write('\nTIME_NS=' + str(time) + '\n')
        if ENABLE_CACHEGRIND:
            system(JOB['cachegrind'] + ' > "' + outfile + '.cache.txt"')
    if DEBUG:
        print('[' + str(JOB['index']) + "] FINISHED: `" + JOB['model'] + "` x" + str(TEST_RUNS))
    pass

if __name__ == "__main__":
    main()

"""
# SPIN_PARAMS  = {} # TODO: add this when we work with everything else

# << =========================================================================================== >>
# <<                                      LAUNCH GENERATORS                                      >>
# << =========================================================================================== >>


# << =========================================================================================== >>
# <<                                       GENERATOR CODE                                        >>
# << =========================================================================================== >>

class ConfigGenerator:
    """To generate the configuration for the testing ROMP"""

    def __init__(self, modgen: str, comp: str, comp_params: str, params: Params_t, models: List[str], exe_ext: str = None) -> None:
        self._modgen: str = modgen
        self._exe_ext: str = Path(modgen).stem if exe_ext is None else exe_ext
        self._src_ext: str = "cpp" if "++" in comp else "c"
        self._comp: str = comp
        self._comp_params: str = comp_params
        self._PARAMS: Params_t = dict(params)
        self._models: List[Path] = [Path(i) for i in models]
        self._param_keys: List[str] = list(self._PARAMS.keys())
        self._param_keys.sort()  # might not need to sort these
        self._index: int = None
        self._i: int = None  # model
        # self._j: int = None # param key
        # self._jj: int = None # next param key
        # self._kk: int = None # next param value
        self._ks: List[int] = None  # param value
        self._config: Config_t = None
        self._len: int = self._calc_len()

    @property
    def PARAMS(self) -> dict:
        return self._PARAMS

    @property
    def index(self) -> int:
        return self._index
    
    @property
    def exe_ext(self) -> str:
        return self._exe_ext

    # def _create_config(self) -> None:
    #     self._config = { key: l[0] for (key,l) in self._PARAMS.items() }

    def _update_config(self) -> None:
        self._config = {self._param_keys[j]: self._PARAMS[self._param_keys[j]][self._ks[j]] for j in range(len(self._param_keys))}
        # self._config[self._param_keys[k]] = self._PARAMS[self._param_keys[k]][j]

    def set_config(self,config:dict) -> None:
        self._config = config

    @property
    def config(self) -> dict:
        if self._config is None:
            raise Exception("config not generated")
        return self._config
    
    @property
    def model(self) -> Path:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        return self._models[self._i]

    @property
    def gen_cmd(self) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = f"{SAVE_PATH}/{self._exe_ext}/{self._models[self._i].stem}"
        other_opts = ' '.join(
            [i.value for i in self._config.values() if isinstance(i, GeneratorConfigOption)])
        if self._modgen[-3::] == "/mu":
            return f"{self._modgen} {other_opts} '{self.model.absolute()}'"
        return f"{self._modgen} {other_opts} -o '{base_model}.{self._src_ext}' '{self.model.absolute()}'"
        # note CMurphy does not accept -o or any output config details (because its annoying and poorly made)

    @property
    def comp_cmd(self) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = f"{SAVE_PATH}/{self._exe_ext}/{self._models[self._i].stem}"
        other_opts = ' '.join(
            [i.value for i in self._config.values() if isinstance(i, CompilerConfigOption)])
        return f"{self._comp} {self._comp_params} {other_opts} -o '{base_model}.{self._index}.{self._exe_ext}' '{base_model}.{self._src_ext}'"

    # def sbatch_cmd(self, slurmOpts: str, outdir:str) -> str:
    #     if self._index is None:
    #         raise Exception("ConfigGenerator not in iterator mode!!")
    #     base_model = f"{SAVE_PATH}/{self._exe_ext}/{self._models[self._i].stem}"
    #     launch_opts = ' '.join([i.value for i in self._config.values(
    #     ) if isinstance(i, ModelCheckerConfigOption)])
    #     return (f"time {base_model.absolute()}.{self._index}.{self._exe_ext} {launch_opts} "
    #             f"> {outdir}/{base_model}__{self._exe_ext}__{self._index}_%j.txt")
    
    @property 
    def launch_cmd(self) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = f"{SAVE_PATH}/{self._exe_ext}/{self._models[self._i].stem}"
        launch_opts = ' '.join([i.value for i in self._config.values(
        ) if isinstance(i, ModelCheckerConfigOption)])
        return (f"{base_model}.{self._index}.{self._exe_ext} {launch_opts}")
    
    @property
    def cachegrind_cmd(self) -> str:
        return (f"valgrind --tool=cachegrind {self.launch_cmd}")

    def _calc_len(self) -> int:
        _len = len(self._models)
        for values in self._PARAMS.values():
            _len *= len(values)
        self._len = _len
        return self._len

    def __len__(self) -> int:
        return self._len

    def __item__(self, index):
        other = copy.deepcopy(self)
        other.__iter__()
        while other._index < index:
            other.__next__()
        return other

    def __iter__(self):
        self._index = 0
        self._i = 0  # model index
        self._ks = [0 for i in range(len(self._param_keys))] # category value index
        self._update_config()
        return self

    def __next__(self):
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        if self._index >= len(self) or self._index < 0:
            raise StopIteration
        self._index += 1
        if self._next_rec():
            self._i += 1
            self._ks = [0 for i in range(len(self._param_keys))]
            if self._i >= len(self._models):
                raise StopIteration
        self._update_config()
        return self

    def _next_rec(self, j: int = 0) -> bool:
        if j >= len(self._param_keys):
            return True
        self._ks[j] += 1
        if self._ks[j] >= len(self.PARAMS[self._param_keys[j]]):
            self._ks[j] = 0
            return self._next_rec(j+1)
        return False


def gen_tests(cg: ConfigGenerator, outputDir: Path) -> None:
    outputDir = Path(str(outputDir.absolute()) + '/' + cg.exe_ext)
    try:
        makedirs(outputDir)
    except Exception as ex:
        print("ERROR : Failed to create new directory (could already exist)")
        return
    jobs: str = ""
    sep: str = ""
    for i in cg:
        jobs += sep

        jobs += ("{"
                 f"'index':{i.index},"
                 f"'model':\"{i.model.stem}\","
                 f"'gen':\"{i.gen_cmd}\","
                 f"'comp':\"{i.comp_cmd}\","
                 f"'run':\"{i.launch_cmd}\","
                 f"'cachegrind':\"{i.cachegrind_cmd}\""
                 "}")
                    # % i._index, i.model.stem, i.gen_cmd, i.comp_cmd, i.launch_cmd, i.cachegrind_cmd)
        if DEBUG:
            print("Writing :", i.index)
            
        sep = ",\n    "
        
    with open(str(outputDir)+"/job.py",'w') as py_file:
        py_file.write(PY_JOB_TEMPLATE % (cg.exe_ext, jobs))
    with open(str(outputDir)+"/launch.slurm",'w') as slurm_file:
        slurm_file.write(SLURM_TEMPLATE.format(job_arr=f"0-{len(cg)-1}", ext=cg.exe_ext))
#? END def gen_tests() -> None       


def main(args) -> None:
    gen_tests(ROMP_CONFIGS, SAVE_PATH)
    gen_tests(CMURPHI_CONFIGS, SAVE_PATH)
    gen_tests(RUMUR_CONFIGS, SAVE_PATH)

    print(f"Finished generating tests")
    print(f"  Time Taken: {(datetime.now()-INIT_TIME).total_seconds!s:s}s")
    print(f"      OutDir: {SAVE_PATH}")
    print(f"   RunCmd(s): ..TODO..\n")

if __name__ == "__main__":
    main(sys.argv)
