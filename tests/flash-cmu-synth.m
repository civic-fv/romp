--| Variable declarations
const
  PROC_NUM : 3;
  PROCTXN_NUM : 3;
  DIR_NUM : 1;
  DIRTXN_NUM : 10;
type
  ProcId : scalarset(PROC_NUM);
  ProcTxnId : scalarset(PROCTXN_NUM);
  DirId : scalarset(DIR_NUM);
  DirTxnId : scalarset(DIRTXN_NUM);
  CacheState : enum { M, E, S, I };
  Command : enum { Empty, Get, GetFwd, Getx, GetxFwd, Puts, PutsFwd, Putx,
                   PutxFwd, Nak, Nakc, NakFwd, Shwb, FAck, Inv, InvAck };
  Flow : union { Command,
                 enum { None, fl_0_1_2_3, fl_0, fl_1, fl_2_3, fl_2, fl_3,
                        fl_4_5_6_7_8_9, fl_4, fl_5, fl_5_6_7, fl_6, fl_7,
                        fl_8, fl_9 } };
  EVENTS : enum { ProcSendsGet, DirRecvsGetAndSendsNak, ProcRecvsNak,
                  DirRecvsGetAndSendsPuts, ProcRecvsPuts,
                  DirRecvsGetAndSendsGetFwd, ProcRecvsGetFwdAndSendsPutsFwd,
                  ProcRecvsPutsFwd, DirRecvsShwb,
                  ProcRecvsGetFwdAndSendsNakFwd, ProcRecvsNakFwd,
                  DirRecvsNakc, ProcSendsGetx, DirRecvsGetxAndSendsNak,
                  DirRecvsGetxAndSendsPutx, ProcRecvsPutx,
                  ProcRecvsInvAndSendsInvAck, DirRecvsInvAck,
                  DirRecvsGetxAndSendsGetxFwd,
                  ProcRecvsGetxFwdAndSendsPutxFwd, ProcRecvsPutxFwd,
                  DirRecvsFAck, ProcRecvsGetxFwdAndSendsNakFwd };
  ProcTxn : record
    flow : Flow;
    event : EVENTS;
    request : boolean;
    primary_id : DirId;
    primary_txn_id : DirTxnId;
  end;
  Proc : record
    state : CacheState;
    invmarked : boolean;
    txns : array[ProcTxnId] of ProcTxn;
  end;
  DirTxn : record
    flow : Flow;
    event : EVENTS;
    request : boolean;
    primary_id : ProcId;
    primary_txn_id : ProcTxnId;
  end;
  Dir : record
    sharset : array[ProcId] of boolean;
    invset : array[ProcId] of boolean;
    sharvld : boolean;
    headptr : ProcId;
    headvld : boolean;
    pending : boolean;
    local : boolean;
    dirty : boolean;
    txns : array[DirTxnId] of DirTxn;
  end;
  MsgProc2Dir : record
    cmd : Command;
    mytid : ProcTxnId;
    yourtid : DirTxnId;
    primary_id : DirId;
    primary_txn_id : DirTxnId;
    data : record
      zeroth : ProcId;
    end;
    read : boolean;
  end;
  MsgProc2Proc : record
    cmd : Command;
    mytid : ProcTxnId;
    yourtid : ProcTxnId;
    primary_id : ProcId;
    primary_txn_id : ProcTxnId;
    read : boolean;
  end;
  MsgDir2Proc : record
    cmd : Command;
    mytid : DirTxnId;
    yourtid : ProcTxnId;
    primary_id : ProcId;
    primary_txn_id : ProcTxnId;
    read : boolean;
    data : record
      zeroth : ProcId;
    end;
  end;
var
  procs : array[ProcId] of Proc;
  dirs : array[DirId] of Dir;
  home : ProcId;
var
  unimsg_req : array[ProcId] of array[ProcTxnId] of array[DirId] of MsgProc2Dir;
  unimsg_rsp : array[DirId] of array[ProcTxnId] of array[ProcId] of MsgDir2Proc;
  unimsg_fwdrsp : array[ProcId] of array[ProcTxnId] of array[ProcId] of MsgProc2Proc;
