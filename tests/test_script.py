from os import system, makedirs
from typing import List, Union as Un, Dict
from pathlib import Path
from dataclasses import dataclass
import sys
from datetime import datetime

DEBUG = False
DO_SLURM = False

"""
NOTE:
    If you want to run this locally I recommend running it with the `nohup` command 
     to allow to ssh in and leave the session and still have it finish running.
"""

"""TODOs & known issues:
    -[X] romp needs way to pass in random seeds
       - put in a handful of seeds as the options for the seed flag
    -[X] cmurphi doesn't have an -o option for generating
       - maybe just use default output for all generators
    -[X] launch needs to handle errors during generation building and launching
    -[ ] Figure out how to identify the output of each job
        - make file names: `YY-MM-DD-HH-MM-SS__model__tool__index_jid.txt`
        - make file names: `YY-MM-DD-HH-MM-SS/model__tool__index_jid.txt`
"""


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

INIT_TIME = datetime.now().strftime("%y-%m-%d_%H-%M-%S")

LOCAL_SAVE_PATH = "./test_results/" + INIT_TIME
CHPC_SAVE_PATH = "/scratch/general/vast/u1350795/romp/" + INIT_TIME
ROMP = "../build/romp/romp"
ROMP_PARAMS: Params_t = {"symmetry": [None, GCO('-s')],
                         "trace": [MCO(f'-t {CHPC_SAVE_PATH if DO_SLURM else LOCAL_SAVE_PATH}'), None],
                         "trace-comp": [GCO('--simple-trace-rep')],
                         "seed": [None, MCO('-s scrappy'), MCO('-s 1234567890')],
                         "walkers":[None,MCO("-w 512"),MCO("-w 1024"),MCO("-w 2048"),MCO("-w 4096"),MCO("-w 8192"), MCO("-w 16384")],
                         "depth":[None,MCO("-d 512"),MCO("-d 1024"),MCO("-d 2048"),MCO("-d 4096"),MCO("-d 8192"), MCO("-d 16384"),MCO("-d 32768")],
                         "attempt-limit":[None,MCO("-ll"),MCO("-ll 4096")]}
CMURPHI = "../../cmurphi/src/mu"
CMURPHI_PARAMS: Params_t = {"HashCompaction": [GCO("-c"), None], "BitCompaction": [GCO("-b"), None],
                            "MemLimit":[MCO("-m10000")], "trace-DFS": [MCO("ON"), MCO("OFF")],
                            "deadlock":[GCO("--deadlock-detection "+i) for i in ["off", "stuck", "stuttering"]]}  # TODO make this option match cmurphi man/help page
RUMUR = "../../rumur/build/rumur/rumur"
RUMUR_PARAMS: Params_t = {"symmetry": [GCO("--symmetry-reduction="+i) for i in ["heuristic", "exhaustive", "off"]],
                          # TODO make this option match rumur man/help page
                          "bound": [None,GCO("--bound=4096"),GCO("--bound=8192"),GCO("--bound=16384")]}  # TODO make this option match rumur man/help page

PASSES: int = 8

SBATCH_PARMAS: str = f'''
#SBATCH -M kingspeak
#SBATCH --account=ganesh
#SBATCH --partition=kingspeak-shared
#SBATCH --nodes=4
#SBATCH --ntasks={PASSES}
#SBATCH -C c16
#SBATCH -c 16
#SBATCH --exclusive
#SBATCH --time=12:00:00
#SBATCH --mail-type=FAIL
#SBATCH --mail-user=ajanthav10@gmail.com '''
# SBATCH_PARMAS: str = "-M kingspeak --account=ganesh --partition=kingspeak-shared --nodes=2 --ntasks=8 -C c16 -c 16 --exclusive --time=12:00:00 --mail-type=FAIL --mail-user=ajanthav10@gmail.com"

ALL_MODELS: List[str] = [
    "./abp.m",
    "./adash_bug.m"
    "./adash.m"
]
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

    # def _create_config(self) -> None:
    #     self._config = { key: l[0] for (key,l) in self._PARAMS.items() }

    def _update_config(self) -> None:
        self._config = {self._param_keys[j]: self._PARAMS[self._param_keys[j]][self._ks[j]] for j in range(len(self._param_keys))}
        # self._config[self._param_keys[k]] = self._PARAMS[self._param_keys[k]][j]

    @property
    def config(self) -> dict:
        if self._config is None:
            raise Exception("config not generated")
        return self._config

    @property
    def gen_cmd(self) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self._models[self._i].with_suffix('')
        other_opts = ' '.join(
            [i.value for i in self._config.values() if isinstance(i, GeneratorConfigOption)])
        if self._modgen[-3::] == "/mu":
            return f"{self._modgen} {other_opts} {self._models[self._i]}"
        return f"{self._modgen} {other_opts} -o {base_model}.{self._src_ext} {self._models[self._i]}"
        # note CMurphy does not accept -o or any output config details (because its annoying and poorly made)

    @property
    def comp_cmd(self) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self._models[self._i].with_suffix('')
        other_opts = ' '.join(
            [i.value for i in self._config.values() if isinstance(i, CompilerConfigOption)])
        return f"{self._comp} {self._comp_params} {other_opts} -o {base_model}.{self._index}.{self._exe_ext} {base_model}.{self._src_ext}"

    def sbatch_cmd(self, slurmOpts: str, outdir:str) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self._models[self._i].with_suffix('')
        launch_opts = ' '.join([i.value for i in self._config.values(
        ) if isinstance(i, ModelCheckerConfigOption)])
        return (f"time {base_model.absolute()}.{self._index}.{self._exe_ext} {launch_opts} "
                f"> {outdir}/{base_model}__{self._exe_ext}__{self._index}_%j.txt")
        
    def launch_cmd(self, outdir:str) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self._models[self._i].with_suffix('')
        launch_opts = ' '.join([i.value for i in self._config.values(
        ) if isinstance(i, ModelCheckerConfigOption)])
        return (f"{base_model.absolute()}.{self._index}.{self._exe_ext} {launch_opts} "
                f"> {outdir}/{base_model}__{self._exe_ext}__{self._index}_$j.txt")
    
    def valgrind_cmd(self, slurmOpts: str, outdir:str) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self._models[self._i].with_suffix('')
        launch_opts = ' '.join([i.value for i in self._config.values(
        ) if isinstance(i, ModelCheckerConfigOption)])
        return (f" {base_model.absolute()}.{self._index}.{self._exe_ext} {launch_opts} "
                f"> {outdir}/{base_model}__{self._exe_ext}__{self._index}_%j.txt")
    

    def _calc_len(self) -> int:
        _len = len(self._models)
        for values in self._PARAMS.values():
            _len *= len(values)
        self._len = _len
        return self._len

    def __len__(self) -> int:
        return self._len

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


