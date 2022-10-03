#pragma once
//* University of Utah, School of Computing, Center for Parallel compute at Utah (CPU), Ganesh Research Group, Romp
//* Andrew Osterhout, Ajantha Varadharaaj

#include<stdio>
#include<functional>
#include<string>

// << =============================== Preprocessor DEclarations ================================ >> 

#define STATE_HISTORY_SIZE;
#ifndef RULES_SIZE
#define RULES_SIZE 0
#endif
#ifndef INVARIANTS_SIZE
#define RULE_COUNT 0
#endif


namespace romp
{

  // << =================================== Type Declarations ==================================== >> 

  class ProtoState {
  public:
    // was this state tripped
    bool valid;
    // tripped thing
    std::string tripped;
    // how many rules have tried to be applied to this state
    int level;
    // how many rules have actually been applied to this state
    int true_level;
    // array of intigers representing the rul ID's applied to this state (treated as a circular buffer array)
    int history[STATE_HISTORY_SIZE];

    /**
     * @brief call if rule is applied to store what rule made the change in the history circular buffer.
     * @param id the id of the rule that was applied.
     */
    void rule_applied(int id) final
    {
      history[true_level % STATE_HISTORY_SIZE] = id;
      true_level++;
    }
  };

  extern class State;


  template<class S>
  class Rule {
  public:
    std::function<bool(S)> Guard;
    std::function<void(S)> Run;
  };





  // << ================================ Extern Predeclarations ================================== >> 
  extern Rule RULES[];
  extern std::function<bool(ProtoState)> INVARIANTS[];
  extern std::function<bool(ProtoState)> ASSERTIONS[];







  // << ========================================================================================== >> 
  // <<                                         ROMP CODE                                          >> 
  // << ========================================================================================== >> 

    // template<class S, class R>
  void Sim1Step(State states[], Rule rule, size_t state_count)
  {
    for (int s = 0; s < state_count; s++)
      if (rule.Guard(states[s]))
      {
        rule.Run(states[s]);
        states[i].rule_applied(rule.id); // this keeps track of history and other overhead
        // These could possibly be parrallelized even better for GPU using shared memory. (not implimented here, could introduce data races)
        for (int i = 0;i < INVARIANTS_SIZE;i++)
          states[s].valid |= INVARIANTS[i](states[i]); // this will need to change after we figure shit out
        for (int a = 0;a < ASSERTIONS_SIZE;a++)
          states[s].valid |= ASSERTIONS[a](states[i]); // this will need to change after we figure shit out
      }
  }
}
