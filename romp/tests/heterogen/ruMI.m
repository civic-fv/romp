/*
  Copyright (c) 2021.  Nicolai Oswald
  Copyright (c) 2021.  University of Edinburgh
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met: redistributions of source code must retain the above copyright
  notice, this list of conditions and the following disclaimer;
  redistributions in binary form must reproduce the above copyright
  notice, this list of conditions and the following disclaimer in the
  documentation and/or other materials provided with the distribution;
  neither the name of the copyright holders nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
--RevMurphi/MurphiModular/Constants/GenConst
  ---- System access constants
  const
    ENABLE_QS: false;
    VAL_COUNT: 1;
    ADR_COUNT: 1;
  
  ---- System network constants
    O_NET_MAX: 12;
    U_NET_MAX: 12;
  
  ---- SSP declaration constants
    NrCachesL1C1: 4;
  
--RevMurphi/MurphiModular/GenTypes
  type
    ----RevMurphi/MurphiModular/Types/GenAdrDef
    Address: scalarset(ADR_COUNT);
    ClValue: 0..VAL_COUNT;
    
    ----RevMurphi/MurphiModular/Types/Enums/GenEnums
      ------RevMurphi/MurphiModular/Types/Enums/SubEnums/GenAccess
      PermissionType: enum {
        load, 
        store, 
        evict, 
        none
      };
      
      ------RevMurphi/MurphiModular/Types/Enums/SubEnums/GenMessageTypes
      MessageType: enum {
        GetML1C1, 
        GetM_Ack_DL1C1, 
        PutML1C1, 
        Fwd_GetML1C1, 
        Put_AckL1C1
      };
      
      ------RevMurphi/MurphiModular/Types/Enums/SubEnums/GenArchEnums
      s_cacheL1C1: enum {
        cacheL1C1_M_evict_x_I,
        cacheL1C1_M_evict,
        cacheL1C1_M,
        cacheL1C1_I_store,
        cacheL1C1_I_load,
        cacheL1C1_I
      };
      
      s_directoryL1C1: enum {
        directoryL1C1_M,
        directoryL1C1_I
      };
      
    ----RevMurphi/MurphiModular/Types/GenMachineSets
      -- Cluster: C1
      OBJSET_cacheL1C1: scalarset(NrCachesL1C1);
      OBJSET_directoryL1C1: enum{directoryL1C1};
      
      Machines: scalarset(NrCachesL1C1+1);
      
      ------RevMurphi/MurphiModular/Types/CheckTypes/GenStoreMonitorType
        GlobalStoreMonitor: array[Address] of ClValue;
      
    
    ----RevMurphi/MurphiModular/Types/GenMessage
      Message: record
        adr: Address;
        mtype: MessageType;
        src: Machines;
        dst: Machines;
        cl: ClValue;
      end;
      
    ----RevMurphi/MurphiModular/Types/GenNetwork
      NET_Ordered: array[Machines] of array[0..O_NET_MAX-1] of Message;
      NET_Ordered_cnt: array[Machines] of 0..O_NET_MAX;
    
    ----RevMurphi/MurphiModular/Types/GenMachines
      
      ENTRY_cacheL1C1: record
        State: s_cacheL1C1;
        cl: ClValue;
      end;
      
      MACH_cacheL1C1: record
        cb: array[Address] of ENTRY_cacheL1C1;
      end;
      
      OBJ_cacheL1C1: array[OBJSET_cacheL1C1] of MACH_cacheL1C1;
      OBJ_NET_cacheL1C1: array[OBJSET_cacheL1C1] of Machines;
      
      ENTRY_directoryL1C1: record
        State: s_directoryL1C1;
        cl: ClValue;
        ownerL1C1: Machines;
      end;
      
      MACH_directoryL1C1: record
        cb: array[Address] of ENTRY_directoryL1C1;
      end;
      
      OBJ_directoryL1C1: array[OBJSET_directoryL1C1] of MACH_directoryL1C1;
      OBJ_NET_directoryL1C1: array[OBJSET_directoryL1C1] of Machines;

  var
    --RevMurphi/MurphiModular/GenVars
      fwd: NET_Ordered;
      cnt_fwd: NET_Ordered_cnt;
      resp: NET_Ordered;
      cnt_resp: NET_Ordered_cnt;
      req: NET_Ordered;
      cnt_req: NET_Ordered_cnt;
  
      g_monitor_store: GlobalStoreMonitor;

      i_cacheL1C1: OBJ_cacheL1C1;
      i_net_cacheL1C1: OBJ_NET_cacheL1C1;
      
      i_directoryL1C1: OBJ_directoryL1C1;
      i_net_directoryL1C1: OBJ_NET_directoryL1C1;
  

--RevMurphi/MurphiModular/GenFunctions

  ----RevMurphi/MurphiModular/Functions/GenResetFunc
    procedure ResetMachine_();
    var net_mach_map: array[0..7] of Machines;
    var net_mach_ind: 0..7;
    begin

      net_mach_ind := 0;
      for m: Machines do
        net_mach_map[net_mach_ind] := m;
        net_mach_ind := net_mach_ind +1;
      endfor;

      net_mach_ind := 0;
      for i:OBJSET_cacheL1C1 do
        i_net_cacheL1C1[i] := net_mach_map[net_mach_ind];
        net_mach_ind := net_mach_ind +1;

        for a:Address do
          i_cacheL1C1[i].cb[a].State := cacheL1C1_I;
          i_cacheL1C1[i].cb[a].cl := 0;
        endfor;
      endfor;

      for i:OBJSET_directoryL1C1 do
        i_net_directoryL1C1[i] := net_mach_map[net_mach_ind];
        net_mach_ind := net_mach_ind +1;

        for a:Address do
          i_directoryL1C1[i].cb[a].State := directoryL1C1_I;
          i_directoryL1C1[i].cb[a].cl := 0;
          undefine i_directoryL1C1[i].cb[a].ownerL1C1;
    
        endfor;
      endfor;


    end;
  

  ----RevMurphi/MurphiModular/Functions/GenEventFunc
  ----RevMurphi/MurphiModular/Functions/GenPermFunc
    procedure Clear_perm(adr: Address; m: Machines);
    begin
    end;
    
    procedure Set_perm(acc_type: PermissionType; adr: Address; m: Machines);
    begin
    end;
    
    procedure Reset_perm();
    begin
    end;
    
  
  ----RevMurphi/MurphiModular/Functions/GenStoreMonitorFunc
    procedure Execute_store_monitor(cb: ClValue; adr: Address);
    begin
      alias cbe: g_monitor_store[adr] do
        if cbe = cb then
          if cbe = VAL_COUNT then
            cbe := 0;
          else
            cbe := cbe + 1;
          endif;
        else
            error "Write linearization failed";
        endif;
      endalias;
    end;
    
    procedure Reset_global_monitor();
    begin
      for adr:Address do
        g_monitor_store[adr] := 0;
      endfor;
    end;
  
    procedure Store(var cbe: ClValue; adr: Address);
    begin
      Execute_store_monitor(cbe, adr);
      if cbe = VAL_COUNT then
        cbe:= 0;
      else
        cbe := cbe + 1;
      endif;
    end;
  
  ----RevMurphi/MurphiModular/Functions/GenFIFOFunc
  ----RevMurphi/MurphiModular/Functions/GenNetworkFunc
    procedure Send_fwd(msg:Message; src: Machines;);
      Assert(cnt_fwd[msg.dst] < O_NET_MAX) "Too many messages";
      fwd[msg.dst][cnt_fwd[msg.dst]] := msg;
      cnt_fwd[msg.dst] := cnt_fwd[msg.dst] + 1;
    end;
    
    procedure Pop_fwd(dst:Machines; src: Machines;);
    begin
      Assert (cnt_fwd[dst] > 0) "Trying to advance empty Q";
      for i := 0 to cnt_fwd[dst]-1 do
        if i < cnt_fwd[dst]-1 then
          fwd[dst][i] := fwd[dst][i+1];
        else
          undefine fwd[dst][i];
        endif;
      endfor;
      cnt_fwd[dst] := cnt_fwd[dst] - 1;
    end;
    
    procedure Send_resp(msg:Message; src: Machines;);
      Assert(cnt_resp[msg.dst] < O_NET_MAX) "Too many messages";
      resp[msg.dst][cnt_resp[msg.dst]] := msg;
      cnt_resp[msg.dst] := cnt_resp[msg.dst] + 1;
    end;
    
    procedure Pop_resp(dst:Machines; src: Machines;);
    begin
      Assert (cnt_resp[dst] > 0) "Trying to advance empty Q";
      for i := 0 to cnt_resp[dst]-1 do
        if i < cnt_resp[dst]-1 then
          resp[dst][i] := resp[dst][i+1];
        else
          undefine resp[dst][i];
        endif;
      endfor;
      cnt_resp[dst] := cnt_resp[dst] - 1;
    end;
    
    procedure Send_req(msg:Message; src: Machines;);
      Assert(cnt_req[msg.dst] < O_NET_MAX) "Too many messages";
      req[msg.dst][cnt_req[msg.dst]] := msg;
      cnt_req[msg.dst] := cnt_req[msg.dst] + 1;
    end;
    
    procedure Pop_req(dst:Machines; src: Machines;);
    begin
      Assert (cnt_req[dst] > 0) "Trying to advance empty Q";
      for i := 0 to cnt_req[dst]-1 do
        if i < cnt_req[dst]-1 then
          req[dst][i] := req[dst][i+1];
        else
          undefine req[dst][i];
        endif;
      endfor;
      cnt_req[dst] := cnt_req[dst] - 1;
    end;
    
    function req_network_ready(): boolean;
    begin
          for dst:Machines do
            for src: Machines do
              if cnt_req[dst] >= (O_NET_MAX-3) then
                return false;
              endif;
            endfor;
          endfor;
    
          return true;
    end;
    function fwd_network_ready(): boolean;
    begin
          for dst:Machines do
            for src: Machines do
              if cnt_fwd[dst] >= (O_NET_MAX-3) then
                return false;
              endif;
            endfor;
          endfor;
    
          return true;
    end;
    function resp_network_ready(): boolean;
    begin
          for dst:Machines do
            for src: Machines do
              if cnt_resp[dst] >= (O_NET_MAX-3) then
                return false;
              endif;
            endfor;
          endfor;
    
          return true;
    end;
    function network_ready(): boolean;
    begin
            if !req_network_ready() then
            return false;
          endif;
    
    
          if !fwd_network_ready() then
            return false;
          endif;
    
    
          if !resp_network_ready() then
            return false;
          endif;
    
    
    
      return true;
    end;
    
    procedure Reset_NET_();
    begin
      
      undefine fwd;
      for dst:Machines do
          cnt_fwd[dst] := 0;
      endfor;
      
      undefine resp;
      for dst:Machines do
          cnt_resp[dst] := 0;
      endfor;
      
      undefine req;
      for dst:Machines do
          cnt_req[dst] := 0;
      endfor;
    
    end;
    
  
  ----RevMurphi/MurphiModular/Functions/GenMessageConstrFunc
    function RequestL1C1(adr: Address; mtype: MessageType; src: Machines; dst: Machines) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
    return Message;
    end;
    
    function AckL1C1(adr: Address; mtype: MessageType; src: Machines; dst: Machines) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
    return Message;
    end;
    
    function RespL1C1(adr: Address; mtype: MessageType; src: Machines; dst: Machines; cl: ClValue) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
      Message.cl := cl;
    return Message;
    end;
    
    function RespAckL1C1(adr: Address; mtype: MessageType; src: Machines; dst: Machines; cl: ClValue) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
      Message.cl := cl;
    return Message;
    end;
    
  

--RevMurphi/MurphiModular/GenStateMachines

  ----RevMurphi/MurphiModular/StateMachines/GenAccessStateMachines
    procedure FSM_Access_cacheL1C1_I_load(adr:Address; i:OBJSET_cacheL1C1);
    var msg: Message;
    begin
    alias cbe: i_cacheL1C1[i].cb[adr] do
    alias m: i_net_cacheL1C1[i] do
      msg := RequestL1C1(adr,GetML1C1,m,i_net_directoryL1C1[directoryL1C1]);
      Send_req(msg, m);
      Clear_perm(adr, m);
      cbe.State := cacheL1C1_I_load;
      return;
    endalias;
    endalias
    end;
    
    procedure FSM_Access_cacheL1C1_I_store(adr:Address; i:OBJSET_cacheL1C1);
    var msg: Message;
    begin
    alias cbe: i_cacheL1C1[i].cb[adr] do
    alias m: i_net_cacheL1C1[i] do
      msg := RequestL1C1(adr,GetML1C1,m,i_net_directoryL1C1[directoryL1C1]);
      Send_req(msg, m);
      Clear_perm(adr, m);
      cbe.State := cacheL1C1_I_store;
      return;
    endalias;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1C1_M_evict(adr:Address; i:OBJSET_cacheL1C1);
    var msg: Message;
    begin
    alias cbe: i_cacheL1C1[i].cb[adr] do
    alias m: i_net_cacheL1C1[i] do
      msg := RespL1C1(adr,PutML1C1,m,i_net_directoryL1C1[directoryL1C1],cbe.cl);
      Send_req(msg, m);
      Clear_perm(adr, m);
      cbe.State := cacheL1C1_M_evict;
      return;
    endalias;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1C1_M_load(adr:Address; i:OBJSET_cacheL1C1);
    begin
    alias cbe: i_cacheL1C1[i].cb[adr] do
    alias m: i_net_cacheL1C1[i] do
      Clear_perm(adr, m); Set_perm(load, adr, m); Set_perm(store, adr, m);
      cbe.State := cacheL1C1_M;
      return;
    endalias;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1C1_M_store(adr:Address; i:OBJSET_cacheL1C1);
    begin
    alias cbe: i_cacheL1C1[i].cb[adr] do
    alias m: i_net_cacheL1C1[i] do
      Clear_perm(adr, m); Set_perm(load, adr, m); Set_perm(store, adr, m);
      Store(cbe.cl, adr);
      cbe.State := cacheL1C1_M;
      return;
    endalias;
    endalias;
    end;
    
  ----RevMurphi/MurphiModular/StateMachines/GenMessageStateMachines
    function FSM_MSG_cacheL1C1(inmsg:Message; i:OBJSET_cacheL1C1) : boolean;
    var msg: Message;
    begin
      alias adr: inmsg.adr do
      alias cbe: i_cacheL1C1[i].cb[adr] do
      alias m: i_net_cacheL1C1[i] do
    switch cbe.State
      case cacheL1C1_I:
      switch inmsg.mtype
        else return false;
      endswitch;
      
      case cacheL1C1_I_load:
      switch inmsg.mtype
        case GetM_Ack_DL1C1:
          cbe.cl := inmsg.cl;
          Clear_perm(adr, m); Set_perm(load, adr, m); Set_perm(store, adr, m);
          cbe.State := cacheL1C1_M;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1C1_I_store:
      switch inmsg.mtype
        case GetM_Ack_DL1C1:
          cbe.cl := inmsg.cl;
          Clear_perm(adr, m); Set_perm(load, adr, m); Set_perm(store, adr, m);
          cbe.State := cacheL1C1_M;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1C1_M:
      switch inmsg.mtype
        case Fwd_GetML1C1:
          msg := RespL1C1(adr,GetM_Ack_DL1C1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1C1_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1C1_M_evict:
      switch inmsg.mtype
        case Fwd_GetML1C1:
          msg := RespL1C1(adr,GetM_Ack_DL1C1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1C1_M_evict_x_I;
          return true;
        
        case Put_AckL1C1:
          Clear_perm(adr, m);
          cbe.State := cacheL1C1_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1C1_M_evict_x_I:
      switch inmsg.mtype
        case Put_AckL1C1:
          Clear_perm(adr, m);
          cbe.State := cacheL1C1_I;
          return true;
        
        else return false;
      endswitch;
      
    endswitch;
    endalias;
    endalias;
    endalias;
    return false;
    end;
    
    function FSM_MSG_directoryL1C1(inmsg:Message; i:OBJSET_directoryL1C1) : boolean;
    var msg: Message;
    begin
      alias adr: inmsg.adr do
      alias cbe: i_directoryL1C1[i].cb[adr] do
      alias m: i_net_directoryL1C1[i] do
    switch cbe.State
      case directoryL1C1_I:
      switch inmsg.mtype
        case GetML1C1:
          msg := RespL1C1(adr,GetM_Ack_DL1C1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          cbe.ownerL1C1 := inmsg.src;
          Clear_perm(adr, m);
          cbe.State := directoryL1C1_M;
          return true;
        
        else return false;
      endswitch;
      
      case directoryL1C1_M:
      switch inmsg.mtype
        case GetML1C1:
          msg := RequestL1C1(adr,Fwd_GetML1C1,inmsg.src,cbe.ownerL1C1);
          Send_fwd(msg, m);
          cbe.ownerL1C1 := inmsg.src;
          Clear_perm(adr, m);
          cbe.State := directoryL1C1_M;
          return true;
        
        case PutML1C1:
          msg := AckL1C1(adr,Put_AckL1C1,m,inmsg.src);
          Send_fwd(msg, m);
          if !(cbe.ownerL1C1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1C1_M;
            return true;
          endif;
          if (cbe.ownerL1C1 = inmsg.src) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1C1_I;
            return true;
          endif;
        
        else return false;
      endswitch;
      
    endswitch;
    endalias;
    endalias;
    endalias;
    return false;
    end;
    

--RevMurphi/MurphiModular/GenResetFunc

  procedure System_Reset();
  begin
  Reset_perm();
  Reset_global_monitor();
  Reset_NET_();
  ResetMachine_();
  end;
  

--RevMurphi/MurphiModular/GenRules
  ----RevMurphi/MurphiModular/Rules/GenAccessRuleSet
    ruleset m:OBJSET_cacheL1C1 do
    ruleset adr:Address do
      alias cbe:i_cacheL1C1[m].cb[adr] do
    
      rule "cacheL1C1_I_store"
        cbe.State = cacheL1C1_I & network_ready() 
      ==>
        FSM_Access_cacheL1C1_I_store(adr, m);
        
      endrule;
    
      rule "cacheL1C1_I_load"
        cbe.State = cacheL1C1_I & network_ready() 
      ==>
        FSM_Access_cacheL1C1_I_load(adr, m);
        
      endrule;
    
      rule "cacheL1C1_M_load"
        cbe.State = cacheL1C1_M 
      ==>
        FSM_Access_cacheL1C1_M_load(adr, m);
        
      endrule;
    
      rule "cacheL1C1_M_store"
        cbe.State = cacheL1C1_M 
      ==>
        FSM_Access_cacheL1C1_M_store(adr, m);
        
      endrule;
    
      rule "cacheL1C1_M_evict"
        cbe.State = cacheL1C1_M & network_ready() 
      ==>
        FSM_Access_cacheL1C1_M_evict(adr, m);
        
      endrule;
    
    
      endalias;
    endruleset;
    endruleset;
    
  ----RevMurphi/MurphiModular/Rules/GenEventRuleSet
  ----RevMurphi/MurphiModular/Rules/GenNetworkRule

    -- CACHE

    ruleset m:OBJSET_cacheL1C1 do
      alias dst: i_net_cacheL1C1[m] do
        ruleset src: Machines do
            alias msg:fwd[dst][0] do
              rule "Receive fwd"
                cnt_fwd[dst] > 0
              ==>
              if FSM_MSG_cacheL1C1(msg, m) then
                  Pop_fwd(dst, src);
              endif;
    
              endrule;
            endalias;
        endruleset;
      endalias;
    endruleset;
    
    ruleset m:OBJSET_cacheL1C1 do
      alias dst: i_net_cacheL1C1[m] do
        ruleset src: Machines do
            alias msg:resp[dst][0] do
              rule "Receive resp"
                cnt_resp[dst] > 0
              ==>
              if FSM_MSG_cacheL1C1(msg, m) then
                  Pop_resp(dst, src);
              endif;
    
              endrule;
            endalias;
        endruleset;
      endalias;
    endruleset;
    
    ruleset m:OBJSET_cacheL1C1 do
      alias dst: i_net_cacheL1C1[m] do
        ruleset src: Machines do
            alias msg:req[dst][0] do
              rule "Receive req"
                cnt_req[dst] > 0
              ==>
              if FSM_MSG_cacheL1C1(msg, m) then
                  Pop_req(dst, src);
              endif;
    
              endrule;
            endalias;
        endruleset;
      endalias;
    endruleset;


  -- DIRECTORY 
    ruleset m:OBJSET_directoryL1C1 do
      alias dst: i_net_directoryL1C1[m] do
        ruleset src: Machines do
            alias msg:fwd[dst][0] do
              rule "Receive fwd"
                cnt_fwd[dst] > 0
              ==>
              if FSM_MSG_directoryL1C1(msg, m) then
                  Pop_fwd(dst, src);
              endif;
    
              endrule;
            endalias;
        endruleset;
      endalias;
    endruleset;
    
    ruleset m:OBJSET_directoryL1C1 do
      alias dst: i_net_directoryL1C1[m] do
        ruleset src: Machines do
            alias msg:resp[dst][0] do
              rule "Receive resp"
                cnt_resp[dst] > 0
              ==>
              if FSM_MSG_directoryL1C1(msg, m) then
                  Pop_resp(dst, src);
              endif;
    
              endrule;
            endalias;
        endruleset;
      endalias;
    endruleset;
    
    ruleset m:OBJSET_directoryL1C1 do
      alias dst: i_net_directoryL1C1[m] do
        ruleset src: Machines do
            alias msg:req[dst][0] do
              rule "Receive req"
                cnt_req[dst] > 0
              ==>
              if FSM_MSG_directoryL1C1(msg, m) then
                  Pop_req(dst, src);
              endif;
    
              endrule;
            endalias;
        endruleset;
      endalias;
    endruleset;



--RevMurphi/MurphiModular/GenStartStates

  startstate
    System_Reset();
  endstartstate;

  
