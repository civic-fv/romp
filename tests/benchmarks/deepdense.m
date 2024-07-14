-- Credit: http://formalverification.cs.utah.edu/pdmc03.html

--------------------------------------------------------------------------------
-- RUN: romp "%s" -o - | c++ - -o /dev/null
--------------------------------------------------------------------------------

-- With H = 4, has 9621 errors, at level 161
Const
        INITIAL_VAL: 50;  -- where to start the count.
        L: 1;             --
--         H: 3;             -- H - L + 1 = number of counter processes.
                          -- determines branching factor and # of states.
		H: 4;
        MAX_VAL: (H-L+1) * INITIAL_VAL;
        DESIRED_VAL : (H-L+1)* 10; -- value of each counter for an accept state.
                          -- determines accept state depth.
        bottleneck:  25; -- value at which there is 1 state between the 2 diamonds.
        RESET_VAL : 10;  -- When to reset a counter.  This causes cycles.
                         -- difference between this value and DESIRED_VAL
                         -- determines cycle size.
                         -- should be less than the desired value.
        RESET_TO  : 50;  -- where to reset the counter to.
                         -- should be greater than desired val

Type
        bool_t: Boolean;
        ind_t: L..H;
        val_t: 0..INITIAL_VAL;
        arr_t: Array[ ind_t ] Of val_t;
        sum_t: 0 .. MAX_VAL;
        state_id: 0 .. 2;

Var
        a: arr_t;
       -- accept: Boolean;
        --stateid: state_id;
        stack: Boolean;

Function desired_value(a : arr_t) : boolean;
     begin
     return (
        forall i : ind_t do
        a[i] = DESIRED_VAL end
        );
     end;

Function everyone_at (a  : arr_t ) : boolean;
begin
return (
        forall i : ind_t do
        a[i] = bottleneck end
        );
end;
Function everyone_above ( a : arr_t) : boolean;
Begin
return (
        forall i : ind_t do
        a[i] >= bottleneck end
        );
end;

Function everyone_below ( a : arr_t) : boolean;
Begin
return (
        Forall i : ind_t do
        a[i] <= bottleneck end
        );
end;

Function resetable ( a : arr_t) : boolean;
Begin
return (
        Forall i : ind_t do
        a[i] <= RESET_VAL end
        );
end;




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


rule "reset everyone"
resetable (a)
     ==>
begin
For j : ind_t Do
        a[j] := RESET_TO;
end;
End;


Ruleset i : L .. H Do

        Rule
                a[i] > bottleneck &
                everyone_above (a)
        ==>
        Begin
                Decrement( a[i] );
        End;

-- added by Hemanth
		Rule
				a[i] >= bottleneck &
					everyone_above (a)
		==>
		Begin
				Increment( a[i] );
		End;

        Rule
                everyone_at (a)
        ==>
        Begin
                Decrement( a[i] );
        End;

        Rule
                a[i] <= bottleneck &
                everyone_below (a)
        ==>
        Begin
                Decrement( a[i] );
        End;

-- added by Hemanth
		Rule
				a[i] < bottleneck &
				everyone_below (a)
		==>
		Begin
				Increment( a[i] );
		End;

End;

--propertyrule "1"
  --      (stateid = 1)
    --    ==>
      --  Begin
        --     stateid := 0;
          --   accept := false;
        --End;

--propertyrule "2"
  --      stateid = 0
    --    ==>
      --  Begin
        --if(Sum(a) = DESIRED_VAL) then
          --   stateid := 2;
            -- accept := true;
        --endif
        --End;
--propertystartstate
--begin
  --      stateid := 0;
    --    accept := false;
--end;

Startstate
  Begin
  --      stateid := 0;
    --    accept := false;
        stack := false;
        For i : ind_t Do
                a[ i ] := INITIAL_VAL;
        End;
  End;

Invariant "sum"
  !(Sum(a) = DESIRED_VAL);
--Invariant "everyone is not ideal"
--Exists i : ind_t Do
 -- a[i] != DESIRED_VAL
--Endexists;
