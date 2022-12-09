
  About the Tests _(and makefile)_
====================================

Here are many of the tests that we have used to test the romp project.
This file should instruct you how to build the various model-checkers
for all included models using romp and for comparison CMurphi and rumur.

Please use `-h` on the generated models to figure out how to run them in detail,
we will provide recommended settings to get successful runs (bugs found) on
each buggy model using each model checker tool.


 makefile usage
----------------
These test files come with a [`makefile`](./makefile) that allows you to build each model with 
CMurphi, rumur (z3 install required) in addition to romp.

To use this makefile work ensure that romp is built properly with cmake, 
and either modify the paths to the various other Murphi model generating tools in the make file,
or that the repo's for the respective tools are located at the same file level as the root to this 
repo, and that their tools are built.

> _**Note:** all commands are given from the directory that the model and makefile are located._

To build one specific model with all tools:
```bash
make <model_name_no_extension>
```

To build one specific model with a specific tool:
```bash
make <model-name-no-extension>.<tool-extension>
```
|     ext    |  description                                                         |
|:----------:|:---------------------------------------------------------------------|
|   `.romp`  | romp with heuristic symmetry reduction enables (same as `.sym.romp`) |
| `.sym.romp`| romp with heuristic symmetry reduction enables (same as `.romp`)     |
|`.nsym.romp`| romp with NO heuristic symmetry reduction enabled                    |
|    `.cm`   | CMurphi derived model checker                                        |
|    `.ru`   | rumur derived model checker                                          |

To build all models with all tools that are compatible with the model:
```bash
make all
```

To build all models compatible tools use one fo the following commands:
```bash
make romp_models
make rumur_models
make cmurphi_models
```

### Further Configuration
To enable the various features in of the model checker generating tools wither modify the makefile,
or append/overwrite the specific tools variable in the command line.

Example to make CMurphi use hash compaction when building the `n_peterson_bug1.m` model:
```bash
make n_peterson_bug1.cm CMURPHI_ARGS+="-c"
```

### Cleanup
Use `make clean` to clean up all generated files.

Use `make clean-inter` to clean up all intermediary files, 
 but keep the generated executable model-checkers.


 Bug Free Models
-----------------
There are a lot of models included in this repo that have no bugs in them,
these are used for general benchmarking.

If the model is not included in the following list(s) then it should not produce
deadlock or report any errors. 
Though one or more of the model-checkers might time out on them.




 Models with *"Real"* Bugs
---------------------------
These models have bugs that are "real" or at least "naturally occurring."
Meaning that they represent bugs that were in some way not intended to exist by
the original creator of the modeled protocol, the author of the murphi model,
or the author of whatever software was used to programmatically generate that specific murphi model.

<!--
- things to include in description:
  - header with link to model
  - basic description of what the model is
    - i.e. basic model, cache coherency, computer generated, hand made, nature of bug
  - Expected results from each model checker (romp rumur and CMurphi)
    - i.e. does it find bug if so what, does it report deadlock (what config did you use to launch it)
  -->

### [`adash_bug.m`](./adash_bug.m)
This is the classic adash (sometimes called stanford dash or just dash) cache coherence protocol.
It has the famous bug of the original version still included in it, and enabled.
This bug is easy for any of the model checkers to find.

#### About the Bug
TODO description of what causes the bug

#### Build & Run _(recommended settings)_
```bash
make adash_bug                                    # build the model checkers
./adash_bug.romp -s 1234 -w 1024 -d 512 -y        # check with romp
./adash_bug.nsym.romp -s 1234 -w 1024 -d 512 -y   # check with romp (no symmetry)
./adash_bug.ru                                    # verify with rumur
./adash_bug.cm -m1024                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores_

|   Tool  |  t _(ms)_  | Bug(s) Found / Property(s) Violated                                        |
|:-------:|-----------:|:---------------------------------------------------------------------------|
|   romp  |  5,799.183 | "Explicit writeback for non dirty remote" & "WRD at home cluster"          |
| ns-romp |  5,841.320 | "Explicit writeback for non dirty remote" & "WRD at home cluster"          |
| CMurphi |  1,550.000 | "Consistency of data"                                                      |
|  rumur  |         -- | Not compatible with rumur (remove later)                                   |


### [`arbiter.m`](./arbiter.m)
TODO AV ... describe this one give results etc.


### [`dpnew.m`](./dpnew.m)
TODO AV ...


### [`sort5.m`](./sort5.m)
TODO AV ... describe the bug (this one needs to be prefaced as a basic proof of concept bug)


### [`flash-flow.m`](./flash-flow.m)
TODO AO ... (cm: deadlock, romp: invariant violation)


### [`german-flow.m`](./flash-flow.m)
TODO AO ... (invariant violation)



 Models with _"Synthetic"_ Bugs
--------------------------------
These models are designed as synthetic benchmarks,
as such they are designed to have bugs in them with varying levels fo difficulty to find in 
a handful of different ways.
Such as introducing bottlenecks that have to be passed, and varying degrees of sparsity for the
violating states in the model.
These factors are such that they are likely to occur naturally in "real" models, 
but in these models they are isolated to better understand the effects that varying design choices in
model checkers can have.

### [`n_peterson_bug.m`](./n_peterson_bug.m)
TODO AV ...


### [`n_peterson_bug1.m`](./n_peterson_bug1.m)
TODO AV ...


### [`deepdense.m`](./deepdense.m)
TODO AO ...


### [`deepsparse.m`](./deepsparse.m)
TODO AO ...


### [`flash_bug.m`](./flash_bug.m)
TODO AO ...


### [`dash_bug.m`](./dash_bug.m)
TODO AO ...



