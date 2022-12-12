
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

#### Build & Run _(with recommended settings)_
```bash
make adash_bug                                    # build the model checkers
./adash_bug.romp -s 1234 -w 1024 -d 512 -y        # check with romp
./adash_bug.nsym.romp -s 1234 -w 1024 -d 512 -y   # check with romp (no symmetry)
./adash_bug.ru                                    # verify with rumur
./adash_bug.cm -m1024                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |  t _(ms)_  | Bug(s) Found / Property(s) Violated                                        |
|:-------:|-----------:|:---------------------------------------------------------------------------|
|   romp  |  5,799.183 | "Explicit writeback for non dirty remote" (x480) & "WRD at home cluster" (x511) |
| ns-romp |  5,841.320 | "Explicit writeback for non dirty remote" (x510) & "WRD at home cluster" (x514) |
| CMurphi |  1,55#.### | "Consistency of data"                                                      |
|  rumur  |         -- | _-- Not compatible with rumur (contains union) --_                         |



### [`arbiter.m`](./arbiter.m)

#### About the Bug

#### Build & Run _(with recommended settings)_
```bash
make arbiter                                    # build the model checkers
./arbiter.romp -s 1234 -w 1024 -d 512 -y        # check with romp
./arbiter.nsym.romp -s 1234 -w 1024 -d 512 -y   # check with romp (no symmetry)
./arbiter.ru                                    # verify with rumur
./arbiter.cm -m1024                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |  t _(ms)_  | Bug(s) Found / Property(s) Violated                                        |
|:-------:|-----------:|:---------------------------------------------------------------------------|
|   romp  |  5,799.183 | "Explicit writeback for non dirty remote" (x480) & "WRD at home cluster" (x511) |
| ns-romp |  5,841.320 | "Explicit writeback for non dirty remote" (x510) & "WRD at home cluster" (x514) |
| CMurphi |  1,55#.### | "Consistency of data"                                                      |
|  rumur  |         -- | _-- Not compatible with rumur (contains union) --_                         |



### [`dpnew.m`](./dpnew.m)

This is a classsic implmentation of synchronization issues in concurrent systems using  Dining Philosophers example. 
#### About the Bug

Deadlock Invariant checks if all the philosophers picking up their left forks and  waiting for
their right forks. All philosophers are waiting for the adjacent philosopher to release their right fork. However, the adjacent philosopher  cannot release their right fork until the philosopher next to them acquires their left fork. It creates a cycle of all philosophers waiting for the adjacent philosopher to release their fork, causing a deadlock.
#### Build & Run _(with recommended settings)_
```bash
make dpnew                                    # build the model checkers
./dpnew.romp -s 1234 -w 1024 -d 512 -y        # check with romp
./dpnew.nsym.romp -s 1234 -w 1024 -d 512 -y   # check with romp (no symmetry)
./dpnew.ru                                    # verify with rumur
./dpnew.cm -m1024                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |  t _(ms)_  | Bug(s) Found / Property(s) Violated                                        |
|:-------:|-----------:|:---------------------------------------------------------------------------|
|   romp  |  5,799.183 | "Explicit writeback for non dirty remote" (x480) & "WRD at home cluster" (x511) |
| ns-romp |  5,841.320 | "Explicit writeback for non dirty remote" (x510) & "WRD at home cluster" (x514) |
| CMurphi |  1,55#.### | "Consistency of data"                                                      |
|  rumur  |         -- | _-- Not compatible with rumur (contains union) --_   



### [`sort5.m`](./sort5.m)

This is the implementation of bubble sort algorithm in Murphi. The code iterates through a list , compares adjustment elements and swaps them if they are in wrong order. 
#### About the Bug

Invariant checks if there exists atleast one pair of adjacent elements where the first element is greater than second element. Once, the array is completely sorted the model fails.

#### Build & Run _(with recommended settings)_
```bash
make sort5                                    # build the model checkers
./sort5.romp -s 1234 -w 1024 -d 512 -y        # check with romp
./sort5.nsym.romp -s 1234 -w 1024 -d 512 -y   # check with romp (no symmetry)
./sort5.ru                                    # verify with rumur
./sort5.cm -m1024                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |  t _(ms)_  | Bug(s) Found / Property(s) Violated                                        |
|:-------:|-----------:|:---------------------------------------------------------------------------|
|   romp  |  5,799.183 | "Explicit writeback for non dirty remote" (x480) & "WRD at home cluster" (x511) |
| ns-romp |  5,841.320 | "Explicit writeback for non dirty remote" (x510) & "WRD at home cluster" (x514) |
| CMurphi |  1,55#.### | "Consistency of data"                                                      |
|  rumur  |         -- | _-- Not compatible with rumur (contains union) --_    



