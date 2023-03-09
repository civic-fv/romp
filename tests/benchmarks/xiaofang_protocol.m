

-------------------------------------------------------------------------------

const

  ------    common part    ------
  DataCnt: 2;

  ------ outside a cluster ------
  HomeCnt: 1;
  RmtCnt:  2;
  ProcCnt: HomeCnt+RmtCnt;

  ------ inside a cluster  ------
  NODE_NUM :  2;

-------------------------------------------------------------------------------

type

  ------    common part    ------
  ClusterCnt:   0..ProcCnt; 
  NODE :   scalarset(NODE_NUM);
  Datas :  scalarset(DataCnt);
  L2Name:  enum{L2};
  NODE_L2: union {NODE, L2Name};

  Homes: enum {Home};
  Rmt: scalarset(RmtCnt);
  Procss: union {Homes, Rmt};

  CacheCnt: 0..NODE_NUM;
  RACState: enum {
        Inval,   -- Invalid
        WRD,     -- basic operation -- waiting for a read reply
        WRDO,    -- basic operation -- waiting for a read reply
                                    -- with ownership transfer
        WRDX,    -- basic operation -- waiting for a read exclusive reply
        WINV,    -- basic operation -- waiting for invalidate acknowledges
        RRD      -- basic operation -- invalidated read/read
    };

  CACHE_STATE : enum {CACHE_I, CACHE_S, CACHE_E, CACHE_M};
  L2State:      enum{Invld, Shrd, Excl};
  NODE_CMD :    enum {NODE_None, NODE_Get, NODE_GetX};

  NODE_STATE: record
      ProcCmd :   NODE_CMD;
      InvMarked : boolean;
      CacheState: CACHE_STATE;
      CacheData : Datas;

      block_WB: boolean;
    end;

  -- uni msg channel
  UNI_CMD: enum {UNI_None, UNI_Get, UNI_GetX, UNI_Put, UNI_PutX, UNI_Nak, UNI_PutXX,
		 WB_WbAck};
  UNI_MSG: record
    Cmd: UNI_CMD;
    Proc: NODE_L2;
    Data: Datas;
  end;

  -- invalidation msg channel
  INV_CMD: enum {INV_None, INV_Inv, INV_InvAck};
  INV_MSG: record
    Cmd: INV_CMD;
  end;

  -- writeback msg channel
  WB_CMD: enum {WB_None, WB_Wb};
  WB_MSG: record
    Cmd: WB_CMD;
    Proc: NODE_L2;
    Data: Datas;
  end;

  -- ShWb msg channel
  SHWB_CMD: enum {SHWB_None, SHWB_ShWb, SHWB_FAck};
  SHWB_MSG: record
    Cmd: SHWB_CMD;
    Proc: NODE_L2;
    Data: Datas;
    Aux: NODE_L2;
  end;

  -- nack-home msg channel
  NAKC_CMD: enum {NAKC_None, NAKC_Nakc,
                  NAKC_SD};
  NAKC_MSG: record
    Cmd: NAKC_CMD;
    Proc: NODE_L2;
    Aux: NODE_L2;
  end;


  -- main structure
  ProcState: record

    -- these 3 are for invariant purposes
    CurrData: Datas;  
    PrevData: Datas;
    Collecting: boolean;

    -- structure inside a cluster 
    Proc :   array [NODE] of NODE_STATE;

    UniMsg: array [NODE_L2] of UNI_MSG;
    InvMsg: array [NODE_L2] of INV_MSG;
    WbMsg: WB_MSG;
    ShWbMsg: SHWB_MSG;
    NakcMsg: NAKC_MSG;

    -- local dir
    L2: record
      State:   L2State;
      Data:    Datas;
      pending: boolean;  
      Dirty:   boolean;
      ShrSet:  array [NODE] of boolean; 
      InvCnt: CacheCnt;
      HeadPtr: NODE_L2; 
      ReqId:   NODE; -- requesting L1 whose req is pending 
      OnlyCopy: boolean; -- if this cluster has the only copy
      ReqCluster: Procss; -- fwded req cluster
      ReqType: boolean;   -- fwded req type: true if Get otherwise GetX 
      Gblock_WB: boolean;
      isRetired: boolean;
      -- Apr 8
      ifHoldMsg: boolean;
    end;

    -- communicating with outside cluster
    RAC: record
      State:   RACState;
      InvCnt:  ClusterCnt;
    end;
  end;


  ------ outside a cluster  ------

  DirState: record
    isBusy: boolean;
    Mem: Datas;
    State: L2State;
    ShrSet: array [Procss] of boolean;
    InvCnt: ClusterCnt;   -- not really used
    isLocal: boolean;
    HeadPtr: Procss;

    -- invariant purpose
    Collecting: boolean; 
    CurrData: Datas;
    PrevData: Datas;
  end;


GUNI_CMD: enum {GUNI_None, RD_H, RD_RAC, RDX_H, RDX_RAC, ACK, NAK, NAK_Home,
		IACK, IACKX, WB_Ack};
GUNI_MSG: record
  Cmd: GUNI_CMD;
  Cluster: Procss;
  InvCnt: ClusterCnt;
  Data: Datas;
end;

GINV_CMD: enum {GINV_None, INV, SACK};
GINV_MSG: record
  Cmd: GINV_CMD;
  Cluster: Procss;
end;

GWB_CMD: enum {GWB_None, WB};
GWB_MSG: record
  Cmd: GWB_CMD;
  Cluster: Procss;
  Data: Datas;
end;

GSHWB_CMD: enum {GSHWB_None, SHWB, DXFER};
GSHWB_MSG: record
  Cmd: GSHWB_CMD;
  Cluster: Procss;
  Data: Datas;
end;

GNAKC_CMD: enum {GNAKC_None, GNAKC_Nakc, GNAKC_DIR};
GNAKC_MSG: record
  Cmd: GNAKC_CMD;
  Cluster: Procss;
end;



-------------------------------------------------------------------------------

var

  GUniMsg: array [Procss] of GUNI_MSG;
  GInvMsg: array [Procss] of GINV_MSG;
  GWbMsg:  GWB_MSG;
  GShWbMsg: GSHWB_MSG;
  GNakcMsg: GNAKC_MSG;

  Procs: array [Procss] of ProcState;
  Dir: DirState;


-------------------------------------------------------------------------------

ruleset d: Datas do
startstate "Init"

  for p: Procss do
    undefine GUniMsg[p];
    undefine GInvMsg[p];
    GUniMsg[p].Cmd := GUNI_None;
    GInvMsg[p].Cmd := GINV_None;
  end;
  GWbMsg.Cmd := GWB_None;
  GShWbMsg.Cmd := GSHWB_None;
  GNakcMsg.Cmd := GNAKC_None;


  for p: Procss do
    undefine Procs[p];

    -- invariant purpose
    Procs[p].Collecting := false;

    for n: NODE do
      Procs[p].Proc[n].ProcCmd := NODE_None;
      Procs[p].Proc[n].InvMarked := false;
      Procs[p].Proc[n].CacheState := CACHE_I;
      Procs[p].Proc[n].block_WB := false;
    end;

    Procs[p].L2.State := Invld;
    Procs[p].L2.pending := false;
    Procs[p].L2.InvCnt := 0;
    for n: NODE do
      Procs[p].L2.ShrSet[n] := false;
    end;
    Procs[p].L2.isRetired := true;

    Procs[p].L2.InvCnt := 0;
    Procs[p].L2.Dirty := false;
    Procs[p].L2.OnlyCopy := false;
    Procs[p].L2.Gblock_WB := false;
    Procs[p].RAC.State := Inval;
    Procs[p].RAC.InvCnt := 0;

    -- Apr 8
    Procs[p].L2.ifHoldMsg := false;

    for n: NODE_L2 do
      Procs[p].UniMsg[n].Cmd := UNI_None;
      Procs[p].InvMsg[n].Cmd := INV_None;
    end;
    Procs[p].WbMsg.Cmd := WB_None;
    Procs[p].ShWbMsg.Cmd := SHWB_None;
    Procs[p].NakcMsg.Cmd := NAKC_None;

  end;

  undefine Dir;
  Dir.isBusy := false;
  Dir.Mem := d;
  Dir.State := Invld;
  Dir.isLocal := false;
  for p: Rmt do
    Dir.ShrSet[p] := false;
  end;

  -- invariant purpose
  Dir.Collecting := false;
  Dir.PrevData := d;
  Dir.CurrData := d;

endstartstate;
endruleset;



--RuleBase
ruleset p: Procss; src : NODE; data : Datas do
rule "L1_Update_Data"
  Procs[p].Proc[src].CacheState = CACHE_E |
  Procs[p].Proc[src].CacheState = CACHE_M
==>
begin
  Procs[p].Proc[src].CacheState := CACHE_M;
  Procs[p].Proc[src].CacheData := data;

  -- invariant purpose
  Procs[p].CurrData := data;
endrule;
endruleset;



--RuleBase
ruleset p: Procss; src : NODE do
rule "L1_Get"
   Procs[p].Proc[src].ProcCmd = NODE_None &
   Procs[p].Proc[src].CacheState = CACHE_I &
   Procs[p].Proc[src].block_WB = false
==>
begin
  Procs[p].Proc[src].ProcCmd := NODE_Get;
  Procs[p].UniMsg[src].Cmd := UNI_Get;
  Procs[p].UniMsg[src].Proc := L2;
  undefine Procs[p].UniMsg[src].Data;
endrule;
endruleset;



-- RuleBase
ruleset p: Procss; src: NODE do
  rule "L2_Recv_Get_Put"
    Procs[p].UniMsg[src].Cmd = UNI_Get &
    Procs[p].UniMsg[src].Proc = L2 &

    Procs[p].L2.pending = false &
    Procs[p].L2.State = Shrd &
    isundefined(Procs[p].L2.HeadPtr)    -- this expr is added to differentiate rule "L2HeadPtr_Recv_Get_Put"
  ==>
  begin
    Procs[p].L2.ShrSet[src] := true;
    Procs[p].UniMsg[src].Cmd := UNI_Put;
    Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
    undefine Procs[p].UniMsg[src].Proc;
  endrule;
endruleset;




-- Ruleset
ruleset p: Procss; src: NODE do
  rule "L2_busy_Recv_Get(X)_Nak"
    (Procs[p].UniMsg[src].Cmd = UNI_Get |
     Procs[p].UniMsg[src].Cmd = UNI_GetX) &
    Procs[p].UniMsg[src].Proc = L2 &

    Procs[p].L2.pending = true
  ==>
  begin
    Procs[p].UniMsg[src].Cmd := UNI_Nak;
    undefine Procs[p].UniMsg[src].Data;
    undefine Procs[p].UniMsg[src].Proc;
  endrule;
endruleset;



-- RuleBase
ruleset p: Procss; src: NODE do
rule "L2HeadPtr_Recv_Get_Put"
  Procs[p].UniMsg[src].Cmd = UNI_Get &
  Procs[p].UniMsg[src].Proc = L2 &

  Procs[p].L2.pending = false &
  !isundefined(Procs[p].L2.HeadPtr) &
  Procs[p].L2.HeadPtr = L2
==>
begin
  Procs[p].L2.State := Shrd;
  undefine Procs[p].L2.HeadPtr;
  Procs[p].L2.ShrSet[src] := true;

  Procs[p].UniMsg[src].Cmd := UNI_Put;
  Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
  undefine Procs[p].UniMsg[src].Proc;
endrule;
endruleset;



-- RuleBase
ruleset p: Procss; src: NODE do
  rule "L2_Fwd_Get(X)"
    Procs[p].L2.pending = false &
    Procs[p].L2.State = Excl &
    ! isundefined(Procs[p].L2.HeadPtr) &
    Procs[p].L2.HeadPtr != L2 &

    (Procs[p].UniMsg[src].Cmd = UNI_Get |
     Procs[p].UniMsg[src].Cmd = UNI_GetX) &
    Procs[p].UniMsg[src].Proc = L2
  ==>
  var  
    owner: NODE;
    isGet: boolean;
  begin
    owner := Procs[p].L2.HeadPtr;
    isGet := true;
    if (Procs[p].UniMsg[src].Cmd = UNI_GetX) then
      isGet := false;
    end;

    -- must have silentdropped itself
    if (src = owner) then
      if (isGet = true) then
        Procs[p].L2.State := Shrd;
        Procs[p].L2.ShrSet[owner] := true;
        undefine Procs[p].L2.HeadPtr;
        Procs[p].UniMsg[src].Cmd := UNI_Put;
        undefine Procs[p].UniMsg[src].Proc;
        Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
      else
        Procs[p].UniMsg[src].Cmd := UNI_PutX;
        undefine Procs[p].UniMsg[src].Proc;
        Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
      end;

    -- fwd req to remote owner
    else
      Procs[p].L2.pending := true;
      if (isGet = true) then
        Procs[p].UniMsg[src].Cmd := UNI_Get;
        Procs[p].UniMsg[src].Proc := owner;
        undefine Procs[p].UniMsg[src].Data;
      else 
        Procs[p].UniMsg[src].Cmd := UNI_GetX;
        Procs[p].UniMsg[src].Proc := owner;
        undefine Procs[p].UniMsg[src].Data;
      end;
    end;
  endrule;
endruleset;



