from os import system as cmd_line
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

CXXPARAMS = "-std=c++17 -O3 -pthread"
CCPARAMS ="-march=native -O3 -lpthread"

SAVE_PATH = "./submit_jobs.sh"
ROMP = None #TODO: path to romp executable from planned cwd or machines root
ROMP_PARAMS:Params_t = {"symmetry":[None,GCO('-s')],"trace":[MCO('-t'),None],"trace-comp":[GCO('--simple-trace-re')]} 
CMURPHI = None #TODO: path to cmurphi executable from planned cwd or machines root
CMURPHI_PARAMS:Params_t = {"HashCompaction":[GCO("-c"),None],"BitCompaction":[GCO("-b"),None],"MemLimit":[MCO("-m10000")],"trace-DFS":[MCO("ON"),MCO("OFF")]} #TODO make this option match cmurphi man/help page
RUMUR = None #TODO: path to rumur executable from planned cwd or machines root
RUMUR_PARAMS:Params_t = {"symmetry":[GCO("--symetry-reduction="+i) for i in ["heustric", "exhaustive", "off"]],
                        "bound":["default",10000], #TODO make this option match rumur man/help page
                        "trace-DFS":["ON","OFF"]}  #TODO make this option match rumur man/help page

SBATCH_PARMAS:str = "-M kingspeak --account=ganesh --partition=kingspeak-shared --nodes=1 --ntasks=1 -C c16 -c 16 --exclusive --time=20:00:00 --mail-type=FAIL,BEGIN,END --mail-user=**0@gmail.com"

ALL_MODELS: List[str] = [
        #TODO past in all file dirs
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
        self.__modgen: str = modgen
        self.__exe_ext: str = Path(modgen).stem if exe_ext is None else exe_ext
        self.__src_ext: str = ".cpp" if "++" in comp else ".c"
        self.__comp: str = comp
        self.__comp_params: str = comp_params
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
        if self.__index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self.__models[self.__i].with_suffix('')
        other_opts = [i.value for i in self.__config.values() if isinstance(i,GeneratorConfigOption)].join(' ')
        return f"{self.__modgen} {other_opts} -o {base_model}.{self.__src_ext}"
        # note CMurphy does not accept -o or any output config details (because its annoying and poorly made)

    
    @property
    def comp_cmd(self) -> str:
        if self.__index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self.__models[self.__i].with_suffix('')
        other_opts = [i.value for i in self.__config.values() if isinstance(i,CompilerConfigOption)].join(' ')
        return f"{self.__comp} {self.__comp_params} {other_opts} -o {base_model}.{self.__exe_ext} {base_model}.{self.__src_ext}"
    
    
    def sbatch_cmd(self,slurmOpts:str) -> str:
        if self.__index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self.__models[self.__i].with_suffix('')
        launch_opts = [i.value for i in self.__config.values() if isinstance(i, ModelCheckerConfigOption)].join(' ')
        return f"sbatch {slurmOpts} {base_model}.{self.__exe_ext} {self.__config.values().join(' ')}"

    def __calc_len(self) -> int:
        _len = 1
        for values in self.__PARAMS.values():
            _len *= len(values)
        self.__len = _len
        return self.__len
    
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

def launch(cg:ConfigGenerator,slurmOpts:str) -> None:
    for i in cg:
        gen_cmd = cg.gen_cmd
        cmd_line.system(gen_cmd)

        # Compiling the model
        comp_cmd = cg.comp_cmd
        cmd_line.system(comp_cmd)

        # Launching  model 
        sbatch_cmd = cg.sbatch_cmd(slurmOpts)
        cmd_line.system(sbatch_cmd)

def main(args)-> None:
    romp_configs = ConfigGenerator(ROMP,CXX,CXX_PARAMS,ROMP_PARAMS,ALL_MODELS,".romp")
    cmurphi_configs = ConfigGenerator(CMURPHI,CXX,CXX_PARAMS,CMURPHI_PARAMS,
                                      ALL_MODELS,".cm")
    rumur_configs = ConfigGenerator(RUMUR,CC,CC_PARAMS,RUMUR_PARAMS,
                                    [i for i in ALL_MODELS if not ("dash.m" in i or "-flow.m" in i or "multi.m" in i)],
                                    ".ru")
    launch(romp_configs,SBATCH_PARMAS)
    launch(cmurphi_configs,SBATCH_PARMAS)
    launch(rumur_configs,SBATCH_PARMAS)
   
if __name__ == "__main__":
    main()