'''def launch(cg:ConfigGenerator,slurmOpts:str) -> None:
    # var = [1,2,3,4]
    # for i in var:
    #     pass #lOOP BODY
    # iter(var) # --> var.__iter__()
    # while:
    #     try:
    #         pass  #lOOP BODY
    #     except StopIteration as ex:
    #         break
    #     next(var) # --> var.__next__()
    for i in cg:
        # gencmd 
        #compcmd
        #sbatch_cmd
        pass
    #TODO use the config gen passed in
    pass
'''


def launch(cg: ConfigGenerator, slurmOpts: str, outputDir: str = "./") -> None:
    if outputDir != "./":
        try:
            makedirs(outputDir)
        except:
            if DEBUG:
                print("ERROR : Failed to create new directory (could already exist)")
            pass
    if not DO_SLURM:
        bash_for_template = f"for j in {' '.join(str(i) for i in range(PASSES))}\ndo\n  {{cmd}}\ndone\n\n"
    with open(outputDir+f"/launch_{cg._exe_ext}.{'slurm' if DO_SLURM else 'sh'}",'w') as file:
        file.write("#!/bin/bash" + slurmOpts if DO_SLURM else '' + '\n')
        for i in cg:
            gen_cmd = i.gen_cmd
            print("Running :", gen_cmd)
            if not DEBUG:
                if system(gen_cmd) != 0:
                    print("ERROR :: could not generate!")
                    continue
                
            # Compiling the model
            comp_cmd = i.comp_cmd
            print("Running :", comp_cmd)
            if not DEBUG:
                if system(comp_cmd) != 0:
                    print("ERROR :: could not build!")
                    continue
                
            # Launching  model
            run_cmd = i.sbatch_cmd(slurmOpts, outputDir) if DO_SLURM else i.launch_cmd(outputDir)
            print("Writing :", run_cmd)
            # if not DEBUG:
            #     if system(sbatch_cmd) != 0:
            #         print("ERROR :: durning sbatch launch!")
            #         continue
            if DO_SLURM:
                file.write(run_cmd+'\n')
            else:
                file.write(bash_for_template.format(cmd=run_cmd))
            #valgrind 
            valgrind_cmd = i.valgrind_cmd(slurmOpts, outputDir)
            print("Writing :", valgrind_cmd)
            file.write(valgrind_cmd+'\n')
            print()
    if DEBUG:
        print("\nRunning : cat {outputDir}/launch_{cg._exe_ext}.slurm\n```")
        system(f"cat {outputDir}/launch_{cg._exe_ext}.{'slurm' if DO_SLURM else 'sh'}")
        print("```\n")
    if DO_SLURM:
        print("\nRunning : sbatch {slurmOpts} {outputDir}/launch_{cg._exe_ext}.slurm\n")
        if not DEBUG:
            if system(f"sbatch {slurmOpts} {outputDir}/launch_{cg._exe_ext}.slurm") != 0:
                print("ERROR :: FAILED TO LAUNCH SBATCH")
    else:
        print(f"\nRunning : {outputDir}/launch_{cg._exe_ext}.sh\n")
        if not DEBUG:
            if system(f"{outputDir}/launch_{cg._exe_ext}.sh") != 0:
                print("ERROR :: FAILED TO LAUNCH BASH SCRIPT")
            
            


def main(args) -> None:
    romp_configs = ConfigGenerator(
        ROMP, CXX, CXX_PARAMS, ROMP_PARAMS, ALL_MODELS, "romp")
    cmurphi_configs = ConfigGenerator(CMURPHI, CXX, CXX_PARAMS, CMURPHI_PARAMS,
                                      ALL_MODELS, "cm")
    rumur_configs = ConfigGenerator(RUMUR, CC, CC_PARAMS, RUMUR_PARAMS,
                                    [i for i in ALL_MODELS if not (
                                        "dash.m" in i or "-flow.m" in i or "multi.m" in i)],
                                    "ru")
    outdir = CHPC_SAVE_PATH if DO_SLURM else LOCAL_SAVE_PATH
    
    
    launch(romp_configs, SBATCH_PARMAS, launch_time)
    launch(cmurphi_configs, SBATCH_PARMAS, launch_time)
    launch(rumur_configs, SBATCH_PARMAS, launch_time)


if __name__ == "__main__":
    main(sys.argv)