-- RuleBase
ruleset p: Procss; src: NODE do
  rule "L2_Recv_Get(X)_OutGet(X)"
    (Procs[p].UniMsg[src].Cmd = UNI_Get |
     Procs[p].UniMsg[src].Cmd = UNI_GetX) &
    Procs[p].UniMsg[src].Proc = L2 &

    Procs[p].L2.State = Invld &
    Procs[p].L2.pending = false &
    Procs[p].RAC.State = Inval &
    Procs[p].L2.Gblock_WB = false
  ==>
  var isGet: boolean;
  begin
    Procs[p].L2.pending := true;
    Procs[p].L2.ReqId := src;

    isGet := true;
    if (Procs[p].UniMsg[src].Cmd = UNI_GetX) then
      isGet := false;
    end;
    if (isGet = true) then
      if (p = Home) then
        Procs[p].RAC.State := WRDO;
      else
        Procs[p].RAC.State := WRD;
        GUniMsg[p].Cmd := RD_H;
        undefine GUniMsg[p].Cluster;
        undefine GUniMsg[p].Data;
        undefine GUniMsg[p].InvCnt;
      end;
    else
      Procs[p].RAC.State := WRDX;
      if (p != Home) then
        GUniMsg[p].Cmd := RDX_H;
        undefine GUniMsg[p].Cluster;
        undefine GUniMsg[p].Data;
        undefine GUniMsg[p].InvCnt;
      end;
    end;
    Procs[p].L2.isRetired := false;

    undefine Procs[p].UniMsg[src];
    Procs[p].UniMsg[src].Cmd := UNI_None;
  endrule;
endruleset;



ruleset p: Procss; src: NODE do
rule "L1_GetX"
  Procs[p].Proc[src].ProcCmd = NODE_None &
  Procs[p].Proc[src].CacheState != CACHE_E &
  Procs[p].Proc[src].CacheState != CACHE_M &
  Procs[p].Proc[src].block_WB = false
==>
begin
  Procs[p].UniMsg[src].Cmd := UNI_GetX;
  Procs[p].UniMsg[src].Proc := L2;
  undefine Procs[p].UniMsg[src].Data;

  Procs[p].Proc[src].ProcCmd := NODE_GetX;
endrule;
endruleset;



-- RuleBase
ruleset p: Procss; src: NODE do
rule "L2HeadPtr_Recv_GetX_PutX"
  Procs[p].UniMsg[src].Cmd = UNI_GetX &
  Procs[p].UniMsg[src].Proc = L2 &

  Procs[p].L2.pending = false &
  !isundefined(Procs[p].L2.HeadPtr) &
  Procs[p].L2.HeadPtr = L2 &
  Procs[p].L2.State != Invld
==>
begin
  if (Procs[p].L2.OnlyCopy = true) then
    Procs[p].L2.State := Excl;
    Procs[p].L2.HeadPtr := src;

    Procs[p].UniMsg[src].Cmd := UNI_PutX;
    Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
    undefine Procs[p].UniMsg[src].Proc;

  else
    if (Procs[p].RAC.State = Inval) then
      Procs[p].L2.pending := true;
      Procs[p].L2.ReqId := src;
      Procs[p].RAC.State := WRDX;
      if (p != Home) then
        GUniMsg[p].Cmd := RDX_H;
        undefine GUniMsg[p].Cluster;
        undefine GUniMsg[p].Data;
        undefine GUniMsg[p].InvCnt;
      end;

      undefine Procs[p].UniMsg[src];
      Procs[p].UniMsg[src].Cmd := UNI_None;
      Procs[p].L2.isRetired := false;

    else 
      undefine Procs[p].UniMsg[src];
      Procs[p].UniMsg[src].Cmd := UNI_Nak;
    end;
  end;
endrule;
endruleset;



-- RuleBase
ruleset p: Procss; src: NODE do
  rule "L2Shrd_Recv_GetX_(PutX)"
    Procs[p].L2.State = Shrd &
    Procs[p].L2.pending = false &
    isundefined(Procs[p].L2.HeadPtr) &

    Procs[p].UniMsg[src].Cmd = UNI_GetX &
    Procs[p].UniMsg[src].Proc = L2
  ==>
  var iCnt: CacheCnt;
  begin

    -- this cluster has the only copy
    if (Procs[p].L2.OnlyCopy = true) then

      Procs[p].L2.State := Excl;
      Procs[p].L2.HeadPtr := src;
      Procs[p].UniMsg[src].Cmd := UNI_PutX;
      Procs[p].UniMsg[src].Data := Procs[p].L2.Data;
      undefine Procs[p].UniMsg[src].Proc;

      -- src is the only sharer
      if (forall n: NODE do (n!=src -> Procs[p].L2.ShrSet[n]=false) end) then
        Procs[p].L2.ShrSet[src] := false;
      else
        Procs[p].L2.pending := true;
        iCnt := 0;
        for n: NODE do
          if (Procs[p].L2.ShrSet[n] = true) then
 	    iCnt := iCnt + 1;
            Procs[p].InvMsg[n].Cmd := INV_Inv;
            Procs[p].L2.ShrSet[n] := false;
          end;
        end;
        Procs[p].L2.InvCnt := iCnt; 
        -- invariant purpose
        Procs[p].PrevData := Procs[p].CurrData;
        Procs[p].Collecting := true;
      end;

    else

      -- no pending activity with RAC
      if (Procs[p].RAC.State = Inval) then
        Procs[p].L2.pending := true;
        if !(forall n: NODE do (Procs[p].L2.ShrSet[n]=false) end) then
	  iCnt := 0;
          for n: NODE do
            if (Procs[p].L2.ShrSet[n] = true) then
	      iCnt := iCnt + 1;
              Procs[p].InvMsg[n].Cmd := INV_Inv;
              Procs[p].L2.ShrSet[n] := false;
            end;
          end;
          Procs[p].L2.InvCnt := iCnt; 
          Procs[p].PrevData := Procs[p].CurrData;
          Procs[p].Collecting := true;
        end;
        Procs[p].RAC.State := WRDX;
        Procs[p].L2.ReqId := src;
        if (p != Home) then 
          GUniMsg[p].Cmd := RDX_H;
          undefine GUniMsg[p].Cluster;
          undefine GUniMsg[p].Data;
          undefine GUniMsg[p].InvCnt;
	end;
        undefine Procs[p].UniMsg[src];
        Procs[p].UniMsg[src].Cmd := UNI_None;
	Procs[p].L2.isRetired := false;

      else
        Procs[p].UniMsg[src].Cmd := UNI_Nak;
        undefine Procs[p].UniMsg[src].Data; 
        undefine Procs[p].UniMsg[src].Proc; 
      end;
    end;
  endrule;
endruleset;



-- RuleBase
ruleset p: Procss; dst: NODE do
  rule "L1_Recv_Inv"
    Procs[p].InvMsg[dst].Cmd = INV_Inv
  ==>
  begin
    Procs[p].InvMsg[dst].Cmd := INV_InvAck;

    if (Procs[p].Proc[dst].CacheState != CACHE_E &
	Procs[p].Proc[dst].CacheState != CACHE_M) then
      Procs[p].Proc[dst].CacheState := CACHE_I;
      undefine Procs[p].Proc[dst].CacheData;
    end;
    if (Procs[p].Proc[dst].ProcCmd = NODE_Get) then
      Procs[p].Proc[dst].InvMarked := true;
    end;
  endrule;
endruleset;



-- RuleBase
ruleset p: Procss; src: NODE do
  rule "L2_Recv_InvAck"
    Procs[p].InvMsg[src].Cmd = INV_InvAck
  ==>
  begin
    assert (Procs[p].L2.pending = true) "Funny pending receiving INV_InvAck.";
    Procs[p].L2.InvCnt := Procs[p].L2.InvCnt - 1;

    if (Procs[p].L2.InvCnt = 0) then
      -- invariant purpose
      Procs[p].Collecting := false;
      if (Procs[p].L2.State = Invld) then
        -- invariant purpose
        undefine Procs[p].CurrData;
        undefine Procs[p].PrevData;
      end;

      if (Procs[p].L2.isRetired = true) then
        Procs[p].L2.pending := false;
      end;
    end;

    Procs[p].InvMsg[src].Cmd := INV_None;
  endrule;
endruleset;




-- RuleBase
ruleset p: Procss; dst: NODE; src: NODE_L2 do
  rule "L1Rmt_Recv_Get(X)_Nak"
    (Procs[p].UniMsg[src].Cmd = UNI_Get |
     Procs[p].UniMsg[src].Cmd = UNI_GetX) &
    Procs[p].UniMsg[src].Proc = dst &

    Procs[p].Proc[dst].CacheState != CACHE_E & 
    Procs[p].Proc[dst].CacheState != CACHE_M &
    Procs[p].Proc[dst].block_WB = false
  ==>
  begin
    assert (src != dst) "Funny forwarded req to itself.";

    if (Procs[p].Proc[dst].CacheState = CACHE_I & 
	Procs[p].Proc[dst].ProcCmd = NODE_None) then
      if (src = L2) then
        Procs[p].NakcMsg.Cmd := NAKC_SD;
        Procs[p].NakcMsg.Proc := dst;
        Procs[p].NakcMsg.Aux := src;
        undefine Procs[p].UniMsg[src];
        Procs[p].UniMsg[src].Cmd := UNI_None;
      else
        Procs[p].NakcMsg.Cmd := NAKC_SD;
        Procs[p].NakcMsg.Proc := dst;
        Procs[p].NakcMsg.Aux := src;
        Procs[p].UniMsg[src].Cmd := UNI_Nak;
        undefine Procs[p].UniMsg[src].Proc;
        undefine Procs[p].UniMsg[src].Data;
      end;

    else
      if (src = L2) then
        Procs[p].NakcMsg.Cmd := NAKC_Nakc;
        Procs[p].NakcMsg.Proc := dst;
        Procs[p].NakcMsg.Aux := src;
        undefine Procs[p].UniMsg[src];
        Procs[p].UniMsg[src].Cmd := UNI_None;
      else
        Procs[p].NakcMsg.Cmd := NAKC_Nakc;
        Procs[p].NakcMsg.Proc := dst;
        Procs[p].NakcMsg.Aux := src;
        Procs[p].UniMsg[src].Cmd := UNI_Nak;
        undefine Procs[p].UniMsg[src].Proc;
        undefine Procs[p].UniMsg[src].Data;
      end;
    end;
  endrule;
endruleset;



-- RuleBase
ruleset p: Procss; src: NODE do
  rule "L2_Recv_NAKC_Nakc"
    Procs[p].NakcMsg.Cmd = NAKC_Nakc
  ==>
  var aux: Procss;
  begin
    assert (Procs[p].L2.pending = true) "Funny pending receiving NAKC_Nakc.";
    Procs[p].L2.pending := false;

    if (Procs[p].NakcMsg.Aux = L2) then
      assert (!isundefined(Procs[p].L2.ReqCluster)) "Funny ReqCluster with NAKC_Nakc to L2.";
      aux := Procs[p].L2.ReqCluster;


      -- Apr 8
      assert (Procs[p].L2.ifHoldMsg = true) "Funny Procs[p].L2.ifHoldMsg value.";
      Procs[p].L2.ifHoldMsg := false;
      if (Procs[p].L2.ReqType = true) then
        if (p = Home) then
          assert (GUniMsg[aux].Cmd = RD_H) "Funny GUniMsg[aux].Cmd value.";
        else
          assert (GUniMsg[aux].Cmd = RD_RAC & GUniMsg[aux].Cluster = p) 
            "Funny GUniMsg[aux].Cmd value.";
        end;

      else
        if (p = Home) then
          assert (GUniMsg[aux].Cmd = RDX_H) "Funny GUniMsg[aux].Cmd value.";
        else
          assert (GUniMsg[aux].Cmd = RDX_RAC & GUniMsg[aux].Cluster = p) 
            "Funny GUniMsg[aux].Cmd value.";
        end;
      end;


      GUniMsg[aux].Cmd := NAK;
      undefine GUniMsg[aux].Data;
      undefine GUniMsg[aux].InvCnt;
      undefine GUniMsg[aux].Cluster;

      if (p != Home & aux != Home) then
        GNakcMsg.Cmd := GNAKC_Nakc;
        GNakcMsg.Cluster := p;
      end;
      undefine Procs[p].L2.ReqCluster;
      undefine Procs[p].L2.ReqType;
    end;
    undefine Procs[p].NakcMsg;
    Procs[p].NakcMsg.Cmd := NAKC_None;
  endrule;
endruleset;




-- RuleBase
ruleset p: Rmt do
  rule "RmtCluster_Recv_NAKC_SD"
    Procs[p].NakcMsg.Cmd = NAKC_SD
  ==>
  var aux: Procss;
      isGet: boolean;
  begin
    assert (Procs[p].L2.pending = true) "Funny pending receiving NAKC_Nakc.";
    Procs[p].L2.pending := false;

    if (Procs[p].NakcMsg.Aux = L2) then
      assert (!isundefined(Procs[p].L2.ReqCluster)) "Funny ReqCluster with NAKC_Nakc to L2.";
      aux := Procs[p].L2.ReqCluster;
      if (Procs[p].L2.HeadPtr = Procs[p].NakcMsg.Proc) then
        Procs[p].L2.HeadPtr := L2;
      end;


      -- Apr 8
      assert (Procs[p].L2.ifHoldMsg = true) "Funny Procs[p].L2.ifHoldMsg value.";
      Procs[p].L2.ifHoldMsg := false;
      if (Procs[p].L2.ReqType = true) then
          assert (GUniMsg[aux].Cmd = RD_RAC & GUniMsg[aux].Cluster = p) 
            "Funny GUniMsg[aux].Cmd value.";
      else
          assert (GUniMsg[aux].Cmd = RDX_RAC & GUniMsg[aux].Cluster = p) 
            "Funny GUniMsg[aux].Cmd value.";
      end;



      isGet := Procs[p].L2.ReqType;
      if (Procs[p].L2.HeadPtr = L2) then
        assert (Procs[p].L2.State != Invld) "Funny L2.State receiving NAKC_SD.";
  
        if (isGet = true) then
          GUniMsg[aux].Cmd := ACK;
        else
	  if (Procs[p].L2.Dirty = false) then
            GUniMsg[aux].Cmd := IACK;
          else
            GUniMsg[aux].Cmd := IACKX;
	  end;
	end;
        GUniMsg[aux].Data := Procs[p].L2.Data;
        GUniMsg[aux].Cluster := p;
        GUniMsg[aux].InvCnt := 0;

        if (isGet = true) then
          Procs[p].L2.State := Shrd;
          Procs[p].L2.OnlyCopy := false;
          Procs[p].L2.Dirty := false;
          if (aux != Home) then
            GShWbMsg.Cmd := SHWB;
            GShWbMsg.Data := Procs[p].L2.Data;
            GShWbMsg.Cluster := aux;
	  end;

        else
	  if (aux != Home) then
            GShWbMsg.Cmd := DXFER;
            GShWbMsg.Cluster := aux;
            undefine GShWbMsg.Data;
    	  end;

	  Procs[p].L2.State := Invld;
          Procs[p].L2.OnlyCopy := false;
          Procs[p].L2.Dirty := false;
          undefine Procs[p].L2.HeadPtr;
          undefine Procs[p].L2.Data;
          undefine Procs[p].CurrData;
          undefine Procs[p].PrevData;
        end;

      else -- impossible to this branch?
	assert (false) "Impossible to this branch.";

        GUniMsg[aux].Cmd := NAK;
        undefine GUniMsg[aux].Data;
        undefine GUniMsg[aux].InvCnt;
        undefine GUniMsg[aux].Cluster;

        if (aux != Home) then
          GNakcMsg.Cmd := GNAKC_Nakc;
          GNakcMsg.Cluster := p;
        end;
      end;
      undefine Procs[p].L2.ReqCluster;
      undefine Procs[p].L2.ReqType;

    else
      if (Procs[p].L2.HeadPtr = Procs[p].NakcMsg.Proc) then
        Procs[p].L2.HeadPtr := L2;
      end;
    end;      

    undefine Procs[p].NakcMsg;
    Procs[p].NakcMsg.Cmd := NAKC_None;
  endrule;