var
  invmsg_req : array[DirId] of array[DirTxnId] of array[ProcId] of MsgDir2Proc;
  invmsg_rsp : array[ProcId] of array[DirTxnId] of array[DirId] of MsgProc2Dir;
  unimsg_fwd : array[DirId] of array[DirTxnId] of array[ProcId] of MsgDir2Proc;
  nakcmsg : array[ProcId] of array[DirTxnId] of array[DirId] of MsgProc2Dir;
  shwbmsg : array[ProcId] of array[DirTxnId] of array[DirId] of MsgProc2Dir;
var
  unimsg_p2p : array[ProcId] of array[ProcTxnId] of array[ProcId] of MsgProc2Proc;
--| Function and procedure declarations
procedure cleartxn_Proc (var txn: ProcTxn);
  begin
    txn.flow := None;
    txn.request := false;
  end;
procedure cleartxn_Dir (var txn: DirTxn);
  begin
    txn.flow := None;
    txn.request := false;
  end;
procedure clearmsg_Proc_Dir (var msg: MsgProc2Dir);
  begin
    msg.cmd := Empty;
  end;
procedure clearmsg_Dir_Proc (var msg: MsgDir2Proc);
  begin
    msg.cmd := Empty;
  end;
procedure clearmsg_Proc_Proc (var msg: MsgProc2Proc);
  begin
    msg.cmd := Empty;
  end;
procedure init ();
  begin
    for i : ProcId do
      for k : DirId do
        for j : ProcTxnId do
          procs[i].txns[j].flow := None;
          procs[i].txns[j].request := false;
          unimsg_req[i][j][k].cmd := Empty;
          unimsg_req[i][j][k].read := false;
          unimsg_rsp[k][j][i].cmd := Empty;
          unimsg_rsp[k][j][i].read := false;
        end;
        for j : DirTxnId do
          dirs[k].txns[j].flow := None;
          dirs[k].txns[j].request := false;
          invmsg_rsp[i][j][k].cmd := Empty;
          invmsg_rsp[i][j][k].read := false;
          invmsg_req[k][j][i].cmd := Empty;
          invmsg_req[k][j][i].read := false;
          shwbmsg[i][j][k].cmd := Empty;
          shwbmsg[i][j][k].read := false;
          nakcmsg[i][j][k].cmd := Empty;
          nakcmsg[i][j][k].read := false;
          unimsg_fwd[k][j][i].cmd := Empty;
          unimsg_fwd[k][j][i].read := false;
        end;
      end;
    end;
    for i : ProcId do
      for k : ProcId do
        for j : ProcTxnId do
          unimsg_fwdrsp[i][j][k].cmd := Empty;
          unimsg_fwdrsp[i][j][k].read := false;
        end;
      end;
    end;
  end;
