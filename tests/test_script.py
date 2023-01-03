from os import system 
from typing import List, Union as Un, Dict
from pathlib import Path
from dataclasses import dataclass
import sys

DEBUG=True

"""TODOs & known issues:
    -[X] romp needs way to pass in random seeds
       - put in a handful of seeds as the options for the seed flag
    -[ ] cmurphi doesn't have an -o option for generating
       - maybe just use default output for all generators
"""



@dataclass
class GeneratorConfigOption:
    value:str
@dataclass
class CompilerConfigOption:
    value:str
@dataclass
class ModelCheckerConfigOption:
    value:str
class SlurmConfigOption:
    value:str

ConfigOpt_t = Un[None,GeneratorConfigOption,CompilerConfigOption,ModelCheckerConfigOption]
Params_t = Dict[str,List[ConfigOpt_t]]
Config_t = Dict[str,ConfigOpt_t]

GCO = GeneratorConfigOption
CCO = CompilerConfigOption
MCO = ModelCheckerConfigOption

# << =========================================================================================== >> 
# <<                                        GLOBAL CONFIG                                        >> 
# << =========================================================================================== >> 

CC = "gcc"
CXX = "g++"

CXX_PARAMS = "-std=c++17 -O3 -pthread"
CC_PARAMS ="-march=native -O3 -lpthread"

SAVE_PATH = "./submit_jobs.sh"
ROMP = "../build/romp/romp"
ROMP_PARAMS:Params_t = {"symmetry":[None,GCO('-s')],"trace":[MCO('-t'),None],"trace-comp":[GCO('--simple-trace-rep')],
                        "seed":[None,MCO('-s scrappy'),MCO('-s 1234567890')]}
CMURPHI = "../../cmurphi/src/mu"
CMURPHI_PARAMS:Params_t = {"HashCompaction":[GCO("-c"),None],"BitCompaction":[GCO("-b"),None],"MemLimit":[MCO("-m10000")],"trace-DFS":[MCO("ON"),MCO("OFF")]} #TODO make this option match cmurphi man/help page
RUMUR = "../../rumur/build/rumur/rumur"
RUMUR_PARAMS:Params_t = {"symmetry":[GCO("--symetry-reduction="+i) for i in ["heustric", "exhaustive", "off"]],
                        "bound":["default",10000], #TODO make this option match rumur man/help page
                        "trace-DFS":["ON","OFF"]}  #TODO make this option match rumur man/help page

SBATCH_PARMAS:str = "-M kingspeak --account=ganesh --partition=kingspeak-shared --nodes=1 --ntasks=1 -C c16 -c 16 --exclusive --time=20:00:00 --mail-type=FAIL,BEGIN,END --mail-user=**0@gmail.com"

ALL_MODELS: List[str] = [
        "./german.m",
        "./sort5.m"
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
    def __init__(self, modgen:str, comp:str, comp_params:str, params:Params_t, models:List[str], exe_ext:str=None) -> None:
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
        self._i: int = None # model
        self._jj: int = None # next param key
        self._kk: int = None # next param value
        self._j: int = None # param key
        self._k: int = None # param value
        self._config: Config_t = None
        self._len:int = self._calc_len()
    
        
    @property
    def PARAMS(self) -> dict:
        return self._PARAMS
    @property
    def index(self) -> int:
        return self._index
    
    def _create_config(self) -> None:
        self._config = { key: l[0] for (key,l) in self._PARAMS.items() }
    
    def _update_config(self,i:int,j:int,k:int) -> None:
        self._config[self._param_keys[j]] = self._PARAMS[self._param_keys[j]][k]
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
        other_opts = ' '.join([i.value for i in self._config.values() if isinstance(i,GeneratorConfigOption)])
        return f"{self._modgen} {other_opts} -o {base_model}.{self._src_ext}"
        # note CMurphy does not accept -o or any output config details (because its annoying and poorly made)

    
    @property
    def comp_cmd(self) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self._models[self._i].with_suffix('')
        other_opts = ' '.join([i.value for i in self._config.values() if isinstance(i,CompilerConfigOption)])
        return f"{self._comp} {self._comp_params} {other_opts} -o {base_model}.{self._exe_ext} {base_model}.{self._src_ext}"
    
    
    def sbatch_cmd(self,slurmOpts:str) -> str:
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self._models[self._i].with_suffix('')
        launch_opts = ' '.join([i.value for i in self._config.values() if isinstance(i, ModelCheckerConfigOption)])
        return f"sbatch {slurmOpts} '{base_model}.{self._exe_ext} {launch_opts}'"

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
        self._i = 0 # model index
        self._jj = 0 # next category index
        self._kk = 0 # next category option index
        self._j = 0 # category index
        self._k = 0 # in category option index
        self._create_config()
        return self
    def __next__(self):
        if self._index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        if self._index >= len(self) or self._index < 0:
            raise StopIteration
        self._index += 1
        self._k += 1
        if self._k >= len(self.PARAMS[self._param_keys[self._j]]):
            # when done cycling through options in config category
            self._k = 0
            self._update_config(self._i,self._j,self._k) # reset prev cycling stat to default
            self._j += 1
            if self._j >= self._jj:
                # when done cycling through all subsequent config categories for a model
                self._j = 0
                self._kk += 1
                if self._kk >= len(self.PARAMS[self._param_keys[self._jj]]):
                    # when done cycling through the current next config category
                    self._kk = 0
                    self._update_config(self._i,self._jj,self._kk) # reset prev cycling stat to default
                    self._jj += 1
                    if self._jj >= len(self._param_keys):
                        # when done cycling through the all permutations config categories for a model
                        self._update_config(self._i,self._j,self._k) # reset prev cycling stat to default
                        self._jj = 0
                        self._i += 1
                        if self._i >= len(self._models):
                            # when done cycling over a model
                            self._i = 0
                else:
                    self._update_config(self._i,self._jj,self._kk) # update the next config option
        self._update_config(self._i,self._j,self._k) # update the lowest config option
        return self     



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

def launch(cg:ConfigGenerator,slurmOpts:str,outputDir:str="./job-") -> None:
    for i in cg:
        gen_cmd = i.gen_cmd
        print("Running :",gen_cmd)
        if not DEBUG:
            system(gen_cmd)

        # Compiling the model
        comp_cmd = i.comp_cmd
        print("Running :",comp_cmd)
        if not DEBUG:
            system(comp_cmd)

        # Launching  model 
        sbatch_cmd = i.sbatch_cmd(slurmOpts)
        print("Running :",sbatch_cmd)
        if not DEBUG:
            system(sbatch_cmd)
        print()

def main(args)-> None:
    romp_configs = ConfigGenerator(ROMP,CXX,CXX_PARAMS,ROMP_PARAMS,ALL_MODELS,"romp")
    cmurphi_configs = ConfigGenerator(CMURPHI,CXX,CXX_PARAMS,CMURPHI_PARAMS,
                                      ALL_MODELS,"cm")
    rumur_configs = ConfigGenerator(RUMUR,CC,CC_PARAMS,RUMUR_PARAMS,
                                    [i for i in ALL_MODELS if not ("dash.m" in i or "-flow.m" in i or "multi.m" in i)],
                                    "ru")
    launch(romp_configs,SBATCH_PARMAS)
    # launch(cmurphi_configs,SBATCH_PARMAS)
    # launch(rumur_configs,SBATCH_PARMAS)
   
if __name__ == "__main__":
    main(sys.argv)