endruleset;


-- RuleBase
  rule "Home_Recv_NAKC_SD"
    Procs[Home].NakcMsg.Cmd = NAKC_SD
  ==>
  var aux: Procss;
      isGet: boolean;
  begin
    assert (Procs[Home].L2.pending = true) "Funny pending receiving NAKC_Nakc.";
    Procs[Home].L2.pending := false;

    if (Procs[Home].NakcMsg.Aux = L2) then
      assert (!isundefined(Procs[Home].L2.ReqCluster)) "Funny ReqCluster with NAKC_Nakc to L2.";
      aux := Procs[Home].L2.ReqCluster;
      if (Procs[Home].L2.HeadPtr = Procs[Home].NakcMsg.Proc) then
        Procs[Home].L2.HeadPtr := L2;
      end;


      -- Apr 8
      assert (Procs[Home].L2.ifHoldMsg = true) "Funny Procs[p].L2.ifHoldMsg value.";
      Procs[Home].L2.ifHoldMsg := false;
      if (Procs[Home].L2.ReqType = true) then      
        assert (GUniMsg[aux].Cmd = RD_H) "Funny GUniMsg[aux].Cmd value";
      else
          assert (GUniMsg[aux].Cmd = RDX_H) "Funny GUniMsg[aux].Cmd value.";
      end;



      isGet := Procs[Home].L2.ReqType;
      if (Procs[Home].L2.HeadPtr = L2) then
        assert (Procs[Home].L2.State != Invld) "Funny L2.State receiving NAKC_SD.";
  
        if (isGet = true) then
          GUniMsg[aux].Cmd := ACK;
          Dir.ShrSet[aux] := true;
          Dir.Mem := Procs[Home].L2.Data;
          -- Dir.CurrData := Procs[Home].L2.Data;
          Dir.State := Shrd;
        else
	  if (Procs[Home].L2.Dirty = false) then
            GUniMsg[aux].Cmd := IACK;
          else
            GUniMsg[aux].Cmd := IACKX;
	  end;
          Dir.HeadPtr := aux;
          Dir.isLocal := false;
	end;
        GUniMsg[aux].Data := Procs[Home].L2.Data;
        undefine GUniMsg[aux].Cluster;
        GUniMsg[aux].InvCnt := 0;

        if (isGet = true) then
          Procs[Home].L2.State := Shrd;
          Procs[Home].L2.OnlyCopy := false;
          Procs[Home].L2.Dirty := false;

        else
	  Procs[Home].L2.State := Invld;
          Procs[Home].L2.OnlyCopy := false;
          Procs[Home].L2.Dirty := false;
          undefine Procs[Home].L2.HeadPtr;
          undefine Procs[Home].L2.Data;
          undefine Procs[Home].CurrData;
          undefine Procs[Home].PrevData;
        end;

      else -- impossible to this branch?
	assert (false) "Impossible to this branch.";

        GUniMsg[aux].Cmd := NAK;
        undefine GUniMsg[aux].Data;
        undefine GUniMsg[aux].InvCnt;
        undefine GUniMsg[aux].Cluster;
      end;
      undefine Procs[Home].L2.ReqCluster;
      undefine Procs[Home].L2.ReqType;

    else
      if (Procs[Home].L2.HeadPtr = Procs[Home].NakcMsg.Proc) then
        Procs[Home].L2.HeadPtr := L2;
      end;
    end;      

    undefine Procs[Home].NakcMsg;
    Procs[Home].NakcMsg.Cmd := NAKC_None;
  endrule;


-- RuleBase
ruleset p: Procss; dst: NODE; src: NODE_L2 do
  rule "L1Rmt_Recv_Get_Put"
    Procs[p].UniMsg[src].Cmd = UNI_Get &
    Procs[p].UniMsg[src].Proc = dst &

    (Procs[p].Proc[dst].CacheState = CACHE_E |
     Procs[p].Proc[dst].CacheState = CACHE_M)
 ==>
  begin
    assert (src != dst) "Funny forwarded req to itself.";

    Procs[p].ShWbMsg.Cmd := SHWB_ShWb;
    Procs[p].ShWbMsg.Proc := dst;
    Procs[p].ShWbMsg.Aux := src;
    if (Procs[p].Proc[dst].CacheState = CACHE_E) then
      undefine Procs[p].ShWbMsg.Data;
    else
      Procs[p].ShWbMsg.Data := Procs[p].Proc[dst].CacheData;
    end;
    undefine Procs[p].UniMsg[src];    
    Procs[p].UniMsg[src].Cmd := UNI_None;

    if (src != L2) then
      Procs[p].UniMsg[src].Cmd := UNI_Put;
      Procs[p].UniMsg[src].Data := Procs[p].Proc[dst].CacheData;
      undefine Procs[p].UniMsg[src].Proc;
    end;

    Procs[p].Proc[dst].CacheState := CACHE_S;
  endrule;
endruleset;



-- RuleBase
ruleset p: Procss do
  rule "L2_Recv_SHWB"
    Procs[p].ShWbMsg.Cmd = SHWB_ShWb
  ==>
  var 
    src: NODE_L2;
    dst: NODE_L2;
    aux: Procss;
  begin
    assert (Procs[p].L2.pending = true) "Funny pending receiving SHWB_ShWb.";

    Procs[p].L2.pending := false;
    Procs[p].L2.State := Shrd;
    src := Procs[p].ShWbMsg.Aux;
    dst := Procs[p].ShWbMsg.Proc;

    if (src != L2) then
      assert (Procs[p].L2.HeadPtr = dst) "Funny HeadPtr value.";
      Procs[p].L2.ShrSet[dst] := true;
      Procs[p].L2.ShrSet[src] := true;
      undefine Procs[p].L2.HeadPtr;
      if (!isundefined(Procs[p].ShWbMsg.Data)) then
        Procs[p].L2.Dirty := true;
        Procs[p].L2.Data := Procs[p].ShWbMsg.Data;
        Dir.CurrData := Procs[p].ShWbMsg.Data;
      end;

    else
      Procs[p].L2.ShrSet[dst] := true;
      assert (Procs[p].L2.HeadPtr = dst) "Funny HeadPtr value.";
      undefine Procs[p].L2.HeadPtr;

      Procs[p].L2.Dirty := false;
      Procs[p].L2.OnlyCopy := false;
      if (!isundefined(Procs[p].ShWbMsg.Data)) then
        Procs[p].L2.Data := Procs[p].ShWbMsg.Data;
        Dir.CurrData := Procs[p].ShWbMsg.Data;
      end;

      assert (!isundefined(Procs[p].L2.ReqCluster)) "Funny ReqCluster with SHWB_ShWb to L2.";
      aux := Procs[p].L2.ReqCluster;
      assert (Procs[p].L2.ReqType = true) "Funny ReqType value.";


      -- Apr 8
      assert (Procs[p].L2.ifHoldMsg = true) "Funny Procs[p].L2.ifHoldMsg value.";
      Procs[p].L2.ifHoldMsg := false;
        if (p = Home) then
          assert (GUniMsg[aux].Cmd = RD_H) "Funny GUniMsg[aux].Cmd value.";
        else
          assert (GUniMsg[aux].Cmd = RD_RAC & GUniMsg[aux].Cluster = p) 
            "Funny GUniMsg[aux].Cmd value.";
        end;


      GUniMsg[aux].Cmd := ACK;
      GUniMsg[aux].Data := Procs[p].L2.Data;
      GUniMsg[aux].Cluster := p;
      GUniMsg[aux].InvCnt := 0;

      if (p = Home) then
        Dir.State := Shrd;
        Dir.ShrSet[aux] := true;
        Dir.Mem := Procs[p].L2.Data;
        Dir.CurrData := Procs[p].L2.Data;

      else
        if (aux != Home) then
          GShWbMsg.Cmd := SHWB;
          GShWbMsg.Data := Procs[p].L2.Data;
          GShWbMsg.Cluster := aux;
	end;
      end;
      undefine Procs[p].L2.ReqCluster;
      undefine Procs[p].L2.ReqType;
    end;

    undefine Procs[p].ShWbMsg;
    Procs[p].ShWbMsg.Cmd := SHWB_None;
  endrule;
endruleset;



-- RuleBase
ruleset p: Procss; dst: NODE; src: NODE_L2 do
rule "L1Rmt_Recv_GetX_PutX"
  Procs[p].UniMsg[src].Cmd = UNI_GetX &
  Procs[p].UniMsg[src].Proc = dst &

  (Procs[p].Proc[dst].CacheState = CACHE_E |
   Procs[p].Proc[dst].CacheState = CACHE_M)
==>
begin
  if (src = L2) then
    Procs[p].ShWbMsg.Cmd := SHWB_FAck;
    Procs[p].ShWbMsg.Proc := dst;
    Procs[p].ShWbMsg.Aux := src;
    if (Procs[p].Proc[dst].CacheState = CACHE_E) then
      undefine Procs[p].ShWbMsg.Data;
    else
      Procs[p].ShWbMsg.Data := Procs[p].Proc[dst].CacheData;
    end;
    undefine Procs[p].UniMsg[src];
    Procs[p].UniMsg[src].Cmd := UNI_None;

  else
    Procs[p].UniMsg[src].Data := Procs[p].Proc[dst].CacheData;
    undefine Procs[p].UniMsg[src].Proc;
    if (Procs[p].Proc[dst].CacheState = CACHE_E) then
      Procs[p].UniMsg[src].Cmd := UNI_PutX;
    else
      Procs[p].UniMsg[src].Cmd := UNI_PutXX;
    end;
    Procs[p].ShWbMsg.Cmd := SHWB_FAck;
    Procs[p].ShWbMsg.Proc := dst;
    Procs[p].ShWbMsg.Aux := src;
    undefine Procs[p].ShWbMsg.Data;
  end;

  Procs[p].Proc[dst].CacheState := CACHE_I;
  undefine Procs[p].Proc[dst].CacheData;
endrule;
endruleset;



-- RuleBase
ruleset p: Procss do
rule "L2_Recv_SHWB_FAck"
  Procs[p].ShWbMsg.Cmd = SHWB_FAck
==>
var 
  src: NODE_L2;
  dst: NODE_L2;
  aux: Procss;
begin
  assert (Procs[p].L2.pending = true) "Funny pending receiving SHWB_FAck.";
  Procs[p].L2.pending := false;

  src := Procs[p].ShWbMsg.Aux;
  dst := Procs[p].ShWbMsg.Proc;

  if (src = L2) then
    assert (!isundefined(Procs[p].L2.ReqCluster)) "Funny ReqCluster undefined with SHWB_FAck to L2.";
    aux := Procs[p].L2.ReqCluster;
    assert (Procs[p].L2.ReqType = false) "Funny SHWB_FAck with ReqType.";



      -- Apr 8
      assert (Procs[p].L2.ifHoldMsg = true) "Funny Procs[p].L2.ifHoldMsg value.";
      Procs[p].L2.ifHoldMsg := false;
        if (p = Home) then
          assert (GUniMsg[aux].Cmd = RDX_H) "Funny GUniMsg[aux].Cmd value.";
        else
          assert (GUniMsg[aux].Cmd = RDX_RAC & GUniMsg[aux].Cluster = p) 
            "Funny GUniMsg[aux].Cmd value.";
        end;



    if (!isundefined(Procs[p].ShWbMsg.Data)) then
      Procs[p].L2.Data := Procs[p].ShWbMsg.Data;
      Dir.CurrData := Procs[p].ShWbMsg.Data;
    end;

    if (p = Home) then
      Dir.isLocal := false;
      Dir.HeadPtr := aux;

    else
      if (aux != Home) then
        GShWbMsg.Cmd := DXFER;
        GShWbMsg.Cluster := aux;
        undefine GShWbMsg.Data;
      end;
    end;


    GUniMsg[aux].Data := Procs[p].L2.Data;
    GUniMsg[aux].Cluster := p;
    GUniMsg[aux].InvCnt := 0;
    if (Procs[p].L2.Dirty = true) then
      GUniMsg[aux].Cmd := IACKX;
    elsif (!isundefined(Procs[p].ShWbMsg.Data)) then
      GUniMsg[aux].Cmd := IACKX;
    else
      GUniMsg[aux].Cmd := IACK;
    end;

    Procs[p].L2.State := Invld;
    Procs[p].L2.OnlyCopy := false;
    Procs[p].L2.Dirty := false;
    undefine Procs[p].CurrData;
    undefine Procs[p].PrevData;
    undefine Procs[p].L2.Data;
    undefine Procs[p].L2.HeadPtr;

    undefine Procs[p].L2.ReqCluster;
    undefine Procs[p].L2.ReqType;

  else
    if (Procs[p].L2.HeadPtr = dst) then
      Procs[p].L2.HeadPtr := src;
    end;
  end;

  undefine Procs[p].ShWbMsg;
  Procs[p].ShWbMsg.Cmd := SHWB_None;
