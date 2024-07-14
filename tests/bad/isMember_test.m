/**
 * a test of how IsMember works in romp vs CMurphi
 */

--------------------------------------------------------------------------------
-- RUN: romp %s -o - | c++ - -o /dev/null
--------------------------------------------------------------------------------

Const N: 8;

Type
  enum_t : Enum {e1, e2, e3};
  scalar_t : Scalarset(N);
  union_t : Union { enum_t, scalar_t, Enum{anon}};
  union_t2 : Union { enum_t, Enum{anon2}};

Var
  union_v: union_t;
  union_v2: union_t2;

StartState "test"
  Undefine union_v;
  put "union_v: "; put union_v; put "\n";
  Clear union_v2;
  put "union_v2: "; put union_v2; put "\n";
EndStartState;

Invariant "Union Undefine's to any member's undefined value" (IsMember(union_v,enum_t) | IsMember(union_v,scalar_t) | IsMember(union_v,Enum{anon}));
Invariant "Union Undefine's to enum_t's Undefined value" IsMember(union_v,enum_t);
Invariant "Union Undefine's to scalar_t's Undefined value" IsMember(union_v,scalar_t);
Invariant "Union Undefine's to scalar_t's Undefined value" IsMember(union_v,Enum{anon});

Invariant "Union Clear's to first member" IsMember(union_v2,enum_t);

Rule "do nothing"
  false ==> Clear union_v2;
EndRule;
