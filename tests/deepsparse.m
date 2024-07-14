
-- Credit: http://formalverification.cs.utah.edu/pdmc03.html

-- --------------------------------------------------------------------
-- Filename:    ss7-bidirected.m
-- Content:     really big transition system, bidirectional edges.
-- Engineer:    Mike Jones
-- Modified:
-- Result:      violate invariant when all counters reach DESIRED_VAL
-- --------------------------------------------------------------------

--------------------------------------------------------------------------------
-- RUN: romp %s -o /dev/stdout | c++ - -o /dev/null
--------------------------------------------------------------------------------


Const
        INITIAL_VAL: 50;  -- where to start the count.
        L: 1;             --
--        H: 3;             -- H - L + 1 = number of counter processes.
                          -- determines branching factor and # of states.
		H: 4;
        MAX_VAL: (H-L+1) * INITIAL_VAL;
        DESIRED_VAL : 20; -- value of each counter for an accept state.
                          -- determines accept state depth.
        RESET_VAL : 0;  -- When to reset a counter.  This causes cycles.
                         -- difference between this value and DESIRED_VAL
                         -- determines cycle size.
                         -- should be less than the desired value.
        RESET_TO  : 20;  -- where to reset the counter to.
                         -- should be greater than desired val

Type
        ind_t: L..H;
        val_t: 0..INITIAL_VAL;
        arr_t: Array[ ind_t ] Of val_t;
        sum_t: 0 .. MAX_VAL;
        state_id: 0 .. 2;

Var
        a: arr_t;
 --       accept: Boolean;
  --      stateid: state_id;
        stack: Boolean;

Procedure Decrement( Var dec : val_t );
Begin
        If dec >= 1 then
                dec := dec - 1;
        End;
End;

Procedure Increment( Var dec : val_t );
Begin
        If dec < INITIAL_VAL then
                dec := dec + 1;
        End;
End;



Function Sum(  a : arr_t ): sum_t;
Var sum : sum_t;
Begin
        sum := 0;
        For i : ind_t Do
                sum := sum + a[i];
        End;
        return sum;
End;


Ruleset i : L .. H Do

        Rule
                a[i] = RESET_VAL
        ==>
        Begin
                a[i] := RESET_TO;
        End;

        Rule
                a[i] > 0
        ==>
        Begin
                Decrement( a[i] );
        End;

        Rule
                a[i] < INITIAL_VAL
        ==>
        Begin
                Increment( a[i] );
        End;
End;

--propertyrule "0"
   --     stateid = 0
    --    ==>
     --   begin
        --    if(a[1] =  DESIRED_VAL & a[2] = DESIRED_VAL & a[3] = DESIRED_VAL)then
          --     stateid := 1;
          --     accept := true;
          --  endif
       -- End;


--propertyrule "1"
       --  (stateid = 1)
       --  ==>
       --  begin
       --     stateid := 0;
       --     accept := false;
       --  End;


Startstate
  Begin
 -- stateid := 0;
  stack := false;
--  accept := false;

        For i : ind_t Do
                a[ i ] := INITIAL_VAL;
        End;
  End;

--propertystartstate
--begin
--  stateid := 0;
--  accept := false;
--End;



--Invariant "Positive sum"
--      Sum(a) > 0;

Invariant "everyone is not ideal"
Exists i : ind_t Do
  a[i] != DESIRED_VAL
Endexists;