endrule;
endruleset;


-- RuleBase
ruleset p: Procss; dst: NODE do
  rule "L1_Recv_Nak"
    Procs[p].UniMsg[dst].Cmd = UNI_Nak
  ==>
  begin
    Procs[p].Proc[dst].ProcCmd := NODE_None;
    Procs[p].Proc[dst].InvMarked := false;
    undefine Procs[p].UniMsg[dst];
    Procs[p].UniMsg[dst].Cmd := UNI_None;
  endrule;
endruleset;


-- RuleBase
ruleset p: Procss; dst: NODE do
  rule "L1_Recv_Put"
    Procs[p].UniMsg[dst].Cmd = UNI_Put
  ==>
  begin

    assert (Procs[p].Proc[dst].ProcCmd = NODE_Get) "Funny ProcCmd receiving UNI_Put.";

    Procs[p].Proc[dst].ProcCmd := NODE_None;
    if (Procs[p].Proc[dst].InvMarked = true) then
      Procs[p].Proc[dst].CacheState := CACHE_I;
      undefine Procs[p].Proc[dst].CacheData;
      Procs[p].Proc[dst].InvMarked := false;
    else
      Procs[p].Proc[dst].CacheState := CACHE_S;
      assert (! isundefined(Procs[p].UniMsg[dst].Data)) "PI req grant should have data.";
      Procs[p].Proc[dst].CacheData := Procs[p].UniMsg[dst].Data;
    end;
    undefine Procs[p].UniMsg[dst];
    Procs[p].UniMsg[dst].Cmd := UNI_None;
  endrule;
endruleset;



-- RuleBase
ruleset p: Procss; dst: NODE do
  rule "L1_Recv_PutX"
    Procs[p].UniMsg[dst].Cmd = UNI_PutX
  ==>
  begin
    assert (Procs[p].Proc[dst].ProcCmd = NODE_GetX) "Funny UNI_PutX received.";
    Procs[p].Proc[dst].ProcCmd := NODE_None;
    Procs[p].Proc[dst].CacheState := CACHE_E;
    assert (! isundefined(Procs[p].UniMsg[dst].Data)) "Excl grant should have data.";
    Procs[p].Proc[dst].CacheData := Procs[p].UniMsg[dst].Data;

    undefine Procs[p].UniMsg[dst];
    Procs[p].UniMsg[dst].Cmd := UNI_None;
  endrule;
endruleset;



-- dirty excl owner transfer
ruleset p: Procss; dst: NODE do
  rule "L1_Recv_PutXX"
    Procs[p].UniMsg[dst].Cmd = UNI_PutXX
  ==>
  begin
    assert (Procs[p].Proc[dst].ProcCmd = NODE_GetX) "Funny UNI_PutX received.";
    Procs[p].Proc[dst].ProcCmd := NODE_None;
    Procs[p].Proc[dst].CacheState := CACHE_M;
    assert (! isundefined(Procs[p].UniMsg[dst].Data)) "Excl grant should have data.";
    Procs[p].Proc[dst].CacheData := Procs[p].UniMsg[dst].Data;

    undefine Procs[p].UniMsg[dst];
    Procs[p].UniMsg[dst].Cmd := UNI_None;
  endrule;
endruleset;


-- RuleBase
ruleset p: Procss; src: NODE do
rule "L1_SilentDrop"
  Procs[p].Proc[src].ProcCmd = NODE_None &
  (Procs[p].Proc[src].CacheState = CACHE_S |
   Procs[p].Proc[src].CacheState = CACHE_E )
==>
begin
  Procs[p].Proc[src].CacheState := CACHE_I;
  undefine Procs[p].Proc[src].CacheData;
endrule;
endruleset;



-- RuleBase
ruleset p: Procss; src: NODE do
rule "L1_WriteBack"
  Procs[p].Proc[src].CacheState = CACHE_M &
  Procs[p].Proc[src].ProcCmd = NODE_None
==>
begin
  Procs[p].Proc[src].CacheState := CACHE_I;
  Procs[p].WbMsg.Cmd := WB_Wb;
  Procs[p].WbMsg.Proc := src;
  Procs[p].WbMsg.Data := Procs[p].Proc[src].CacheData;

  undefine Procs[p].Proc[src].CacheData;
  Procs[p].Proc[src].block_WB := true;
endrule;
endruleset;



ruleset p: Procss do
  rule "L2_Recv_WB_Remain"
    Procs[p].WbMsg.Cmd = WB_Wb
  ==>
  var src: NODE;
  begin
    assert (Procs[p].L2.State = Excl) "Funny WB_Wb without being excl.";
    Procs[p].L2.HeadPtr := L2;
    Procs[p].L2.Dirty := true;
    Procs[p].L2.Data := Procs[p].WbMsg.Data;
    Dir.CurrData := Procs[p].WbMsg.Data;

    src := Procs[p].WbMsg.Proc;
    Procs[p].UniMsg[src].Cmd := WB_WbAck;
    undefine Procs[p].UniMsg[src].Proc;
    undefine Procs[p].UniMsg[src].Data;

    undefine Procs[p].WbMsg;
    Procs[p].WbMsg.Cmd := WB_None;
  endrule;
endruleset;



ruleset p: Procss; dst: NODE do
rule "L1_Recv_WbAck"
  Procs[p].UniMsg[dst].Cmd = WB_WbAck
==>
begin
  assert (Procs[p].Proc[dst].block_WB = true &
	  Procs[p].Proc[dst].ProcCmd = NODE_None) 
     "Funny Proc[dst] state receiving WB_WbAck.";

  Procs[p].Proc[dst].block_WB := false;
  undefine Procs[p].UniMsg[dst];
  Procs[p].UniMsg[dst].Cmd := UNI_None;
endrule;
endruleset;



-- RuleBase
ruleset p: Procss do
rule "L2_SilentDrop"
  Procs[p].L2.State != Invld &
  Procs[p].L2.pending = false &
  (forall n: NODE do
       (Procs[p].L2.ShrSet[n] = false) end) &
  Procs[p].L2.Dirty = false &
  Procs[p].L2.HeadPtr = L2 &
  Procs[p].RAC.State = Inval
==>
begin
  Procs[p].L2.State := Invld;
  Procs[p].L2.OnlyCopy := false;
  undefine Procs[p].L2.Data;
  undefine Procs[p].L2.HeadPtr;

  -- invariant purpose
  undefine Procs[p].PrevData;
  undefine Procs[p].CurrData;
endrule;
endruleset;



------ outside a cluster  ------

rule "Dir_HomeGet_Put"
  Procs[Home].RAC.State = WRDO &
  Dir.isBusy = false &
  (Dir.State = Invld | Dir.State = Shrd)
==>
var src: NODE;
begin
  Dir.State := Shrd;
  Dir.isLocal := true;
  Procs[Home].L2.State := Shrd;
  Procs[Home].L2.Data := Dir.Mem;
  Procs[Home].RAC.State := Inval;
  Procs[Home].L2.pending := false;
  assert (!isundefined(Procs[Home].L2.ReqId)) "Funny undefined ReqId.";
  src := Procs[Home].L2.ReqId;
  Procs[Home].L2.ShrSet[src] := true;

  Procs[Home].CurrData := Dir.Mem;
  Procs[Home].UniMsg[src].Cmd := UNI_Put;
  Procs[Home].UniMsg[src].Data := Procs[Home].L2.Data;
  undefine Procs[Home].UniMsg[src].Proc;
  undefine Procs[Home].L2.ReqId;

  assert (Procs[Home].L2.isRetired = false) "Funny L2.isRetired value in Dir_HomeGet_Put.";
  Procs[Home].L2.isRetired := true;
endrule;



rule "Dir_HomeGet_RmtGet"
  Procs[Home].RAC.State = WRDO &
  Dir.isBusy = false &
  Dir.State = Excl &
  Dir.isLocal = false 
==>
begin
  Dir.isBusy := true;
  assert (! isundefined(Dir.HeadPtr)) "Remote excl without headptr1.";
  GUniMsg[Home].Cmd := RD_RAC;
  GUniMsg[Home].Cluster := Dir.HeadPtr;
  undefine GUniMsg[Home].Data;
  undefine GUniMsg[Home].InvCnt;
endrule;



rule "Dir_HomeGet_isLocal_Put"
  Procs[Home].RAC.State = WRDO &
  Dir.isBusy = false &
  Dir.State = Excl &
  Dir.isLocal = true 
==>
var src: NODE;
begin
  assert (isundefined(Dir.HeadPtr)) "Funny Dir.HeadPtr and isLocal.";

  Dir.State := Shrd;
  Procs[Home].L2.State := Shrd;
  Procs[Home].L2.Data := Dir.Mem;
  Procs[Home].L2.OnlyCopy := false;
  Procs[Home].RAC.State := Inval;
  Procs[Home].L2.pending := false;
  assert (!isundefined(Procs[Home].L2.ReqId)) "Funny undefined ReqId.";
  src := Procs[Home].L2.ReqId;
  Procs[Home].L2.ShrSet[src] := true;

  -- invariant purpose
  Procs[Home].CurrData := Dir.Mem;
  Procs[Home].UniMsg[src].Cmd := UNI_Put;
  Procs[Home].UniMsg[src].Data := Dir.Mem;
  undefine Procs[Home].UniMsg[src].Proc;
  undefine Procs[Home].L2.ReqId;

  assert (Procs[Home].L2.isRetired = false) "Funny L2.isRetired value in Dir_HomeGet_isLocal_Put.";
  Procs[Home].L2.isRetired := true;
endrule;



rule "Dir_HomeGetX_RmtGetX"
  Procs[Home].RAC.State = WRDX &
  Dir.isBusy = false & 
  Dir.State = Excl &
  Dir.isLocal = false 
==>
begin
  Dir.isBusy := true;
  assert (! isundefined(Dir.HeadPtr)) "Remote excl without headptr3.";

  GUniMsg[Home].Cmd := RDX_RAC;
  GUniMsg[Home].Cluster := Dir.HeadPtr;
  undefine GUniMsg[Home].InvCnt;
  undefine GUniMsg[Home].Data;
endrule;



rule "Dir_HomeGetX_isLocal_PutX"
  Procs[Home].RAC.State = WRDX &
  Dir.isBusy = false &
  Dir.State = Excl &
  Dir.isLocal = true 
==>
var src: NODE;
begin
  assert (isundefined(Dir.HeadPtr)) "Funny Dir.HeadPtr and isLocal both true.";

  Dir.State := Excl;
  Procs[Home].L2.State := Excl;
  Procs[Home].L2.Data := Dir.Mem;
  Procs[Home].L2.OnlyCopy := true;

  assert (Procs[Home].L2.pending = true & !isundefined(Procs[Home].L2.ReqId)) 
     "Funny Procs[Home].L2 state with outside reply42.";
  Procs[Home].RAC.State := Inval;
  Procs[Home].L2.HeadPtr := Procs[Home].L2.ReqId;
  Procs[Home].L2.Dirty := false;

  assert (forall n: NODE do Procs[Home].L2.ShrSet[n] = false end &
	  Procs[Home].L2.InvCnt = 0)
     "Funny Procs[Home].L2.ShrSet state.";
  Procs[Home].L2.pending := false;
  -- invariant purpose  
  Procs[Home].CurrData := Dir.Mem;

  src := Procs[Home].L2.ReqId;
  Procs[Home].UniMsg[src].Cmd := UNI_PutX;
  Procs[Home].UniMsg[src].Data := Dir.Mem;
  undefine Procs[Home].UniMsg[src].Proc;
  undefine Procs[Home].L2.ReqId;

  assert (Procs[Home].L2.isRetired = false) "Funny L2.isRetired value in Dir_HomeGetX_isLocal_PutX.";
  Procs[Home].L2.isRetired := true;
endrule;



rule "Dir_HomeGetX_PutX"
  Procs[Home].RAC.State = WRDX &
  Dir.isBusy = false &
  Dir.State = Invld
==>
var src: NODE;
begin
  assert (Dir.isLocal = false & isundefined(Dir.HeadPtr)) 
     "Funny Dir Invld and isLocal/HeadPtr.";

  Dir.State := Excl;
  Dir.isLocal := true;
  Procs[Home].L2.State := Excl;
  Procs[Home].L2.OnlyCopy := true;
  Procs[Home].L2.Data := Dir.Mem;
  Procs[Home].L2.Dirty := false;

  assert (Procs[Home].L2.pending = true & !isundefined(Procs[Home].L2.ReqId)) 
     "Funny Procs[Home].L2 state with outside reply41.";
  Procs[Home].RAC.State := Inval;
  Procs[Home].L2.HeadPtr := Procs[Home].L2.ReqId;
  if (Procs[Home].L2.InvCnt = 0) then
    Procs[Home].L2.pending := false;
  end;
  -- invariant purpose  
  Procs[Home].CurrData := Dir.Mem;

  src := Procs[Home].L2.ReqId;
  Procs[Home].UniMsg[src].Cmd := UNI_PutX;
  Procs[Home].UniMsg[src].Data := Dir.Mem;
  undefine Procs[Home].UniMsg[src].Proc;
  undefine Procs[Home].L2.ReqId;

  assert (Procs[Home].L2.isRetired = false) "Funny L2.isRetired value in Dir_HomeGetX_PutX.";
  Procs[Home].L2.isRetired := true;
