--------------------------------------------------------------------------------
--
--  Murphi Model of 802.16e Multicast/Broadcast Security Protocol
--
--  Ju-Yi Kuo
--
--------------------------------------------------------------------------------


--------------------------------------------------------------------------------
-- constants, types and variables
--------------------------------------------------------------------------------

-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
const
  
  INTRUDER_PARTICIPATES:     true;
  
  -- enable/disable invariants
  CHK_MEMBERSHIP:            true;
  CHK_GKEY_LIFE:             true;
  CHK_GTEY_LIFE:             true;
  CHK_KEY_FRESHNESS:         true;

  NumMS:                      2;   -- number of mobile stations including the 1 intruder
  NetworkSize:                1;   -- max. number of outstanding messages in network
  MaxKnowledge:              50;   -- max. number of messages intruder can remember
  NumGroups:                  2;
  MaxSessionsPerMSPerGroup:   2;
  MumGKEKs:                   2;
  NumTKEKperGKEK:             2;
  MaxMSNonce:                20;
  MaxSequenceNum:            50;   -- sequence number/counter used for msgs and keys
  MaxKeyLifetime:            50;   -- max life time of keys

  InvalidGKEK:               MumGKEKs + 1;
  InvalidGTEK:               NumTKEKperGKEK + 1;
  InvalidKeyLifetime:        MaxKeyLifetime + 1;
  
-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
type
  MSID:         scalarset (NumMS);   -- mobile station identifiers
  MSCOUNT:      0..NumMS;
  GSAID:        scalarset (NumGroups);   -- group identifiers
  GKEKID:       1..MumGKEKs;  -- version Id of the GKEK of a group
  GTEKID:       1..NumTKEKperGKEK;  -- version Id of the GTEK of a GKEK of a group
  MSSessions:   0..MaxSessionsPerMSPerGroup;
  NonceID:      1..MaxMSNonce;
  SequenceNum:  0..MaxSequenceNum;
  KeyLifetime:  0..MaxKeyLifetime;
  
 
  -- hmac/cmac related types
  PacketNumber_Uni : record
    ul:    SequenceNum;
    dl:    SequenceNum;
  end;
  
  GMacKey_Uni : record  -- unicast msg mac key
    gid:  GSAID;
    msid: MSID;
    ul:   boolean;   -- uplink or not
  end;
  
  GMacKey_MBS : record  -- multicast/broadcast msg mac key (always downlink)
    gid:  GSAID;
    gkek: GKEKID;
  end;
  
  GMacKeyKnown_Uni : array[GSAID] of array[MSID] of array[boolean] of boolean;
  
  GMacKeyKnown_MBS : array[GSAID] of array[GKEKID] of boolean;
  
  -- group key related types
  GTEKParam : record
    gkekVer: GKEKID;
    gtekVer: GTEKID;
  end;
  
  GKEK : record
    gid: GSAID;
    gkekVer: GKEKID;
    encKEK: MSID;     -- the kek that encrypts this gkek
    param: GKEKID;
    life: KeyLifetime;
  end;
  
  GKEKey : record
    gid: GSAID;
    gkekVer: GKEKID;
  end;
  
  GTEK : record
    gid: GSAID;
    gkekVer: GKEKID;
    gtekVer: GTEKID;
    encGKEK: GKEKID;  -- the gkek that encrypts this gtek
    param: GTEKParam;
    life: KeyLifetime;
  end;
  
  GTEKey : record
    gid: GSAID;
    gkekVer: GKEKID;
    gtekVer: GTEKID;
  end;
  
  GKey1_t : record
    gkek: boolean;
    gtek: array[GTEKID] of boolean;
  end;
  GKeyKnown : array[GSAID] of array[GKEKID] of GKey1_t;
  
  -- message related types
  MessageType : enum {           -- different types of messages
    KeyReq,              --  {Na, A}Kb:   nonce and address
    KeyRsp,         --  {Na,Nb,B}Ka: two nonces and address
    KeyUpdGKEK,                      --  {Nb}Kb:      one nonce
    KeyUpdGTEK
  };

  MIC : record
    cid:      MSID;              -- connection id
    mType:    MessageType;       -- type of message. this can be identified by msg header
    gsaId:    GSAID;             -- source of message
    nonce:    NonceID;
    gkek:     GKEK;              -- 
    gtek:     GTEK;              -- 
    seq:      SequenceNum;       -- key push counter
    pn:       SequenceNum;       -- packet number counter
  end;

  Message : record
    fromIntruder:    boolean;       -- an optimization trick
    multiReceivers:  multiset[NumMS] of MSID;  -- multicast message simulation
    cid:         MSID;              -- connection id
    mType:       MessageType;       -- type of message. this can be identified by msg header
    gsaId:       GSAID;             -- source of message
    nonce:       NonceID;
    gkek:        GKEK;              -- 
    gtek:        GTEK;              -- 
    seq:         SequenceNum;
    pn:          SequenceNum;       -- packet number counter
    
    gMacKey_Uni:  GMacKey_Uni;         -- unicast group mac key used for msg verification
    gMacKey_MBS:  GMacKey_MBS;         -- MBS group mac key used for msg verification
    mic:          MIC;
  end;

  -- mobile station related types
  MSStates : enum {
    M_Start,                     -- state that MS is not in the group
    M_OpWait,                    -- waiting for response from BS
    M_Operational,               -- MS operating inside of a group
    M_RekeyInterWait
  };                             

  MobileStation : record
    state:        array [GSAID] of MSStates;
    inGroup:      array [GSAID] of boolean;
    lastSentNonce:  NonceID;
    curNonce:     array[GSAID] of NonceID;       -- nonce used in KeyReq messages
    curGkek:      array[GSAID] of GKEKey;
    curGkekParam: array[GSAID] of GKEKID;
    curGkekSeq:   array[GSAID] of SequenceNum;   -- current GKEK sequence number received
    curGkekLife:  array[GSAID] of KeyLifetime;   -- current GKEK lifetime received
    curGtek:      array[GSAID] of GTEKey;
    curGtekParam: array[GSAID] of GTEKParam;
    curGtekSeq:   array[GSAID] of SequenceNum;   -- current GTEK sequence number received
    curGtekLife:  array[GSAID] of KeyLifetime;   -- current GTEK lifetime received
    
    pn_uni:       array[GSAID] of PacketNumber_Uni;
    pn_mbs:       array[GSAID] of SequenceNum;
    
    sessions:     array[GSAID] of MSSessions;
  end;

  -- base station related types
  BSStates : enum {
    B_Operational,               -- normal state that no rekeying is going on
    B_GKEKRekey,                 -- rekey GKEK to each MS in the group
    B_GTEKRekey                  -- rekey TKEK to all MS in the group thru multicast
  };                             

  GroupMembers : array[MSID] of boolean;
  
  BaseStation : record
    state:            array[GSAID] of BSStates;
    groupMembership:  array[GSAID] of GroupMembers;
    gkekRekeyRecp:    array[GSAID] of multiset[NumMS] of MSID;  -- recipients of GKEK Rekey msg of a group 
    curGkek:          array[GSAID] of GKEKID;        -- current GKEKs versions
    curGkekLife:      array[GSAID] of KeyLifetime;   -- current GKEK lifetime
    curGtek:          array[GSAID] of GTEKID;        -- current GTEKs versions
    curGtekLife:      array[GSAID] of KeyLifetime;   -- current GTEK lifetime
    
    --keyReqSeq:        array[GSAID] of array[MSID] of SequenceNum;    
    pn_uni:           array[GSAID] of array[MSID] of PacketNumber_Uni;
    pn_mbs:           array[GSAID] of SequenceNum;
  end;
  
  -- Intruder knowledge
  Intruder : record
    gmacs_uni:  GMacKeyKnown_Uni;
    gmacs_mbs:  GMacKeyKnown_MBS;
    ak:         array[MSID] of boolean;
    kek:        array[MSID] of boolean;
    nonces:     array[MSID] of array[NonceID] of boolean;
    gkekKnown:  array[GSAID] of array[GKEKID] of boolean;
    gtekKnown:  array[GSAID] of array[GKEKID] of array[GTEKID] of boolean;

    messages: multiset[MaxKnowledge] of Message;   -- known messages
  end;

-- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
var                                         -- state variables for
  net: multiset[NetworkSize] of Message;    --  network
  ms: array[MSID] of MobileStation;     --  all mobile stations (includes the one intruder)
  bs: BaseStation;
  
  intruderId: MSID;        --  intruder's MSID
  intruderInGroup: GSAID;  --  the 1 group that intruder joins
  intd: Intruder;          --  intruder knowledge


--------------------------------------------------------------------------------
-- procedures and functions
--------------------------------------------------------------------------------

-- count the members of a group
function memberCount(mems: GroupMembers): MSCOUNT;
var
  cnt: MSCOUNT;
begin
  cnt := 0;
  for msid: MSID do
    if mems[msid] = true then
      cnt := cnt + 1;
    end;
  end;
  return cnt;
end;

function verifyGKEK(k1, k2: GKEK): boolean;
  return (k1.gid = k2.gid &
          k1.gkekVer = k2.gkekVer &
          k1.encKEK = k2.encKEK & 
          k1.param = k2.param &
          k1.life = k2.life
         );
end;

function verifyGTEK(k1, k2: GTEK): boolean;
  return (k1.gid = k2.gid &
          k1.gkekVer = k2.gkekVer &
          k1.gtekVer = k2.gtekVer &
          k1.encGKEK = k2.encGKEK & 
          k1.param.gkekVer = k2.param.gkekVer &
          k1.param.gtekVer = k2.param.gtekVer &
          k1.life = k2.life
         );
end;

function verifyKeyReqMac(msg: Message): boolean;
begin
  return (msg.gMacKey_Uni.gid = msg.gsaId &
          msg.gMacKey_Uni.msid = msg.cid &
          msg.gMacKey_Uni.ul = true &
          msg.cid = msg.mic.cid &
          msg.gsaId = msg.mic.gsaId &
          msg.nonce = msg.mic.nonce &
          msg.pn = msg.mic.pn
         );
end;

function verifyKeyRspMac(msg: Message): boolean;
begin
  return (msg.gMacKey_Uni.gid = msg.gsaId &
          msg.gMacKey_Uni.msid = msg.cid &
          msg.gMacKey_Uni.ul = false &
          msg.cid = msg.mic.cid &
          msg.gsaId = msg.mic.gsaId &
          msg.nonce = msg.mic.nonce &
          msg.pn = msg.mic.pn &
          verifyGKEK(msg.gkek, msg.mic.gkek) &
          verifyGTEK(msg.gtek, msg.mic.gtek)          
         );
end;

function verifyKeyUpdGKEKMac(msg: Message): boolean;
begin
  return (msg.gMacKey_Uni.gid = msg.gsaId &
          msg.gMacKey_Uni.msid = msg.cid &
          msg.gMacKey_Uni.ul = false &
          msg.cid = msg.mic.cid &
          msg.gsaId = msg.mic.gsaId &
          msg.seq = msg.mic.seq &
          msg.pn = msg.mic.pn &
          verifyGKEK(msg.gkek, msg.mic.gkek)
         );
end;

function verifyKeyUpdGTEKMac(msg: Message; gkek: GKEKID): boolean;
begin
  return (msg.gMacKey_MBS.gid = msg.gsaId &
          msg.gMacKey_MBS.gkek = gkek &
          msg.cid = msg.mic.cid &
          msg.gsaId = msg.mic.gsaId &
          msg.seq = msg.mic.seq &
          msg.pn = msg.mic.pn &
          verifyGTEK(msg.gtek, msg.mic.gtek)
         );
end;

function equalGKEK(k1, k2: GKEK): boolean;
begin
  return (k1.gid = k2.gid &
          k1.gkekVer = k2.gkekVer &
          k1.encKEK = k2.encKEK &
          k1.param = k2.param &
          k1.life = k2.life
         );