--| Rules
startstate "III"
begin
  init();
  for i : ProcId do
    procs[i].state := I;
    procs[i].invmarked := false;
    home := i;
    for j : DirId do
      dirs[j].sharset[i] := false;
      dirs[j].invset[i] := false;
      dirs[j].pending := false;
      dirs[j].headvld := false;
      dirs[j].headptr := i;
      dirs[j].local := false;
      dirs[j].dirty := false;
      dirs[j].sharvld := false;
    end;
  end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGet"
    procs[procid].state = I & procid != home
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_0_1_2_3;
    txn.event := ProcSendsGet;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Get;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetAndSendsNak"
    (dirs[dirid].pending = true
     | dirs[dirid].dirty & !dirs[dirid].local & dirs[dirid].headptr = procid
     | dirs[dirid].dirty & dirs[dirid].local & procs[home].state != E)
    & recv0.cmd = Get
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_0;
    txn.event := DirRecvsGetAndSendsNak;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].cmd := Nak;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].mytid := dir_txn_id;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].yourtid :=
    txn.primary_txn_id;
    cleartxn_Dir(txn);
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_rsp[dirid][proc_txn_id][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsNak"
    true
    & recv0.cmd = Nak
    & recv0.yourtid = proc_txn_id
    & txn.flow = fl_0_1_2_3
  ==>
  begin
    txn.flow := fl_0;
    txn.event := ProcRecvsNak;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGet1"
    procs[procid].state = I & procid != home
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_0_1_2_3;
    txn.event := ProcSendsGet;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Get;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetAndSendsPuts"
    !dirs[dirid].pending
    & (!dirs[dirid].dirty | dirs[dirid].dirty & dirs[dirid].local)
    & recv0.cmd = Get
    & txn.flow = None
  ==>
  begin
    if dirs[dirid].dirty then
      dirs[dirid].dirty := false;
      procs[home].state := I;
      dirs[dirid].local := false;
      dirs[dirid].headvld := true;
      dirs[dirid].headptr := procid;
    else
      if dirs[dirid].headvld then
        dirs[dirid].sharvld := true;
        dirs[dirid].sharset[procid] := true;
      else
        dirs[dirid].headvld := true;
        dirs[dirid].headptr := procid;
      end;
    end;
    dirs[dirid].sharvld := true;
    txn.flow := fl_1;
    txn.event := DirRecvsGetAndSendsPuts;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].cmd := Puts;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].mytid := dir_txn_id;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].yourtid :=
    txn.primary_txn_id;
    cleartxn_Dir(txn);
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_rsp[dirid][proc_txn_id][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsPuts"
    true
    & recv0.cmd = Puts
    & recv0.yourtid = proc_txn_id
    & txn.flow = fl_0_1_2_3
  ==>
  begin
    if !procs[procid].invmarked then
      procs[procid].state := S;
    else
      procs[procid].invmarked := false;
    end;
    txn.flow := fl_1;
    txn.event := ProcRecvsPuts;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGet2"
    procs[procid].state = I & procid != home
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_0_1_2_3;
    txn.event := ProcSendsGet;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Get;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetAndSendsGetFwd"
    !dirs[dirid].pending
    & dirs[dirid].dirty
    & !dirs[dirid].local
    & recv0.cmd = Get
    & txn.flow = None
  ==>
  begin
    dirs[dirid].pending := true;
    txn.flow := fl_2_3;
    txn.event := DirRecvsGetAndSendsGetFwd;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    for proc2id : ProcId do
      if proc2id = dirs[dirid].headptr then
        unimsg_fwd[dirid][dir_txn_id][proc2id].cmd := GetFwd;
        unimsg_fwd[dirid][dir_txn_id][proc2id].mytid := dir_txn_id;
        unimsg_fwd[dirid][dir_txn_id][proc2id].data.zeroth := procid;
      end;
    end;
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  proc2id : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : unimsg_fwd[dirid][dir_txn_id][proc2id];
  procid : recv0.data.zeroth;
  txn : procs[proc2id].txns[proc_txn_id]
do
  rule "ProcRecvsGetFwdAndSendsPutsFwd"
    (procs[proc2id].state = E |procs[proc2id].state = S) & recv0.cmd = GetFwd & txn.flow = None
  ==>
  begin
    procs[proc2id].state := S;
    txn.flow := fl_2;
    txn.event := ProcRecvsGetFwdAndSendsPutsFwd;
    txn.primary_id := dirid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].cmd := PutsFwd;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].mytid := proc_txn_id;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].yourtid :=
    proc_txn_id;
    shwbmsg[proc2id][txn.primary_txn_id][dirid].cmd := Shwb;
    shwbmsg[proc2id][txn.primary_txn_id][dirid].mytid := proc_txn_id;
    shwbmsg[proc2id][txn.primary_txn_id][dirid].yourtid := txn.primary_txn_id;
    shwbmsg[proc2id][txn.primary_txn_id][dirid].data.zeroth := procid;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;

ruleset
  procid : ProcId;
  proc2id : ProcId;
proc_txn_id : ProcTxnId;
  proc_txn_id1 : ProcTxnId
