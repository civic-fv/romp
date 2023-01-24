type
    ms_t: multiset [4] of 0..3;

var
    m1,m2: ms_t;


Startstate "init uneven"
Begin
    MultisetAdd(0,m1);
    MultisetAdd(0,m1);
    MultisetAdd(0,m2);
    MultisetAdd(1,m1);
    MultisetAdd(1,m2);
    MultisetAdd(1,m2);
EndStartstate;

rule "spin"
    (1 = 2) ==> begin EndRule;

Invariant "multiplicity matters" m1 = m2;
Invariant "multiplicity does NOT matter" m1 != m2;