end;

function equalGTEK(k1, k2: GTEK): boolean;
begin
  return (k1.gid = k2.gid &
          k1.gkekVer = k2.gkekVer &
          k1.gtekVer = k2.gtekVer &
          k1.encGKEK = k2.encGKEK &
          k1.param.gkekVer = k2.param.gkekVer &
          k1.param.gtekVer = k2.param.gtekVer &
          k1.life = k2.life
         );
end;

function equalGMacKey_Uni(k1, k2: GMacKey_Uni): boolean;
begin
  return (k1.gid = k2.gid &
          k1.msid = k2.msid &
          k1.ul = k2.ul
         );
end;

function equalGMacKey_MBS(k1, k2: GMacKey_MBS): boolean;
begin
  return (k1.gid = k2.gid &
          k1.gkek = k2.gkek
         );
end;

function equalKeyReqMIC(m1, m2: MIC): boolean;
begin
  return (m1.mType = m2.mType &
          m1.cid = m2.cid &
          m1.gsaId = m2.gsaId &
          m1.pn = m2.pn &
          m1.nonce = m2.nonce
         );
end;

function equalKeyRspMIC(m1, m2: MIC): boolean;
begin
  return (m1.mType = m2.mType &
          m1.gsaId = m2.gsaId &
          m1.nonce = m2.nonce &
          m1.pn = m2.pn &
          equalGKEK(m1.gkek, m2.gkek) &
          equalGTEK(m1.gtek, m2.gtek)
         );
end;

function equalKeyUpdGKEKMIC(m1, m2: MIC): boolean;
begin
  return (m1.mType = m2.mType &
          m1.cid = m2.cid &
          m1.gsaId = m2.gsaId &
          m1.pn = m2.pn &
          equalGKEK(m1.gkek, m2.gkek) &
          m1.seq = m2.seq
         );
end;

function equalKeyUpdTKEKMIC(m1, m2: MIC): boolean;
begin
  return (m1.mType = m2.mType &
          m1.gsaId = m2.gsaId &
          m1.pn = m2.pn &
          equalGTEK(m1.gtek, m2.gtek) &
          m1.seq = m2.seq
         );
end;

function equalMessage(m1, m2: Message): boolean;
begin
  if !(m1.mType = m2.mType & m1.gsaId = m2.gsaId & m1.pn = m2.pn &
       (m1.mType = KeyUpdGTEK | (m1.cid = m2.cid)) ) then
    return false;
  end;
  
  switch m1.mType
    case KeyReq:
      return (m1.nonce = m2.nonce &
              equalGMacKey_Uni(m1.gMacKey_Uni, m2.gMacKey_Uni) &
              equalKeyReqMIC(m1.mic, m2.mic)
             );
    case KeyRsp:
      return (m1.nonce = m2.nonce &
              equalGKEK(m1.gkek, m2.gkek) &
              equalGTEK(m1.gtek, m2.gtek) &
              equalGMacKey_Uni(m1.gMacKey_Uni, m2.gMacKey_Uni) &
              equalKeyRspMIC(m1.mic, m2.mic)
             );
    case KeyUpdGKEK:
      return (m1.seq = m2.seq &
              equalGKEK(m1.gkek, m2.gkek) &
              equalGMacKey_Uni(m1.gMacKey_Uni, m2.gMacKey_Uni) &
              equalKeyUpdGKEKMIC(m1.mic, m2.mic)
             );
    case KeyUpdGTEK:
      return (m1.seq = m2.seq &
              equalGTEK(m1.gtek, m2.gtek) &
              equalGMacKey_MBS(m1.gMacKey_MBS, m2.gMacKey_MBS) &
              equalKeyUpdTKEKMIC(m1.mic, m2.mic)
             );
  end;
  return false;
end;

procedure intruderLearns(msg: Message);
begin

  switch msg.mType
    case KeyReq:
      intd.nonces[msg.cid][msg.nonce] := true;
    case KeyRsp:
      intd.nonces[msg.cid][msg.nonce] := true;
      if intd.kek[msg.cid] then
        intd.gkekKnown[msg.gsaId][msg.gkek.gkekVer] := true;
      end;
      if intd.gkekKnown[msg.gsaId][msg.gtek.gkekVer] then
        intd.gtekKnown[msg.gsaId][msg.gtek.gkekVer][msg.gtek.gtekVer] := true;
      end;
    case KeyUpdGKEK:
      if intd.kek[msg.cid] then
        intd.gkekKnown[msg.gsaId][msg.gkek.gkekVer] := true;
      end;
    case KeyUpdGTEK:
      if intd.gkekKnown[msg.gsaId][msg.gtek.gkekVer] then
        intd.gtekKnown[msg.gsaId][msg.gtek.gkekVer][msg.gtek.gtekVer] := true;
      end;
  end;
end;

--------------------------------------------------------------------------------
-- rules
--------------------------------------------------------------------------------


--------------------------------------------------------------------------------
-- behavior of mobile stations
--------------------------------------------------------------------------------

-- mobile station starts protocol by sending key request msg to base station
ruleset msid: MSID do
  ruleset gid: GSAID do
    rule 20 "ms starts protocol"

      ms[msid].state[gid] = M_Start &
      ms[msid].sessions[gid] < MaxSessionsPerMSPerGroup &
      ( INTRUDER_PARTICIPATES | msid != intruderId ) &
      ( !INTRUDER_PARTICIPATES | (msid != intruderId | isundefined(intruderInGroup)) ) &
      multisetcount (l:net, true) < NetworkSize

    ==>
    
    var
      outM: Message;   -- outgoing message
      gmacKey: GMacKey_Uni;
      mic: MIC;

    begin
      undefine outM;
      outM.fromIntruder := false;
      outM.cid     := msid;
      outM.mType   := KeyReq;
      outM.gsaId   := gid;
      outM.nonce   := ms[msid].curNonce[gid];
      outM.pn      := ms[msid].pn_uni[gid].ul;
      
      undefine gmacKey;
      gmacKey.gid := gid;
      gmacKey.msid := msid;
      gmacKey.ul := true;
      outM.gMacKey_Uni := gmacKey;
      
      undefine mic;
      mic.cid   := msid;
      mic.mType := KeyReq;
      mic.gsaId := gid;
      mic.nonce := ms[msid].curNonce[gid];
      mic.pn    := outM.pn;
      outM.mic  := mic;

      multisetadd (outM,net);

      ms[msid].state[gid]     := M_OpWait;
      ms[msid].lastSentNonce  := ms[msid].curNonce[gid];
      ms[msid].curNonce[gid]  := ms[msid].curNonce[gid] + 1;
      
      ms[msid].pn_uni[gid].ul := outM.pn + 1;
      
      if msid = intruderId then
        intruderInGroup := gid;
      end;
    end;
  end;