endrule;



rule "Dir_Shrd_HomeGetX_PutX"
  Procs[Home].RAC.State = WRDX &
  Dir.isBusy = false &
  Dir.State = Shrd 
==>
var ShrCnt: ClusterCnt;
    src: NODE;
begin
  Dir.State := Excl;
  assert (isundefined(Dir.HeadPtr)) "Funny dir shared with headptr.";
  Procs[Home].L2.State := Excl;
  Procs[Home].L2.Data := Dir.Mem;
  Procs[Home].L2.Dirty := false;
  Procs[Home].L2.OnlyCopy := true;

  -- Home is the only sharer
  if (forall r: Rmt do
      Dir.ShrSet[r] = false end) then
    assert (Dir.isLocal = true) "Funny dir shared without any copy.";
    Procs[Home].RAC.State := Inval;

  -- exist remote cluster sharer
  else
    ShrCnt := 0;
    for r: Rmt do
      if (Dir.ShrSet[r] = true) then
        Dir.ShrSet[r] := false;
        ShrCnt := ShrCnt + 1;
        GInvMsg[r].Cmd := INV;
        GInvMsg[r].Cluster := Home;        
      end;
    end;
    Procs[Home].RAC.State := WINV;
    Procs[Home].RAC.InvCnt := ShrCnt;

    -- invariant purpose
    Dir.Collecting := true;
    Dir.PrevData := Dir.CurrData;
  end;

  Dir.isLocal := true;
  assert (Procs[Home].L2.pending = true & !isundefined(Procs[Home].L2.ReqId)) 
    "Funny Procs[Home].L2 state with outside reply4.";
  Procs[Home].L2.HeadPtr := Procs[Home].L2.ReqId;
  src := Procs[Home].L2.ReqId;

  if (Procs[Home].L2.InvCnt = 0) then
    Procs[Home].L2.pending := false;
  end;

  Procs[Home].CurrData := Dir.Mem;
  src := Procs[Home].L2.ReqId;
  Procs[Home].UniMsg[src].Cmd := UNI_PutX;
  Procs[Home].UniMsg[src].Data := Dir.Mem;
  undefine Procs[Home].UniMsg[src].Proc;
  undefine Procs[Home].L2.ReqId;

  assert (Procs[Home].L2.isRetired = false) "Funny L2.isRetired value in Dir_Shrd_HomeGetX_PutX.";
  Procs[Home].L2.isRetired := true;
endrule;



ruleset src: Procss do
rule "Home_Recv_InvAck"
  GInvMsg[src].Cmd = SACK &
  GInvMsg[src].Cluster = Home
==>
begin

  switch Procs[Home].RAC.State

  -- receive InvAck after reply from Dir
  case WINV:
    Procs[Home].RAC.InvCnt := Procs[Home].RAC.InvCnt - 1;

    -- all InvAck received
    if (Procs[Home].RAC.InvCnt = 0) then
      Procs[Home].RAC.State := Inval;
      -- invariant purpose
      Dir.Collecting := false;
    end;

  else
    Error "Funny Home state receiving SACK.";
  end;

  undefine GInvMsg[src];
  GInvMsg[src].Cmd := GINV_None;
endrule;
endruleset;



rule "Home_Recv_IACK(X)"
  GUniMsg[Home].Cmd = IACK |
  GUniMsg[Home].Cmd = IACKX
==>
var dst: Procss;
    src: NODE;
begin 
  assert (Dir.isBusy = true) "Funny Dir.isBusy state1.";
  Dir.isBusy := false;
  assert (Procs[Home].RAC.State = WRDX) "Funny cluster state receive IACK(X).";

  Procs[Home].L2.Data := GUniMsg[Home].Data;
  Procs[Home].CurrData := GUniMsg[Home].Data;
  -- Dir.CurrData := GUniMsg[Home].Data;
  Procs[Home].L2.State := Excl;
  Procs[Home].L2.OnlyCopy := true;
  if (GUniMsg[Home].Cmd = IACK) then
    Procs[Home].L2.Dirty := false;
  else
    Procs[Home].L2.Dirty := true;
  end;

  assert (Procs[Home].L2.pending = true & !isundefined(Procs[Home].L2.ReqId)) 
     "Funny Procs[Home].L2 state with outside reply.";
  src := Procs[Home].L2.ReqId;
  Procs[Home].L2.HeadPtr := src;
  if (Procs[Home].L2.InvCnt = 0) then
    Procs[Home].L2.pending := false;
  end;
  Procs[Home].UniMsg[src].Cmd := UNI_PutX;
  Procs[Home].UniMsg[src].Data := Procs[Home].L2.Data;
  undefine Procs[Home].UniMsg[src].Proc;
  undefine Procs[Home].L2.ReqId;

  assert (Dir.State = Excl & !isundefined(GUniMsg[Home].Cluster) &
	  Dir.HeadPtr = GUniMsg[Home].Cluster) 
     "Funny Dir state with home IACK.";
  undefine Dir.HeadPtr;
  Dir.isLocal := true;
  Procs[Home].RAC.State := Inval;
  Procs[Home].RAC.InvCnt := 0;

  undefine GUniMsg[Home];
  GUniMsg[Home].Cmd := GUNI_None;

  assert (Procs[Home].L2.isRetired = false) "Funny L2.isRetired value in Home_Recv_IACK(X).";
  Procs[Home].L2.isRetired := true;
endrule;


-- we can grant Home req when NAK_Home, but it will need another 
-- ReqType inside L2.
rule "Home_Recv_Nak"
  GUniMsg[Home].Cmd = NAK |
  GUniMsg[Home].Cmd = NAK_Home
==>
var src: NODE;
begin
  assert (Dir.isBusy = true) "Funny Dir.isBusy state2.";
  Dir.isBusy := false;

  Procs[Home].RAC.State := Inval;
  Procs[Home].RAC.InvCnt := 0;
  assert (Procs[Home].L2.pending = true & !isundefined(Procs[Home].L2.ReqId)) 
    "Funny Procs[Home].L2 state with outside reply.";
  if (Procs[Home].L2.InvCnt = 0) then
    Procs[Home].L2.pending := false;
  end;

  src := Procs[Home].L2.ReqId;
  Procs[Home].UniMsg[src].Cmd := UNI_Nak;
  undefine Procs[Home].UniMsg[src].Data;
  undefine Procs[Home].UniMsg[src].Proc;
  undefine Procs[Home].L2.ReqId;

  if (GUniMsg[Home].Cmd = NAK_Home) then
    assert (!isundefined(GUniMsg[Home].Cluster)) "Funny GUniMsg without Cluster.";
    if (Dir.State = Excl & Dir.HeadPtr = GUniMsg[Home].Cluster) then
      -- remove old owner
      Dir.State := Invld;
      undefine Dir.HeadPtr;
    end;
  end;
  undefine GUniMsg[Home];
  GUniMsg[Home].Cmd := GUNI_None;

  assert (Procs[Home].L2.isRetired = false) "Funny L2.isRetired value in Home_Recv_Nak.";
  Procs[Home].L2.isRetired := true;
endrule;



rule "Dir_Recv_NAKC_DIR"
  GNakcMsg.Cmd = GNAKC_DIR |
  GNakcMsg.Cmd = GNAKC_Nakc
==>
begin
  assert (Dir.isBusy = true) "Funny Dir.isBusy state3.";
  Dir.isBusy := false;

  if (GNakcMsg.Cmd = GNAKC_DIR) then
    assert (!isundefined(GNakcMsg.Cluster)) "Funny GNakc_Dir without Cluster.";
    if (Dir.State = Excl & Dir.HeadPtr = GNakcMsg.Cluster) then
      Dir.State := Invld;
      undefine Dir.HeadPtr;
    end;
  end;

  undefine GNakcMsg;
  GNakcMsg.Cmd := GNAKC_None;
endrule;



rule "Home_Recv_ACK"
  GUniMsg[Home].Cmd = ACK
==>
var src: NODE;
begin
  assert (Dir.isBusy = true) "Funny Dir.isBusy state4.";
  Dir.isBusy := false;

  assert (Procs[Home].L2.pending = true) "Funny request without pending.";
  assert (Procs[Home].RAC.State != Inval) "Funny ACK in Inval RAC state.";

  switch Procs[Home].RAC.State 

  -- home wait read reply
  case WRDO:
    Procs[Home].L2.State := Shrd;
    Procs[Home].L2.Data := GUniMsg[Home].Data;
    Procs[Home].RAC.State := Inval;
    Procs[Home].RAC.InvCnt := 0;
    Dir.Mem := GUniMsg[Home].Data;
    -- Dir.CurrData := GUniMsg[Home].Data;

    assert (Dir.State = Excl & Dir.HeadPtr = GUniMsg[Home].Cluster) 
     "Funny dir state with home receiving ACK.";
    Dir.State := Shrd;
    Dir.ShrSet[Dir.HeadPtr] := true;
    undefine Dir.HeadPtr;
    Dir.isLocal := true;

    Procs[Home].L2.OnlyCopy := false;
    Procs[Home].L2.pending := false;
    src := Procs[Home].L2.ReqId;
    Procs[Home].L2.ShrSet[src] := true;

    -- invariant purpose
    Procs[Home].CurrData := Dir.Mem;
    Procs[Home].UniMsg[src].Cmd := UNI_Put;
    Procs[Home].UniMsg[src].Data := Dir.Mem;
    undefine Procs[Home].UniMsg[src].Proc;
    undefine Procs[Home].L2.ReqId;

  -- invalidated before reply come back
  case RRD:
    Procs[Home].RAC.State := Inval;
    Procs[Home].RAC.InvCnt := 0;

    assert (Procs[Home].L2.pending = true & !isundefined(Procs[Home].L2.ReqId)) 
      "Funny Procs[Home].L2 state with outside reply.";
    Procs[Home].L2.pending := false;

    assert (Dir.State = Excl & Dir.HeadPtr = GUniMsg[Home].Cluster) 
     "Funny dir state with home receiving ACK.";
    Dir.State := Shrd;
    Dir.ShrSet[Dir.HeadPtr] := true;
    undefine Dir.HeadPtr;
    Dir.Mem := GUniMsg[Home].Data;
    -- Dir.CurrData := GUniMsg[Home].Data;

    src := Procs[Home].L2.ReqId;
    Procs[Home].UniMsg[src].Cmd := UNI_Nak;
    undefine Procs[Home].UniMsg[src].Data;
    undefine Procs[Home].UniMsg[src].Proc;
    undefine Procs[Home].L2.ReqId;

  else
    Error "Funny WRD/WRDX state in home.";
  end;

  undefine GUniMsg[Home];
  GUniMsg[Home].Cmd := GUNI_None;

  assert (Procs[Home].L2.isRetired = false) "Funny L2.isRetired value in Home_Recv_ACK.";
  Procs[Home].L2.isRetired := true;
endrule;


ruleset r: Rmt; src: Procss do
rule "RmtCluster_Recv_Get"
  GUniMsg[src].Cmd = RD_RAC &
  GUniMsg[src].Cluster = r &
  Procs[r].L2.Gblock_WB = false &

  -- Apr 8
  Procs[r].L2.ifHoldMsg = false
==>
begin
  assert (src != r) "Funny forwarded req to itself.";

  if (Procs[r].RAC.State = Inval & Procs[r].L2.pending = false) then
    if (!isundefined(Procs[r].L2.HeadPtr) & Procs[r].L2.HeadPtr = L2) then
      Procs[r].L2.OnlyCopy := false;
      Procs[r].L2.Dirty := false;
      Procs[r].L2.State := Shrd;

      GUniMsg[src].Cmd := ACK;
      GUniMsg[src].Data := Procs[r].L2.Data;
      GUniMsg[src].Cluster := r;
      GUniMsg[src].InvCnt := 0;

      if (src != Home) then
        GShWbMsg.Cmd := SHWB;
        GShWbMsg.Cluster := src;
        GShWbMsg.Data := Procs[r].L2.Data;
      end;

    elsif (!isundefined(Procs[r].L2.HeadPtr) & Procs[r].L2.HeadPtr != L2 & 
	   Procs[r].L2.State = Excl) then
      Procs[r].L2.pending := true;
      Procs[r].UniMsg[L2].Cmd := UNI_Get;
      undefine Procs[r].UniMsg[L2].Data;
      Procs[r].UniMsg[L2].Proc := Procs[r].L2.HeadPtr;

      Procs[r].L2.ReqCluster := src;
      Procs[r].L2.ReqType := true;

      -- Apr 8
      -- undefine GUniMsg[src];
      -- GUniMsg[src].Cmd := GUNI_None;
      Procs[r].L2.ifHoldMsg := true;

    elsif (Procs[r].L2.State = Shrd) then
      assert (Procs[r].L2.OnlyCopy = true) "Funny OnlyCopy value.";
      Procs[r].L2.OnlyCopy := false;
      Procs[r].L2.Dirty := false;

      GUniMsg[src].Cmd := ACK;
      GUniMsg[src].Data := Procs[r].L2.Data;
      GUniMsg[src].Cluster := r;
      GUniMsg[src].InvCnt := 0;

      if (src != Home) then
        GShWbMsg.Cmd := SHWB;
        GShWbMsg.Cluster := src;
        GShWbMsg.Data := Procs[r].L2.Data;
      end;

    else
      if (src = Home) then
        GUniMsg[src].Cmd := NAK_Home;
        undefine GUniMsg[src].Data;
        GUniMsg[src].Cluster := r;
        undefine GUniMsg[src].InvCnt;
      else
        GUniMsg[src].Cmd := NAK;
        undefine GUniMsg[src].Data;
        GUniMsg[src].Cluster := r;
        undefine GUniMsg[src].InvCnt;

        GNakcMsg.Cmd := GNAKC_DIR;
        GNakcMsg.Cluster := r;
      end;
    end;


  else
    GUniMsg[src].Cmd := NAK;
    undefine GUniMsg[src].Data;
    GUniMsg[src].Cluster := r;
    undefine GUniMsg[src].InvCnt;
    if (src != Home) then
      GNakcMsg.Cmd := GNAKC_Nakc;
      GNakcMsg.Cluster := r;
    end;
  end;