do
alias
  recv0 : unimsg_fwdrsp[proc2id][proc_txn_id1][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsPutsFwd"
    true
    & recv0.cmd = PutsFwd
    & recv0.yourtid = proc_txn_id1
    & txn.flow = fl_0_1_2_3
  ==>
  begin
    if !procs[procid].invmarked then
      procs[procid].state := S;
    else
      procs[procid].invmarked := false;
    end;
    txn.flow := fl_2;
    txn.event := ProcRecvsPutsFwd;
    cleartxn_Proc(txn);
    clearmsg_Proc_Proc(recv0);
  end
end;
end;
ruleset
  dirid : DirId;
  proc2id : ProcId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : shwbmsg[proc2id][dir_txn_id][dirid];
  procid : recv0.data.zeroth;
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsShwb"
    true & recv0.cmd = Shwb & recv0.yourtid = dir_txn_id & txn.flow = fl_2_3
  ==>
  begin
    dirs[dirid].pending := false;
    dirs[dirid].dirty := false;
    dirs[dirid].sharvld := true;
    dirs[dirid].sharset[procid] := true;
    txn.flow := fl_2;
    txn.event := DirRecvsShwb;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Dir(txn);
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGet3"
    procs[procid].state = I & procid != home
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_0_1_2_3;
    txn.event := ProcSendsGet;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Get;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetAndSendsGetFwd1"
    !dirs[dirid].pending
    & dirs[dirid].dirty
    & !dirs[dirid].local
    & recv0.cmd = Get
    & txn.flow = None
  ==>
  begin
    dirs[dirid].pending := true;
    txn.flow := fl_2_3;
    txn.event := DirRecvsGetAndSendsGetFwd;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    for proc2id : ProcId do
      if proc2id = dirs[dirid].headptr then
        unimsg_fwd[dirid][dir_txn_id][proc2id].cmd := GetFwd;
        unimsg_fwd[dirid][dir_txn_id][proc2id].mytid := dir_txn_id;
        unimsg_fwd[dirid][dir_txn_id][proc2id].data.zeroth := procid;
      end;
    end;
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  proc2id : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : unimsg_fwd[dirid][dir_txn_id][proc2id];
  procid : recv0.data.zeroth;
  txn : procs[proc2id].txns[proc_txn_id]
do
  rule "ProcRecvsGetFwdAndSendsNakFwd"
    procs[proc2id].state != E & procs[proc2id].state != S & recv0.cmd = GetFwd & txn.flow = None
  ==>
  begin
    txn.flow := fl_3;
    txn.event := ProcRecvsGetFwdAndSendsNakFwd;
    txn.primary_id := dirid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].cmd := NakFwd;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].mytid := proc_txn_id;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].yourtid :=
    proc_txn_id;
    nakcmsg[proc2id][txn.primary_txn_id][dirid].cmd := Nakc;
    nakcmsg[proc2id][txn.primary_txn_id][dirid].mytid := proc_txn_id;
    nakcmsg[proc2id][txn.primary_txn_id][dirid].yourtid := txn.primary_txn_id;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;

ruleset
  procid : ProcId;
  proc2id : ProcId;
proc_txn_id : ProcTxnId;
  proc_txn_id1 : ProcTxnId