end;

-- mobile station receives KeyRsp message
ruleset msid: MSID do
  ruleset gid: GSAID do
    choose i: net do
      rule 21 "ms receives KeyRsp"
        net[i].fromIntruder &
        net[i].mType = KeyRsp &
        net[i].cid = msid
        
      ==>
      
      var
        inM:     Message;
        gkekey:  GKEKey;
        gtekey:  GTEKey;
        
      begin
        inM := net[i];
        multisetremove(i, net);
        
        if ms[msid].state[gid] = M_OpWait &
           inM.pn > ms[msid].pn_uni[inM.gsaId].dl then
          
          ms[msid].pn_uni[inM.gsaId].dl := inM.pn;
          
          if (verifyKeyRspMac(inM) & 
              inM.nonce = ms[msid].lastSentNonce) then
         
            if (ms[msid].curGkekLife[gid] < inM.gkek.life) then
              if CHK_GKEY_LIFE then
                error "GKEK lifetime got extended!!!"
              end;
            end;
            if (ms[msid].curGtekLife[gid] < inM.gtek.life) then
              if CHK_GTEY_LIFE then
                error "GTEK lifetime got extended!!!"
              end;
            end;
         
            undefine gkekey;
            gkekey.gid := inM.gkek.gid;
            gkekey.gkekVer := inM.gkek.gkekVer;
            ms[msid].curGkek[gid] := gkekey;
            ms[msid].curGkekParam[gid] := inM.gkek.param;
            ms[msid].curGkekSeq[gid] := inM.gkek.gkekVer;
            ms[msid].curGkekLife[gid] := inM.gkek.life;
         
            undefine gtekey;
            gtekey.gid := inM.gtek.gid;
            gtekey.gkekVer := inM.gtek.gkekVer;
            gtekey.gtekVer := inM.gtek.gtekVer;
            ms[msid].curGtek[gid] := gtekey;
            ms[msid].curGtekParam[gid] := inM.gtek.param;
            ms[msid].curGtekSeq[gid] := inM.gtek.gtekVer;
            ms[msid].curGtekLife[gid] := inM.gtek.life;
         
            ms[msid].inGroup[gid] := true;
            ms[msid].state[gid] := M_Operational;
            undefine ms[msid].lastSentNonce;
          end;
        end;
             
      end;
    end;
  end;
end;

-- mobile station receives GKEK KeyUpd message
ruleset msid: MSID do
  ruleset gid: GSAID do
    choose i: net do
      rule "ms receives GKEK KeyUpd"
        net[i].fromIntruder &
        net[i].mType = KeyUpdGKEK &
        net[i].cid = msid
        
      ==>
      
      var
        inM:     Message;
        gkekey:  GKEKey;
        
      begin
        inM := net[i];
        multisetremove(i, net);
        
        if ms[msid].state[gid] = M_Operational &
           inM.pn > ms[msid].pn_uni[inM.gsaId].dl then
          
          ms[msid].pn_uni[inM.gsaId].dl := inM.pn;
          
          if (verifyKeyUpdGKEKMac(inM)) then
            if (ms[msid].curGkekLife[gid] < inM.gkek.life) then
              if CHK_GKEY_LIFE then
                error "GKEK lifetime got extended!!!"
              end;
            end;
          
            undefine gkekey;
            gkekey.gid := inM.gkek.gid;
            gkekey.gkekVer := inM.gkek.gkekVer;
            ms[msid].curGkek[gid] := gkekey;
            ms[msid].curGkekParam[gid] := inM.gkek.param;
            ms[msid].curGkekSeq[gid] := inM.gkek.gkekVer;
            ms[msid].curGkekLife[gid] := inM.gkek.life;
          
            ms[msid].state[gid] := M_RekeyInterWait;
          end;
        end;
        
      end;
    endchoose;
  end;
end;

-- mobile station receives GTEK KeyUpd broadcast message
ruleset msid: MSID do
  ruleset gid: GSAID do
    choose i: net do
      rule "ms receives GTEK KeyUpd broadcast message"
        net[i].fromIntruder &
        net[i].mType = KeyUpdGTEK &
        multisetcount(j:net[i].multiReceivers, net[i].multiReceivers[j] = msid) > 0
        
      ==>
      
      var
        inM:     Message;
        gtekey:  GTEKey;
      
      begin
        inM := net[i];
        if ms[msid].state[gid] = M_RekeyInterWait &
           inM.pn > ms[msid].pn_mbs[inM.gsaId] then
          
          ms[msid].pn_mbs[inM.gsaId] := inM.pn;
         
          if (verifyKeyUpdGTEKMac(inM, ms[msid].curGkek[gid].gkekVer)) then
            if (ms[msid].curGtekLife[gid] < inM.gtek.life) then
              if CHK_GTEY_LIFE then
                error "GTEK lifetime got extended!!!"
              end;
            end;
          
            undefine gtekey;
            gtekey.gid := inM.gtek.gid;
            gtekey.gkekVer := inM.gtek.gkekVer;
            gtekey.gtekVer := inM.gtek.gtekVer;
            ms[msid].curGtek[gid] := gtekey;
            ms[msid].curGtekParam[gid] := inM.gtek.param;
            ms[msid].curGtekSeq[gid] := inM.gtek.gtekVer;
            ms[msid].curGtekLife[gid] := inM.gtek.life;
          
            ms[msid].state[gid] := M_Operational;
          end;
	  	end;
	  	
        multisetremovepred(j:net[i].multiReceivers, net[i].multiReceivers[j] = msid);
        if multisetcount(j:net[i].multiReceivers, true) = 0 then
	  	  multisetremove(i, net);
	  	end;
	  	
      end;
      
    endchoose;
  end;