### [`flash-flow.m`](./flash-flow.m)
This is the classic flash cache coherency protocol programmatically translated into murphi from
the flows language, by an experimental tool.

#### About the Bug
We have not bothered t figure out what is actually broken in this model, 
since the generated murphi model is unnecessarily complicated.

#### Build & Run _(with recommended settings)_
```bash
make flash-flow                                    # build the model checkers
./flash-flow.romp -s 1234 -w 1024 -d 512 -y       # check with romp
./flash-flow.nsym.romp -s 1234 -w 1024 -d 1024 -y  # check with romp (no symmetry)
./flash-flow.cm -m2048                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |   t _(ms)_  | Bug(s) Found / Property(s) Violated                                       |
|:-------:|------------:|:--------------------------------------------------------------------------|
|   romp  |  31,607.### | invariant "safety" (x69)                                                  |
| ns-romp |  28,189.### | invariant "safety" (x21)                                                  |
| CMurphi | 178,55#.### | invariant "safety"                                                        |
|  rumur  |          -- | _-- Not compatible with rumur (contains union) --_                        |


### [`german-flow.m`](./flash-flow.m)
This is the classic german protocol programmatically translated into murphi from
the flows language, by an experimental tool.

#### About the Bug
We have not bothered t figure out what is actually broken in this model, 
since the generated murphi model is unnecessarily complicated.

#### Build & Run _(with recommended settings)_
```bash
make flash-flow                                    # build the model checkers
./flash-flow.romp -s 1234 -w 1024 -d 512 -y        # check with romp
./flash-flow.nsym.romp -s 1234 -w 1024 -d 512 -y   # check with romp (no symmetry)
./flash-flow.cm -m2048                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |   t _(ms)_  | Bug(s) Found / Property(s) Violated                                       |
|:-------:|------------:|:--------------------------------------------------------------------------|
|   romp  |  28,133.### | invariant "CntrlPropl" (x4)                                               |
| ns-romp |  27,375.### | invariant "CntrlPropl" (x6)                                               |
| CMurphi |   3,42#.### | Deadlocked state found                                                    |
|  rumur  |          -- | _-- Not compatible with rumur (contains union) --_                        |





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

#### About the Bug

#### Build & Run _(with recommended settings)_
```bash
make n_peterson_bug                                    # build the model checkers
./n_peterson_bug.romp -s 1234 -w 1024 -d 512 -y        # check with romp
./n_peterson_bug.nsym.romp -s 1234 -w 1024 -d 512 -y   # check with romp (no symmetry)
./n_peterson_bug.ru                                    # verify with rumur
./n_peterson_bug.cm -m1024                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |  t _(ms)_  | Bug(s) Found / Property(s) Violated                                        |
|:-------:|-----------:|:---------------------------------------------------------------------------|
|   romp  |  5,799.183 | "Explicit writeback for non dirty remote" (x480) & "WRD at home cluster" (x511) |
| ns-romp |  5,841.320 | "Explicit writeback for non dirty remote" (x510) & "WRD at home cluster" (x514) |
| CMurphi |  1,55#.### | "Consistency of data"                                                      |
|  rumur  |         -- | _-- Not compatible with rumur (contains union) --_   

### [`n_peterson_bug1.m`](./n_peterson_bug1.m)

#### About the Bug

#### Build & Run _(with recommended settings)_
```bash
make n_peterson_bug1                                    # build the model checkers
./n_peterson_bug1.romp -s 1234 -w 1024 -d 512 -y        # check with romp
./n_peterson_bug1.nsym.romp -s 1234 -w 1024 -d 512 -y   # check with romp (no symmetry)
./n_peterson_bug1.ru                                    # verify with rumur
./n_peterson_bug1.cm -m1024                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |  t _(ms)_  | Bug(s) Found / Property(s) Violated                                        |
|:-------:|-----------:|:---------------------------------------------------------------------------|
|   romp  |  5,799.183 | "Explicit writeback for non dirty remote" (x480) & "WRD at home cluster" (x511) |
| ns-romp |  5,841.320 | "Explicit writeback for non dirty remote" (x510) & "WRD at home cluster" (x514) |
| CMurphi |  1,55#.### | "Consistency of data"                                                      |
|  rumur  |         -- | _-- Not compatible with rumur (contains union) --_   