do
alias
  recv0 : unimsg_fwdrsp[proc2id][proc_txn_id1][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsNakFwd"
    true
    & recv0.cmd = NakFwd
    & recv0.yourtid = proc_txn_id1
    & txn.flow = fl_0_1_2_3
  ==>
  begin
    txn.flow := fl_3;
    txn.event := ProcRecvsNakFwd;
    cleartxn_Proc(txn);
    clearmsg_Proc_Proc(recv0);
  end
end;
end;
ruleset
  dirid : DirId;
  proc2id : ProcId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : nakcmsg[proc2id][dir_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsNakc"
    true & recv0.cmd = Nakc & recv0.yourtid = dir_txn_id & txn.flow = fl_2_3
  ==>
  begin
    dirs[dirid].pending := false;
    txn.flow := fl_3;
    txn.event := DirRecvsNakc;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Dir(txn);
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGetx"
    (procs[procid].state = I | procs[procid].state = S)
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_4_5_6_7_8_9;
    txn.event := ProcSendsGetx;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Getx;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetxAndSendsNak"
    (dirs[dirid].pending = true
     | dirs[dirid].dirty & !dirs[dirid].local & dirs[dirid].headptr = procid
     | dirs[dirid].dirty & dirs[dirid].local & procs[home].state != E)
    & recv0.cmd = Getx
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_4;
    txn.event := DirRecvsGetxAndSendsNak;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].cmd := Nak;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].mytid := dir_txn_id;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].yourtid :=
    txn.primary_txn_id;
    cleartxn_Dir(txn);
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_rsp[dirid][proc_txn_id][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsNak1"
    true
    & recv0.cmd = Nak
    & recv0.yourtid = proc_txn_id
    & txn.flow = fl_4_5_6_7_8_9
  ==>
  begin
    txn.flow := fl_4;
    txn.event := ProcRecvsNak;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGetx1"
    (procs[procid].state = I | procs[procid].state = S)
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_4_5_6_7_8_9;
    txn.event := ProcSendsGetx;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Getx;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetxAndSendsPutx"
    !dirs[dirid].pending
    & (dirs[dirid].dirty -> dirs[dirid].local & procs[home].state = E)
    & dirs[dirid].dirty
    & recv0.cmd = Getx
    & txn.flow = None
  ==>
  begin
    for p : ProcId do
      dirs[dirid].sharset[p] := false;
      dirs[dirid].invset[p] := false;
    end;
    dirs[dirid].dirty := true;
    dirs[dirid].sharvld := false;
    dirs[dirid].headvld := true;
    dirs[dirid].headptr := procid;
    dirs[dirid].local := false;
    procs[home].state := I;
    txn.flow := fl_5;
    txn.event := DirRecvsGetxAndSendsPutx;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].cmd := Putx;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].mytid := dir_txn_id;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].yourtid :=
    txn.primary_txn_id;
    cleartxn_Dir(txn);
    clearmsg_Proc_Dir(recv0);
  end
end;
end;

ruleset
  procid : ProcId;
  dirid : DirId;
proc_txn_id : ProcTxnId;
  proc_txn_id1 : ProcTxnId
