import os
from typing import List
from pathlib import Path

# << =========================================================================================== >> 
# <<                                        GLOBAL CONFIG                                        >> 
# << =========================================================================================== >> 

CC = "gcc"
CXX = "g++"

CPARAMS = "-std=c11 -O3 -pthread"
CXXPARAMS = "-std=c++17 -O3 -pthread"

SAVE_PATH = "./submit_jobs.sh"
ROMP = None #TODO: path to romp executable from planned cwd or machines root
ROMP_PARAMS = {"symmetry":[None,'-s'],"trace":['-t %s',None],} 
CMURPHI = None #TODO: path to cmurphi executable from planned cwd or machines root
CMURPHI_PARAMS = {"HashCompaction":["ON","OFF"],"Bit-Compaction":["ON","OFF"],"bound":['default',10000],"trace-DFS":["ON","OFF"]}
RUMUR = None #TODO: path to rumur executable from planned cwd or machines root
RUMUR_PARAMS = {"symmetry":["heustric", "exhaustive", "none"],"pack-state":["ON","OFF"],"bound":["default",10000],"trace-DFS":["ON","OFF"]}
# SPIN_PARAMS  = {} # TODO: add this when we work with everything else

# << =========================================================================================== >> 
# <<                                      LAUNCH GENERATORS                                      >> 
# << =========================================================================================== >> 




# << =========================================================================================== >> 
# <<                                       GENERATOR CODE                                        >> 
# << =========================================================================================== >> 
class ConfigGenerator:
    """To generate the configuration for the testing ROMP"""
    def __init__(self, modgen:str, comp:str, comp_params:str, params:dict, models:List[str], exe_ext:str=None) -> None:
        self.__modgen: str = modgen
        self.__exe_ext: str = Path(modgen).stem
        self.__src_ext: str = "cpp" if "++" in comp else "c"
        self.__comp: str = comp
        self.__comp_params: str = comp_params
        self.__PARAMS: dict = dict(params)
        self.__models: List[Path] = [Path(i) for i in models]
        self.__index: int = None
        self.__i: int = None # model
        self.__j: int = None # param key
        self.__k: int = None # param value
        self.__config: dict = None
        self.__len:int = self.__calc_len()
        
    @property
    def PARAMS(self) -> dict:
        return self.__PARAMS
    @property
    def index(self) -> int:
        return self.__index
    
    def __create_config(self) -> None:
        #TODO create a dictionary representing the config
        pass
    
    @property
    def config(self) -> dict:
        if self.__config is None:
            raise Exception("config not generated")
        return self.__config
    
    @property
    def gen_cmd(self) -> str:
        pass
    
    @property
    def comp_cmd(self) -> str:
        if self.__index is None:
            raise Exception("ConfigGenerator not in iterator mode!!")
        base_model = self.__models[self.__i].with_suffix('') + self.__exe_ext
        return f"{self.__comp} {self.__comp_params} -o {base_model} {base_model}.{self.__src_ext}"
    
    @property    
    def sbatch_cmd(self) -> str:
        
        template=f"""
            #!/bin/bash -x
            #SBATCH -M kingspeak
            #SBATCH --account=ganesh
            #SBATCH --partition=kingspeak-shared
            #SBATCH --nodes=1
            #SBATCH --ntasks=1
            #SBATCH -C c16
            #SBATCH -c 16
            #SBATCH --exclusive
            #SBATCH --time=20:00:00  # maximum time to run for
            #SBATCH --mail-type=FAIL,BEGIN,END
            #SBATCH --mail-user=**0@gmail.com
            """
        template = dedent(template).lstrip() 
        with open(BASH_SAVE_PATH, "w") as fp:
            fp.write(template)
    
    def __calc_len(self) -> int:
        #TODO calculate permutation count
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
        k += 1
        if k < len(self.__PARAMS[self.__PARAMS.keys[j]]):
            pass   
        else:
            k = 0
            j += 1
            if j < len(self.__PARAMS):
                pass
            else:
                j = 0
                i += 1
                if i < len(self.__models):
                    pass
                else:
                    i = 0
        self.__create_config()
        return self      


def main(args)-> None:
    romp_configs = ConfigGenerator(ROMP_PARAMS, ["TODO:models"])# how to take the default vlues ????
    cmurphi_configs = ConfigGenerator(CMURPHI_PARAMS,
                                      ["TODO:models"])
    rumur_configs = ConfigGenerator(,
                                    ["TODO:models"])
   
if __name__ == "__main__":
    main()