endrule;
endruleset;



ruleset dst: Rmt; src: Procss do
rule "RmtCluster_Recv_GetX"
  GUniMsg[src].Cmd = RDX_RAC &
  GUniMsg[src].Cluster = dst &
  Procs[dst].L2.Gblock_WB = false &

  -- Apr 8
  Procs[dst].L2.ifHoldMsg = false
==>
var 
  iCnt: CacheCnt;
begin
  assert (src != dst) "Funny forwarded req to itself.";

  if (Procs[dst].RAC.State = Inval & Procs[dst].L2.pending = false) then
    if (!isundefined(Procs[dst].L2.HeadPtr) & Procs[dst].L2.HeadPtr = L2) then
      Procs[dst].L2.OnlyCopy := false;
      Procs[dst].L2.State := Invld;
      GUniMsg[src].Data := Procs[dst].L2.Data;
      GUniMsg[src].InvCnt := 0;
      GUniMsg[src].Cluster := dst;
      if (Procs[dst].L2.Dirty = true) then
        GUniMsg[src].Cmd := IACKX;
      else
        GUniMsg[src].Cmd := IACK;
      end;

      if (src != Home) then
        GShWbMsg.Cmd := DXFER;
        GShWbMsg.Cluster := src;
        undefine GShWbMsg.Data;
      end;

      Procs[dst].L2.Dirty := false;
      undefine Procs[dst].L2.HeadPtr;
      undefine Procs[dst].L2.Data;
      undefine Procs[dst].PrevData;
      undefine Procs[dst].CurrData;

    elsif (!isundefined(Procs[dst].L2.HeadPtr) & Procs[dst].L2.HeadPtr != L2 & 
	   Procs[dst].L2.State = Excl) then
      Procs[dst].L2.pending := true;

      -- Apr 8
      -- undefine GUniMsg[src];
      -- GUniMsg[src].Cmd := GUNI_None;
      Procs[dst].L2.ifHoldMsg := true;


      Procs[dst].UniMsg[L2].Cmd := UNI_GetX;
      undefine Procs[dst].UniMsg[L2].Data;
      Procs[dst].UniMsg[L2].Proc := Procs[dst].L2.HeadPtr;

      Procs[dst].L2.ReqCluster := src;
      Procs[dst].L2.ReqType := false;

    elsif (Procs[dst].L2.State = Shrd) then
      assert (Procs[dst].L2.OnlyCopy = true) "Funny Procs[dst].L2.OnlyCopy value.";

      Procs[dst].L2.pending := true;
      Procs[dst].Collecting := true;
      Procs[dst].PrevData := Procs[dst].CurrData;
      iCnt := 0;
      for n: NODE do
        if Procs[dst].L2.ShrSet[n] = true then
          Procs[dst].InvMsg[n].Cmd := INV_Inv; 
          iCnt := iCnt + 1;
          Procs[dst].L2.ShrSet[n] := false;
        end;
      end;
      Procs[dst].L2.InvCnt := iCnt;

      GUniMsg[src].Data := Procs[dst].L2.Data;
      GUniMsg[src].InvCnt := 0;
      GUniMsg[src].Cluster := dst;
      if (Procs[dst].L2.Dirty = true) then
        GUniMsg[src].Cmd := IACKX;
      else
        GUniMsg[src].Cmd := IACK;
      end;

      if (src != Home) then
        GShWbMsg.Cmd := DXFER;
        GShWbMsg.Cluster := src;
        undefine GShWbMsg.Data;
      end;

      Procs[dst].L2.State := Invld;
      Procs[dst].L2.OnlyCopy := false;
      Procs[dst].L2.Dirty := false;
      undefine Procs[dst].L2.Data;

    else
      if (src = Home) then
        GUniMsg[src].Cmd := NAK_Home;
        undefine GUniMsg[src].Data;
        GUniMsg[src].Cluster := dst;
        undefine GUniMsg[src].InvCnt;
      else
        GUniMsg[src].Cmd := NAK;
        undefine GUniMsg[src].Data;
        GUniMsg[src].Cluster := dst;
        undefine GUniMsg[src].InvCnt;

        GNakcMsg.Cmd := GNAKC_DIR;
        GNakcMsg.Cluster := dst;
      end;
    end;

  else
    GUniMsg[src].Cmd := NAK;
    undefine GUniMsg[src].Data;
    GUniMsg[src].Cluster := dst;
    undefine GUniMsg[src].InvCnt;
    if (src != Home) then
      GNakcMsg.Cmd := GNAKC_Nakc;
      GNakcMsg.Cluster := dst;
    end;
  end;
endrule;
endruleset;



rule "Dir_Recv_DXFER"
  GShWbMsg.Cmd = DXFER
==>
begin
  assert (Dir.isBusy = true) "Funny Dir.isBusy state5.";
  Dir.isBusy := false;
  if (Dir.State = Excl & !isundefined(Dir.HeadPtr)) then
    Dir.HeadPtr := GShWbMsg.Cluster;
  end;
  undefine GShWbMsg;
  GShWbMsg.Cmd := GSHWB_None;
endrule;



rule "Dir_Recv_ShWb"  
  GShWbMsg.Cmd = SHWB
==>
begin
  assert (Dir.isBusy = true) "Funny Dir.isBusy state6.";
  Dir.isBusy := false;

  assert (Dir.State = Excl) "Funny ShWb without being excl.";
  assert (!isundefined(Dir.HeadPtr) & Dir.isLocal = false) 
     "Funny ShWb without remote being excl.";
  Dir.Mem := GShWbMsg.Data;
  -- Dir.CurrData := GShWbMsg.Data;
  Dir.State := Shrd;
  Dir.ShrSet[GShWbMsg.Cluster] := true;
  Dir.ShrSet[Dir.HeadPtr] := true;
  undefine Dir.HeadPtr;

  undefine GShWbMsg;
  GShWbMsg.Cmd := GSHWB_None;
endrule;



ruleset dst: Rmt do
rule "RmtCluster_Recv_ACK"
  GUniMsg[dst].Cmd = ACK
==>
var aux: NODE;
begin
  assert (Procs[dst].RAC.State != Inval) "Funny ACK in Inval RAC state.";

  switch Procs[dst].RAC.State 

  -- remote wait read reply
  case WRD:
    Procs[dst].L2.State := Shrd;
    Procs[dst].L2.Data := GUniMsg[dst].Data;
    Procs[dst].RAC.State := Inval;
    Procs[dst].RAC.InvCnt := 0;

    assert (!isundefined(Procs[dst].L2.ReqId)) "Funny L2.ReqId value.";
    assert (Procs[dst].L2.pending = true) "Funny L2.pending value.";
    Procs[dst].L2.pending := false;
    aux := Procs[dst].L2.ReqId;
    Procs[dst].L2.ShrSet[aux] := true;
    Procs[dst].UniMsg[aux].Cmd := UNI_Put;
    Procs[dst].UniMsg[aux].Data := Procs[dst].L2.Data;
    undefine Procs[dst].UniMsg[aux].Proc;
    undefine Procs[dst].L2.ReqId;

    -- invariant purpose
    Procs[dst].CurrData := GUniMsg[dst].Data;

  -- home wait read reply
  case WRDO:
    Error "No remote cluster can be WRDO.";

  -- cluster wait excl reply
  case WRDX:
    Procs[dst].L2.State := Excl;
    Procs[dst].L2.Data := GUniMsg[dst].Data;
    Procs[dst].L2.OnlyCopy := true;
    Procs[dst].RAC.State := Inval;
    Procs[dst].RAC.InvCnt := 0;
    Procs[dst].L2.Dirty := false;
    -- invariant purpose
    Procs[dst].CurrData := Procs[dst].L2.Data;

    assert (!isundefined(Procs[dst].L2.ReqId)) "Funny L2.ReqId value.";
    aux := Procs[dst].L2.ReqId;
    Procs[dst].L2.HeadPtr := aux;
    Procs[dst].UniMsg[aux].Cmd := UNI_PutX;
    Procs[dst].UniMsg[aux].Data := Procs[dst].L2.Data;
    undefine Procs[dst].UniMsg[aux].Proc;
    undefine Procs[dst].L2.ReqId;

    assert (Procs[dst].L2.pending = true) "Funny L2.pending value.";
    if (Procs[dst].L2.InvCnt = 0) then
      Procs[dst].L2.pending := false;
    end;

  -- invalidated before reply come back
  case RRD:
    Procs[dst].RAC.State := Inval;
    Procs[dst].RAC.InvCnt := 0;

    assert (!isundefined(Procs[dst].L2.ReqId)) "Funny L2.ReqId value.";
    aux := Procs[dst].L2.ReqId;
    Procs[dst].UniMsg[aux].Cmd := UNI_Nak;
    undefine Procs[dst].UniMsg[aux].Data;
    undefine Procs[dst].UniMsg[aux].Proc;
    undefine Procs[dst].L2.ReqId;

    assert (Procs[dst].L2.pending = true) "Funny L2.pending value.";
    Procs[dst].L2.pending := false;

  end;
  undefine GUniMsg[dst];
  GUniMsg[dst].Cmd := GUNI_None;

  assert (Procs[dst].L2.isRetired = false) "Funny L2.isRetired value in RmtCluster_Recv_ACK.";
  Procs[dst].L2.isRetired := true;
endrule;
endruleset;



ruleset dst: Rmt do
rule "RmtCluster_Recv_Nak"
  GUniMsg[dst].Cmd = NAK
==>
var aux: NODE;
begin
  assert ((Procs[dst].RAC.State != Inval) & (Procs[dst].RAC.State != WINV)) 
     "Funny NAK in Inval/WINV RAC state2.";
  Procs[dst].RAC.State := Inval;
  Procs[dst].RAC.InvCnt := 0;

  assert (!isundefined(Procs[dst].L2.ReqId)) "Funny L2.ReqId value.";
  aux := Procs[dst].L2.ReqId;
  Procs[dst].UniMsg[aux].Cmd := UNI_Nak;
  undefine Procs[dst].UniMsg[aux].Data;
  undefine Procs[dst].UniMsg[aux].Proc;
  undefine Procs[dst].L2.ReqId;

  assert (Procs[dst].L2.pending = true) "Funny L2.pending value.";
  if (Procs[dst].L2.InvCnt = 0) then
    Procs[dst].L2.pending := false;
  end;

  undefine GUniMsg[dst];
  GUniMsg[dst].Cmd := GUNI_None;

  assert (Procs[dst].L2.isRetired = false) "Funny L2.isRetired value in RmtCluster_Recv_Nak.";
  Procs[dst].L2.isRetired := true;
endrule;
endruleset;



ruleset dst: Procss do
rule "Cluster_Recv_Inv"
  GInvMsg[dst].Cmd = INV
==>
var proc: Procss;
    iCnt: CacheCnt;
begin
  proc := GInvMsg[dst].Cluster;

  switch Procs[dst].RAC.State
  case Inval:
    assert (Procs[dst].L2.OnlyCopy != true) "Funny L2.State value.";
    if (Procs[dst].L2.State = Shrd) then
      if (!isundefined(Procs[dst].L2.HeadPtr) & Procs[dst].L2.HeadPtr = L2) then
        undefine Procs[dst].L2.HeadPtr;
        undefine Procs[dst].PrevData;
        undefine Procs[dst].CurrData;

      elsif (! forall m: NODE do Procs[dst].L2.ShrSet[m] = false end) then
        -- invariant purpose
        Procs[dst].PrevData := Procs[dst].CurrData;
        Procs[dst].Collecting := true;
        Procs[dst].L2.pending := true;
        iCnt := 0;
        for n: NODE do
          if (Procs[dst].L2.ShrSet[n] = true) then
	    iCnt := iCnt + 1;
            Procs[dst].InvMsg[n].Cmd := INV_Inv;
            Procs[dst].L2.ShrSet[n] := false;
          end;
        end;
        Procs[dst].L2.InvCnt := iCnt;
      end;
    end;

    Procs[dst].L2.State := Invld;
    undefine Procs[dst].L2.Data;

  case WRD:
    Procs[dst].RAC.State := RRD;
  case WRDO:
    Procs[dst].RAC.State := RRD;
  case WRDX:
    if (proc = dst) then
      Procs[dst].RAC.InvCnt := Procs[dst].RAC.InvCnt + 1;
    else 
      Procs[dst].L2.State := Invld;
      undefine Procs[dst].L2.Data;
      if (!isundefined(Procs[dst].L2.HeadPtr) & Procs[dst].L2.HeadPtr = L2) then
        undefine Procs[dst].L2.HeadPtr;
      end;
    end;
  case WINV:
    if (proc = dst) then
      Procs[dst].RAC.InvCnt := Procs[dst].RAC.InvCnt - 1;
      -- all InvAck received
      if (Procs[dst].RAC.InvCnt = 0) then
        Procs[dst].RAC.State := Inval;
        -- invariant purpose
        Dir.Collecting := false;
      end;

    else
      Error "Funny WINV receiving INV.";
    end;
  end;

  if (proc != dst) then
    GInvMsg[dst].Cmd := SACK;
    GInvMsg[dst].Cluster := proc;
  else
    undefine GInvMsg[dst];
    GInvMsg[dst].Cmd := GINV_None;
  end;
endrule;
endruleset;



ruleset dst: Rmt; src: Procss do
rule "RmtCluster_Recv_InvAck"
  GInvMsg[src].Cmd = SACK &
  GInvMsg[src].Cluster = dst
