
/**
 * Credit: http://www.cs.cmu.edu/~tmurali/flow_examples/
 */

--| Variable declarations
const
  AGT_NUM : 3;
  AGTTXN_NUM : 3;
  DIR_NUM : 1;
  DIRTXN_NUM : 10;
type
  AgtId : scalarset(AGT_NUM);
  AgtTxnId : scalarset(AGTTXN_NUM);
  DirId : scalarset(DIR_NUM);
  DirTxnId : scalarset(DIRTXN_NUM);
  CacheState : enum { M_state, E_state, S_state, I_state };
  Command : enum { Empty, ReqS, ReqE, SnpInv, InvAck, GntS, GntE };
  FlowEnum : enum { None, fl_0_1, fl_0, fl_1, fl_2, fl_3_4, fl_3, fl_4 };
  Flow : union { Command,
                 FlowEnum };
  Event : enum { NoEvent, AgtSendsReqS, DirRecvsReqSAndSendsGntS,
                 AgtRecvsGntS, DirRecvsReqSAndSendsSnpInv,
                 DirRecvsInvAckAndSendsGntS, AgtRecvsSnpInvAndSendsInvAck,
                 AgtSendsReqE, DirRecvsReqEAndSendsGntE, AgtRecvsGntE,
                 DirRecvsReqEAndSendsSnpInv, DirRecvsInvAckAndSendsGntE };
  AgtTxn : record
    flow : Flow;
    event : Event;
    request : boolean;
    primary_id : DirId;
    primary_txn_id : DirTxnId;
  end;
  Agt : record
    state : CacheState;
    txns : array[AgtTxnId] of AgtTxn;
  end;
  DirTxn : record
    flow : Flow;
    event : Event;
    request : boolean;
    primary_id : AgtId;
    primary_txn_id : AgtTxnId;
  end;
  Dir : record
    cv : array[AgtId] of boolean;
    busy : boolean;
    excl_gntd : boolean;
    txns : array[DirTxnId] of DirTxn;
  end;
  MsgAgt2Dir : record
    cmd : Command;
    mytid : AgtTxnId;
    yourtid : DirTxnId;
    primary_id : DirId;
    primary_txn_id : DirTxnId;
    read : boolean;
  end;
  MsgDir2Agt : record
    cmd : Command;
    mytid : DirTxnId;
    yourtid : AgtTxnId;
    primary_id : AgtId;
    primary_txn_id : AgtTxnId;
    read : boolean;
  end;
var
  agts : array[AgtId] of Agt;
  dirs : array[DirId] of Dir;
var
  chan1 : array[AgtId] of array[AgtTxnId] of array[DirId] of MsgAgt2Dir;
  chan3 : array[AgtId] of array[DirTxnId] of array[DirId] of MsgAgt2Dir;
var
  chan2 : array[DirId] of array[AgtTxnId] of array[AgtId] of MsgDir2Agt;
--| Function and procedure declarations
procedure cleartxn_Agt (var txn: AgtTxn);
  begin
    txn.flow := None;
    txn.request := false;
  end;
procedure cleartxn_Dir (var txn: DirTxn);
  begin
    txn.flow := None;
    txn.request := false;
  end;
procedure clearmsg_Agt_Dir (var msg: MsgAgt2Dir);
  begin
    msg.cmd := Empty;
  end;
procedure clearmsg_Dir_Agt (var msg: MsgDir2Agt);
  begin
    msg.cmd := Empty;
  end;
procedure clearcvs (d: DirId);
  begin
    for i : AgtId do
      dirs[d].cv[i] := false;
    end;
  end;
function othercvempty (d: DirId; a: AgtId) : boolean;
  begin
    if forall i : AgtId do i = a | !dirs[d].cv[i] end then
      return true;
    else
      return false;
    end;
  end;
procedure init ();
  begin
    for i : AgtId do
      for k : DirId do
        for j : AgtTxnId do
          for l : DirTxnId do
            agts[i].txns[j].flow := None;
            agts[i].txns[j].request := false;
            agts[i].txns[j].event := NoEvent;
            agts[i].txns[j].primary_id := k;
            agts[i].txns[j].primary_txn_id := l;
            chan1[i][j][k].cmd := Empty;
            chan1[i][j][k].read := false;
            chan1[i][j][k].mytid := j;
            chan1[i][j][k].yourtid := l;
            chan1[i][j][k].primary_id := k;
            chan1[i][j][k].primary_txn_id := l;
            chan2[k][j][i].cmd := Empty;
            chan2[k][j][i].read := false;
            chan2[k][j][i].yourtid := j;
            chan2[k][j][i].mytid := l;
            chan2[k][j][i].primary_id := i;
            chan2[k][j][i].primary_txn_id := j;
          end;
        end;
      end;
    end;
    for i : AgtId do
      for k : DirId do
        for j : DirTxnId do
          for l : AgtTxnId do
            dirs[k].txns[j].flow := None;
            dirs[k].txns[j].request := false;
            dirs[k].txns[j].event := NoEvent;
            dirs[k].txns[j].primary_id := i;
            dirs[k].txns[j].primary_txn_id := l;
            chan3[i][j][k].cmd := Empty;
            chan3[i][j][k].read := false;
            chan3[i][j][k].yourtid := j;
            chan3[i][j][k].mytid := l;
            chan3[i][j][k].primary_id := k;
            chan3[i][j][k].primary_txn_id := j;
          end;
        end;
      end;
    end;
  end;