do
alias
  recv0 : unimsg_rsp[dirid][proc_txn_id1][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsPutx"
    true
    & recv0.cmd = Putx
    & recv0.yourtid = proc_txn_id1
    & txn.flow = fl_4_5_6_7_8_9
  ==>
  begin
    procs[procid].state := E;
    procs[procid].invmarked := false;
    txn.flow := fl_5_6_7;
    txn.event := ProcRecvsPutx;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGetx2"
    (procs[procid].state = I | procs[procid].state = S)
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_4_5_6_7_8_9;
    txn.event := ProcSendsGetx;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Getx;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetxAndSendsPutx1"
    !dirs[dirid].pending
    & (dirs[dirid].dirty -> dirs[dirid].local & procs[home].state = E)
    & !dirs[dirid].dirty
    & (dirs[dirid].headvld -> dirs[dirid].headptr = procid)
    & forall p : ProcId do p != procid -> !dirs[dirid].sharset[p] end
    & recv0.cmd = Getx
    & txn.flow = None
  ==>
  begin
    for p : ProcId do
      dirs[dirid].sharset[p] := false;
      dirs[dirid].invset[p] := false;
    end;
    dirs[dirid].headptr := procid;
    procs[home].state := I;
    dirs[dirid].local := false;
    dirs[dirid].dirty := true;
    dirs[dirid].sharvld := false;
    if dirs[dirid].local then
      procs[home].invmarked := true;
    end;
    txn.flow := fl_6;
    txn.event := DirRecvsGetxAndSendsPutx;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].cmd := Putx;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].mytid := dir_txn_id;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].yourtid :=
    txn.primary_txn_id;
    cleartxn_Dir(txn);
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_rsp[dirid][proc_txn_id][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsPutx1"
    true
    & recv0.cmd = Putx
    & recv0.yourtid = proc_txn_id
    & txn.flow = fl_4_5_6_7_8_9
  ==>
  begin
    procs[procid].state := E;
    procs[procid].invmarked := false;
    txn.flow := fl_5_6_7;
    txn.event := ProcRecvsPutx;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGetx3"
    (procs[procid].state = I | procs[procid].state = S)
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_4_5_6_7_8_9;
    txn.event := ProcSendsGetx;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Getx;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetxAndSendsPutx2"
    !dirs[dirid].pending
    & (dirs[dirid].dirty -> dirs[dirid].local & procs[home].state = E)
    & !dirs[dirid].dirty
    & !((dirs[dirid].headvld -> dirs[dirid].headptr = procid)
        & forall p : ProcId do p != procid -> !dirs[dirid].sharset[p] end)
    & recv0.cmd = Getx
    & txn.flow = None
  ==>
  begin
    for p : ProcId do
      dirs[dirid].sharset[p] := false;
      if p != procid
         & p != home
         & (dirs[dirid].sharvld & dirs[dirid].sharset[p]
            | dirs[dirid].headvld & dirs[dirid].headptr = p) then
        dirs[dirid].invset[p] := true;
      else
        dirs[dirid].invset[p] := false;
      end;
    end;
    dirs[dirid].headptr := procid;
    procs[home].state := I;
    dirs[dirid].local := false;
    dirs[dirid].dirty := true;
    dirs[dirid].sharvld := false;
    if dirs[dirid].local then
      procs[home].invmarked := true;
    end;
    dirs[dirid].pending := true;
    txn.flow := fl_7;
    txn.event := DirRecvsGetxAndSendsPutx;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].cmd := Putx;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].mytid := dir_txn_id;
    unimsg_rsp[dirid][txn.primary_txn_id][procid].yourtid :=
    txn.primary_txn_id;
    for proc2id : ProcId do
      if proc2id != procid & proc2id != home then
        invmsg_req[dirid][dir_txn_id][proc2id].cmd := Inv;
        invmsg_req[dirid][dir_txn_id][proc2id].mytid := dir_txn_id;
      end;
    end;
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_rsp[dirid][proc_txn_id][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsPutx2"
    true
    & recv0.cmd = Putx
    & recv0.yourtid = proc_txn_id
    & txn.flow = fl_4_5_6_7_8_9
  ==>
  begin
    procs[procid].state := E;
    procs[procid].invmarked := false;
    txn.flow := fl_5_6_7;
    txn.event := ProcRecvsPutx;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;
ruleset
  proc2id : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : invmsg_req[dirid][dir_txn_id][proc2id];
  txn : procs[proc2id].txns[proc_txn_id]
do
  rule "ProcRecvsInvAndSendsInvAck"
    true & recv0.cmd = Inv & txn.flow = None
  ==>
  begin
    if procs[proc2id].state != I then
      procs[proc2id].state := I;
    else
      procs[proc2id].invmarked := true;
    end;
    txn.flow := fl_7;
    txn.event := ProcRecvsInvAndSendsInvAck;
    txn.primary_id := dirid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    invmsg_rsp[proc2id][txn.primary_txn_id][dirid].cmd := InvAck;
    invmsg_rsp[proc2id][txn.primary_txn_id][dirid].mytid := proc_txn_id;
    invmsg_rsp[proc2id][txn.primary_txn_id][dirid].yourtid :=
    txn.primary_txn_id;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;
ruleset
  dirid : DirId;
  dir_txn_id : DirTxnId
do
alias
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsInvAck"
    true
    & forall proc2id : ProcId do
        dirs[dirid].invset[proc2id] ->
          invmsg_rsp[proc2id][dir_txn_id][dirid].cmd = InvAck
          & invmsg_rsp[proc2id][dir_txn_id][dirid].yourtid = dir_txn_id
      end
    & exists proc2id : ProcId do dirs[dirid].invset[proc2id] end
    & txn.flow = fl_7
  ==>
  begin
    for proc2id : ProcId do
      if dirs[dirid].invset[proc2id] then
        invmsg_rsp[proc2id][dir_txn_id][dirid].read := true;
      end;
    end;
    dirs[dirid].pending := false;
    txn.flow := fl_7;
    txn.event := DirRecvsInvAck;
    cleartxn_Dir(txn);
    for proc2id : ProcId do
      if invmsg_rsp[proc2id][dir_txn_id][dirid].read = true then
        clearmsg_Proc_Dir(invmsg_rsp[proc2id][dir_txn_id][dirid]);
      end;
    end;
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGetx4"
    (procs[procid].state = I | procs[procid].state = S)
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_4_5_6_7_8_9;
    txn.event := ProcSendsGetx;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Getx;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetxAndSendsGetxFwd"
    !dirs[dirid].pending
    & dirs[dirid].dirty
    & !dirs[dirid].local
    & dirs[dirid].headptr != procid
    & recv0.cmd = Getx
    & txn.flow = None
  ==>
  begin
    dirs[dirid].pending := true;
    txn.flow := fl_8;
    txn.event := DirRecvsGetxAndSendsGetxFwd;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    for proc2id : ProcId do
      if proc2id = dirs[dirid].headptr then
        unimsg_fwd[dirid][dir_txn_id][proc2id].cmd := GetxFwd;
        unimsg_fwd[dirid][dir_txn_id][proc2id].mytid := dir_txn_id;
        unimsg_fwd[dirid][dir_txn_id][proc2id].data.zeroth := procid;
      end;
    end;
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  proc2id : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : unimsg_fwd[dirid][dir_txn_id][proc2id];
  procid : recv0.data.zeroth;
  txn : procs[proc2id].txns[proc_txn_id]
do
  rule "ProcRecvsGetxFwdAndSendsPutxFwd"
    procs[proc2id].state = E & recv0.cmd = GetxFwd & txn.flow = None
  ==>
  begin
    procs[proc2id].state := I;
    txn.flow := fl_8;
    txn.event := ProcRecvsGetxFwdAndSendsPutxFwd;
    txn.primary_id := dirid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].cmd := PutxFwd;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].mytid := proc_txn_id;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].yourtid :=
    proc_txn_id;
    shwbmsg[proc2id][txn.primary_txn_id][dirid].cmd := FAck;
    shwbmsg[proc2id][txn.primary_txn_id][dirid].mytid := proc_txn_id;
    shwbmsg[proc2id][txn.primary_txn_id][dirid].yourtid := txn.primary_txn_id;
    shwbmsg[proc2id][txn.primary_txn_id][dirid].data.zeroth := procid;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;

