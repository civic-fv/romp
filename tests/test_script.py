import os
from argparse import ArgumentParser
import argparse
from shutil import rmtree
from pathlib import Path
from textwrap import dedent

class config:
    """To generate the configuration for the testing ROMP"""
    def __init__(self)->None:
    def create_config(self,params)->None:
        #todo
        """
        1) config dictionary 
            Model:-Romp  , rumur , cmurphi
            Under Romp  +   Sample sbatch file for each module


            symmetry reduction - ON/off
            depth - user defined/default
            walks - user defined / default
            trace - yes-> path for files
                    No

            
            Under Rumur
            symmetry - heustric, exhaustive, none
            bound ( max-memory) - limit int value 
            pack-state - (state-compaction) - yes/no
            
            Under Cmurphi
            HashCompac
            Bit-Compaction=
            max-memory
            BFS/DFS      
            """
def create_bash()->None:
    bash_save_path = "./submit_jobs.sh"
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
    with open(bash_save_path, "w") as fp:
        fp.write(template)        

def parse_args():
    description="Generating the set of params for Slurm "
    parser=argparse.ArgumentParser(description=description)
    #add an argument and  # Parse the argument
    parser.add_argument("--m",choices=['Romp','Cmurphi','Rumur'],required=True,help='murphi version',nargs='+')
    args = parser.parse_args()
    return args 

def main(args)-> None:

    model = args.m
    if model=="Romp":
        params={"symmetry":["ON","OFF"],"trace":["ON","OFF"],}# how to take the default vlues ????
    if model=="Cmurphi":
        params={"HashCompaction":["ON","OFF"],"Bit-Compaction":["ON","OFF"],"bound":['default',10000],"trace-DFS":["ON","OFF"]}
    if model=="Rumur":
        params={"symmetry":["heustric", "exhaustive", "none"],"pack-state":["ON","OFF"],"bound":["default",10000],"trace-DFS":["ON","OFF"]}
   
if __name__ == "__main__":
    main()