==>
begin
  assert (src != dst) "Funny InvAck to itself.";

  switch Procs[dst].RAC.State
  -- receive InvAck before reply from Dir
  case WRDX:
    Procs[dst].RAC.InvCnt := Procs[dst].RAC.InvCnt + 1;

  -- receive InvAck after reply from Dir
  case WINV:
    Procs[dst].RAC.InvCnt := Procs[dst].RAC.InvCnt - 1;
    -- all InvAck received
    if (Procs[dst].RAC.InvCnt = 0) then
      Procs[dst].RAC.State := Inval;
      -- invariant purpose
      Dir.Collecting := false;
    end;

  else
    Error "Funny RAC.State value."; 
  end;

  undefine GInvMsg[src];
  GInvMsg[src].Cmd := GINV_None;
endrule;
endruleset;



ruleset dst: Rmt do
rule "RmtCluster_Recv_IACK(X)"
  GUniMsg[dst].Cmd = IACK |
  GUniMsg[dst].Cmd = IACKX
==>
var aux: NODE;
begin
  assert (Procs[dst].RAC.State = WRDX) "Funny cluster state receive IACK.";

  Procs[dst].RAC.InvCnt := GUniMsg[dst].InvCnt - Procs[dst].RAC.InvCnt;
  Procs[dst].L2.Data := GUniMsg[dst].Data;
  Procs[dst].CurrData := GUniMsg[dst].Data;
  Procs[dst].L2.State := Excl;
  Procs[dst].L2.OnlyCopy := true;
  if (GUniMsg[dst].Cmd = IACK) then
    Procs[dst].L2.Dirty := false;
  else
    Procs[dst].L2.Dirty := true;
  end;

  -- still wait for InvAck
  if (Procs[dst].RAC.InvCnt > 0) then
     Procs[dst].RAC.State := WINV;
  -- all InvAck received
  else
    Procs[dst].RAC.State := Inval;
    Dir.Collecting := false;
  end;

  assert (Procs[dst].L2.pending = true & !isundefined(Procs[dst].L2.ReqId)) 
     "Funny L2.pending and ReqId values receiving IACK(X).";
  if (Procs[dst].L2.InvCnt = 0) then
    Procs[dst].L2.pending := false;
  end;
  aux := Procs[dst].L2.ReqId;
  Procs[dst].UniMsg[aux].Cmd := UNI_PutX;
  undefine Procs[dst].UniMsg[aux].Proc;
  Procs[dst].UniMsg[aux].Data := Procs[dst].L2.Data;
  Procs[dst].L2.HeadPtr := aux;
  undefine Procs[dst].L2.ReqId;

  undefine GUniMsg[dst];
  GUniMsg[dst].Cmd := GUNI_None;

  assert (Procs[dst].L2.isRetired = false) "Funny L2.isRetired value in RmtCluster_Recv_IACK(X).";
  Procs[dst].L2.isRetired := true;
endrule;
endruleset;



ruleset r: Rmt do
rule "Dir_Recv_RmtGet_Put"
  (Dir.State = Invld | 
   Dir.State = Shrd) &
  Dir.isBusy = false &
  GUniMsg[r].Cmd = RD_H
==>
begin
  Dir.State := Shrd;
  Dir.ShrSet[r] := true;

  GUniMsg[r].Cmd := ACK;
  GUniMsg[r].Data := Dir.Mem;
  undefine GUniMsg[r].Cluster;
  GUniMsg[r].InvCnt := 0;
endrule;
endruleset;


/*
-- commenting this rule will in fact queue those requests coming to
-- Dir when Dir is busy.
ruleset r: Rmt do
rule "Dir_Recv_RmtGet(X)_Nak"
  Dir.isBusy = true &
  (GUniMsg[r].Cmd = RD_H |
   GUniMsg[r].Cmd = RDX_H)
==>
begin
  GUniMsg[r].Cmd := NAK;
  undefine GUniMsg[r].Data;
  undefine GUniMsg[r].Cluster;
  GUniMsg[r].InvCnt := 0;
endrule;
endruleset;
*/


ruleset r: Rmt do
rule "Dir_Recv_RmtGet_(RmtGet)"
  Dir.State = Excl &
  Dir.isBusy = false &
  Dir.isLocal = false &
  GUniMsg[r].Cmd = RD_H
==>
begin
  assert (! isundefined(Dir.HeadPtr)) "Remote excl without headptr2.";
  if (Dir.HeadPtr = r) then
    GUniMsg[r].Cmd := ACK;
    GUniMsg[r].Data := Dir.Mem;
    undefine GUniMsg[r].Cluster;
    GUniMsg[r].InvCnt := 0;

    Dir.State := Shrd;
    Dir.ShrSet[r] := true;
    undefine Dir.HeadPtr;
  else 
    Dir.isBusy := true;
    GUniMsg[r].Cmd := RD_RAC;
    undefine GUniMsg[r].Data;
    GUniMsg[r].Cluster := Dir.HeadPtr;
    undefine GUniMsg[r].InvCnt;
  end;
endrule;
endruleset;



-- no need to ABS
ruleset r: Rmt do
rule "Dir_Recv_RmtGetX_(RmtGetX)"
  Dir.State = Excl &
  Dir.isBusy = false & 
  Dir.isLocal = false &
  GUniMsg[r].Cmd = RDX_H
==>
begin
  if (Dir.HeadPtr = r) then
    GUniMsg[r].Cmd := ACK;
    GUniMsg[r].Data := Dir.Mem;
    undefine GUniMsg[r].Cluster;
    GUniMsg[r].InvCnt := 0;
  else 
    Dir.isBusy := true;
    GUniMsg[r].Cmd := RDX_RAC;
    undefine GUniMsg[r].Data;
    GUniMsg[r].Cluster := Dir.HeadPtr;
    undefine GUniMsg[r].InvCnt;
  end;
endrule;
endruleset;



-- no need to ABS
ruleset r: Rmt do
rule "Dir_Recv_RmtGetX_isLocal"
  Dir.State = Excl &
  Dir.isBusy = false & 
  Dir.isLocal = true &
  GUniMsg[r].Cmd = RDX_H &

  -- Apr 8
  Procs[Home].L2.ifHoldMsg = false
==>
var iCnt: CacheCnt;
begin
  if (Procs[Home].RAC.State = Inval & Procs[Home].L2.pending = false) then
    if (!isundefined(Procs[Home].L2.HeadPtr) & Procs[Home].L2.HeadPtr = L2) then
      Procs[Home].L2.OnlyCopy := false;
      Procs[Home].L2.State := Invld;

      GUniMsg[r].Data := Procs[Home].L2.Data;
      GUniMsg[r].InvCnt := 0;
      undefine GUniMsg[r].Cluster;
      if (Procs[Home].L2.Dirty = true) then
        GUniMsg[r].Cmd := IACKX;
      else
        GUniMsg[r].Cmd := IACK;
      end;

      Procs[Home].L2.Dirty := false;
      undefine Procs[Home].L2.HeadPtr;
      undefine Procs[Home].L2.Data;
      undefine Procs[Home].CurrData;
      undefine Procs[Home].PrevData;
      Dir.isLocal := false;
      Dir.HeadPtr := r;

    elsif (Procs[Home].L2.State = Excl & !isundefined(Procs[Home].L2.HeadPtr) & 
	   Procs[Home].L2.HeadPtr != L2) then
      Procs[Home].L2.pending := true;
      Procs[Home].UniMsg[L2].Cmd := UNI_GetX;
      Procs[Home].UniMsg[L2].Proc := Procs[Home].L2.HeadPtr;
      undefine Procs[Home].UniMsg[L2].Data;

      Procs[Home].L2.ReqCluster := r;
      Procs[Home].L2.ReqType := false;

      -- Apr 8
      -- undefine GUniMsg[r];
      -- GUniMsg[r].Cmd := GUNI_None;
      Procs[Home].L2.ifHoldMsg := true;


    elsif (Procs[Home].L2.State = Shrd ) then
      assert (Procs[Home].L2.OnlyCopy = true) "Funny L2.OnlyCopy value.";
      Procs[Home].L2.pending := true;
      iCnt := 0;
      for n: NODE do
        if (Procs[Home].L2.ShrSet[n] = true) then
          Procs[Home].InvMsg[n].Cmd := INV_Inv;
          iCnt := iCnt + 1;
          Procs[Home].L2.ShrSet[n] := false;
        end;
      end;
      Procs[Home].L2.InvCnt := iCnt;
      Procs[Home].PrevData := Procs[Home].CurrData;
      Procs[Home].Collecting := true;

      GUniMsg[r].Data := Procs[Home].L2.Data;
      GUniMsg[r].InvCnt := 0;
      undefine GUniMsg[r].Cluster;
      if (Procs[Home].L2.Dirty = true) then
        GUniMsg[r].Cmd := IACKX;
      else
        GUniMsg[r].Cmd := IACK;
      end;

      Procs[Home].L2.State := Invld;
      Procs[Home].L2.OnlyCopy := false;
      Procs[Home].L2.Dirty := false;
      undefine Procs[Home].L2.Data;
      Dir.isLocal := false;
      Dir.HeadPtr := r;

    else 
      GUniMsg[r].Data := Dir.Mem;
      GUniMsg[r].InvCnt := 0;
      undefine GUniMsg[r].Cluster;
      GUniMsg[r].Cmd := IACK;

      Dir.isLocal := false;
      Dir.HeadPtr := r;
    end;


  -- home busy
  else
    undefine GUniMsg[r].Data;
    undefine GUniMsg[r].InvCnt;
    undefine GUniMsg[r].Cluster;
    GUniMsg[r].Cmd := NAK;
  end; 
endrule;
endruleset;



ruleset r: Rmt do
rule "Dir_Recv_RmtGet_isLocal"
  Dir.State = Excl &
  Dir.isBusy = false & 
  Dir.isLocal = true &
  GUniMsg[r].Cmd = RD_H &

  -- Apr 8
  Procs[Home].L2.ifHoldMsg = false
==>
begin
  if (Procs[Home].RAC.State = Inval & Procs[Home].L2.pending = false) then
    if (!isundefined(Procs[Home].L2.HeadPtr) & Procs[Home].L2.HeadPtr = L2) then
      Procs[Home].L2.State := Shrd;
      Procs[Home].L2.OnlyCopy := false;
      Procs[Home].L2.Dirty := false;
      Dir.State := Shrd;
      Dir.Mem := Procs[Home].L2.Data;
      -- Dir.CurrData := Procs[Home].L2.Data;
      GUniMsg[r].Cmd := ACK;
      GUniMsg[r].Data := Dir.Mem;
      GUniMsg[r].InvCnt := 0;
      undefine GUniMsg[r].Cluster;
      Dir.ShrSet[r] := true;

    elsif (Procs[Home].L2.State = Excl & !isundefined(Procs[Home].L2.HeadPtr) & 
	   Procs[Home].L2.HeadPtr != L2) then
      Procs[Home].L2.pending := true;
      Procs[Home].UniMsg[L2].Cmd := UNI_Get;
      Procs[Home].UniMsg[L2].Proc := Procs[Home].L2.HeadPtr;
      undefine Procs[Home].UniMsg[L2].Data;

      Procs[Home].L2.ReqCluster := r;
      Procs[Home].L2.ReqType := true;


      -- Apr 8
      -- undefine GUniMsg[r];
      -- GUniMsg[r].Cmd := GUNI_None;
      Procs[Home].L2.ifHoldMsg := true;


    elsif (Procs[Home].L2.State = Shrd) then
      assert (Procs[Home].L2.OnlyCopy = true) "Funny Home.OnlyCopy value.";
      Procs[Home].L2.OnlyCopy := false;
      Procs[Home].L2.Dirty := false;
      Dir.Mem := Procs[Home].L2.Data;
      -- Dir.CurrData := Procs[Home].L2.Data;
      Dir.ShrSet[r] := true;
      Dir.State := Shrd;

      GUniMsg[r].Cmd := ACK;
      GUniMsg[r].Data := Dir.Mem;
      GUniMsg[r].InvCnt := 0;
      undefine GUniMsg[r].Cluster;

    else 
      Dir.isLocal := false;
      Dir.State := Shrd;
      Dir.ShrSet[r] := true;
      GUniMsg[r].Cmd := ACK;
      GUniMsg[r].Data := Dir.Mem;
      GUniMsg[r].InvCnt := 0;
      undefine GUniMsg[r].Cluster
    end;


  -- home busy
  else
    GUniMsg[r].Cmd := NAK;
    undefine GUniMsg[r].Data;
    undefine GUniMsg[r].InvCnt;
    undefine GUniMsg[r].Cluster
  end; 
endrule;
endruleset;



ruleset r: Rmt do
rule "Dir_Recv_RmtGetX_PutX"
  Dir.State = Invld &
  Dir.isBusy = false &
  GUniMsg[r].Cmd = RDX_H 
==>
begin
  Dir.State := Excl;
  Dir.HeadPtr := r;
  assert (Dir.isLocal = false) "Funny Invld with home having valid copy.";

  GUniMsg[r].Cmd := ACK;
  GUniMsg[r].InvCnt := 0;
  GUniMsg[r].Data := Dir.Mem;
  undefine GUniMsg[r].Cluster;
endrule;
endruleset;



ruleset p: Procss do
rule "Cluster_WriteBack"
  Procs[p].L2.State = Excl &
  Procs[p].L2.Dirty = true &
  Procs[p].RAC.State = Inval &
  Procs[p].L2.HeadPtr = L2 &
  Procs[p].L2.pending = false
==>
begin
  for n: NODE do
    assert (Procs[p].L2.ShrSet[n] = false) "Funny sharer with Excl and dirty.";
  end;

  undefine Procs[p].L2.HeadPtr;
  Procs[p].L2.State := Invld;
  Procs[p].L2.OnlyCopy := false;
  Procs[p].L2.Dirty := false;
  if (p = Home) then
    Dir.isLocal := false;
    Dir.Mem := Procs[p].L2.Data;
    -- Dir.CurrData := Procs[p].L2.Data;
    Dir.State := Invld;
  else
    Procs[p].L2.Gblock_WB := true;
    GWbMsg.Cmd := WB;
    GWbMsg.Cluster := p;
    GWbMsg.Data := Procs[p].L2.Data;
  end;
  undefine Procs[p].L2.Data;

  -- invariant purpose
  undefine Procs[p].PrevData;
  undefine Procs[p].CurrData;
