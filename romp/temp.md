> ### **NOT FINISHED, HAD TO CUT MEETING SHORT**
> ### **Please hold comments until finished**

## Data points and tests

> #### Terms:
> - **Murphi model checkers**: model checkers that use the Murphi modeling language (rumur, CMurphi BFS, and CMurphi DFS)
> - **all other model checkers**: all model checkers regardless of modeling language (the above plus: spin, spin swarm, TLA+)


 1. Comparing `romp`'s heuristic symmetry reduction to the control _(pure random)_
    > NOTE: In this case "out-performs" means that **if** NO bug exists then the better performer tries more unique transitions (aka more coverage) than its competitor, **ELSE if** A bug does exist, then overall both performers should have fewer unique transitions (compared to bug model), but the better performer should have the fewest.
    - **H0:** romp's heuristic symmetry reduction out performs the control _(pure random)_ for our class of models in terms of the in terms of **_unique tried transitions_** WHEN there _ARE_ or _are NOT_ _**bugs**_ to find in the model.
      - **Data Selection Rule:** `data = FROM Data WHERE CheckerID=='romp'`
        - We can use pretty much all data run on romp, but we might need to use seprate data from other Hyp groups since we will likely run all of those tests with or with our symmetry reduction based upon the results from this category.  
      - **Stats Test:** 
        ```py
        OneWay_ANOVA_Test(g = { 's-b':   data[RedMeth=='heur-sym' and ModelBugCount>0 ].TransTried, 
                                's-nb':  data[RedMeth=='heur-sym' and ModelBugCount==0].TransTried,
                                'ns-b':  data[RedMeth is None     and ModelBugCount>0 ].TransTried, 
                                'ns-nb': data[RedMeth is None     and ModelBugCount==0].TransTried }, 
                          hyp = `mean(g['s-nb']) >= mean(g['ns-nb']) > mean(g['ns-b']]) >= mean(g['s-b'])`,
                          conf_level = .95)
        ```
        - we are comparing multiple groups/categories of data that have no overlap with each other, and we want to see a compound hypothesis test.
      - **Min Pop Size (_n_):** at least 5 models with buggy and non-buggy implementations (would be a good idea to add an equal number of buggy and non-buggy models made by students or the like), each model should be ran at least 5 times with different seeds per symmetry configuration.
        - good sample size with even distrobution helps reduce the error of ANOVA, , but we need to make sure that we have either NO models who's bug lends itself to either of the implementations, or at least that we have an _even_ or _representative_ selection of said models.
      - **Confidence-Interval/_p_-value:** 95% (0.05)
        - Keep a strict but not unreasonable value given our small sample sizes but likely decently large standard deviations.
    - **H1:** romp's heuristic symmetry reduction out performs the control _(pure random)_ for our class of models in terms of the in terms of **_unique tried transitions_** when there are _bugs_ to find.
      - **Data Selection Rule:** `data = FROM Data WHERE CheckerID=='romp' && ModelBugCount>0`
        - ...same as 1.H3... 
      - **Stats Test:** `Paired_t_Test(g1=data[RedMeth=='heur-sym'].TriedTrans, g2=data[RedMeth='None'].TriedTrans, hyp='mean(g1)>mean(g2)', conf_level=.95)`
        - ...same as 1.H3...
      - **Min Pop Size (_n_):** ...same as 1.H3...
        - ...same as 1.H3..., but we need to make sure that we have either NO models who's bug lends itself to either of the implementations, or at least that we have an _even_ or _representative_ selection of said models.
      - **Confidence-Interval/_p_-value:** 95% (.05)
        - ...same as 1.H3...
    - **H2:** romp's heuristic symmetry reduction out performs the control _(pure random)_ for our class of models in terms of the in terms of **_unique tried transitions_** when there are _NO bugs_ to find.
      - **Data Selection Rule:** `data = FROM Data WHERE CheckerID=='romp' && ModelBugCount==0`
        - ...same as 1.H3 ...
      - **Stats Test:** `Paired_t_Test(g1=data[RedMeth=='heur-sym'].TriedTrans, g2=data[RedMeth='None'].TriedTrans, hyp='mean(g1)>mean(g2)', conf_level=.95)`
        - ...same as 1.H3 ...
      - **Min Pop Size (_n_):** ...same as 1.H3...
        - ...same as 1.H3 ...
      - **Confidence-Interval/_p_-value:** 95% (.05)
        - ...same as 1.H3 ...
    - **H3:** romp's heuristic symmetry reduction out performs the control _(pure random)_ for our class of models in terms of the **_per walk bug discovery rate_** when there are bugs to find.
      - **Data Selection Rule:** `data = FROM Data WHERE CheckerID=='romp' && ModelBugCount>0`
        - We want only tests done with romp, the data table will encode all data that has our hurestic symmetry reduction that we will filter form for our groups, and we want to see only when there are bugs to find
      - **Stats Test:** `Paired_t_Test(g1=data[RedMeth=='heur-sym'].ErrorRate, g2=data[RedMeth='None'].ErrorRate, hyp='mean(g1)<=mean(g2)', conf_level=.95)`
        - we have continuous outcome variable data, and paired exposure variables (each run should have the same model, depth, rand-seed, _etc_; but either has sym-reduction enabled or doesn't)
      - **Min Sample Size (_n_):** at least 5 models that fit our criteria with greater than 5 different runs each 
        - this is arbitrary, but if it is too low we might get false positives
      - **Confidence-Interval/_p_-value:** 95% (.05)
        - This is a generous interval to help with our likely small sample sizes
        
 2. Comparing our class of models/protocols effectiveness on romp with different ratios of \# of walkers to the maximum depth.
    - **H0:** For our class of models/protocols romp is more effective when run with a smaller depth but a larger number of random walkers in terms of _unique tried transitions_ WHERE _**IF**_ there are _**bugs**_ or _NOT_ in the model AND **_IF_** **_heuristic symmetry reduction_**  is _ENABLED_ or _DISABLED_.
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** `OneWay_ANOVA_Test(...)`
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
    - **H1:** For our class of models/protocols romp is more effective when run with a smaller depth but a larger number of random walkers in terms of _unique tried transitions_ when there are **_NO bugs_** in the model and **_heuristic symmetry reduction ENABLED_**.
      - **Data Selection Rule:** `data = FROM Data WHERE CheckerID=='romp' && RedMeth=='heur-sym' && ModelBugCount==0`
        - We only want data from romp runs for internal romp comparisons where we only care about when symmetry is enabled, we only want models that have NO bugs to find, so we can ensure that we are getting maximum unique transitions.
        The Runtime might not be very signficant with/without Symmetry Reduction 
      - **Stats Test:** `Paired_t_Test(g1=data[RedMeth=='heur-sym'].TriedTrans, g2=data[RedMeth='heur-sym'].TriedTrans, hyp='mean(g1)>mean(g2)', conf_level=.95)`
        - We have continuous outcome variable data, and paired exposure variables (each run should have the same model, depth, rand-seed, _etc_; but either has sym-reduction enabled or doesn't)
      - **Min Pop Size (_n_):** ...same as 1.H1/1.H2...
        - ...same as 1.H1/1.H2...
      - **Confidence-Interval/_p_-value:** 95% (.05)
        - Picking a arbitary  higher likelihood 
    - **H2:** For our class of models/protocols romp is more effective when run with a smaller depth but a larger number of random walkers in terms of _unique tried transitions_ when there are **_NO bugs_** in the model and **_heuristic symmetry reduction DISABLED_**.
      - **Data Selection Rule:** `data = FROM Data WHERE CheckerID=='romp' && RedMeth=='None' && ModelBugCount==0`
        - We only want data from romp runs for internal romp comparisons where we only care about when symmetry is disabled, we only want models that have NO bugs to find, so we can ensure that we are getting maximum coverage in case there are No Bugs.
      - **Stats Test:** `Paired_t_Test(g1=data[RedMeth=='heur-sym'].TriedTrans, g2=data[RedMeth='None'].TriedTrans, hyp='mean(g1)>mean(g2)', conf_level=.95)`
        - we have continuous outcome variable data, and paired exposure variables (each run should have the same model, depth, rand-seed, _etc_; but either has sym-reduction enabled or doesn't)
      - **Min Pop Size (_n_):** ...same as 1.H1/1.H2...
        - ...same as 1.H1/1.H2...
      - **Confidence-Interval/_p_-value:** 95% (.05)
        - <reasons>
    - **H3:** For our class of models/protocols romp is more effective when run with a smaller depth but a larger number of random walkers in terms of _unique tried transitions_ when there are **_bugs_** in the model and **_heuristic symmetry reduction ENABLED_**.
      - **Data Selection Rule:** `data = FROM Data WHERE CheckerID=='romp' && RedMeth=='heur-sym' && ModelBugCount>0`
        -  We only want data from romp runs for internal romp comparisons where we only care about when symmetry is enabled, we only want models that have bugs to find, so we can ensure that we are getting maximum unique transitions. The Runtime might not be very signficant with/without Symmetry Reduction 
      - **Stats Test:** `Paired_t_Test(g1=data[RedMeth=='heur-sym'].TriedTrans, g2=data[RedMeth='heur-sym'].TriedTrans, hyp='mean(g1)<mean(g2)', conf_level=.95)`
        - We have continuous outcome variable data, and paired exposure variables (each run should have the same model, depth, rand-seed, _etc_; but either has sym-reduction enabled or doesn't)
      - **Min Pop Size (_n_):** at least 5 models that fit our criteria with greater than 5 different runs each 
        - Picking a arbitary Sample size 
      - **Confidence-Interval/_p_-value:** 95% (.05)
        - Picking a arbitary  higher likelihood
    - **H4:** For our class of models/protocols romp is more effective when run with a smaller depth but a larger number of random walkers in terms of _unique tried transitions_ when there are **_bugs_** in the model and **_heuristic symmetry reduction DISABLED_**.
      - **Data Selection Rule:** `data = FROM Data WHERE CheckerID=='romp' && RedMeth=='None' && ModelBugCount>0`
        - We only want data from romp runs for internal romp comparisons where we only care about when symmetry is enabled, we only want models that have bugs to find, so we can ensure that we are getting maximum unique transitions. The Runtime might not be very signficant with/without Symmetry Reduction 
      - **Stats Test:**`Paired_t_Test(g1=data[RedMeth=='None'].TriedTrans, g2=data[RedMeth='none'].TriedTrans, hyp='mean(g1)<mean(g2)', conf_level=.95)`
        - We have continuous outcome variable data, and paired exposure variables (each run should have the same model, depth, rand-seed, _etc_; but either has sym-reduction enabled or doesn't)
      - **Min Pop Size (_n_):** at least 5 models that fit our criteria with greater than 5 different runs each 
        - Picking a arbitary Sample size <-- Edit me latter
      - **Confidence-Interval/_p_-value:** 95% (.05)
        - Picking a arbitary  higher likelihood  <-- Edit me latter
 
 3. Compare the **runtime** of `romp` to other **_Murphi model checkers_**
    - **H:** `romp` can have a lower runtime than other Murphi model checkers for models with large state spaces, and still find bugs. (aka romp can find bugs faster on larger models)
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
        
 4. Compare the **memory usage** and **cache hits** to other **_Murphi model checkers_**
    - **H1:** romp's lack of a hash table uses less memory than other murphi model checkers and still find bugs
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
    - **H2:** romp's lack of hash table and overall design structure allows for increased caching performance on the cpu, compared to other Murphi model checkers.
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
        
 5. Compare `romp`'s **unique state generation** to other **_Murphi Model Checkers_**
    - **H0:** romp explores more unique states when it doesn't find bugs than other Murphi model checkers on the same model(s) and don't find bugs.
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
    - **H1:** romp explores more unique states when it doesn't find bugs than other Murphi model checkers on the same model(s) and don't find bugs.
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
    - **H2:** romp explores fewer unique states when it finds bugs than other Murphi model checkers on the same large models regardless of if they find a bug not. 
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
    
 6. _¿¿_ Compare `romp`'s number of **rules applied** to other **_Murphi model checkers_** _??_
    - Can we do this? since it means different things in our system compared to non random walking systems (aka comparing apples and oranges).
      - I can technically in romp convert rules applied to be the same as in other model-checkers (by keeping track of ordered pairs of states and rules applied), but it breaks the rate hypothesis from below.
    - **H:** romp can apply rules at a faster rate than other Murphi model checkers.
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
        
 7. Compare **runtime** of `romp` to **_all model checkers_** in consideration.
    - **H:** romp can have a lower runtime than all other model checkers in consideration for our class of models/protocols
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
        
 8. Compare `romp`'s **memory usage** and **cache hits** to **_all model checkers_** in consideration.
    - **H1:** romp's lack of a hash table uses less memory than all other model checkers in consideration and still find bugs
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
    - **H2:** romp's lack of hash table and overall design structure allows for increased caching performance on the cpu, compared to all other model checkers in consideration.
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
        
 9. _¿¿_ Compare `romp`'s **unique state generation** to **_all model checkers_** in consideration with our class of models/protocols _??_
    - Can we do this? since the other systems might not consider state the same way that Murphi does (aka comparing apples and oranges).
    - **H1:** romp explores more unique states when it doesn't find bugs than all other model checkers on the same model(s) and don't find bugs.
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
    - **H2:** romp explores fewer unique states when it finds bugs than all other model checkers on the same large models regardless of if they find a bug not. 
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
        
 10. _¿¿_ Compare `romp`'s number of **rules applied** to **_all model checkers_** in consideration _??_
    - Can we do this? since it means different things in romp _(& possibly spin-swarm)_ compared to non random walking systems (aka comparing apples and oranges).
      - I can technically in romp convert rules applied to be the same as in other non random walking model-checkers (by keeping track of ordered pairs of states and rules applied), but it breaks the rate hypothesis from below.
    - **H:** romp can apply rules at a faster rate than other Murphi model checkers.
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
        
1.  _¿¿_ Compare Murphi model checkers to other languages for cache protocols _??_
    - To prove that Murphi's syntax is better for our target models/protocols
      - we could also pull in other research for this point
    - **H:** <TODO>
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>
      
2.  _¿¿_ Reason out that the other model checkers we are comparing to are reasonable and representative model checkers to use for our class of models at all _??_
    - To prove/reason our comparisons are reasonable
      - we can also pull from other research for this point
    - **H:** <TODO>
      - **Data Selection Rule:** <TODO>
        - <reasons> 
      - **Stats Test:** <TODO>
        - <reasons>
      - **Min Pop Size (_n_):** <TODO>
        - <reasons>
      - **Confidence-Interval/_p_-value:** <TODO>
        - <reasons>


## Data Collection Plans & Procedures

- run all data collection through CHPC with standardized/same config
```sh
#!/bin/sh
#SBATCH --account=<TODO>
#SBATCH --partition=<TODO>
# #SBATCH -n <N/A>  # you should not use this in the slurm scripts but when launching from overall test script
#SBATCH --cpu-per-task=16
#SBATCH --mem=8000
# #SBATCH --time=<N/A> # might end up doing this might just use default
```

- write single script that will queue all tests (and maybe launch data processing and such after it detects all tasks as done)
  - another script to call when data is produced to process all the data
  - make all scripts modular so we can manual rerun single tests if necessary.

- We need to run romp with **_same config_** twice once with traces once without whenever we need both data for time and state generation and/or cache data.  (since trace files conflict with normal runtime)
  - get cache and time data from run with traces **_disabled_**
  - get state generation and rule coverage data from run with trace **_enabled_**

- ...


* * *

## Data Processing Plans & Procedures

- ...