ruleset
  procid : ProcId;
  proc2id : ProcId;
proc_txn_id : ProcTxnId;
  proc_txn_id1 : ProcTxnId
do
alias
  recv0 : unimsg_fwdrsp[proc2id][proc_txn_id1][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsPutxFwd"
    true
    & recv0.cmd = PutxFwd
    & recv0.yourtid = proc_txn_id1
    & txn.flow = fl_4_5_6_7_8_9
  ==>
  begin
    procs[procid].state := E;
    procs[procid].invmarked := false;
    txn.flow := fl_8;
    txn.event := ProcRecvsPutxFwd;
    cleartxn_Proc(txn);
    clearmsg_Proc_Proc(recv0);
  end
end;
end;
ruleset
  dirid : DirId;
  proc2id : ProcId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : shwbmsg[proc2id][dir_txn_id][dirid];
  procid : recv0.data.zeroth;
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsFAck"
    true & recv0.cmd = FAck & recv0.yourtid = dir_txn_id & txn.flow = fl_8
  ==>
  begin
    dirs[dirid].pending := false;
    dirs[dirid].dirty := true;
    dirs[dirid].headvld := true;
    dirs[dirid].headptr := procid;
    txn.flow := fl_8;
    txn.event := DirRecvsFAck;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Dir(txn);
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  procid : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId
do
alias
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcSendsGetx5"
    (procs[procid].state = I | procs[procid].state = S)
    & true
    & forall i : ProcTxnId do !procs[procid].txns[i].request end
    & txn.flow = None
  ==>
  begin
    txn.flow := fl_4_5_6_7_8_9;
    txn.event := ProcSendsGetx;
    txn.request := true;
    txn.primary_id := dirid;
    unimsg_req[procid][proc_txn_id][dirid].cmd := Getx;
    unimsg_req[procid][proc_txn_id][dirid].mytid := proc_txn_id;
  end
end;
end;
ruleset
  dirid : DirId;
  procid : ProcId;
  dir_txn_id : DirTxnId;
  proc_txn_id : ProcTxnId
do
alias
  recv0 : unimsg_req[procid][proc_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsGetxAndSendsGetxFwd1"
    !dirs[dirid].pending
    & dirs[dirid].dirty
    & !dirs[dirid].local
    & recv0.cmd = Getx
    & txn.flow = None
  ==>
  begin
    dirs[dirid].pending := true;
    txn.flow := fl_9;
    txn.event := DirRecvsGetxAndSendsGetxFwd;
    txn.primary_id := procid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    for proc2id : ProcId do
      if proc2id = dirs[dirid].headptr then
        unimsg_fwd[dirid][dir_txn_id][proc2id].cmd := GetxFwd;
        unimsg_fwd[dirid][dir_txn_id][proc2id].mytid := dir_txn_id;
        unimsg_fwd[dirid][dir_txn_id][proc2id].data.zeroth := procid;
      end;
    end;
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
ruleset
  proc2id : ProcId;
  dirid : DirId;
  proc_txn_id : ProcTxnId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : unimsg_fwd[dirid][dir_txn_id][proc2id];
  procid : recv0.data.zeroth;
  txn : procs[proc2id].txns[proc_txn_id]
do
  rule "ProcRecvsGetxFwdAndSendsNakFwd"
    procs[proc2id].state != E & recv0.cmd = GetxFwd & txn.flow = None
  ==>
  begin
    txn.flow := fl_9;
    txn.event := ProcRecvsGetxFwdAndSendsNakFwd;
    txn.primary_id := dirid;
    txn.primary_txn_id := recv0.mytid;
    txn.primary_txn_id := recv0.mytid;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].cmd := NakFwd;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].mytid := proc_txn_id;
    unimsg_fwdrsp[proc2id][proc_txn_id][procid].yourtid :=
    proc_txn_id;
    nakcmsg[proc2id][txn.primary_txn_id][dirid].cmd := Nakc;
    nakcmsg[proc2id][txn.primary_txn_id][dirid].mytid := proc_txn_id;
    nakcmsg[proc2id][txn.primary_txn_id][dirid].yourtid := txn.primary_txn_id;
    cleartxn_Proc(txn);
    clearmsg_Dir_Proc(recv0);
  end