end;

-- mobile station leaves a group. this happens only when both bs & ms are in Operational state
ruleset msid: MSID do
  ruleset gid: GSAID do
    rule "ms leaves a group"
      msid != intruderId &  -- intruder can join 1 group max and won't leave the group
      ms[msid].state[gid] = M_Operational &
      bs.state[gid] = B_Operational
      
    ==>
    
    begin
      ms[msid].state[gid] := M_Start;
      ms[msid].inGroup[gid] := false;
      ms[msid].sessions[gid] := ms[msid].sessions[gid] + 1;
      
      bs.state[gid] := B_GKEKRekey;  -- bs should be in rekey mode immediately
      bs.groupMembership[gid][msid] := false;
    end;
  end;
end;

--------------------------------------------------------------------------------
-- behavior of base station
--------------------------------------------------------------------------------

-- base station receives KeyReq message and sends KeyRsp message
choose i: net do
  rule 30 "bs receives KeyReq and sends KeyRsp message"
    net[i].fromIntruder &
    net[i].mType = KeyReq
    
  ==>
  
  var
    outM:  Message;
    inM:   Message;
    gkek:  GKEK;
    gtek:  GTEK;
    gtekp: GTEKParam;
    gmack: GMacKey_Uni;
    mic:   MIC;
    
  begin
    inM := net[i];
    multisetremove(i, net);
    if (verifyKeyReqMac(inM) &
        inM.pn > bs.pn_uni[inM.gsaId][inM.cid].ul
       ) then
       
      --first, update packet number counter
      bs.pn_uni[inM.gsaId][inM.cid].ul := inM.pn;
       
      undefine outM;
      outM.fromIntruder := false;
      outM.cid := inM.cid;
      outM.mType := KeyRsp;
      outM.gsaId := inM.gsaId;
      outM.nonce := inM.nonce;
      outM.pn    := bs.pn_uni[inM.gsaId][inM.cid].dl;
      
      undefine gkek;
      gkek.gid := inM.gsaId;
      gkek.gkekVer := bs.curGkek[inM.gsaId];
      gkek.encKEK := inM.cid;
      gkek.param := bs.curGkek[inM.gsaId];
      gkek.life := bs.curGkekLife[inM.gsaId];
      outM.gkek := gkek;
      bs.curGkekLife[inM.gsaId] := bs.curGkekLife[inM.gsaId] - 1;
      
      undefine gtek;
      gtek.gid := inM.gsaId;
      gtek.gkekVer := bs.curGkek[inM.gsaId];
      gtek.gtekVer := bs.curGtek[inM.gsaId];
      gtek.encGKEK := bs.curGkek[inM.gsaId];
      undefine gtekp;
      gtekp.gkekVer := bs.curGkek[inM.gsaId];
      gtekp.gtekVer := bs.curGtek[inM.gsaId];
      gtek.param := gtekp;
      gtek.life := bs.curGtekLife[inM.gsaId];
      outM.gtek := gtek;
      bs.curGtekLife[inM.gsaId] := bs.curGtekLife[inM.gsaId] - 1;
      
      undefine gmack;
      gmack.gid := inM.gsaId;
      gmack.msid := inM.cid;
      gmack.ul := false;
      outM.gMacKey_Uni := gmack;
      
      undefine mic;
      mic.cid := outM.cid;
      mic.mType := outM.mType;
      mic.gsaId := outM.gsaId;
      mic.nonce := outM.nonce;
      mic.gkek  := outM.gkek;
      mic.gtek  := outM.gtek;
      mic.pn    := outM.pn;
      outM.mic  := mic;
      
      multisetadd(outM, net);
      
      bs.groupMembership[outM.gsaId][outM.cid] := true;  -- BS authenticates MS into the group
      bs.pn_uni[outM.gsaId][outM.cid].dl := outM.pn + 1;
    end;
  end;
end; 

-- base station spontaneously enters GKEK rekey mode
ruleset gid: GSAID do
  rule "bs enters GKEK rekey mode"
  
    bs.state[gid] = B_Operational &
    memberCount(bs.groupMembership[gid]) > 0  -- an optimization. only rekey when the group is not empty
    
  ==>
  
  begin
    bs.state[gid] := B_GKEKRekey;
    for i:MSID do
      if bs.groupMembership[gid][i] then
        multisetadd(i, bs.gkekRekeyRecp[gid]); -- specify recipients
      end;
    end;
  end;
end;

-- base station sends out GKEK Update msg to each MS in the group
ruleset gid: GSAID do
  ruleset msid: MSID do
    rule "bs sends out GKEK Update messages"
  
      bs.state[gid] = B_GKEKRekey &
      multisetcount(j:bs.gkekRekeyRecp[gid], bs.gkekRekeyRecp[gid][j] = msid) > 0 &
      multisetcount (l:net, true) < NetworkSize
    
    ==>
  
    var
    
      outM:     Message;
      gkek:     GKEK;
      gmacKey:  GMacKey_Uni;
      mic:      MIC;
      
    begin
      undefine outM;
      outM.fromIntruder := false;
      outM.cid := msid;
      outM.mType := KeyUpdGKEK;
      outM.gsaId := gid;
      outM.pn := bs.pn_uni[gid][msid].dl;
      
      undefine gkek;
      gkek.gid := gid;
      gkek.gkekVer := bs.curGkek[gid];
      gkek.encKEK := msid;
      gkek.param := bs.curGkek[gid];
      gkek.life := bs.curGkekLife[gid];
      outM.gkek := gkek;
      
      outM.seq := gkek.gkekVer;
      
      undefine gmacKey;
      gmacKey.gid := gid;
      gmacKey.msid := msid;
      gmacKey.ul := false;
      outM.gMacKey_Uni := gmacKey;
      
      undefine mic;
      mic.cid := msid;
      mic.mType := KeyUpdGKEK;
      mic.gsaId := gid;
      mic.gkek := outM.gkek;
      mic.seq := outM.seq;
      mic.pn := outM.pn;
      outM.mic := mic;
      
      multisetadd(outM, net);
      
      bs.pn_uni[gid][msid].dl := outM.pn + 1;
      bs.curGkekLife[gid] := bs.curGkekLife[gid] - 1;
    end;
  end;