### [`deepdense.m`](./deepdense.m)
This model is a synthetic model that introduces a bottleneck at a set distance away from the start,
that after being passed the model enters a "dense field" of violating states. 

#### About the Bug
TODO description of what causes the bug

#### Build & Run _(with recommended settings)_
```bash
make deepdense                                    # build the model checkers
./deepdense.romp -s 1234 -w 1024 -d 4096 -y       # check with romp
./deepdense.nsym.romp -s 1234 -w 1024 -d 4096 -y  # check with romp (no symmetry)
./deepdense.ru                                    # verify with rumur
./deepdense.cm -m1024                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |  t _(ms)_  | Bug(s) Found / Property(s) Violated                                        |
|:-------:|-----------:|:---------------------------------------------------------------------------|
|   romp  |  6,073.600 | invariant "sum" (x45)                                                      |
| ns-romp | 20,687.### | invariant "sum" (x2)                                                       |
|  rumur  |  1,###.### | invariant "sum"                                                            |
| CMurphi |  1,55#.### | invariant "sum"                                                            |

Note how romp with no symmetry reduction requires more walks 
and a greater max depth than it's counterpart with our symmetry reduction enabled 
and still only a few of the walks with this seed find the bug.



### [`deepsparse.m`](./deepsparse.m)
This model is a synthetic model that introduces a bottleneck at a set distance away from the start,
that after being passed the model enters a "sparse field" of violating states. 

#### About the Bug
TODO description of what causes the bug

#### Build & Run _(with recommended settings)_
```bash
make deepsparse                                    # build the model checkers
./deepsparse.romp -s 1234 -w 1024 -d 2048 -y       # check with romp
./deepsparse.nsym.romp -s 1234 -w 1024 -d 4096 -y  # check with romp (no symmetry)
./deepsparse.ru                                    # verify with rumur
./deepsparse.cm -m1024                             # verify with CMurphi
```

#### Expected Results
> _**Note:** run times are highly dependent on your hardware & current utilization,_
> _all our results are on x86-64/AMD64 systems with at least 6 cores._<br/>
> `#` denotes when the value of the place was not given by the measuring software.

|   Tool  |  t _(ms)_  | Bug(s) Found / Property(s) Violated                                        |
|:-------:|-----------:|:---------------------------------------------------------------------------|
|   romp  |  5,871.763 | invariant "everyone_is_not_ideal" (x18)                                    |
| ns-romp | 11,802.### | invariant "everyone_is_not_ideal" (x2)                                     |
|  rumur  |  2,###.### | invariant "everyone_is_not_ideal"                                          |
| CMurphi |  6,76#.### | invariant "everyone_is_not_ideal"                                          |

Note how romp with no symmetry reduction requires more walks 
and a greater max depth than it's counterpart with our symmetry reduction enabled 
and still only a few of the walks with this seed find the bug.


### [`flash_bug.m`](./flash_bug.m)
TODO AO ...
TODO AO finish creating this model before inserting it's info here


### [`dash_bug.m`](./dash_bug.m)
TODO AO ...
TODO AO finish creating this model before inserting it's info here