end;
end;

ruleset
  procid : ProcId;
  proc2id : ProcId;
proc_txn_id : ProcTxnId;
  proc_txn_id1 : ProcTxnId
do
alias
  recv0 : unimsg_fwdrsp[proc2id][proc_txn_id1][procid];
  txn : procs[procid].txns[proc_txn_id]
do
  rule "ProcRecvsNakFwd1"
    true
    & recv0.cmd = NakFwd
    & recv0.yourtid = proc_txn_id1
    & txn.flow = fl_4_5_6_7_8_9
  ==>
  begin
    txn.flow := fl_9;
    txn.event := ProcRecvsNakFwd;
    cleartxn_Proc(txn);
    clearmsg_Proc_Proc(recv0);
  end
end;
end;
ruleset
  dirid : DirId;
  proc2id : ProcId;
  dir_txn_id : DirTxnId
do
alias
  recv0 : nakcmsg[proc2id][dir_txn_id][dirid];
  txn : dirs[dirid].txns[dir_txn_id]
do
  rule "DirRecvsNakc1"
    true & recv0.cmd = Nakc & recv0.yourtid = dir_txn_id & txn.flow = fl_9
  ==>
  begin
    dirs[dirid].pending := false;
    txn.flow := fl_9;
    txn.event := DirRecvsNakc;
    txn.primary_txn_id := recv0.mytid;
    cleartxn_Dir(txn);
    clearmsg_Proc_Dir(recv0);
  end
end;
end;
--| End of model

--invariant
invariant "safety"
  forall i: ProcId; j:ProcId; d: DirId do
                      ((i != j & !dirs[d].pending) ->  (procs[i].state = E -> procs[j].state = I))
                        end;