end;

-- base station enters GTEK rekey mode
ruleset gid: GSAID do
  rule "bs enters GTEK rekey mode"
  
    bs.state[gid] = B_GKEKRekey &
    multisetcount(j:bs.gkekRekeyRecp[gid], true) = 0
    
  ==>
  
  begin
    bs.state[gid] := B_GTEKRekey;
  end;
end;

-- base station broadcasts GTEK Update msg to the group
ruleset gid: GSAID do
  rule "bs broadcasts GTEK Update message"
  
    bs.state[gid] = B_GTEKRekey & 
    multisetcount (l:net, true) < NetworkSize
    
  ==>

  var
    
    outM:     Message;
    gtek:     GTEK;
    gmacKey:  GMacKey_MBS;
    gtekp:    GTEKParam;
    mic:      MIC;
      
  begin
    undefine outM;
    outM.fromIntruder := false;
    for i:MSID do
      if bs.groupMembership[gid][i] then
        multisetadd(i, outM.multiReceivers);
      end;
    end;
    outM.mType := KeyUpdGTEK;
    outM.gsaId := gid;
    outM.pn := bs.pn_mbs[gid];
      
    undefine gtek;
    gtek.gid := gid;
    gtek.gkekVer := bs.curGkek[gid];
    gtek.gtekVer := bs.curGtek[gid];
    gtek.encGKEK := bs.curGkek[gid];
    undefine gtekp;
    gtekp.gkekVer := bs.curGkek[gid];
    gtekp.gtekVer := bs.curGtek[gid];
    gtek.param := gtekp;
    gtek.life := bs.curGtekLife[gid];
    outM.gtek := gtek;
      
    outM.seq := gtek.gtekVer;
      
    undefine gmacKey;
    gmacKey.gid := gid;
    gmacKey.gkek := bs.curGkek[gid];
    outM.gMacKey_MBS := gmacKey;
      
    undefine mic;
    mic.mType := outM.mType;
    mic.gsaId := outM.gsaId;
    mic.seq := outM.seq;
    mic.gtek := outM.gtek;
    mic.pn := outM.pn;
    outM.mic := mic;
      
    multisetadd(outM, net);
      
    bs.state[gid] := B_Operational;
    bs.pn_mbs[gid] := outM.pn + 1;
    bs.curGtekLife[gid] := bs.curGtekLife[gid] - 1;
  end;
end;

--------------------------------------------------------------------------------
-- behavior of intruder
--------------------------------------------------------------------------------

-- intruder intercepts a message
choose i: net do
  rule "Intruder intercepts a message"

    !(net[i].fromIntruder) &
    net[i].cid != intruderId
    
  ==>

  var
    inM: Message;
    
  begin
    inM := net[i];
    intruderLearns(inM);
    
    -- store the whole message for replay
    if multisetcount(j:intd.messages, equalMessage(inM, intd.messages[j])) = 0 then

      inM.fromIntruder := true;
      multisetadd(inM, intd.messages);
    end;

    multisetremove (i, net);
  end;
endchoose;

-- intruder sends recorded unicast message
choose i: intd.messages do   --  recorded message
  ruleset msid: MSID do        --  destination
    rule "intruder sends recorded unicast message"

      msid != intruderId &                 -- not to intruder
      intd.messages[i].mType != KeyUpdGTEK &
      multisetcount (l:net, true) < NetworkSize

    ==>

    var
      outM: Message;

    begin
      outM := intd.messages[i];
      outM.fromIntruder := true;
	  outM.cid := msid;
      
      multisetadd(outM, net);
    end;
  end;
end;

-- intruder sends recorded broadcast message
choose i: intd.messages do   --  recorded message
  rule "intruder sends recorded broadcast message"

    intd.messages[i].mType = KeyUpdGTEK &
    multisetcount (l:net, true) < NetworkSize

  ==>

  var
    outM: Message;

  begin
    outM := intd.messages[i];
    outM.fromIntruder := true;
    for j:MSID do
      if bs.groupMembership[outM.gsaId][j] then
        multisetadd(j, outM.multiReceivers);
      end;
    end;
    
    multisetadd(outM, net);
  end;
end;
        
-- intruder generates a KeyReq message
ruleset msid: MSID do
  ruleset gid: GSAID do
    ruleset nn: NonceID do
      rule "intruder generates a KeyReq message"
        intd.nonces[msid][nn] &
        intd.ak[msid] &
        multisetcount (l:net, true) < NetworkSize &
        msid != intruderId
      
      ==>
    
      var
        outM:    Message;
        gmacKey: GMacKey_Uni;
        mic: MIC;
        
      begin
        undefine outM;
        outM.fromIntruder    := true;
        outM.cid     := msid;
        outM.mType   := KeyReq;
        outM.gsaId   := gid;
        outM.nonce   := nn;
        outM.pn      := ms[msid].pn_uni[gid].ul;  -- assume intd already know because he's been observing all traffic
      
        -- if AK is known, then gmac key is known
        undefine gmacKey;
        gmacKey.gid := gid;
        gmacKey.msid := msid;
        gmacKey.ul := true;
        outM.gMacKey_Uni := gmacKey;
      
        undefine mic;
        mic.cid   := msid;
        mic.mType := KeyReq;
        mic.gsaId := gid;
        mic.nonce := nn;
        mic.pn    := outM.pn;
        outM.mic  := mic;

        multisetadd (outM,net);
      end;
    end;
  end;