--| Rules
invariant "CntrlProp1"
  forall i : AgtId do
    forall j : AgtId do
      i != j -> (agts[i].state = E_state -> agts[j].state = I_state)
    end
  end;
invariant "CntrlProp2"
  forall i : AgtId do
    forall j : AgtId do
      i != j ->
        (agts[i].state = S_state ->
           agts[j].state = I_state | agts[j].state = S_state)
    end
  end;
startstate "III"
begin
  init();
  for i : AgtId do
    agts[i].state := I_state;
    for j : DirId do
      dirs[j].cv[i] := false;
      dirs[j].busy := false;
      dirs[j].excl_gntd := false;
    end;
  end;
end;
ruleset
  agtid : AgtId;
  dirid : DirId;
  agt_txn_id : AgtTxnId
do
alias
  txn : agts[agtid].txns[agt_txn_id]
do
  rule "AgtSendsReqS"
    agts[agtid].state = I_state
    & true
    & forall i : AgtTxnId do !agts[agtid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_0_1;
    txn.event := AgtSendsReqS;
    txn.request := true;
    txn.primary_id := dirid;
    chan1[agtid][agt_txn_id][dirid].cmd := ReqS;
    chan1[agtid][agt_txn_id][dirid].mytid := agt_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  agtid : AgtId;
  dir_txn_id : DirTxnId;
  agt_txn_id : AgtTxnId
do
alias
  recv0 : chan1[agtid][agt_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsReqSAndSendsGntS"
    dirs[dirid].busy = false
    & dirs[dirid].excl_gntd = false
    & recv0.cmd = ReqS
    & txn.flow = None
  ==>
  begin
    dirs[dirid].cv[agtid] := true;
    txn.flow := fl_0;
    txn.event := DirRecvsReqSAndSendsGntS;
    txn.primary_id := agtid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    chan2[dirid][txn.primary_txn_id][agtid].cmd := GntS;
    chan2[dirid][txn.primary_txn_id][agtid].mytid := dir_txn_id;
    chan2[dirid][txn.primary_txn_id][agtid].yourtid := txn.primary_txn_id;
    cleartxn_Dir(txn);
    clearmsg_Agt_Dir(recv0);
  end
end;
end;
ruleset
  agtid : AgtId;
  dirid : DirId;
  agt_txn_id : AgtTxnId
do
alias
  recv0 : chan2[dirid][agt_txn_id][agtid];
  txn : agts[agtid].txns[agt_txn_id]
do
  rule "AgtRecvsGntS"
    true & recv0.cmd = GntS & recv0.yourtid = agt_txn_id & txn.flow = fl_0_1
  ==>
  begin
    agts[agtid].state := S_state;
    txn.flow := fl_0_1;
    txn.event := AgtRecvsGntS;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Agt(txn);
    clearmsg_Dir_Agt(recv0);
  end
end;
end;
ruleset
  agtid : AgtId;
  dirid : DirId;
  agt_txn_id : AgtTxnId
do
alias
  txn : agts[agtid].txns[agt_txn_id]
do
  rule "AgtSendsReqS1"
    agts[agtid].state = I_state
    & true
    & forall i : AgtTxnId do !agts[agtid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_0_1;
    txn.event := AgtSendsReqS;
    txn.request := true;
    txn.primary_id := dirid;
    chan1[agtid][agt_txn_id][dirid].cmd := ReqS;
    chan1[agtid][agt_txn_id][dirid].mytid := agt_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  agtid : AgtId;
  dir_txn_id : DirTxnId;
  agt_txn_id : AgtTxnId
do
alias
  recv0 : chan1[agtid][agt_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsReqSAndSendsSnpInv"
    dirs[dirid].busy = false
    & dirs[dirid].excl_gntd = true
    & recv0.cmd = ReqS
    & txn.flow = None
  ==>
  begin
    dirs[dirid].busy := true;
    txn.flow := fl_1;
    txn.event := DirRecvsReqSAndSendsSnpInv;
    txn.primary_id := agtid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    for agt2id : AgtId do
      if dirs[dirid].cv[agt2id] then
        chan2[dirid][agt_txn_id][agt2id].cmd := SnpInv;
        chan2[dirid][agt_txn_id][agt2id].mytid := dir_txn_id;
      end;
    end;
    clearmsg_Agt_Dir(recv0);
  end
end;
end;
ruleset
  dirid : DirId;
  agtid : AgtId;
  dir_txn_id : DirTxnId
do
alias
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsInvAckAndSendsGntS"
    true
    & forall agt2id : AgtId do
        dirs[dirid].cv[agt2id] ->
          chan3[agt2id][dir_txn_id][dirid].cmd = InvAck
          & chan3[agt2id][dir_txn_id][dirid].yourtid = dir_txn_id
      end
    & exists agt2id : AgtId do dirs[dirid].cv[agt2id] end
    & txn.flow = fl_1
  ==>
  begin
    for agt2id : AgtId do
      if dirs[dirid].cv[agt2id] then
        chan3[agt2id][dir_txn_id][dirid].read := true;
      end;
    end;
    clearcvs(dirid);
    dirs[dirid].cv[agtid] := true;
    dirs[dirid].excl_gntd := false;
    dirs[dirid].busy := false;
    txn.flow := fl_1;
    txn.event := DirRecvsInvAckAndSendsGntS;
    chan2[dirid][txn.primary_txn_id][agtid].cmd := GntS;
    chan2[dirid][txn.primary_txn_id][agtid].mytid := dir_txn_id;
    chan2[dirid][txn.primary_txn_id][agtid].yourtid := txn.primary_txn_id;
    cleartxn_Dir(txn);
    for agt2id : AgtId do
      if chan3[agt2id][dir_txn_id][dirid].read = true then
        clearmsg_Agt_Dir(chan3[agt2id][dir_txn_id][dirid]);
      end;
    end;
  end
end;
end;
ruleset
  agtid : AgtId;
  dirid : DirId;
  agt_txn_id : AgtTxnId
do
alias
  recv0 : chan2[dirid][agt_txn_id][agtid];
  txn : agts[agtid].txns[agt_txn_id]
do
  rule "AgtRecvsGntS1"
    true & recv0.cmd = GntS & recv0.yourtid = agt_txn_id & txn.flow = fl_0_1
  ==>
  begin
    agts[agtid].state := S_state;
    txn.flow := fl_0_1;
    txn.event := AgtRecvsGntS;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Agt(txn);
    clearmsg_Dir_Agt(recv0);
  end
end;
end;
ruleset
  agtid : AgtId;
  dirid : DirId;
  agt_txn_id : AgtTxnId;
  agt_txn_id1 : AgtTxnId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : chan2[dirid][agt_txn_id1][agtid];
  txn : agts[agtid].txns[agt_txn_id]
do
  rule "AgtRecvsSnpInvAndSendsInvAck"
    (agts[agtid].state = S_state | agts[agtid].state = E_state)
    & recv0.cmd = SnpInv
    & txn.flow = None
  ==>
  begin
    agts[agtid].state := I_state;
    txn.flow := fl_2;
    txn.event := AgtRecvsSnpInvAndSendsInvAck;
    txn.primary_id := dirid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    chan3[agtid][txn.primary_txn_id][dirid].cmd := InvAck;
    chan3[agtid][txn.primary_txn_id][dirid].mytid := agt_txn_id;
    chan3[agtid][txn.primary_txn_id][dirid].yourtid := txn.primary_txn_id;
    cleartxn_Agt(txn);
    clearmsg_Dir_Agt(recv0);
  end
end;
end;
ruleset
  agtid : AgtId;
  dirid : DirId;
  agt_txn_id : AgtTxnId
do
alias
  txn : agts[agtid].txns[agt_txn_id]
do
  rule "AgtSendsReqE"
    (agts[agtid].state = I_state | agts[agtid].state = S_state)
    & true
    & forall i : AgtTxnId do !agts[agtid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_3_4;
    txn.event := AgtSendsReqE;
    txn.request := true;
    txn.primary_id := dirid;
    chan1[agtid][agt_txn_id][dirid].cmd := ReqE;
    chan1[agtid][agt_txn_id][dirid].mytid := agt_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  agtid : AgtId;
  dir_txn_id : DirTxnId;
  agt_txn_id : AgtTxnId
do
alias
  recv0 : chan1[agtid][agt_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsReqEAndSendsGntE"
    dirs[dirid].busy = false
    & othercvempty(dirid, agtid)
    & recv0.cmd = ReqE
    & txn.flow = None
  ==>
  begin
    dirs[dirid].cv[agtid] := true;
    dirs[dirid].excl_gntd := true;
    txn.flow := fl_3;
    txn.event := DirRecvsReqEAndSendsGntE;
    txn.primary_id := agtid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    chan2[dirid][txn.primary_txn_id][agtid].cmd := GntE;
    chan2[dirid][txn.primary_txn_id][agtid].mytid := dir_txn_id;
    chan2[dirid][txn.primary_txn_id][agtid].yourtid := txn.primary_txn_id;
    cleartxn_Dir(txn);
    clearmsg_Agt_Dir(recv0);
  end
end;
end;
ruleset
  agtid : AgtId;
  dirid : DirId;
  agt_txn_id : AgtTxnId
do
alias
  recv0 : chan2[dirid][agt_txn_id][agtid];
  txn : agts[agtid].txns[agt_txn_id]
do
  rule "AgtRecvsGntE"
    true & recv0.cmd = GntE & recv0.yourtid = agt_txn_id & txn.flow = fl_3_4
  ==>
  begin
    agts[agtid].state := E_state;
    txn.flow := fl_3_4;
    txn.event := AgtRecvsGntE;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Agt(txn);
    clearmsg_Dir_Agt(recv0);
  end
end;
end;
ruleset
  agtid : AgtId;
  dirid : DirId;
  agt_txn_id : AgtTxnId
do
alias
  txn : agts[agtid].txns[agt_txn_id]
do
  rule "AgtSendsReqE1"
    (agts[agtid].state = I_state | agts[agtid].state = S_state)
    & true
    & forall i : AgtTxnId do !agts[agtid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_3_4;
    txn.event := AgtSendsReqE;
    txn.request := true;
    txn.primary_id := dirid;
    chan1[agtid][agt_txn_id][dirid].cmd := ReqE;
    chan1[agtid][agt_txn_id][dirid].mytid := agt_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  agtid : AgtId;
  dir_txn_id : DirTxnId;
  agt_txn_id : AgtTxnId
do
alias
  recv0 : chan1[agtid][agt_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsReqEAndSendsSnpInv"
    dirs[dirid].busy = false
    & !othercvempty(dirid, agtid)
    & recv0.cmd = ReqE
    & txn.flow = None
  ==>
  begin
    dirs[dirid].busy := true;
    txn.flow := fl_4;
    txn.event := DirRecvsReqEAndSendsSnpInv;
    txn.primary_id := agtid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    for agt2id : AgtId do
      if dirs[dirid].cv[agt2id] then
        chan2[dirid][agt_txn_id][agt2id].cmd := SnpInv;
        chan2[dirid][agt_txn_id][agt2id].mytid := dir_txn_id;
      end;
    end;
    clearmsg_Agt_Dir(recv0);
  end
end;
end;
ruleset
  dirid : DirId;
  agtid : AgtId;
  dir_txn_id : DirTxnId
do
alias
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsInvAckAndSendsGntE"
    true
    & forall agt2id : AgtId do
        dirs[dirid].cv[agt2id] ->
          chan3[agt2id][dir_txn_id][dirid].cmd = InvAck
          & chan3[agt2id][dir_txn_id][dirid].yourtid = dir_txn_id
      end
    & exists agt2id : AgtId do dirs[dirid].cv[agt2id] end
    & txn.flow = fl_4
  ==>
  begin
    for agt2id : AgtId do
      if dirs[dirid].cv[agt2id] then
        chan3[agt2id][dir_txn_id][dirid].read := true;
      end;
    end;
    clearcvs(dirid);
    dirs[dirid].cv[agtid] := true;
    dirs[dirid].excl_gntd := true;
    dirs[dirid].busy := false;
    txn.flow := fl_4;
    txn.event := DirRecvsInvAckAndSendsGntE;
    chan2[dirid][txn.primary_txn_id][agtid].cmd := GntE;
    chan2[dirid][txn.primary_txn_id][agtid].mytid := dir_txn_id;
    chan2[dirid][txn.primary_txn_id][agtid].yourtid := txn.primary_txn_id;
    cleartxn_Dir(txn);
    for agt2id : AgtId do
      if chan3[agt2id][dir_txn_id][dirid].read = true then
        clearmsg_Agt_Dir(chan3[agt2id][dir_txn_id][dirid]);
      end;
    end;
  end
end;
end;
ruleset
  agtid : AgtId;
  dirid : DirId;
  agt_txn_id : AgtTxnId
do
alias
  recv0 : chan2[dirid][agt_txn_id][agtid];
  txn : agts[agtid].txns[agt_txn_id]
do
  rule "AgtRecvsGntE1"
    true & recv0.cmd = GntE & recv0.yourtid = agt_txn_id & txn.flow = fl_3_4
  ==>
  begin
    agts[agtid].state := E_state;
    txn.flow := fl_3_4;
    txn.event := AgtRecvsGntE;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Agt(txn);
    clearmsg_Dir_Agt(recv0);
  end
end;
end;
--| End of model