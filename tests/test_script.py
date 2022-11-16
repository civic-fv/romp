import os
from typing import List, Union as Un, Dict
from pathlib import Path
from dataclasses import dataclass

@dataclass
class GeneratorConfigOption:
    value:str
@dataclass
class CompilerConfigOption:
    value:str
@dataclass
class ModelCheckerConfigOption:
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

CPARAMS = "-std=c11 -O3 -pthread"
CXXPARAMS = "-std=c++17 -O3 -pthread"
CCPARAMS ="-march=native -O3 -lpthread"

SAVE_PATH = "./submit_jobs.sh"
ROMP = None #TODO: path to romp executable from planned cwd or machines root
ROMP_PARAMS:Params_t = {"symmetry":[None,GCO('-s')],"trace":[MCO('-t %s'),None],} 
CMURPHI = None #TODO: path to cmurphi executable from planned cwd or machines root
CMURPHI_PARAMS:Params_t = {"HashCompaction":[GCO("-c"),None],"BitCompaction":[GCO("-b"),None],"MemLimit":[None,MCO("-m10000")],"trace-DFS":[MCO("ON"),MCO("OFF")]}
RUMUR = None #TODO: path to rumur executable from planned cwd or machines root
RUMUR_PARAMS:Params_t = {"symmetry":[GCO("--symetry-reduction="+i) for i in ["heustric", "exhaustive", "off"]],
                        "pack-state":["ON","OFF"],
                        "bound":["default",10000],
                        "trace-DFS":["ON","OFF"]}

SBATCH_PARMAS:str = "-M kingspeak --account=ganesh --partition=kingspeak-shared --nodes=1 --ntasks=1 -C c16 -c 16 --exclusive --time=20:00:00 --mail-type=FAIL,BEGIN,END --mail-user=**0@gmail.com"

ALL_MODELS: List[str] = [
        #TODO
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
    def __init__(self, modgen:str, comp:str, comp_params:str, params:Params_t, models:List[str], exe_ext:str=None, sbatch_params:str=None) -> None:
        self.__modgen: str = modgen
        self.__exe_ext: str = Path(modgen).stem if exe_ext is None else exe_ext
        self.__src_ext: str = ".cpp" if "++" in comp else ".c"
        self.__comp: str = comp
        self.__comp_params: str = comp_params
        self.__sbatch_params: str = sbatch_params #contains the launch options for the slurm job/sbatch-launch
        self.__PARAMS: Params_t = dict(params)
        self.__models: List[Path] = [Path(i) for i in models]
        self.__param_keys: List[str] = self.__PARAMS.keys().sort()
        self.__index: int = None
        self.__i: int = None # model
        self.__j: int = None # param key
        self.__k: int = None # param value
        self.__config: Config_t = None
        self.__len:int = self.__calc_len()
    
        
    @property
    def PARAMS(self) -> dict:
        return self.__PARAMS
    @property
    def index(self) -> int:
        return self.__index
    
    def __create_config(self) -> None:
        self.__config = { key: l[0] for (key,l) in self.__PARAMS.items() }
    
    def __update_config(self,i,j,k) -> None:
        self.__config[self.__param_keys[j]] = self.__PARAMS[self.__param_keys[j]][k]
    
    @property
    def config(self) -> dict:
        if self.__config is None:
            raise Exception("config not generated")
        return self.__config
    
    @property
    def gen_cmd(self) -> str:
        #TODO first
        pass
    
    @property
    def comp_cmd(self) -> str:
        if self.__index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self.__models[self.__i].with_suffix('')
        other_opts = [i.value for i in self.__config.values() if isinstance(i,CompilerConfigOption)].join(' ')
        return f"{self.__comp} {self.__comp_params} {other_opts} -o {base_model}.{self.__exe_ext} {base_model}.{self.__src_ext}"
    
    @property    
    def sbatch_cmd(self) -> str:
        #TODO second
        pass
    
    def __calc_len(self) -> int:
        #TODO calculate permutation count    
        self.__len = #TODO third
        pass
    
    def __len__(self) -> int:
        return self.__len
    def __iter__(self):
        self.__index = 0
        self.__i = 0
        self.__j = 0
        self.__k = 0
        self.__create_config()
        return self
    def __next__(self):
        if self.__index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        if self.__index >= len(self) or self.__index < 0:
            raise StopIteration
        self.__index += 1
        self.__k += 1
        if self.__k < len(self.__PARAMS[self.__PARAMS.keys[j]]):
            pass   
        else:
            self.__k = 0
            self.__j += 1
            if self.__j < len(self.__PARAMS):
                pass
            else:
                self.__update_config(self.__i,self.__j,self.__k)
                self.__j = 0
                self.__i += 1
                if self.__i < len(self.__models):
                    pass
                else:
                    self.__i = 0
        self.__update_config(self.__i,self.__j,self.__k)
        return self      


def main(args)-> None:
    romp_configs = ConfigGenerator(ROMP_PARAMS, ["TODO:models"])# how to take the default vlues ????
    cmurphi_configs = ConfigGenerator(CMURPHI_PARAMS,
                                      ["TODO:models"])
    rumur_configs = ConfigGenerator(RUMUR_PARAMS,
                                    ["TODO:models"])
   
if __name__ == "__main__":
    main()