end;
        
-- intruder generates a KeyRsp message
ruleset msid: MSID do
  ruleset gid: GSAID do
    ruleset nn: NonceID do
      rule "intruder generates a KeyReq message"
        intd.nonces[msid][nn] &
        intd.ak[msid] &
        multisetcount (l:net, true) < NetworkSize &
        msid != intruderId
      
      ==>
    
      var
        outM:    Message;
        gkek:  GKEK;
        gtek:  GTEK;
        gtekp: GTEKParam;
        gmack: GMacKey_Uni;
        mic:   MIC;
        
      begin
        undefine outM;
        outM.fromIntruder    := true;
        outM.cid     := msid;
        outM.mType   := KeyRsp;
        outM.gsaId   := gid;
        outM.nonce   := nn;
        outM.pn      := bs.pn_uni[gid][msid].dl;  -- assume intd already know because he's been observing all traffic
       
        undefine gkek;
        gkek.gid := gid;
        gkek.gkekVer := InvalidGKEK;
        gkek.encKEK := msid;  -- MS would decrypt using his KEK and get garbage key value
        gkek.param := InvalidGKEK;
        gkek.life := InvalidKeyLifetime;
        outM.gkek := gkek;
      
        undefine gtek;
        gtek.gid := gid;
        gtek.gkekVer := InvalidGKEK;
        gtek.gtekVer := InvalidGTEK;
        gtek.encGKEK := ms[msid].curGkek[gid].gkekVer;  -- MS would decrypt using his GKEK and get garbage key value
        undefine gtekp;
        gtekp.gkekVer := InvalidGKEK;
        gtekp.gtekVer := InvalidGTEK;
        gtek.param := gtekp;
        gtek.life := InvalidKeyLifetime;
        outM.gtek := gtek;
      
        -- if AK is known, then gmac key is known
        undefine gmack;
        gmack.gid := gid;
        gmack.msid := msid;
        gmack.ul := false;
        outM.gMacKey_Uni := gmack;
      
        undefine mic;
        mic.cid := outM.cid;
        mic.mType := outM.mType;
        mic.gsaId := outM.gsaId;
        mic.nonce := outM.nonce;
        mic.gkek  := outM.gkek;
        mic.gtek  := outM.gtek;
        mic.pn    := outM.pn;
        outM.mic  := mic;

        multisetadd (outM,net);
      end;
    end;
  end;
end;
        
-- intruder generates a KeyUpdGKEK message
ruleset msid: MSID do
  ruleset gid: GSAID do
    rule "intruder generates a KeyUpdGKEK message"
      intd.ak[msid] &
      multisetcount (l:net, true) < NetworkSize &
      msid != intruderId
      
    ==>
    
    var
      outM:    Message;
      gkek:  GKEK;
      gmack: GMacKey_Uni;
      mic:   MIC;
        
    begin
      undefine outM;
      outM.fromIntruder    := true;
      outM.cid     := msid;
      outM.mType   := KeyUpdGKEK;
      outM.gsaId   := gid;
      outM.pn      := bs.pn_uni[gid][msid].dl;  -- assume intd already know because he's been observing all traffic
       
      undefine gkek;
      gkek.gid := gid;
      gkek.gkekVer := InvalidGKEK;
      gkek.encKEK := msid;  -- MS would decrypt using his KEK and get garbage key value
      gkek.param := InvalidGKEK;
      gkek.life := InvalidKeyLifetime;
      outM.gkek := gkek;

      outM.seq := gkek.gkekVer;
            
      -- if AK is known, then gmac key is known
      undefine gmack;
      gmack.gid := gid;
      gmack.msid := msid;
      gmack.ul := false;
      outM.gMacKey_Uni := gmack;
      
      undefine mic;
      mic.cid := outM.cid;
      mic.mType := outM.mType;
      mic.gsaId := outM.gsaId;
      mic.gkek  := outM.gkek;
      mic.seq   := outM.seq;
      mic.pn    := outM.pn;
      outM.mic  := mic;

      multisetadd (outM, net);
    end;
  end;
end;
        
-- intruder generates a KeyUpdGTEK message
ruleset msid: MSID do
  ruleset gid: GSAID do
    ruleset gkekVer: GKEKID do
      rule "intruder generates a KeyUpdGTEK message"
        intd.gkekKnown[gid][gkekVer] &
        multisetcount (l:net, true) < NetworkSize &
        msid != intruderId
      
      ==>
    
      var
        outM:    Message;
        gtek:  GTEK;
        gtekp: GTEKParam;
        gmack: GMacKey_MBS;
        mic:   MIC;
        
      begin
        undefine outM;
        outM.fromIntruder    := true;
        -- intruder knows all members of a group because he observed all traffic
        for i:MSID do
          if bs.groupMembership[gid][i] then
            multisetadd(i, outM.multiReceivers);
          end;
        end;
        outM.mType   := KeyUpdGTEK;
        outM.gsaId   := gid;
        outM.pn      := bs.pn_mbs[gid];  -- assume intd already know because he's been observing all traffic
            
        undefine gtek;
        gtek.gid := gid;
        gtek.gkekVer := InvalidGKEK;
        gtek.gtekVer := InvalidGTEK;
        gtek.encGKEK := gkekVer;
        undefine gtekp;
        gtekp.gkekVer := InvalidGKEK;
        gtekp.gtekVer := InvalidGTEK;
        gtek.param := gtekp;
        gtek.life := InvalidKeyLifetime;
        outM.gtek := gtek;
      
        outM.seq := gtek.gtekVer;
        
        undefine gmack;
        gmack.gid := gid;
        gmack.gkek := gkekVer;
        outM.gMacKey_MBS := gmack;
      
        undefine mic;
        mic.mType := outM.mType;
        mic.gsaId := outM.gsaId;
        mic.seq   := outM.seq;
        mic.gtek  := outM.gtek;
        mic.pn    := outM.pn;
        outM.mic  := mic;

        multisetadd (outM,net);
      end;
    end;
  end;