endrule;
endruleset;


rule "Dir_Recv_WB"
  GWbMsg.Cmd = WB
==>
begin
  /*
  -- cannot assert the following:
  assert (Dir.State = Excl & Dir.HeadPtr = r & Dir.isLocal = false) 
     "Writeback with funny directory state.";
  -- counterexample:
    Rmt_Send_GetX, r:Rmt_1
    Dir_RmtGetX_PutX, r:Rmt_1
    Rmt_Send_GetX, r:Rmt_2
    Dir_RmtGetX_(RmtGetX), r:Rmt_2
    RmtCluster_Recv_ACK, dst:Rmt_1
    Cluster_Update_Data, d:Datas_1, p:Rmt_1
    RmtCluster_Recv_GetX, dst:Rmt_1
    RmtCluster_Recv_IACK, dst:Rmt_2
    Cluster_WriteBack, p:Rmt_2
  */
  assert (Dir.State = Excl & !isundefined(Dir.HeadPtr) & Dir.isLocal = false) 
     "Writeback with funny directory state.";
  Dir.State := Invld;
  undefine Dir.HeadPtr;
  Dir.Mem := GWbMsg.Data;

  GUniMsg[GWbMsg.Cluster].Cmd := WB_Ack;
  undefine GUniMsg[GWbMsg.Cluster].Data;
  undefine GUniMsg[GWbMsg.Cluster].Cluster;
  undefine GUniMsg[GWbMsg.Cluster].InvCnt;

  undefine GWbMsg;
  GWbMsg.Cmd := GWB_None;
endrule;


ruleset r: Rmt do
rule "RmtCluster_Recv_WBAck"
  GUniMsg[r].Cmd = WB_Ack
==>
begin
  assert (Procs[r].L2.Gblock_WB = true & Procs[r].RAC.State = Inval) 
     "Funny Gblock_WB state receiving WB_Ack";
  Procs[r].L2.Gblock_WB := false;
  undefine GUniMsg[r];
  GUniMsg[r].Cmd := GUNI_None;
endrule;
endruleset;



ruleset r: Rmt do
rule "Dir_Shrd_RmtGetX_PutX"
  GUniMsg[r].Cmd = RDX_H &
  Dir.State = Shrd &
  Dir.isBusy = false
==>
var ShrCnt: ClusterCnt;
begin
  -- Dir.ShrSet[r] := false;
  ShrCnt := 0;
  if (Dir.isLocal = true) then
    ShrCnt := 1;
    GInvMsg[Home].Cmd := INV;
    GInvMsg[Home].Cluster := r;
    Dir.Collecting := true;
    Dir.PrevData := Dir.CurrData;
    Dir.isLocal := false;
  end;

  Dir.State := Excl;
  Dir.HeadPtr := r;

  -- only r is in the sharer list
  if (ShrCnt = 0 & 
      forall i: Rmt do i != r -> Dir.ShrSet[i] = false end) then
    GUniMsg[r].Cmd := ACK;
    GUniMsg[r].Data := Dir.Mem;
    GUniMsg[r].InvCnt := 0;
    undefine GUniMsg[r].Cluster;

  else
    for p: Rmt do
      if (Dir.ShrSet[p] = true) then
        ShrCnt := ShrCnt + 1;
        Dir.ShrSet[p] := false;
        GInvMsg[p].Cmd := INV;
        GInvMsg[p].Cluster := r;

        -- invariant purpose
        Dir.Collecting := true;
        Dir.PrevData := Dir.CurrData;
      end;
    end;
    GUniMsg[r].Cmd := IACK;
    GUniMsg[r].Data := Dir.Mem;
    GUniMsg[r].InvCnt := ShrCnt;
    undefine GUniMsg[r].Cluster;  
  end;
endrule;
endruleset;


-------------------------------------------------------------------------------
------ inside a cluster ------

invariant "CacheStateProp"
  forall p: Procss do
  forall n1: NODE do forall n2: NODE do
    n1 != n2 ->
    !((Procs[p].Proc[n1].CacheState = CACHE_E | 
       Procs[p].Proc[n1].CacheState = CACHE_M) & 
      (Procs[p].Proc[n2].CacheState = CACHE_E |  
       Procs[p].Proc[n2].CacheState = CACHE_M))
  end end end;


invariant "CacheDataProp"   
  forall p: Procss do
  forall n : NODE do
    ((Procs[p].Proc[n].CacheState = CACHE_E |  
      Procs[p].Proc[n].CacheState = CACHE_M) 
     ->
     Procs[p].Proc[n].CacheData = Procs[p].CurrData ) &
    (Procs[p].Proc[n].CacheState = CACHE_S ->
      (Procs[p].Collecting -> Procs[p].Proc[n].CacheData = Procs[p].PrevData ) &
      (!Procs[p].Collecting -> Procs[p].Proc[n].CacheData = Procs[p].CurrData ) )
  end end;


invariant "OnlyCopyProp"
  forall p: Procss do
  ((Procs[p].L2.Dirty = true | Procs[p].L2.State = Excl) ->
   (Procs[p].L2.OnlyCopy = true))
  end;

invariant "CacheInvldDataProp"
  forall p: Procss do
  forall n: NODE do
    Procs[p].Proc[n].CacheState = CACHE_I -> isundefined(Procs[p].Proc[n].CacheData)
  end end;


invariant "L2InvldDataProp"
  forall p: Procss do
    (Procs[p].L2.State = Invld) 
     -> 
    (isundefined(Procs[p].L2.Data) &
     Procs[p].L2.OnlyCopy = false & 
     Procs[p].L2.Dirty = false)
  end;


------ outside a cluster  ------

invariant "Remote cluster cannot be WRDO."
  forall r : Rmt do
    ( Procs[r].RAC.State != WRDO )
  end;


invariant "ClusterStateProp" 
  forall p: Procss do
    forall q: Procss do
      !((p != q) &
        (Procs[p].L2.State = Excl & Procs[q].L2.State = Excl))
  end end;


invariant "InvldDataProp"
  forall p: Procss do
    (Procs[p].L2.State = Invld) ->
    (isundefined(Procs[p].L2.Data)) 
  end;


invariant "RACINvalProp"
  forall p: Procss do 
    (Procs[p].RAC.State = Inval) ->
    (Procs[p].RAC.InvCnt = 0)
  end;



invariant "InvStateProp"
  forall p: Procss do
  forall q: Procss do
    ((p != q) & (Procs[p].RAC.State = WINV) & (Procs[q].L2.State = Shrd)) 
    ->
    (GInvMsg[q].Cmd = INV)
  end end;


/*
-- not a valid invariant, counterexample as following:
Start rule :
    Init, d:Datas_1
Other rules:
    L1_GetX, src:NODE_1, p:Home
    L2_Recv_Get(X)_OutGet(X), src:NODE_1, p:Home
    L1_Get, src:NODE_2, p:Home
    L1_Get, src:NODE_1, p:Rmt_1
    L2_Recv_Get(X)_OutGet(X), src:NODE_1, p:Rmt_2
    Dir_Recv_RmtGet_Put, r:Rmt_2
    Dir_Shrd_HomeGetX_PutX
    L1_Recv_PutX, dst:NODE_1, p:Home
    L2_Fwd_Get(X), src:NODE_2, p:Home
    L1_Update_Data, data:Datas_2, src:NODE_1, p:Home
    L1Rmt_Recv_Get_Put, dst:NODE_1, p:Home
    L2_Recv_SHWB, src:NODE_1, p:Home

invariant "ClusterShrdDataProp"
  forall p: Procss do
    ((Procs[p].L2.State = Shrd) ->
     ((Dir.Collecting -> Procs[p].L2.Data = Dir.PrevData) &
      (!Dir.Collecting -> Procs[p].L2.Data = Dir.CurrData)))
  end;
*/

invariant "MemDataProp"
  (!(Dir.State = Excl)) -> (Dir.Mem = Dir.CurrData);


/*
-- not a valid invariant
-- counterexample:
-- 1. p1 gets shared
-- 2. p1 silent drop
-- 3. p1 req shared
-- 4. p2 req excl, dir invalidates p1, grants p2
-- 5. p1 get Invalidated
-- 6. dir receives p1's req, forwards to p2
-- 7. p2 grants p1's req, shwb to dir
-- 8. dir set p1 & p2 to be sharers
-- 9. p3 req excl, dir invalidates p1 and p2, grants p3
-- 10 p1 receives 2nd INV before p2's reply to p1.
invariant "ClusterRecvInvProp"
  forall p: Procss do 
    (GInvMsg[p].Cmd = INV) 
     ->
    (Procs[p].RAC.State != RRD )
  end;
*/

invariant "tmpProp"
forall p: Procss do
  forall src: NODE do
    (Procs[p].InvMsg[src].Cmd = INV_InvAck) 
    ->
    Procs[p].L2.pending = true
end end;


invariant "L2.InvCnt>=0"  
forall p: Procss do
  forall src: NODE do
    (Procs[p].InvMsg[src].Cmd = INV_InvAck)
    ->
    (Procs[p].L2.InvCnt > 0)
end end;


invariant "Nak.Inval.WINV"
forall p: Procss do
  (GUniMsg[p].Cmd = NAK)
  ->
  (Procs[p].RAC.State != Inval & Procs[p].RAC.State != WINV)
end;




invariant "Uni_PutwithDataProp"
forall p: Procss do
  forall n: NODE do
    Procs[p].UniMsg[n].Cmd = UNI_Put 
    ->
    !isundefined(Procs[p].UniMsg[n].Data)
end end;

invariant "HomeRecvIACK(X)Prop"
  GUniMsg[Home].Cmd = IACK |
  GUniMsg[Home].Cmd = IACKX
->
  Dir.isBusy = true;


invariant "isRetiredProp1"
forall p: Procss do
  Procs[p].L2.isRetired = true 
->
  Procs[p].RAC.State = Inval | 
  Procs[p].RAC.State = WINV |
  Procs[p].L2.OnlyCopy = true
end;


invariant "isRetiredProp2"
forall p: Procss do
  Procs[p].RAC.State = Inval | 
  Procs[p].RAC.State = WINV 
->
  Procs[p].L2.isRetired = true 
end;


invariant "StateProp"
  Dir.isLocal = false 
->
  Procs[Home].L2.State != Excl;


invariant "HeadPtrProp"
forall p: Procss do
  Procs[p].L2.pending = false &
  !isundefined(Procs[p].L2.HeadPtr) &
  Procs[p].L2.HeadPtr = L2
->
  Procs[p].L2.State != Invld
end;


invariant "Excl->OnlyCopy"
forall p: Procss do
  Procs[p].L2.State = Excl 
->
  Procs[p].L2.OnlyCopy = true
end;


invariant "HeadPtrL2->NoSharers"
forall p: Procss do
  !isundefined(Procs[p].L2.HeadPtr) &
  Procs[p].L2.HeadPtr = L2
->
  forall n: NODE do
    Procs[p].L2.ShrSet[n] = false
  end
end;



invariant "HeadPtrL2OnlyCopy->Excl"
forall p: Procss do
  !isundefined(Procs[p].L2.HeadPtr) &
  Procs[p].L2.HeadPtr = L2 &
  Procs[p].L2.OnlyCopy = true
->
  Procs[p].L2.State = Excl
end;



invariant "HeadPtrL2!OnlyCopy->Shrd"
forall p: Procss do
  !isundefined(Procs[p].L2.HeadPtr) &
  Procs[p].L2.HeadPtr = L2 &
  Procs[p].L2.OnlyCopy = false
->
  Procs[p].L2.State = Shrd
end;


invariant "!Invld->!Gblock_WB"
forall p: Procss do
  Procs[p].L2.State != Invld 
->
  Procs[p].L2.Gblock_WB = false
end;


invariant "NAKC_Nakc->Excl&Inval"
forall p: Procss do
  Procs[p].NakcMsg.Cmd = NAKC_Nakc &
  Procs[p].NakcMsg.Aux = L2
->
  Procs[p].L2.State = Excl &
  Procs[p].RAC.State = Inval
end;


invariant "NAKC_SD->Excl&Inval&!Gblock_WB"
forall p: Procss do
  Procs[p].NakcMsg.Cmd = NAKC_SD &
  Procs[p].NakcMsg.Aux = L2
->
  Procs[p].L2.State = Excl &
  Procs[p].RAC.State = Inval &
  Procs[p].L2.Gblock_WB = false
end;



invariant "SHWB_ShWb+L2->Excl+Inval"
forall p: Procss do
  Procs[p].ShWbMsg.Cmd = SHWB_ShWb &
  Procs[p].ShWbMsg.Aux = L2
->
  Procs[p].L2.State = Excl &
  Procs[p].RAC.State = Inval
end;



invariant "SHWB_ShWb->Excl"
forall p: Procss do
  Procs[p].ShWbMsg.Cmd = SHWB_ShWb 
->
  Procs[p].L2.State = Excl 
end;


invariant "SHWB_FAck+L2->Excl+Inval"
forall p: Procss do
  Procs[p].ShWbMsg.Cmd = SHWB_FAck &
  Procs[p].ShWbMsg.Aux = L2
->
  Procs[p].L2.State = Excl &
  Procs[p].RAC.State = Inval
end;


invariant "l2HeadPtr+RD_RAC->Excl"
forall p: Procss do
forall src: Procss do
  (GUniMsg[src].Cmd = RD_RAC|
   GUniMsg[src].Cmd = RDX_RAC) &
  GUniMsg[src].Cluster = p &
  Procs[p].RAC.State = Inval &
  !isundefined(Procs[p].L2.HeadPtr) & 
  Procs[p].L2.HeadPtr = L2
-> 
  Procs[p].L2.State = Excl
end end;