end;


--------------------------------------------------------------------------------
-- startstate
--------------------------------------------------------------------------------

startstate
  -- initialize mobile stations
  undefine ms;
  for msid: MSID do
    for gid: GSAID do
		ms[msid].state[gid]       := M_Start;
		ms[msid].inGroup[gid]     := false;
        ms[msid].curNonce[gid]    := 1;
        ms[msid].curGkekSeq[gid]  := 0;
        ms[msid].curGkekLife[gid] := MaxKeyLifetime;
        ms[msid].curGtekSeq[gid]  := 0;
        ms[msid].curGtekLife[gid] := MaxKeyLifetime;
	
	    ms[msid].pn_uni[gid].ul   := 1;
	    ms[msid].pn_uni[gid].dl   := 0;
	    ms[msid].pn_mbs[gid]      := 0;
	    
	    ms[msid].sessions[gid]    := 0;
	end;
  end;
  
  -- initialize base station
  undefine bs;
  for gid: GSAID do
    bs.state[gid] := B_Operational;
    bs.curGkek[gid] := 1;
    bs.curGkekLife[gid] := MaxKeyLifetime;
    bs.curGtek[gid] := 1;
    bs.curGtekLife[gid] := MaxKeyLifetime;
    for msid: MSID do
      bs.groupMembership[gid][msid] := false;
      
	  bs.pn_uni[gid][msid].ul   := 0;
	  bs.pn_uni[gid][msid].dl   := 1;
    end;
	bs.pn_mbs[gid]              := 1;
  end;

  -- select 1 mobile station to be the intruder and initialize intruder
  undefine intruderId;
  undefine intruderInGroup;
  undefine intd;
  for i: MSID do
    if isundefined(intruderId) then
      intruderId := i
    end;

  end;
  
  for gid: GSAID do   -- 
    for msid: MSID do  
      intd.gmacs_uni[gid][msid][true] := false;
      intd.gmacs_uni[gid][msid][false] := false;
    end;
    for gkekid: GKEKID do
      intd.gmacs_mbs[gid][gkekid] := false;
      intd.gkekKnown[gid][gkekid] := false;
      for gtekid: GTEKID do 
        intd.gtekKnown[gid][gkekid][gtekid] := false;
      end;
    end;
  end;
  
  for msid: MSID do  
    intd.kek[msid] := false;
    intd.ak[msid]  := false;
    for nid: NonceID do
      intd.nonces[msid][nid] := false;
    end;
  end;
  intd.kek[intruderId] := true;
  intd.ak[intruderId]  := true;

  -- initialize network 
  undefine net;
  
end;



--------------------------------------------------------------------------------
-- invariants
--------------------------------------------------------------------------------

invariant "group membership consistency"
  forall gid: GSAID do
    forall msid: MSID do
      CHK_MEMBERSHIP &
      (
      ms[msid].state[gid] = M_Operational |
      ms[msid].state[gid] = M_Start |
      ms[msid].state[gid] = M_RekeyInterWait
      )
      ->
      bs.groupMembership[gid][msid] = ms[msid].inGroup[gid]
    end
  end;

invariant "pairwise ak secrecy"
  forall msid: MSID do
    msid != intruderId
    ->
    intd.ak[msid] = false
  end;

invariant "pairwise kek secrecy"
  forall msid: MSID do
    msid != intruderId
    ->
    intd.kek[msid] = false
  end;

invariant "unicast group mac key secrecy"
  forall gid: GSAID do
    forall msid: MSID do
      gid != intruderInGroup &
      msid != intruderId
      ->
      intd.gmacs_uni[gid][msid][true] = false &
      intd.gmacs_uni[gid][msid][false] = false
    end
  end;

invariant "multicast/broadcast group mac key secrecy"
  forall gid: GSAID do
    forall gkekid: GKEKID do
      gid != intruderInGroup
      ->
      intd.gmacs_mbs[gid][gkekid] = false
    end
  end;

invariant "GKEK and GTEK key freshness"
  forall gid: GSAID do
    forall msid: MSID do
      CHK_KEY_FRESHNESS &
      ms[msid].state[gid] = M_Operational &
      bs.state[gid] = B_Operational
      ->
      ms[msid].curGkek[gid].gid = gid &
      ms[msid].curGkek[gid].gkekVer = bs.curGkek[gid] &
      ms[msid].curGtek[gid].gid = gid &
      ms[msid].curGtek[gid].gkekVer = bs.curGkek[gid] &
      ms[msid].curGtek[gid].gtekVer = bs.curGtek[gid]
    end
  end;

invariant "GKEK and GTEK key paramters integrity"
  forall gid: GSAID do
    forall msid: MSID do
      CHK_KEY_FRESHNESS &
      ms[msid].state[gid] = M_Operational &
      bs.state[gid] = B_Operational
      ->
      ms[msid].curGkek[gid].gid = gid &
      ms[msid].curGkek[gid].gkekVer = bs.curGkek[gid] &
      ms[msid].curGtek[gid].gid = gid &
      ms[msid].curGtek[gid].gkekVer = bs.curGkek[gid] &
      ms[msid].curGtek[gid].gtekVer = bs.curGtek[gid]
    end
  end;
  
invariant "cross group gkek secrecy"
  forall gid: GSAID do
    forall gkekid: GKEKID do
      !isundefined(intruderInGroup) &
      gid != intruderInGroup
      ->
      intd.gkekKnown[gid][gkekid] = false
    end
  end;
  
invariant "cross group gtek secrecy"
  forall gid: GSAID do
    forall gkekid: GKEKID do
      forall gtekid: GTEKID do
        !isundefined(intruderInGroup) &
        gid != intruderInGroup
        ->
        intd.gtekKnown[gid][gkekid][gtekid] = false
      end
    end
  end;
