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
--Backend/Murphi/MurphiModular/Constants/GenConst
  ---- System access constants
  const
    ENABLE_QS: false;
    VAL_COUNT: 1;
    ADR_COUNT: 1;
  
  ---- System network constants
    O_NET_MAX: 16;
    U_NET_MAX: 16;
  
  ---- SSP declaration constants 
    -- The actual number of simulated caches is NrCaches-1, because of proxy caches
    NrCachesL1_1: 2;
    NrCachesL1_2: 2;
  
--Backend/Murphi/MurphiModular/GenTypes
  type
    ----Backend/Murphi/MurphiModular/Types/GenAdrDef
    Address: scalarset(ADR_COUNT);
    ClValue: 0..VAL_COUNT;
    
    ----Backend/Murphi/MurphiModular/Types/Enums/GenEnums
      ------Backend/Murphi/MurphiModular/Types/Enums/SubEnums/GenAccess
      PermissionType: enum {
        load, 
        store, 
        evict, 
        acquire, 
        release, 
        none
      };
      
      ------Backend/Murphi/MurphiModular/Types/Enums/SubEnums/GenMessageTypes
      MessageType: enum {
        GetSL1_1, 
        GetML1_1, 
        PutSL1_1, 
        Inv_AckL1_1, 
        GetM_Ack_DL1_1, 
        GetS_AckL1_1, 
        WBL1_1, 
        PutML1_1, 
        PutEL1_1, 
        GetM_Ack_ADL1_1, 
        InvL1_1, 
        Put_AckL1_1, 
        Fwd_GetSL1_1, 
        Fwd_GetML1_1, 
        GetVL1_2, 
        GetOL1_2, 
        PutOL1_2, 
        WB_AckL1_2, 
        GetV_AckL1_2, 
        GetO_AckL1_2, 
        PutO_AckL1_2, 
        Fwd_GetOL1_2, 
        GetVL1_2acquire, 
        GetOL1_2release
      };
      
      ------Backend/Murphi/MurphiModular/Types/Enums/SubEnums/GenArchEnums
      s_directoryL1_1: enum {
        directoryL1_1_S__C__V,
        directoryL1_1_M__C__V,
        directoryL1_1_I__C__V,
        directoryL1_1_I__C__O,
        directoryL1_1_GetVL1_2dS_x_pI_load__C__V,
        directoryL1_1_GetVL1_2dM_GetS_x_pS__C__V,
        directoryL1_1_GetVL1_2dM_GetS_x_pI_load__C__V,
        directoryL1_1_GetVL1_2dE_GetS_x_pS__C__V,
        directoryL1_1_GetVL1_2dE_GetS_x_pI_load__C__V,
        directoryL1_1_GetVL1_2acquiredS_x_pI_load__C__V,
        directoryL1_1_GetVL1_2acquiredM_GetS_x_pS__C__V,
        directoryL1_1_GetVL1_2acquiredM_GetS_x_pI_load__C__V,
        directoryL1_1_GetVL1_2acquiredE_GetS_x_pS__C__V,
        directoryL1_1_GetVL1_2acquiredE_GetS_x_pI_load__C__V,
        directoryL1_1_GetVL1_2acquireI__C__O_GetV,
        directoryL1_1_GetVL1_2I__C__O_GetV,
        directoryL1_1_GetSL1_1M_GetS__C__V,
        directoryL1_1_GetSL1_1I__C__dO_GetO_x_pI_release,
        directoryL1_1_GetSL1_1E_GetS__C__V,
        directoryL1_1_GetOL1_2releasedM_x_pI_store__C__V,
        directoryL1_1_GetOL1_2releasedM_x_pI_store_GetM_Ack_AD__C__V,
        directoryL1_1_GetOL1_2releaseI__C__O_GetO,
        directoryL1_1_GetOL1_2dM_x_pI_store__C__V,
        directoryL1_1_GetOL1_2dM_x_pI_store_GetM_Ack_AD__C__V,
        directoryL1_1_GetOL1_2I__C__O_GetO,
        directoryL1_1_GetML1_1I__C__dO_GetO_x_pI_release,
        directoryL1_1_E__C__V
      };
      
      e_directoryL1_1: enum {
        directoryL1_1_acq_eventL1_2
      };
      
      s_cacheL1_2: enum {
        cacheL1_2_V_store,
        cacheL1_2_V_release,
        cacheL1_2_V_acquire_GetV_Ack,
        cacheL1_2_V_acquire,
        cacheL1_2_V,
        cacheL1_2_O_evict_x_V,
        cacheL1_2_O_evict,
        cacheL1_2_O,
        cacheL1_2_I_store,
        cacheL1_2_I_release,
        cacheL1_2_I_load,
        cacheL1_2_I_acquire_GetV_Ack,
        cacheL1_2_I_acquire,
        cacheL1_2_I
      };
      
      e_cacheL1_2: enum {
        cacheL1_2_acq_eventL1_2
      };
      
      s_cacheL1_1: enum {
        cacheL1_1_S_store_GetM_Ack_AD,
        cacheL1_1_S_store,
        cacheL1_1_S_evict_x_I,
        cacheL1_1_S_evict,
        cacheL1_1_S,
        cacheL1_1_M_evict_x_I,
        cacheL1_1_M_evict,
        cacheL1_1_M,
        cacheL1_1_I_store_GetM_Ack_AD,
        cacheL1_1_I_store,
        cacheL1_1_I_load,
        cacheL1_1_I,
        cacheL1_1_E_evict_x_I,
        cacheL1_1_E_evict,
        cacheL1_1_E
      };
      
    ----Backend/Murphi/MurphiModular/Types/GenMachineSets
      -- Cluster: C1
      OBJSET_directoryL1_1: enum{directoryL1_1};
      OBJSET_cacheL1_2: scalarset(NrCachesL1_1-1);
      OBJSET_cacheL1_1: scalarset(NrCachesL1_2-1);
      C1Machines: union{OBJSET_directoryL1_1, OBJSET_cacheL1_2, OBJSET_cacheL1_1};
      
      Machines: union{OBJSET_directoryL1_1, OBJSET_cacheL1_2, OBJSET_cacheL1_1};
    
    ----Backend/Murphi/MurphiModular/Types/GenCheckTypes
      ------Backend/Murphi/MurphiModular/Types/CheckTypes/GenPermType
        acc_type_obj: multiset[3] of PermissionType;
        PermMonitor: array[Machines] of array[Address] of acc_type_obj;
      
    
    ----Backend/Murphi/MurphiModular/Types/GenMessage
      Message: record
        adr: Address;
        mtype: MessageType;
        src: Machines;
        dst: Machines;
        cl: ClValue;
        acksExpectedL1_1: 0..NrCachesL1_1;
      end;
      
    ----Backend/Murphi/MurphiModular/Types/GenNetwork
      NET_Ordered: array[Machines] of array[0..O_NET_MAX-1] of Message;
      NET_Ordered_cnt: array[Machines] of 0..O_NET_MAX;
      NET_Unordered: array[Machines] of multiset[U_NET_MAX] of Message;
    
    ----Backend/Murphi/MurphiModular/Types/GenMachines
      v_cacheL1_1: multiset[NrCachesL1_1] of Machines;
      cnt_v_cacheL1_1: 0..NrCachesL1_1;
      
      ENTRY_directoryL1_1: record
        State: s_directoryL1_1;
        cl: ClValue;
        cacheL1_1: v_cacheL1_1;
        ownerL1_1: Machines;
        acksReceivedL1_1: 0..NrCachesL1_1;
        acksExpectedL1_1: 0..NrCachesL1_1;
        proxy_msg: Message;
        ownerL1_2: Machines;
      end;
      
      EVENT_ENTRY_directoryL1_1: record
          evt_type: e_directoryL1_1;
          evt_adr: Address;
      end;
      
      EVENT_directoryL1_1: record
          event_queue: array[0..ADR_COUNT] of EVENT_ENTRY_directoryL1_1;
          event_queue_index: 0..ADR_COUNT+1;
          pend_adr: multiset[ADR_COUNT+1] of Address;
          event_lock_adr: Address;
      
      end;
      
      MACH_directoryL1_1: record
        cb: array[Address] of ENTRY_directoryL1_1;
        evt: EVENT_directoryL1_1;
      end;
      
      OBJ_directoryL1_1: array[OBJSET_directoryL1_1] of MACH_directoryL1_1;
      
      ENTRY_cacheL1_2: record
        State: s_cacheL1_2;
        cl: ClValue;
      end;
      
      EVENT_ENTRY_cacheL1_2: record
          evt_type: e_cacheL1_2;
          evt_adr: Address;
      end;
      
      EVENT_cacheL1_2: record
          event_queue: array[0..ADR_COUNT] of EVENT_ENTRY_cacheL1_2;
          event_queue_index: 0..ADR_COUNT+1;
          pend_adr: multiset[ADR_COUNT+1] of Address;
          event_lock_adr: Address;
      
      end;
      
      MACH_cacheL1_2: record
        cb: array[Address] of ENTRY_cacheL1_2;
        evt: EVENT_cacheL1_2;
      end;
      
      OBJ_cacheL1_2: array[OBJSET_cacheL1_2] of MACH_cacheL1_2;
      
      ENTRY_cacheL1_1: record
        State: s_cacheL1_1;
        cl: ClValue;
        acksReceivedL1_1: 0..NrCachesL1_1;
        acksExpectedL1_1: 0..NrCachesL1_1;
      end;
      
      MACH_cacheL1_1: record
        cb: array[Address] of ENTRY_cacheL1_1;
      end;
      
      OBJ_cacheL1_1: array[OBJSET_cacheL1_1] of MACH_cacheL1_1;
    

  var
    --Backend/Murphi/MurphiModular/GenVars
      fwd: NET_Ordered;
      cnt_fwd: NET_Ordered_cnt;
      resp: NET_Ordered;
      cnt_resp: NET_Ordered_cnt;
      req: NET_Ordered;
      cnt_req: NET_Ordered_cnt;
    
    
      g_perm: PermMonitor;
      i_directoryL1_1: OBJ_directoryL1_1;
      i_cacheL1_2: OBJ_cacheL1_2;
      i_cacheL1_1: OBJ_cacheL1_1;
  
--Backend/Murphi/MurphiModular/GenFunctions

  ----Backend/Murphi/MurphiModular/Functions/GenResetFunc
    procedure ResetMachine_directoryL1_1();
    begin
      for i:OBJSET_directoryL1_1 do
        for a:Address do
          i_directoryL1_1[i].cb[a].State := directoryL1_1_I__C__V;
          i_directoryL1_1[i].cb[a].cl := 0;
          undefine i_directoryL1_1[i].cb[a].cacheL1_1;
          undefine i_directoryL1_1[i].cb[a].ownerL1_1;
          undefine i_directoryL1_1[i].cb[a].proxy_msg;
          undefine i_directoryL1_1[i].cb[a].ownerL1_2;
          i_directoryL1_1[i].cb[a].acksReceivedL1_1 := 0;
          i_directoryL1_1[i].cb[a].acksExpectedL1_1 := 0;
    
        endfor;
      endfor;
    end;
    
    procedure ResetMachine_cacheL1_2();
    begin
      for i:OBJSET_cacheL1_2 do
        for a:Address do
          i_cacheL1_2[i].cb[a].State := cacheL1_2_I;
          i_cacheL1_2[i].cb[a].cl := 0;
    
        endfor;
      endfor;
    end;
    
    procedure ResetMachine_cacheL1_1();
    begin
      for i:OBJSET_cacheL1_1 do
        for a:Address do
          i_cacheL1_1[i].cb[a].State := cacheL1_1_I;
          i_cacheL1_1[i].cb[a].cl := 0;
          i_cacheL1_1[i].cb[a].acksReceivedL1_1 := 0;
          i_cacheL1_1[i].cb[a].acksExpectedL1_1 := 0;
    
        endfor;
      endfor;
    end;
    
      procedure ResetMachine_();
      begin
      ResetMachine_cacheL1_1();
      ResetMachine_cacheL1_2();
      ResetMachine_directoryL1_1();
      
      end;
  ----Backend/Murphi/MurphiModular/Functions/GenEventFunc
    procedure NextEvent_directoryL1_1(m: OBJSET_directoryL1_1);
    begin
      alias evt_entry: i_directoryL1_1[m].evt do
      alias evt_index: evt_entry.event_queue_index do
      alias pend_adr: evt_entry.pend_adr do
    
        if isundefined(evt_entry.event_queue[0].evt_type) then
            return;
        endif;
    
        if MultisetCount(a:pend_adr, true) > 0 then
          return;
        else
          if evt_entry.event_queue_index > 0 then
            for a: Address do
              if a != evt_entry.event_queue[0].evt_adr then
                MultisetAdd(a, pend_adr);
              endif;
            endfor;
          endif;
        endif;
    
      endalias;
      endalias;
      endalias;
    end;
    
    procedure PopEvent_directoryL1_1(m: OBJSET_directoryL1_1);
    begin
      alias evt_entry: i_directoryL1_1[m].evt do
      alias evt_index: evt_entry.event_queue_index do
    
        for i := 0 to evt_index-1 do
          if i < evt_index-1 then
            evt_entry.event_queue[i] := evt_entry.event_queue[i+1];
          else
            undefine evt_entry.event_queue[i];
          endif;
        endfor;
    
        evt_index := evt_index - 1;
    
      endalias;
      endalias;
    end;
    
    procedure ResetEvent_directoryL1_1();
    begin
      for m: OBJSET_directoryL1_1 do
        alias evt_entry: i_directoryL1_1[m].evt do
          undefine evt_entry.event_queue;
          evt_entry.event_queue_index := 0;
          undefine evt_entry.pend_adr;
          undefine evt_entry.event_lock_adr
        endalias;
      endfor;
    end;
    
    procedure IssueEvent_directoryL1_1(evt_type: e_directoryL1_1; m: OBJSET_directoryL1_1; adr: Address);
    begin
      alias evt_entry: i_directoryL1_1[m].evt do
      alias evt_index: evt_entry.event_queue_index do
    
        evt_entry.event_queue[evt_index].evt_type := evt_type;
        evt_entry.event_queue[evt_index].evt_adr := adr;
        evt_index := evt_index + 1;
    
        NextEvent_directoryL1_1(m);
    
      endalias;
      endalias;
    end;
    
    /* Event: Checks if the currently pending event has been served*/
    function CheckRemoteEvent_directoryL1_1(cur_evt_type: e_directoryL1_1; m: OBJSET_directoryL1_1; adr: Address): boolean;
    begin
      alias evt_entry: i_directoryL1_1[m].evt do
      alias pend_adr: i_directoryL1_1[m].evt.pend_adr do
    
        if isundefined(evt_entry.event_queue[0].evt_type) then
            return false;
        endif;
    
        /* Check if the event type matches and the event still need to be served for this address */
        if evt_entry.event_queue[0].evt_type = cur_evt_type & MultisetCount(a: pend_adr, pend_adr[a] = adr) = 1 then
            return true;
        endif;
    
        return false;
    
      endalias;
      endalias;
    end;
    
    procedure ServeRemoteEvent_directoryL1_1(cur_evt_type: e_directoryL1_1; m: OBJSET_directoryL1_1; adr: Address);
    begin
      alias evt_entry: i_directoryL1_1[m].evt do
      alias pend_adr: i_directoryL1_1[m].evt.pend_adr do
    
        /* Check if the event type matches and the event still need to be served for this address */
        if evt_entry.event_queue[0].evt_type = cur_evt_type & MultisetCount(a: pend_adr, pend_adr[a] = adr) = 1 then
            MultisetRemovePred(a: pend_adr, pend_adr[a] = adr);
        endif;
    
      endalias;
      endalias;
    end;
    
    /* Event Ack: Checks if the currently pending event has been served by all addresses */
    function CheckInitEvent_directoryL1_1(cur_evt_type: e_directoryL1_1; m: OBJSET_directoryL1_1; adr: Address): boolean;
    begin
      alias evt_entry: i_directoryL1_1[m].evt do
      alias pend_adr: i_directoryL1_1[m].evt.pend_adr do
    
        if isundefined(evt_entry.event_queue[0].evt_type) then
            return false;
        endif;
    
        if evt_entry.event_queue[0].evt_type = cur_evt_type & MultisetCount(a:pend_adr, true) = 0 then
            return true;
        endif;
    
        return false;
    
      endalias;
      endalias;
    end;
    
    procedure ServeInitEvent_directoryL1_1(cur_evt_type: e_directoryL1_1; m: OBJSET_directoryL1_1; adr: Address);
    begin
      alias evt_entry: i_directoryL1_1[m].evt do
      alias pend_adr: i_directoryL1_1[m].evt.pend_adr do
    
        if evt_entry.event_queue[0].evt_type = cur_evt_type & MultisetCount(a:pend_adr, true) = 0 then
            PopEvent_directoryL1_1(m);
            NextEvent_directoryL1_1(m);
        endif;
    
      endalias;
      endalias;
    end;
    
    function TestAtomicEvent_directoryL1_1(m: OBJSET_directoryL1_1): boolean;
    begin
        if isundefined(i_directoryL1_1[m].evt.event_lock_adr) then
            return true;
        else
            return false;
        endif;
    end;
    
    procedure LockAtomicEvent_directoryL1_1(m: OBJSET_directoryL1_1; adr: Address);
    begin
      i_directoryL1_1[m].evt.event_lock_adr := adr;
    end;
    
    procedure UnlockAtomicEvent_directoryL1_1(m: OBJSET_directoryL1_1; adr: Address);
    begin
        if !isundefined(i_directoryL1_1[m].evt.event_lock_adr) then
            if i_directoryL1_1[m].evt.event_lock_adr = adr then
                undefine i_directoryL1_1[m].evt.event_lock_adr;
            endif;
        endif;
    end;
    
    procedure NextEvent_cacheL1_2(m: OBJSET_cacheL1_2);
    begin
      alias evt_entry: i_cacheL1_2[m].evt do
      alias evt_index: evt_entry.event_queue_index do
      alias pend_adr: evt_entry.pend_adr do
    
        if isundefined(evt_entry.event_queue[0].evt_type) then
            return;
        endif;
    
        if MultisetCount(a:pend_adr, true) > 0 then
          return;
        else
          if evt_entry.event_queue_index > 0 then
            for a: Address do
              if a != evt_entry.event_queue[0].evt_adr then
                MultisetAdd(a, pend_adr);
              endif;
            endfor;
          endif;
        endif;
    
      endalias;
      endalias;
      endalias;
    end;
    
    procedure PopEvent_cacheL1_2(m: OBJSET_cacheL1_2);
    begin
      alias evt_entry: i_cacheL1_2[m].evt do
      alias evt_index: evt_entry.event_queue_index do
    
        for i := 0 to evt_index-1 do
          if i < evt_index-1 then
            evt_entry.event_queue[i] := evt_entry.event_queue[i+1];
          else
            undefine evt_entry.event_queue[i];
          endif;
        endfor;
    
        evt_index := evt_index - 1;
    
      endalias;
      endalias;
    end;
    
    procedure ResetEvent_cacheL1_2();
    begin
      for m: OBJSET_cacheL1_2 do
        alias evt_entry: i_cacheL1_2[m].evt do
          undefine evt_entry.event_queue;
          evt_entry.event_queue_index := 0;
          undefine evt_entry.pend_adr;
          undefine evt_entry.event_lock_adr
        endalias;
      endfor;
    end;
    
    procedure IssueEvent_cacheL1_2(evt_type: e_cacheL1_2; m: OBJSET_cacheL1_2; adr: Address);
    begin
      alias evt_entry: i_cacheL1_2[m].evt do
      alias evt_index: evt_entry.event_queue_index do
    
        evt_entry.event_queue[evt_index].evt_type := evt_type;
        evt_entry.event_queue[evt_index].evt_adr := adr;
        evt_index := evt_index + 1;
    
        NextEvent_cacheL1_2(m);
    
      endalias;
      endalias;
    end;
    
    /* Event: Checks if the currently pending event has been served*/
    function CheckRemoteEvent_cacheL1_2(cur_evt_type: e_cacheL1_2; m: OBJSET_cacheL1_2; adr: Address): boolean;
    begin
      alias evt_entry: i_cacheL1_2[m].evt do
      alias pend_adr: i_cacheL1_2[m].evt.pend_adr do
    
        if isundefined(evt_entry.event_queue[0].evt_type) then
            return false;
        endif;
    
        /* Check if the event type matches and the event still need to be served for this address */
        if evt_entry.event_queue[0].evt_type = cur_evt_type & MultisetCount(a: pend_adr, pend_adr[a] = adr) = 1 then
            return true;
        endif;
    
        return false;
    
      endalias;
      endalias;
    end;
    
    procedure ServeRemoteEvent_cacheL1_2(cur_evt_type: e_cacheL1_2; m: OBJSET_cacheL1_2; adr: Address);
    begin
      alias evt_entry: i_cacheL1_2[m].evt do
      alias pend_adr: i_cacheL1_2[m].evt.pend_adr do
    
        /* Check if the event type matches and the event still need to be served for this address */
        if evt_entry.event_queue[0].evt_type = cur_evt_type & MultisetCount(a: pend_adr, pend_adr[a] = adr) = 1 then
            MultisetRemovePred(a: pend_adr, pend_adr[a] = adr);
        endif;
    
      endalias;
      endalias;
    end;
    
    /* Event Ack: Checks if the currently pending event has been served by all addresses */
    function CheckInitEvent_cacheL1_2(cur_evt_type: e_cacheL1_2; m: OBJSET_cacheL1_2; adr: Address): boolean;
    begin
      alias evt_entry: i_cacheL1_2[m].evt do
      alias pend_adr: i_cacheL1_2[m].evt.pend_adr do
    
        if isundefined(evt_entry.event_queue[0].evt_type) then
            return false;
        endif;
    
        if evt_entry.event_queue[0].evt_type = cur_evt_type & MultisetCount(a:pend_adr, true) = 0 then
            return true;
        endif;
    
        return false;
    
      endalias;
      endalias;
    end;
    
    procedure ServeInitEvent_cacheL1_2(cur_evt_type: e_cacheL1_2; m: OBJSET_cacheL1_2; adr: Address);
    begin
      alias evt_entry: i_cacheL1_2[m].evt do
      alias pend_adr: i_cacheL1_2[m].evt.pend_adr do
    
        if evt_entry.event_queue[0].evt_type = cur_evt_type & MultisetCount(a:pend_adr, true) = 0 then
            PopEvent_cacheL1_2(m);
            NextEvent_cacheL1_2(m);
        endif;
    
      endalias;
      endalias;
    end;
    
    function TestAtomicEvent_cacheL1_2(m: OBJSET_cacheL1_2): boolean;
    begin
        if isundefined(i_cacheL1_2[m].evt.event_lock_adr) then
            return true;
        else
            return false;
        endif;
    end;
    
    procedure LockAtomicEvent_cacheL1_2(m: OBJSET_cacheL1_2; adr: Address);
    begin
      i_cacheL1_2[m].evt.event_lock_adr := adr;
    end;
    
    procedure UnlockAtomicEvent_cacheL1_2(m: OBJSET_cacheL1_2; adr: Address);
    begin
        if !isundefined(i_cacheL1_2[m].evt.event_lock_adr) then
            if i_cacheL1_2[m].evt.event_lock_adr = adr then
                undefine i_cacheL1_2[m].evt.event_lock_adr;
            endif;
        endif;
    end;
    
    procedure ResetEvent_();
    begin
      ResetEvent_cacheL1_2();
      ResetEvent_directoryL1_1();
    
    end;
  ----Backend/Murphi/MurphiModular/Functions/GenPermFunc
    procedure Clear_perm(adr: Address; m: Machines);
    begin
      alias l_perm_set:g_perm[m][adr] do
          undefine l_perm_set;
      endalias;
    end;
    
    procedure Set_perm(acc_type: PermissionType; adr: Address; m: Machines);
    begin
      alias l_perm_set:g_perm[m][adr] do
      if MultiSetCount(i:l_perm_set, l_perm_set[i] = acc_type) = 0 then
          MultisetAdd(acc_type, l_perm_set);
      endif;
      endalias;
    end;
    
    procedure Reset_perm();
    begin
      for m:Machines do
        for adr:Address do
          Clear_perm(adr, m);
        endfor;
      endfor;
    end;
    
  
  ----Backend/Murphi/MurphiModular/Functions/GenVectorFunc
    -- .add()
    procedure AddElement_cacheL1_1(var sv:v_cacheL1_1; n:Machines);
    begin
        if MultiSetCount(i:sv, sv[i] = n) = 0 then
          MultiSetAdd(n, sv);
        endif;
    end;
    
    -- .del()
    procedure RemoveElement_cacheL1_1(var sv:v_cacheL1_1; n:Machines);
    begin
        if MultiSetCount(i:sv, sv[i] = n) = 1 then
          MultiSetRemovePred(i:sv, sv[i] = n);
        endif;
    end;
    
    -- .clear()
    procedure ClearVector_cacheL1_1(var sv:v_cacheL1_1;);
    begin
        MultiSetRemovePred(i:sv, true);
    end;
    
    -- .contains()
    function IsElement_cacheL1_1(var sv:v_cacheL1_1; n:Machines) : boolean;
    begin
        if MultiSetCount(i:sv, sv[i] = n) = 1 then
          return true;
        elsif MultiSetCount(i:sv, sv[i] = n) = 0 then
          return false;
        else
          Error "Multiple Entries of Sharer in SV multiset";
        endif;
      return false;
    end;
    
    -- .empty()
    function HasElement_cacheL1_1(var sv:v_cacheL1_1; n:Machines) : boolean;
    begin
        if MultiSetCount(i:sv, true) = 0 then
          return false;
        endif;
    
        return true;
    end;
    
    -- .count()
    function VectorCount_cacheL1_1(var sv:v_cacheL1_1) : cnt_v_cacheL1_1;
    begin
        return MultiSetCount(i:sv, true);
    end;
    
  ----Backend/Murphi/MurphiModular/Functions/GenFIFOFunc
  ----Backend/Murphi/MurphiModular/Functions/GenNetworkFunc
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
    
    procedure Multicast_fwd_v_cacheL1_1(var msg: Message; dst_vect: v_cacheL1_1; src: Machines;);
    begin
          for n:Machines do
              if n!=msg.src then
                if MultiSetCount(i:dst_vect, dst_vect[i] = n) = 1 then
                  msg.dst := n;
                  Send_fwd(msg, src);
                endif;
              endif;
          endfor;
    end;
    
    function resp_network_ready(): boolean;
    begin
          for dst:Machines do
            for src: Machines do
              if cnt_resp[dst] >= (O_NET_MAX-7) then
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
              if cnt_fwd[dst] >= (O_NET_MAX-7) then
                return false;
              endif;
            endfor;
          endfor;
    
          return true;
    end;
    function req_network_ready(): boolean;
    begin
          for dst:Machines do
            for src: Machines do
              if cnt_req[dst] >= (O_NET_MAX-7) then
                return false;
              endif;
            endfor;
          endfor;
    
          return true;
    end;
    function network_ready(): boolean;
    begin
            if !resp_network_ready() then
            return false;
          endif;
    
    
          if !fwd_network_ready() then
            return false;
          endif;
    
    
          if !resp_network_ready() then
            return false;
          endif;
    
    
          if !req_network_ready() then
            return false;
          endif;
    
    
          if !req_network_ready() then
            return false;
          endif;
    
    
          if !fwd_network_ready() then
            return false;
          endif;
    
    
    
      return true;
    end;
    
    procedure Reset_NET_();
    begin
      
      undefine resp;
      for dst:Machines do
          cnt_resp[dst] := 0;
      endfor;
      
      undefine req;
      for dst:Machines do
          cnt_req[dst] := 0;
      endfor;
      
      undefine fwd;
      for dst:Machines do
          cnt_fwd[dst] := 0;
      endfor;
    
    end;
    
  
  ----Backend/Murphi/MurphiModular/Functions/GenMessageConstrFunc
    function RequestL1_1(adr: Address; mtype: MessageType; src: Machines; dst: Machines) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
    return Message;
    end;
    
    function AckL1_1(adr: Address; mtype: MessageType; src: Machines; dst: Machines) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
    return Message;
    end;
    
    function RespL1_1(adr: Address; mtype: MessageType; src: Machines; dst: Machines; cl: ClValue) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
      Message.cl := cl;
    return Message;
    end;
    
    function RespAckL1_1(adr: Address; mtype: MessageType; src: Machines; dst: Machines; cl: ClValue; acksExpectedL1_1: 0..NrCachesL1_1) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
      Message.cl := cl;
      Message.acksExpectedL1_1 := acksExpectedL1_1;
    return Message;
    end;
    
    function RequestL1_2(adr: Address; mtype: MessageType; src: Machines; dst: Machines) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
    return Message;
    end;
    
    function AckL1_2(adr: Address; mtype: MessageType; src: Machines; dst: Machines) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
    return Message;
    end;
    
    function RespL1_2(adr: Address; mtype: MessageType; src: Machines; dst: Machines; cl: ClValue) : Message;
    var Message: Message;
    begin
      Message.adr := adr;
      Message.mtype := mtype;
      Message.src := src;
      Message.dst := dst;
      Message.cl := cl;
    return Message;
    end;
    
  

--Backend/Murphi/MurphiModular/GenStateMachines

  ----Backend/Murphi/MurphiModular/StateMachines/GenAccessStateMachines
    procedure FSM_Access_cacheL1_1_E_evict(adr:Address; m:OBJSET_cacheL1_1);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      msg := AckL1_1(adr, PutEL1_1, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_1_E_evict;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_E_load(adr:Address; m:OBJSET_cacheL1_1);
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      Set_perm(load, adr, m);cbe.State := cacheL1_1_E;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_E_store(adr:Address; m:OBJSET_cacheL1_1);
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      Set_perm(store, adr, m);cbe.State := cacheL1_1_M;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_I_load(adr:Address; m:OBJSET_cacheL1_1);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      msg := RequestL1_1(adr, GetSL1_1, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_1_I_load;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_I_store(adr:Address; m:OBJSET_cacheL1_1);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      msg := RequestL1_1(adr, GetML1_1, m, directoryL1_1);
      Send_req(msg, m);
      cbe.acksReceivedL1_1 := 0;
      cbe.State := cacheL1_1_I_store;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_M_evict(adr:Address; m:OBJSET_cacheL1_1);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      msg := RespL1_1(adr, PutML1_1, m, directoryL1_1, cbe.cl);
      Send_req(msg, m);
      cbe.State := cacheL1_1_M_evict;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_M_load(adr:Address; m:OBJSET_cacheL1_1);
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      Set_perm(load, adr, m);cbe.State := cacheL1_1_M;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_M_store(adr:Address; m:OBJSET_cacheL1_1);
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      Set_perm(store, adr, m);cbe.State := cacheL1_1_M;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_S_evict(adr:Address; m:OBJSET_cacheL1_1);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      msg := RequestL1_1(adr, PutSL1_1, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_1_S_evict;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_S_load(adr:Address; m:OBJSET_cacheL1_1);
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      Set_perm(load, adr, m);cbe.State := cacheL1_1_S;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_1_S_store(adr:Address; m:OBJSET_cacheL1_1);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_1[m].cb[adr] do
      msg := RequestL1_1(adr, GetML1_1, m, directoryL1_1);
      Send_req(msg, m);
      cbe.acksReceivedL1_1 := 0;
      cbe.State := cacheL1_1_S_store;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_I_acq_eventL1_2(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      ServeRemoteEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr);
      cbe.State := cacheL1_2_I;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_I_acquire(adr:Address; m:OBJSET_cacheL1_2);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      msg := RequestL1_2(adr, GetVL1_2, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_2_I_acquire;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_I_load(adr:Address; m:OBJSET_cacheL1_2);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      msg := RequestL1_2(adr, GetVL1_2, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_2_I_load;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_I_release(adr:Address; m:OBJSET_cacheL1_2);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      msg := RequestL1_2(adr, GetOL1_2, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_2_I_release;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_I_store(adr:Address; m:OBJSET_cacheL1_2);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      msg := RequestL1_2(adr, GetOL1_2, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_2_I_store;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_I_acquire_GetV_Ack_acq_eventL1_2(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      Set_perm(load, adr, m);cbe.State := cacheL1_2_V;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_O_acq_eventL1_2(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      ServeRemoteEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr);
      cbe.State := cacheL1_2_O;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_O_acquire(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      Set_perm(load, adr, m);cbe.State := cacheL1_2_O;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_O_evict(adr:Address; m:OBJSET_cacheL1_2);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      msg := RespL1_2(adr, PutOL1_2, m, directoryL1_1, cbe.cl);
      Send_req(msg, m);
      cbe.State := cacheL1_2_O_evict;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_O_load(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      cbe.State := cacheL1_2_O;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_O_release(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      Set_perm(store, adr, m);cbe.State := cacheL1_2_O;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_O_store(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      cbe.State := cacheL1_2_O;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_V_acq_eventL1_2(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      ServeRemoteEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr);
      cbe.State := cacheL1_2_I;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_V_acquire(adr:Address; m:OBJSET_cacheL1_2);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      msg := RequestL1_2(adr, GetVL1_2, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_2_V_acquire;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_V_evict(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      cbe.State := cacheL1_2_I;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_V_load(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      cbe.State := cacheL1_2_V;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_V_release(adr:Address; m:OBJSET_cacheL1_2);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      msg := RequestL1_2(adr, GetOL1_2release, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_2_V_release;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_V_store(adr:Address; m:OBJSET_cacheL1_2);
    var msg: Message;
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      msg := RequestL1_2(adr, GetOL1_2, m, directoryL1_1);
      Send_req(msg, m);
      cbe.State := cacheL1_2_V_store;
    endalias;
    end;
    
    procedure FSM_Access_cacheL1_2_V_acquire_GetV_Ack_acq_eventL1_2(adr:Address; m:OBJSET_cacheL1_2);
    begin
    alias cbe: i_cacheL1_2[m].cb[adr] do
      Set_perm(load, adr, m);cbe.State := cacheL1_2_V;
    endalias;
    end;
    
    procedure FSM_Access_directoryL1_1_E__C__V_acq_eventL1_2(adr:Address; m:OBJSET_directoryL1_1);
    begin
    alias cbe: i_directoryL1_1[m].cb[adr] do
      ServeRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr);
      cbe.State := directoryL1_1_E__C__V;
    endalias;
    end;
    
    procedure FSM_Access_directoryL1_1_I__C__O_acq_eventL1_2(adr:Address; m:OBJSET_directoryL1_1);
    begin
    alias cbe: i_directoryL1_1[m].cb[adr] do
      ServeRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr);
      cbe.State := directoryL1_1_I__C__O;
    endalias;
    end;
    
    procedure FSM_Access_directoryL1_1_I__C__V_acq_eventL1_2(adr:Address; m:OBJSET_directoryL1_1);
    begin
    alias cbe: i_directoryL1_1[m].cb[adr] do
      ServeRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr);
      cbe.State := directoryL1_1_I__C__V;
    endalias;
    end;
    
    procedure FSM_Access_directoryL1_1_M__C__V_acq_eventL1_2(adr:Address; m:OBJSET_directoryL1_1);
    begin
    alias cbe: i_directoryL1_1[m].cb[adr] do
      ServeRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr);
      cbe.State := directoryL1_1_M__C__V;
    endalias;
    end;
    
    procedure FSM_Access_directoryL1_1_S__C__V_acq_eventL1_2(adr:Address; m:OBJSET_directoryL1_1);
    begin
    alias cbe: i_directoryL1_1[m].cb[adr] do
      ServeRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr);
      cbe.State := directoryL1_1_S__C__V;
    endalias;
    end;
    
  ----Backend/Murphi/MurphiModular/StateMachines/GenMessageStateMachines
    function FSM_MSG_directoryL1_1(inmsg:Message; m:OBJSET_directoryL1_1) : boolean;
    var msg_GetOL1_2: Message;
    var msg_GetO_AckL1_2: Message;
    var msg_PutOL1_2: Message;
    var msg_PutO_AckL1_2: Message;
    var msg: Message;
    var msg_GetML1_1: Message;
    var msg_GetVL1_2: Message;
    var msg_GetV_AckL1_2: Message;
    var msg_GetSL1_1: Message;
    var msg_PutML1_1: Message;
    var msg_Put_AckL1_1: Message;
    var msg_PutSL1_1: Message;
    var msg_GetM_Ack_ADL1_1: Message;
    var msg_GetM_Ack_DL1_1: Message;
    var msg_PutEL1_1: Message;
    var msg_GetS_AckL1_1: Message;
    begin
      alias adr: inmsg.adr do
      alias cbe: i_directoryL1_1[m].cb[adr] do
    switch cbe.State
      case directoryL1_1_E__C__V:
      switch inmsg.mtype
        case GetML1_1:
          msg_GetOL1_2 := RequestL1_2(adr,GetOL1_2,m,m);
          msg_GetO_AckL1_2 := RespL1_2(adr,GetO_AckL1_2,m,msg_GetOL1_2.src,cbe.cl);
          cbe.ownerL1_2 := msg_GetOL1_2.src;
          cbe.cl := msg_GetO_AckL1_2.cl;
          Set_perm(store, adr, m);
          msg_PutOL1_2 := RespL1_2(adr,PutOL1_2,m,m,cbe.cl);
          msg_PutO_AckL1_2 := AckL1_2(adr,PutO_AckL1_2,m,msg_PutOL1_2.src);
          if (cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.cl := msg_PutOL1_2.cl;
            cbe.proxy_msg := inmsg;
            msg := RequestL1_1(adr,Fwd_GetML1_1,cbe.proxy_msg.src,cbe.ownerL1_1);
            Send_fwd(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
          if !(cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.proxy_msg := inmsg;
            msg := RequestL1_1(adr,Fwd_GetML1_1,cbe.proxy_msg.src,cbe.ownerL1_1);
            Send_fwd(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
        
        case GetOL1_2:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          msg := RequestL1_1(adr,Fwd_GetML1_1,msg_GetML1_1.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          cbe.ownerL1_1 := msg_GetML1_1.src;
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetOL1_2dM_x_pI_store__C__V;
          return true;
        
        case GetOL1_2release:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          msg := RequestL1_1(adr,Fwd_GetML1_1,msg_GetML1_1.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          cbe.ownerL1_1 := msg_GetML1_1.src;
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetOL1_2releasedM_x_pI_store__C__V;
          return true;
        
        case GetSL1_1:
          msg_GetVL1_2 := RequestL1_2(adr,GetVL1_2,m,m);
          msg_GetV_AckL1_2 := RespL1_2(adr,GetV_AckL1_2,m,msg_GetVL1_2.src,cbe.cl);
          cbe.cl := msg_GetV_AckL1_2.cl;
          cbe.proxy_msg := inmsg;
          msg := RequestL1_1(adr,Fwd_GetSL1_1,cbe.proxy_msg.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          AddElement_cacheL1_1(cbe.cacheL1_1, cbe.proxy_msg.src);
          AddElement_cacheL1_1(cbe.cacheL1_1, cbe.ownerL1_1);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetSL1_1E_GetS__C__V;
          return true;
        
        case GetVL1_2:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg := RequestL1_1(adr,Fwd_GetSL1_1,msg_GetSL1_1.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          AddElement_cacheL1_1(cbe.cacheL1_1, msg_GetSL1_1.src);
          AddElement_cacheL1_1(cbe.cacheL1_1, cbe.ownerL1_1);
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2dE_GetS_x_pI_load__C__V;
          return true;
        
        case GetVL1_2acquire:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg := RequestL1_1(adr,Fwd_GetSL1_1,msg_GetSL1_1.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          AddElement_cacheL1_1(cbe.cacheL1_1, msg_GetSL1_1.src);
          AddElement_cacheL1_1(cbe.cacheL1_1, cbe.ownerL1_1);
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2acquiredE_GetS_x_pI_load__C__V;
          return true;
        
        case PutEL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_E__C__V;
            return true;
          endif;
          if (cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        case PutML1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if (cbe.ownerL1_1 = inmsg.src) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_E__C__V;
            return true;
          endif;
        
        case PutOL1_2:
          msg := AckL1_2(adr,PutO_AckL1_2,m,inmsg.src);
          Send_fwd(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_E__C__V;
          return true;
        
        case PutSL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if (cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_E__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetML1_1I__C__dO_GetO_x_pI_release:
      switch inmsg.mtype
        case WB_AckL1_2:
          msg_GetO_AckL1_2 := RespL1_2(adr,GetO_AckL1_2,m,inmsg.src,inmsg.cl);
          cbe.cl := msg_GetO_AckL1_2.cl;
          Set_perm(store, adr, m);
          msg_PutOL1_2 := RespL1_2(adr,PutOL1_2,m,m,cbe.cl);
          msg_PutO_AckL1_2 := AckL1_2(adr,PutO_AckL1_2,m,msg_PutOL1_2.src);
          if !(cbe.ownerL1_2 = msg_PutOL1_2.src) then
            msg := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,cbe.proxy_msg.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
            Send_resp(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
          if (cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.cl := msg_PutOL1_2.cl;
            msg := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,cbe.proxy_msg.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
            Send_resp(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetOL1_2I__C__O_GetO:
      switch inmsg.mtype
        case WB_AckL1_2:
          msg := RespL1_2(adr,GetO_AckL1_2,m,inmsg.src,inmsg.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__O;
          return true;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetOL1_2dM_x_pI_store_GetM_Ack_AD__C__V:
      switch inmsg.mtype
        case Inv_AckL1_1:
          cbe.acksReceivedL1_1 := cbe.acksReceivedL1_1+1;
          if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_GetOL1_2dM_x_pI_store_GetM_Ack_AD__C__V;
            return true;
          endif;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Set_perm(store, adr, m);
            msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
            msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
            RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
            if (cbe.ownerL1_1 = msg_PutML1_1.src) then
            cbe.cl := msg_PutML1_1.cl;
            msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            cbe.ownerL1_2 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__O;
            return true;
            endif;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetOL1_2dM_x_pI_store__C__V:
      switch inmsg.mtype
        case GetM_Ack_DL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(store, adr, m);
          msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
          if (cbe.ownerL1_1 = msg_PutML1_1.src) then
          cbe.cl := msg_PutML1_1.cl;
          msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
          Send_resp(msg, m);
          cbe.ownerL1_2 := cbe.proxy_msg.src;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__O;
          return true;
          endif;
        
        case Inv_AckL1_1:
          cbe.acksReceivedL1_1 := cbe.acksReceivedL1_1+1;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetOL1_2dM_x_pI_store__C__V;
          return true;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetOL1_2releaseI__C__O_GetO:
      switch inmsg.mtype
        case WB_AckL1_2:
          msg := RespL1_2(adr,GetO_AckL1_2,m,inmsg.src,inmsg.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__O;
          return true;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetOL1_2releasedM_x_pI_store_GetM_Ack_AD__C__V:
      switch inmsg.mtype
        case Inv_AckL1_1:
          cbe.acksReceivedL1_1 := cbe.acksReceivedL1_1+1;
          if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_GetOL1_2releasedM_x_pI_store_GetM_Ack_AD__C__V;
            return true;
          endif;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Set_perm(store, adr, m);
            msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
            msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
            RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
            if (cbe.ownerL1_1 = msg_PutML1_1.src) then
            cbe.cl := msg_PutML1_1.cl;
            msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            cbe.ownerL1_2 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__O;
            return true;
            endif;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetOL1_2releasedM_x_pI_store__C__V:
      switch inmsg.mtype
        case GetM_Ack_DL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(store, adr, m);
          msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
          if (cbe.ownerL1_1 = msg_PutML1_1.src) then
          cbe.cl := msg_PutML1_1.cl;
          msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
          Send_resp(msg, m);
          cbe.ownerL1_2 := cbe.proxy_msg.src;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__O;
          return true;
          endif;
        
        case Inv_AckL1_1:
          cbe.acksReceivedL1_1 := cbe.acksReceivedL1_1+1;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetOL1_2releasedM_x_pI_store__C__V;
          return true;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetSL1_1E_GetS__C__V:
      switch inmsg.mtype
        case WBL1_1:
          if !(inmsg.src = cbe.ownerL1_1) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_GetSL1_1E_GetS__C__V;
            return true;
          endif;
          if (inmsg.src = cbe.ownerL1_1) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetSL1_1I__C__dO_GetO_x_pI_release:
      switch inmsg.mtype
        case WB_AckL1_2:
          msg_GetO_AckL1_2 := RespL1_2(adr,GetO_AckL1_2,m,inmsg.src,inmsg.cl);
          cbe.cl := msg_GetO_AckL1_2.cl;
          Set_perm(store, adr, m);
          msg_PutOL1_2 := RespL1_2(adr,PutOL1_2,m,m,cbe.cl);
          msg_PutO_AckL1_2 := AckL1_2(adr,PutO_AckL1_2,m,msg_PutOL1_2.src);
          if !(cbe.ownerL1_2 = msg_PutOL1_2.src) then
            msg := RespL1_1(adr,GetM_Ack_DL1_1,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_E__C__V;
            return true;
          endif;
          if (cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.cl := msg_PutOL1_2.cl;
            msg := RespL1_1(adr,GetM_Ack_DL1_1,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_E__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetSL1_1M_GetS__C__V:
      switch inmsg.mtype
        case WBL1_1:
          if (inmsg.src = cbe.ownerL1_1) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          if !(inmsg.src = cbe.ownerL1_1) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_GetSL1_1M_GetS__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2I__C__O_GetV:
      switch inmsg.mtype
        case WB_AckL1_2:
          cbe.cl := inmsg.cl;
          msg := RespL1_2(adr,GetV_AckL1_2,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__V;
          return true;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2acquireI__C__O_GetV:
      switch inmsg.mtype
        case WB_AckL1_2:
          cbe.cl := inmsg.cl;
          msg := RespL1_2(adr,GetV_AckL1_2,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__V;
          return true;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2acquiredE_GetS_x_pI_load__C__V:
      switch inmsg.mtype
        case GetS_AckL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(load, adr, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2acquiredE_GetS_x_pS__C__V;
          return true;
        
        case WBL1_1:
          if (inmsg.src = cbe.ownerL1_1) then
          cbe.cl := inmsg.cl;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2acquiredS_x_pI_load__C__V;
          return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2acquiredE_GetS_x_pS__C__V:
      switch inmsg.mtype
        case WBL1_1:
          if (inmsg.src = cbe.ownerL1_1) then
          cbe.cl := inmsg.cl;
          msg_PutSL1_1 := RequestL1_1(adr,PutSL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutSL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutSL1_1.src);
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2acquiredM_GetS_x_pI_load__C__V:
      switch inmsg.mtype
        case GetS_AckL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(load, adr, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2acquiredM_GetS_x_pS__C__V;
          return true;
        
        case WBL1_1:
          if (inmsg.src = cbe.ownerL1_1) then
          cbe.cl := inmsg.cl;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2acquiredS_x_pI_load__C__V;
          return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2acquiredM_GetS_x_pS__C__V:
      switch inmsg.mtype
        case WBL1_1:
          if (inmsg.src = cbe.ownerL1_1) then
          cbe.cl := inmsg.cl;
          msg_PutSL1_1 := RequestL1_1(adr,PutSL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutSL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutSL1_1.src);
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2acquiredS_x_pI_load__C__V:
      switch inmsg.mtype
        case GetS_AckL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(load, adr, m);
          msg_PutSL1_1 := RequestL1_1(adr,PutSL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutSL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutSL1_1.src);
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2dE_GetS_x_pI_load__C__V:
      switch inmsg.mtype
        case GetS_AckL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(load, adr, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2dE_GetS_x_pS__C__V;
          return true;
        
        case WBL1_1:
          if (inmsg.src = cbe.ownerL1_1) then
          cbe.cl := inmsg.cl;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2dS_x_pI_load__C__V;
          return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2dE_GetS_x_pS__C__V:
      switch inmsg.mtype
        case WBL1_1:
          if (inmsg.src = cbe.ownerL1_1) then
          cbe.cl := inmsg.cl;
          msg_PutSL1_1 := RequestL1_1(adr,PutSL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutSL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutSL1_1.src);
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2dM_GetS_x_pI_load__C__V:
      switch inmsg.mtype
        case GetS_AckL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(load, adr, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2dM_GetS_x_pS__C__V;
          return true;
        
        case WBL1_1:
          if (inmsg.src = cbe.ownerL1_1) then
          cbe.cl := inmsg.cl;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2dS_x_pI_load__C__V;
          return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2dM_GetS_x_pS__C__V:
      switch inmsg.mtype
        case WBL1_1:
          if (inmsg.src = cbe.ownerL1_1) then
          cbe.cl := inmsg.cl;
          msg_PutSL1_1 := RequestL1_1(adr,PutSL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutSL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutSL1_1.src);
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_GetVL1_2dS_x_pI_load__C__V:
      switch inmsg.mtype
        case GetS_AckL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(load, adr, m);
          msg_PutSL1_1 := RequestL1_1(adr,PutSL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutSL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutSL1_1.src);
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_I__C__O:
      switch inmsg.mtype
        case GetML1_1:
          msg_GetOL1_2 := RequestL1_2(adr,GetOL1_2,m,m);
          msg := RequestL1_2(adr,Fwd_GetOL1_2,msg_GetOL1_2.src,cbe.ownerL1_2);
          Send_fwd(msg, m);
          cbe.ownerL1_2 := msg_GetOL1_2.src;
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetML1_1I__C__dO_GetO_x_pI_release;
          return true;
        
        case GetOL1_2:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          msg_GetM_Ack_ADL1_1 := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,msg_GetML1_1.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
          cbe.ownerL1_1 := msg_GetML1_1.src;
          cbe.cl := msg_GetM_Ack_ADL1_1.cl;
          cbe.acksExpectedL1_1 := msg_GetM_Ack_ADL1_1.acksExpectedL1_1;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
          Set_perm(store, adr, m);
          msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
          if (cbe.ownerL1_1 = msg_PutML1_1.src) then
          cbe.cl := msg_PutML1_1.cl;
          cbe.proxy_msg := inmsg;
          msg := RequestL1_2(adr,Fwd_GetOL1_2,cbe.proxy_msg.src,cbe.ownerL1_2);
          Send_fwd(msg, m);
          cbe.ownerL1_2 := cbe.proxy_msg.src;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetOL1_2I__C__O_GetO;
          return true;
          endif;
          endif;
        
        case GetOL1_2release:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          msg_GetM_Ack_ADL1_1 := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,msg_GetML1_1.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
          cbe.ownerL1_1 := msg_GetML1_1.src;
          cbe.cl := msg_GetM_Ack_ADL1_1.cl;
          cbe.acksExpectedL1_1 := msg_GetM_Ack_ADL1_1.acksExpectedL1_1;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
          Set_perm(store, adr, m);
          msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
          if (cbe.ownerL1_1 = msg_PutML1_1.src) then
          cbe.cl := msg_PutML1_1.cl;
          cbe.proxy_msg := inmsg;
          msg := RequestL1_2(adr,Fwd_GetOL1_2,cbe.proxy_msg.src,cbe.ownerL1_2);
          Send_fwd(msg, m);
          cbe.ownerL1_2 := cbe.proxy_msg.src;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetOL1_2releaseI__C__O_GetO;
          return true;
          endif;
          endif;
        
        case GetSL1_1:
          msg_GetOL1_2 := RequestL1_2(adr,GetOL1_2,m,m);
          msg := RequestL1_2(adr,Fwd_GetOL1_2,msg_GetOL1_2.src,cbe.ownerL1_2);
          Send_fwd(msg, m);
          cbe.ownerL1_2 := msg_GetOL1_2.src;
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetSL1_1I__C__dO_GetO_x_pI_release;
          return true;
        
        case GetVL1_2:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg_GetM_Ack_DL1_1 := RespL1_1(adr,GetM_Ack_DL1_1,m,msg_GetSL1_1.src,cbe.cl);
          cbe.ownerL1_1 := msg_GetSL1_1.src;
          cbe.cl := msg_GetM_Ack_DL1_1.cl;
          Set_perm(load, adr, m);
          msg_PutEL1_1 := AckL1_1(adr,PutEL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutEL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutEL1_1.src);
          if (cbe.ownerL1_1 = msg_PutEL1_1.src) then
          cbe.proxy_msg := inmsg;
          msg := RequestL1_2(adr,Fwd_GetOL1_2,cbe.proxy_msg.src,cbe.ownerL1_2);
          Send_fwd(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2I__C__O_GetV;
          return true;
          endif;
        
        case GetVL1_2acquire:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg_GetM_Ack_DL1_1 := RespL1_1(adr,GetM_Ack_DL1_1,m,msg_GetSL1_1.src,cbe.cl);
          cbe.ownerL1_1 := msg_GetSL1_1.src;
          cbe.cl := msg_GetM_Ack_DL1_1.cl;
          Set_perm(load, adr, m);
          msg_PutEL1_1 := AckL1_1(adr,PutEL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutEL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutEL1_1.src);
          if (cbe.ownerL1_1 = msg_PutEL1_1.src) then
          cbe.proxy_msg := inmsg;
          msg := RequestL1_2(adr,Fwd_GetOL1_2,cbe.proxy_msg.src,cbe.ownerL1_2);
          Send_fwd(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2acquireI__C__O_GetV;
          return true;
          endif;
        
        case PutEL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if (cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__O;
            return true;
          endif;
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__O;
            return true;
          endif;
        
        case PutML1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if (cbe.ownerL1_1 = inmsg.src) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__O;
            return true;
          endif;
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__O;
            return true;
          endif;
        
        case PutOL1_2:
          msg := AckL1_2(adr,PutO_AckL1_2,m,inmsg.src);
          Send_fwd(msg, m);
          if (cbe.ownerL1_2 = inmsg.src) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(cbe.ownerL1_2 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        case PutSL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__O;
            return true;
          endif;
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__O;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_I__C__V:
      switch inmsg.mtype
        case GetML1_1:
          msg_GetOL1_2 := RequestL1_2(adr,GetOL1_2,m,m);
          msg_GetO_AckL1_2 := RespL1_2(adr,GetO_AckL1_2,m,msg_GetOL1_2.src,cbe.cl);
          cbe.ownerL1_2 := msg_GetOL1_2.src;
          cbe.cl := msg_GetO_AckL1_2.cl;
          Set_perm(store, adr, m);
          msg_PutOL1_2 := RespL1_2(adr,PutOL1_2,m,m,cbe.cl);
          msg_PutO_AckL1_2 := AckL1_2(adr,PutO_AckL1_2,m,msg_PutOL1_2.src);
          if (cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.cl := msg_PutOL1_2.cl;
            cbe.proxy_msg := inmsg;
            msg := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,cbe.proxy_msg.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
            Send_resp(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
          if !(cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.proxy_msg := inmsg;
            msg := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,cbe.proxy_msg.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
            Send_resp(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
        
        case GetOL1_2:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          msg_GetM_Ack_ADL1_1 := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,msg_GetML1_1.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
          cbe.ownerL1_1 := msg_GetML1_1.src;
          cbe.cl := msg_GetM_Ack_ADL1_1.cl;
          cbe.acksExpectedL1_1 := msg_GetM_Ack_ADL1_1.acksExpectedL1_1;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
          Set_perm(store, adr, m);
          msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
          if (cbe.ownerL1_1 = msg_PutML1_1.src) then
          cbe.cl := msg_PutML1_1.cl;
          cbe.proxy_msg := inmsg;
          msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
          Send_resp(msg, m);
          cbe.ownerL1_2 := cbe.proxy_msg.src;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__O;
          return true;
          endif;
          endif;
        
        case GetOL1_2release:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          msg_GetM_Ack_ADL1_1 := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,msg_GetML1_1.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
          cbe.ownerL1_1 := msg_GetML1_1.src;
          cbe.cl := msg_GetM_Ack_ADL1_1.cl;
          cbe.acksExpectedL1_1 := msg_GetM_Ack_ADL1_1.acksExpectedL1_1;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
          Set_perm(store, adr, m);
          msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
          if (cbe.ownerL1_1 = msg_PutML1_1.src) then
          cbe.cl := msg_PutML1_1.cl;
          cbe.proxy_msg := inmsg;
          msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
          Send_resp(msg, m);
          cbe.ownerL1_2 := cbe.proxy_msg.src;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__O;
          return true;
          endif;
          endif;
        
        case GetSL1_1:
          msg_GetOL1_2 := RequestL1_2(adr,GetOL1_2,m,m);
          msg_GetO_AckL1_2 := RespL1_2(adr,GetO_AckL1_2,m,msg_GetOL1_2.src,cbe.cl);
          cbe.ownerL1_2 := msg_GetOL1_2.src;
          cbe.cl := msg_GetO_AckL1_2.cl;
          Set_perm(store, adr, m);
          msg_PutOL1_2 := RespL1_2(adr,PutOL1_2,m,m,cbe.cl);
          msg_PutO_AckL1_2 := AckL1_2(adr,PutO_AckL1_2,m,msg_PutOL1_2.src);
          if !(cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.proxy_msg := inmsg;
            msg := RespL1_1(adr,GetM_Ack_DL1_1,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_E__C__V;
            return true;
          endif;
          if (cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.cl := msg_PutOL1_2.cl;
            cbe.proxy_msg := inmsg;
            msg := RespL1_1(adr,GetM_Ack_DL1_1,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_E__C__V;
            return true;
          endif;
        
        case GetVL1_2:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg_GetM_Ack_DL1_1 := RespL1_1(adr,GetM_Ack_DL1_1,m,msg_GetSL1_1.src,cbe.cl);
          cbe.ownerL1_1 := msg_GetSL1_1.src;
          cbe.cl := msg_GetM_Ack_DL1_1.cl;
          Set_perm(load, adr, m);
          msg_PutEL1_1 := AckL1_1(adr,PutEL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutEL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutEL1_1.src);
          if (cbe.ownerL1_1 = msg_PutEL1_1.src) then
          cbe.proxy_msg := inmsg;
          msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__V;
          return true;
          endif;
        
        case GetVL1_2acquire:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg_GetM_Ack_DL1_1 := RespL1_1(adr,GetM_Ack_DL1_1,m,msg_GetSL1_1.src,cbe.cl);
          cbe.ownerL1_1 := msg_GetSL1_1.src;
          cbe.cl := msg_GetM_Ack_DL1_1.cl;
          Set_perm(load, adr, m);
          msg_PutEL1_1 := AckL1_1(adr,PutEL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutEL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutEL1_1.src);
          if (cbe.ownerL1_1 = msg_PutEL1_1.src) then
          cbe.proxy_msg := inmsg;
          msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__V;
          return true;
          endif;
        
        case PutEL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if (cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        case PutML1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if (cbe.ownerL1_1 = inmsg.src) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        case PutOL1_2:
          msg := AckL1_2(adr,PutO_AckL1_2,m,inmsg.src);
          Send_fwd(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_I__C__V;
          return true;
        
        case PutSL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_M__C__V:
      switch inmsg.mtype
        case GetML1_1:
          msg_GetOL1_2 := RequestL1_2(adr,GetOL1_2,m,m);
          msg_GetO_AckL1_2 := RespL1_2(adr,GetO_AckL1_2,m,msg_GetOL1_2.src,cbe.cl);
          cbe.ownerL1_2 := msg_GetOL1_2.src;
          cbe.cl := msg_GetO_AckL1_2.cl;
          Set_perm(store, adr, m);
          msg_PutOL1_2 := RespL1_2(adr,PutOL1_2,m,m,cbe.cl);
          msg_PutO_AckL1_2 := AckL1_2(adr,PutO_AckL1_2,m,msg_PutOL1_2.src);
          if !(cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.proxy_msg := inmsg;
            msg := RequestL1_1(adr,Fwd_GetML1_1,cbe.proxy_msg.src,cbe.ownerL1_1);
            Send_fwd(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
          if (cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.cl := msg_PutOL1_2.cl;
            cbe.proxy_msg := inmsg;
            msg := RequestL1_1(adr,Fwd_GetML1_1,cbe.proxy_msg.src,cbe.ownerL1_1);
            Send_fwd(msg, m);
            cbe.ownerL1_1 := cbe.proxy_msg.src;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
        
        case GetOL1_2:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          msg := RequestL1_1(adr,Fwd_GetML1_1,msg_GetML1_1.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          cbe.ownerL1_1 := msg_GetML1_1.src;
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetOL1_2dM_x_pI_store__C__V;
          return true;
        
        case GetOL1_2release:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          msg := RequestL1_1(adr,Fwd_GetML1_1,msg_GetML1_1.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          cbe.ownerL1_1 := msg_GetML1_1.src;
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetOL1_2releasedM_x_pI_store__C__V;
          return true;
        
        case GetSL1_1:
          msg_GetVL1_2 := RequestL1_2(adr,GetVL1_2,m,m);
          msg_GetV_AckL1_2 := RespL1_2(adr,GetV_AckL1_2,m,msg_GetVL1_2.src,cbe.cl);
          cbe.cl := msg_GetV_AckL1_2.cl;
          cbe.proxy_msg := inmsg;
          msg := RequestL1_1(adr,Fwd_GetSL1_1,cbe.proxy_msg.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          AddElement_cacheL1_1(cbe.cacheL1_1, cbe.proxy_msg.src);
          AddElement_cacheL1_1(cbe.cacheL1_1, cbe.ownerL1_1);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetSL1_1M_GetS__C__V;
          return true;
        
        case GetVL1_2:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg := RequestL1_1(adr,Fwd_GetSL1_1,msg_GetSL1_1.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          AddElement_cacheL1_1(cbe.cacheL1_1, msg_GetSL1_1.src);
          AddElement_cacheL1_1(cbe.cacheL1_1, cbe.ownerL1_1);
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2dM_GetS_x_pI_load__C__V;
          return true;
        
        case GetVL1_2acquire:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg := RequestL1_1(adr,Fwd_GetSL1_1,msg_GetSL1_1.src,cbe.ownerL1_1);
          Send_fwd(msg, m);
          AddElement_cacheL1_1(cbe.cacheL1_1, msg_GetSL1_1.src);
          AddElement_cacheL1_1(cbe.cacheL1_1, cbe.ownerL1_1);
          cbe.proxy_msg := inmsg;
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_GetVL1_2acquiredM_GetS_x_pI_load__C__V;
          return true;
        
        case PutEL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
          if (cbe.ownerL1_1 = inmsg.src) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        case PutML1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if (cbe.ownerL1_1 = inmsg.src) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
        
        case PutOL1_2:
          msg := AckL1_2(adr,PutO_AckL1_2,m,inmsg.src);
          Send_fwd(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_M__C__V;
          return true;
        
        case PutSL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if !(cbe.ownerL1_1 = inmsg.src) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_M__C__V;
            return true;
          endif;
          if (cbe.ownerL1_1 = inmsg.src) then
            cbe.cl := inmsg.cl;
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case directoryL1_1_S__C__V:
      switch inmsg.mtype
        case GetML1_1:
          msg_GetOL1_2 := RequestL1_2(adr,GetOL1_2,m,m);
          msg_GetO_AckL1_2 := RespL1_2(adr,GetO_AckL1_2,m,msg_GetOL1_2.src,cbe.cl);
          cbe.ownerL1_2 := msg_GetOL1_2.src;
          cbe.cl := msg_GetO_AckL1_2.cl;
          Set_perm(store, adr, m);
          msg_PutOL1_2 := RespL1_2(adr,PutOL1_2,m,m,cbe.cl);
          msg_PutO_AckL1_2 := AckL1_2(adr,PutO_AckL1_2,m,msg_PutOL1_2.src);
          if (cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.cl := msg_PutOL1_2.cl;
            cbe.proxy_msg := inmsg;
            if !(IsElement_cacheL1_1(cbe.cacheL1_1, cbe.proxy_msg.src)) then
              msg := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,cbe.proxy_msg.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
              Send_resp(msg, m);
              msg := AckL1_1(adr,InvL1_1,cbe.proxy_msg.src,cbe.proxy_msg.src);
              Multicast_fwd_v_cacheL1_1(msg, cbe.cacheL1_1, m);
              cbe.ownerL1_1 := cbe.proxy_msg.src;
              ClearVector_cacheL1_1(cbe.cacheL1_1);
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_M__C__V;
              return true;
            endif;
            if (IsElement_cacheL1_1(cbe.cacheL1_1, cbe.proxy_msg.src)) then
              RemoveElement_cacheL1_1(cbe.cacheL1_1, cbe.proxy_msg.src);
              msg := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,cbe.proxy_msg.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
              Send_resp(msg, m);
              msg := AckL1_1(adr,InvL1_1,cbe.proxy_msg.src,cbe.proxy_msg.src);
              Multicast_fwd_v_cacheL1_1(msg, cbe.cacheL1_1, m);
              cbe.ownerL1_1 := cbe.proxy_msg.src;
              ClearVector_cacheL1_1(cbe.cacheL1_1);
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_M__C__V;
              return true;
            endif;
          endif;
          if !(cbe.ownerL1_2 = msg_PutOL1_2.src) then
            cbe.proxy_msg := inmsg;
            if !(IsElement_cacheL1_1(cbe.cacheL1_1, cbe.proxy_msg.src)) then
              msg := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,cbe.proxy_msg.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
              Send_resp(msg, m);
              msg := AckL1_1(adr,InvL1_1,cbe.proxy_msg.src,cbe.proxy_msg.src);
              Multicast_fwd_v_cacheL1_1(msg, cbe.cacheL1_1, m);
              cbe.ownerL1_1 := cbe.proxy_msg.src;
              ClearVector_cacheL1_1(cbe.cacheL1_1);
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_M__C__V;
              return true;
            endif;
            if (IsElement_cacheL1_1(cbe.cacheL1_1, cbe.proxy_msg.src)) then
              RemoveElement_cacheL1_1(cbe.cacheL1_1, cbe.proxy_msg.src);
              msg := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,cbe.proxy_msg.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
              Send_resp(msg, m);
              msg := AckL1_1(adr,InvL1_1,cbe.proxy_msg.src,cbe.proxy_msg.src);
              Multicast_fwd_v_cacheL1_1(msg, cbe.cacheL1_1, m);
              cbe.ownerL1_1 := cbe.proxy_msg.src;
              ClearVector_cacheL1_1(cbe.cacheL1_1);
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_M__C__V;
              return true;
            endif;
          endif;
        
        case GetOL1_2:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          if !(IsElement_cacheL1_1(cbe.cacheL1_1, msg_GetML1_1.src)) then
            msg_GetM_Ack_ADL1_1 := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,msg_GetML1_1.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
            msg := AckL1_1(adr,InvL1_1,msg_GetML1_1.src,msg_GetML1_1.src);
            Multicast_fwd_v_cacheL1_1(msg, cbe.cacheL1_1, m);
            cbe.ownerL1_1 := msg_GetML1_1.src;
            ClearVector_cacheL1_1(cbe.cacheL1_1);
            cbe.cl := msg_GetM_Ack_ADL1_1.cl;
            cbe.acksExpectedL1_1 := msg_GetM_Ack_ADL1_1.acksExpectedL1_1;
            if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
              Set_perm(store, adr, m);
              msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
              msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
              RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
              if (cbe.ownerL1_1 = msg_PutML1_1.src) then
              cbe.cl := msg_PutML1_1.cl;
              cbe.proxy_msg := inmsg;
              msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
              Send_resp(msg, m);
              cbe.ownerL1_2 := cbe.proxy_msg.src;
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_I__C__O;
              return true;
              endif;
            endif;
            if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
              cbe.proxy_msg := inmsg;
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_GetOL1_2dM_x_pI_store_GetM_Ack_AD__C__V;
              return true;
            endif;
          endif;
          if (IsElement_cacheL1_1(cbe.cacheL1_1, msg_GetML1_1.src)) then
            RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_GetML1_1.src);
            msg_GetM_Ack_ADL1_1 := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,msg_GetML1_1.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
            msg := AckL1_1(adr,InvL1_1,msg_GetML1_1.src,msg_GetML1_1.src);
            Multicast_fwd_v_cacheL1_1(msg, cbe.cacheL1_1, m);
            cbe.ownerL1_1 := msg_GetML1_1.src;
            ClearVector_cacheL1_1(cbe.cacheL1_1);
            cbe.cl := msg_GetM_Ack_ADL1_1.cl;
            cbe.acksExpectedL1_1 := msg_GetM_Ack_ADL1_1.acksExpectedL1_1;
            if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
              Set_perm(store, adr, m);
              msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
              msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
              RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
              if (cbe.ownerL1_1 = msg_PutML1_1.src) then
              cbe.cl := msg_PutML1_1.cl;
              cbe.proxy_msg := inmsg;
              msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
              Send_resp(msg, m);
              cbe.ownerL1_2 := cbe.proxy_msg.src;
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_I__C__O;
              return true;
              endif;
            endif;
            if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
              cbe.proxy_msg := inmsg;
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_GetOL1_2dM_x_pI_store_GetM_Ack_AD__C__V;
              return true;
            endif;
          endif;
        
        case GetOL1_2release:
          msg_GetML1_1 := RequestL1_1(adr,GetML1_1,m,m);
          cbe.acksReceivedL1_1 := 0;
          if !(IsElement_cacheL1_1(cbe.cacheL1_1, msg_GetML1_1.src)) then
            msg_GetM_Ack_ADL1_1 := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,msg_GetML1_1.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
            msg := AckL1_1(adr,InvL1_1,msg_GetML1_1.src,msg_GetML1_1.src);
            Multicast_fwd_v_cacheL1_1(msg, cbe.cacheL1_1, m);
            cbe.ownerL1_1 := msg_GetML1_1.src;
            ClearVector_cacheL1_1(cbe.cacheL1_1);
            cbe.cl := msg_GetM_Ack_ADL1_1.cl;
            cbe.acksExpectedL1_1 := msg_GetM_Ack_ADL1_1.acksExpectedL1_1;
            if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
              Set_perm(store, adr, m);
              msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
              msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
              RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
              if (cbe.ownerL1_1 = msg_PutML1_1.src) then
              cbe.cl := msg_PutML1_1.cl;
              cbe.proxy_msg := inmsg;
              msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
              Send_resp(msg, m);
              cbe.ownerL1_2 := cbe.proxy_msg.src;
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_I__C__O;
              return true;
              endif;
            endif;
            if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
              cbe.proxy_msg := inmsg;
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_GetOL1_2releasedM_x_pI_store_GetM_Ack_AD__C__V;
              return true;
            endif;
          endif;
          if (IsElement_cacheL1_1(cbe.cacheL1_1, msg_GetML1_1.src)) then
            RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_GetML1_1.src);
            msg_GetM_Ack_ADL1_1 := RespAckL1_1(adr,GetM_Ack_ADL1_1,m,msg_GetML1_1.src,cbe.cl,VectorCount_cacheL1_1(cbe.cacheL1_1));
            msg := AckL1_1(adr,InvL1_1,msg_GetML1_1.src,msg_GetML1_1.src);
            Multicast_fwd_v_cacheL1_1(msg, cbe.cacheL1_1, m);
            cbe.ownerL1_1 := msg_GetML1_1.src;
            ClearVector_cacheL1_1(cbe.cacheL1_1);
            cbe.cl := msg_GetM_Ack_ADL1_1.cl;
            cbe.acksExpectedL1_1 := msg_GetM_Ack_ADL1_1.acksExpectedL1_1;
            if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
              cbe.proxy_msg := inmsg;
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_GetOL1_2releasedM_x_pI_store_GetM_Ack_AD__C__V;
              return true;
            endif;
            if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
              Set_perm(store, adr, m);
              msg_PutML1_1 := RespL1_1(adr,PutML1_1,m,m,cbe.cl);
              msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutML1_1.src);
              RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutML1_1.src);
              if (cbe.ownerL1_1 = msg_PutML1_1.src) then
              cbe.cl := msg_PutML1_1.cl;
              cbe.proxy_msg := inmsg;
              msg := RespL1_2(adr,GetO_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
              Send_resp(msg, m);
              cbe.ownerL1_2 := cbe.proxy_msg.src;
              Clear_perm(adr, m);
              cbe.State := directoryL1_1_I__C__O;
              return true;
              endif;
            endif;
          endif;
        
        case GetSL1_1:
          msg_GetVL1_2 := RequestL1_2(adr,GetVL1_2,m,m);
          msg_GetV_AckL1_2 := RespL1_2(adr,GetV_AckL1_2,m,msg_GetVL1_2.src,cbe.cl);
          cbe.cl := msg_GetV_AckL1_2.cl;
          cbe.proxy_msg := inmsg;
          msg := RespL1_1(adr,GetS_AckL1_1,m,cbe.proxy_msg.src,cbe.cl);
          Send_resp(msg, m);
          AddElement_cacheL1_1(cbe.cacheL1_1, cbe.proxy_msg.src);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_S__C__V;
          return true;
        
        case GetVL1_2:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg_GetS_AckL1_1 := RespL1_1(adr,GetS_AckL1_1,m,msg_GetSL1_1.src,cbe.cl);
          AddElement_cacheL1_1(cbe.cacheL1_1, msg_GetSL1_1.src);
          cbe.cl := msg_GetS_AckL1_1.cl;
          Set_perm(load, adr, m);
          msg_PutSL1_1 := RequestL1_1(adr,PutSL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutSL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutSL1_1.src);
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            cbe.proxy_msg := inmsg;
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            cbe.proxy_msg := inmsg;
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        case GetVL1_2acquire:
          msg_GetSL1_1 := RequestL1_1(adr,GetSL1_1,m,m);
          msg_GetS_AckL1_1 := RespL1_1(adr,GetS_AckL1_1,m,msg_GetSL1_1.src,cbe.cl);
          AddElement_cacheL1_1(cbe.cacheL1_1, msg_GetSL1_1.src);
          cbe.cl := msg_GetS_AckL1_1.cl;
          Set_perm(load, adr, m);
          msg_PutSL1_1 := RequestL1_1(adr,PutSL1_1,m,m);
          msg_Put_AckL1_1 := AckL1_1(adr,Put_AckL1_1,m,msg_PutSL1_1.src);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, msg_PutSL1_1.src);
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            cbe.proxy_msg := inmsg;
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            cbe.proxy_msg := inmsg;
            msg := RespL1_2(adr,GetV_AckL1_2,m,cbe.proxy_msg.src,cbe.cl);
            Send_resp(msg, m);
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        case PutEL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
        
        case PutML1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        case PutOL1_2:
          msg := AckL1_2(adr,PutO_AckL1_2,m,inmsg.src);
          Send_fwd(msg, m);
          Clear_perm(adr, m);
          cbe.State := directoryL1_1_S__C__V;
          return true;
        
        case PutSL1_1:
          msg := AckL1_1(adr,Put_AckL1_1,m,inmsg.src);
          Send_fwd(msg, m);
          RemoveElement_cacheL1_1(cbe.cacheL1_1, inmsg.src);
          if !(VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_S__C__V;
            return true;
          endif;
          if (VectorCount_cacheL1_1(cbe.cacheL1_1) = 0) then
            Clear_perm(adr, m);
            cbe.State := directoryL1_1_I__C__V;
            return true;
          endif;
        
        else return false;
      endswitch;
      
    endswitch;
    endalias;
    endalias;
    return false;
    end;
    
    function FSM_MSG_cacheL1_2(inmsg:Message; m:OBJSET_cacheL1_2) : boolean;
    var msg: Message;
    begin
      alias adr: inmsg.adr do
      alias cbe: i_cacheL1_2[m].cb[adr] do
    switch cbe.State
      case cacheL1_2_I:
      switch inmsg.mtype
        else return false;
      endswitch;
      
      case cacheL1_2_I_acquire:
      switch inmsg.mtype
        case GetV_AckL1_2:
          cbe.cl := inmsg.cl;
          IssueEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr);
          Clear_perm(adr, m);
          cbe.State := cacheL1_2_I_acquire_GetV_Ack;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_2_I_acquire_GetV_Ack:
      switch inmsg.mtype
        else return false;
      endswitch;
      
      case cacheL1_2_I_load:
      switch inmsg.mtype
        case GetV_AckL1_2:
          cbe.cl := inmsg.cl;
          Clear_perm(adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_2_V;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_2_I_release:
      switch inmsg.mtype
        case GetO_AckL1_2:
          cbe.cl := inmsg.cl;
          Set_perm(store, adr, m);
          Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_2_O;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_2_I_store:
      switch inmsg.mtype
        case GetO_AckL1_2:
          cbe.cl := inmsg.cl;
          Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_2_O;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_2_O:
      switch inmsg.mtype
        case Fwd_GetOL1_2:
          msg := RespL1_2(adr,WB_AckL1_2,inmsg.src,directoryL1_1,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_2_V;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_2_O_evict:
      switch inmsg.mtype
        case Fwd_GetOL1_2:
          msg := RespL1_2(adr,WB_AckL1_2,inmsg.src,directoryL1_1,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_2_O_evict_x_V;
          return true;
        
        case PutO_AckL1_2:
          Clear_perm(adr, m);
          cbe.State := cacheL1_2_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_2_O_evict_x_V:
      switch inmsg.mtype
        case PutO_AckL1_2:
          Clear_perm(adr, m);
          cbe.State := cacheL1_2_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_2_V:
      switch inmsg.mtype
        else return false;
      endswitch;
      
      case cacheL1_2_V_acquire:
      switch inmsg.mtype
        case GetV_AckL1_2:
          cbe.cl := inmsg.cl;
          IssueEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr);
          Clear_perm(adr, m);
          cbe.State := cacheL1_2_V_acquire_GetV_Ack;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_2_V_acquire_GetV_Ack:
      switch inmsg.mtype
        else return false;
      endswitch;
      
      case cacheL1_2_V_release:
      switch inmsg.mtype
        case GetO_AckL1_2:
          cbe.cl := inmsg.cl;
          Set_perm(store, adr, m);
          Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_2_O;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_2_V_store:
      switch inmsg.mtype
        case GetO_AckL1_2:
          cbe.cl := inmsg.cl;
          Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_2_O;
          return true;
        
        else return false;
      endswitch;
      
    endswitch;
    endalias;
    endalias;
    return false;
    end;
    
    function FSM_MSG_cacheL1_1(inmsg:Message; m:OBJSET_cacheL1_1) : boolean;
    var msg: Message;
    begin
      alias adr: inmsg.adr do
      alias cbe: i_cacheL1_1[m].cb[adr] do
    switch cbe.State
      case cacheL1_1_E:
      switch inmsg.mtype
        case Fwd_GetML1_1:
          msg := RespL1_1(adr,GetM_Ack_DL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I;
          return true;
        
        case Fwd_GetSL1_1:
          msg := RespL1_1(adr,GetS_AckL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          msg := RespL1_1(adr,WBL1_1,m,directoryL1_1,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_1_S;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_E_evict:
      switch inmsg.mtype
        case Fwd_GetML1_1:
          msg := RespL1_1(adr,GetM_Ack_DL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_E_evict_x_I;
          return true;
        
        case Fwd_GetSL1_1:
          msg := RespL1_1(adr,GetS_AckL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          msg := RespL1_1(adr,WBL1_1,m,directoryL1_1,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_S_evict;
          return true;
        
        case Put_AckL1_1:
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_E_evict_x_I:
      switch inmsg.mtype
        case Put_AckL1_1:
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_I:
      switch inmsg.mtype
        else return false;
      endswitch;
      
      case cacheL1_1_I_load:
      switch inmsg.mtype
        case GetM_Ack_DL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(load, adr, m);
          Clear_perm(adr, m); Set_perm(load, adr, m); Set_perm(store, adr, m);
          cbe.State := cacheL1_1_E;
          return true;
        
        case GetS_AckL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(load, adr, m);
          Clear_perm(adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_1_S;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_I_store:
      switch inmsg.mtype
        case GetM_Ack_ADL1_1:
          cbe.cl := inmsg.cl;
          cbe.acksExpectedL1_1 := inmsg.acksExpectedL1_1;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Set_perm(store, adr, m);
            Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
            cbe.State := cacheL1_1_M;
            return true;
          endif;
          if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Clear_perm(adr, m);
            cbe.State := cacheL1_1_I_store_GetM_Ack_AD;
            return true;
          endif;
        
        case GetM_Ack_DL1_1:
          cbe.cl := inmsg.cl;
          Set_perm(store, adr, m);
          Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_1_M;
          return true;
        
        case Inv_AckL1_1:
          cbe.acksReceivedL1_1 := cbe.acksReceivedL1_1+1;
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I_store;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_I_store_GetM_Ack_AD:
      switch inmsg.mtype
        case Inv_AckL1_1:
          cbe.acksReceivedL1_1 := cbe.acksReceivedL1_1+1;
          if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Clear_perm(adr, m);
            cbe.State := cacheL1_1_I_store_GetM_Ack_AD;
            return true;
          endif;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Set_perm(store, adr, m);
            Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
            cbe.State := cacheL1_1_M;
            return true;
          endif;
        
        else return false;
      endswitch;
      
      case cacheL1_1_M:
      switch inmsg.mtype
        case Fwd_GetML1_1:
          msg := RespL1_1(adr,GetM_Ack_DL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I;
          return true;
        
        case Fwd_GetSL1_1:
          msg := RespL1_1(adr,GetS_AckL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          msg := RespL1_1(adr,WBL1_1,m,directoryL1_1,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_1_S;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_M_evict:
      switch inmsg.mtype
        case Fwd_GetML1_1:
          msg := RespL1_1(adr,GetM_Ack_DL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_M_evict_x_I;
          return true;
        
        case Fwd_GetSL1_1:
          msg := RespL1_1(adr,GetS_AckL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          msg := RespL1_1(adr,WBL1_1,m,directoryL1_1,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_S_evict;
          return true;
        
        case Put_AckL1_1:
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_M_evict_x_I:
      switch inmsg.mtype
        case Put_AckL1_1:
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_S:
      switch inmsg.mtype
        case InvL1_1:
          msg := RespL1_1(adr,Inv_AckL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_S_evict:
      switch inmsg.mtype
        case InvL1_1:
          msg := RespL1_1(adr,Inv_AckL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_S_evict_x_I;
          return true;
        
        case Put_AckL1_1:
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_S_evict_x_I:
      switch inmsg.mtype
        case Put_AckL1_1:
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_S_store:
      switch inmsg.mtype
        case GetM_Ack_ADL1_1:
          cbe.acksExpectedL1_1 := inmsg.acksExpectedL1_1;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Set_perm(store, adr, m);
            Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
            cbe.State := cacheL1_1_M;
            return true;
          endif;
          if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Clear_perm(adr, m);
            cbe.State := cacheL1_1_S_store_GetM_Ack_AD;
            return true;
          endif;
        
        case GetM_Ack_DL1_1:
          Set_perm(store, adr, m);
          Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
          cbe.State := cacheL1_1_M;
          return true;
        
        case InvL1_1:
          msg := RespL1_1(adr,Inv_AckL1_1,m,inmsg.src,cbe.cl);
          Send_resp(msg, m);
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_I_store;
          return true;
        
        case Inv_AckL1_1:
          cbe.acksReceivedL1_1 := cbe.acksReceivedL1_1+1;
          Clear_perm(adr, m);
          cbe.State := cacheL1_1_S_store;
          return true;
        
        else return false;
      endswitch;
      
      case cacheL1_1_S_store_GetM_Ack_AD:
      switch inmsg.mtype
        case Inv_AckL1_1:
          cbe.acksReceivedL1_1 := cbe.acksReceivedL1_1+1;
          if !(cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Clear_perm(adr, m);
            cbe.State := cacheL1_1_S_store_GetM_Ack_AD;
            return true;
          endif;
          if (cbe.acksExpectedL1_1 = cbe.acksReceivedL1_1) then
            Set_perm(store, adr, m);
            Clear_perm(adr, m); Set_perm(store, adr, m); Set_perm(load, adr, m);
            cbe.State := cacheL1_1_M;
            return true;
          endif;
        
        else return false;
      endswitch;
      
    endswitch;
    endalias;
    endalias;
    return false;
    end;
    

--Backend/Murphi/MurphiModular/GenResetFunc

  procedure System_Reset();
  begin
  Reset_perm();
  Reset_NET_();
  ResetMachine_();
  ResetEvent_();
  end;
  

--Backend/Murphi/MurphiModular/GenRules
  ----Backend/Murphi/MurphiModular/Rules/GenAccessRuleSet
    ruleset m:OBJSET_cacheL1_2 do
    ruleset adr:Address do
      alias cbe:i_cacheL1_2[m].cb[adr] do
    
      rule "cacheL1_2_I_acquire"
        cbe.State = cacheL1_2_I & network_ready() & TestAtomicEvent_cacheL1_2(m)
      ==>
        FSM_Access_cacheL1_2_I_acquire(adr, m);
        LockAtomicEvent_cacheL1_2(m, adr);
      endrule;
    
      rule "cacheL1_2_I_load"
        cbe.State = cacheL1_2_I & network_ready() 
      ==>
        FSM_Access_cacheL1_2_I_load(adr, m);
        
      endrule;
    
      rule "cacheL1_2_I_release"
        cbe.State = cacheL1_2_I & network_ready() 
      ==>
        FSM_Access_cacheL1_2_I_release(adr, m);
        
      endrule;
    
      rule "cacheL1_2_I_store"
        cbe.State = cacheL1_2_I & network_ready() 
      ==>
        FSM_Access_cacheL1_2_I_store(adr, m);
        
      endrule;
    
      rule "cacheL1_2_O_store"
        cbe.State = cacheL1_2_O 
      ==>
        FSM_Access_cacheL1_2_O_store(adr, m);
        
      endrule;
    
      rule "cacheL1_2_O_load"
        cbe.State = cacheL1_2_O 
      ==>
        FSM_Access_cacheL1_2_O_load(adr, m);
        
      endrule;
    
      rule "cacheL1_2_O_acquire"
        cbe.State = cacheL1_2_O 
      ==>
        FSM_Access_cacheL1_2_O_acquire(adr, m);
        
      endrule;
    
      rule "cacheL1_2_O_evict"
        cbe.State = cacheL1_2_O & network_ready() 
      ==>
        FSM_Access_cacheL1_2_O_evict(adr, m);
        
      endrule;
    
      rule "cacheL1_2_O_release"
        cbe.State = cacheL1_2_O 
      ==>
        FSM_Access_cacheL1_2_O_release(adr, m);
        
      endrule;
    
      rule "cacheL1_2_V_load"
        cbe.State = cacheL1_2_V 
      ==>
        FSM_Access_cacheL1_2_V_load(adr, m);
        
      endrule;
    
      rule "cacheL1_2_V_store"
        cbe.State = cacheL1_2_V & network_ready() 
      ==>
        FSM_Access_cacheL1_2_V_store(adr, m);
        
      endrule;
    
      rule "cacheL1_2_V_release"
        cbe.State = cacheL1_2_V & network_ready() 
      ==>
        FSM_Access_cacheL1_2_V_release(adr, m);
        
      endrule;
    
      rule "cacheL1_2_V_acquire"
        cbe.State = cacheL1_2_V & network_ready() & TestAtomicEvent_cacheL1_2(m)
      ==>
        FSM_Access_cacheL1_2_V_acquire(adr, m);
        LockAtomicEvent_cacheL1_2(m, adr);
      endrule;
    
      rule "cacheL1_2_V_evict"
        cbe.State = cacheL1_2_V 
      ==>
        FSM_Access_cacheL1_2_V_evict(adr, m);
        
      endrule;
    
    
      endalias;
    endruleset;
    endruleset;
    
    ruleset m:OBJSET_cacheL1_1 do
    ruleset adr:Address do
      alias cbe:i_cacheL1_1[m].cb[adr] do
    
      rule "cacheL1_1_E_load"
        cbe.State = cacheL1_1_E 
      ==>
        FSM_Access_cacheL1_1_E_load(adr, m);
        
      endrule;
    
      rule "cacheL1_1_E_evict"
        cbe.State = cacheL1_1_E & network_ready() 
      ==>
        FSM_Access_cacheL1_1_E_evict(adr, m);
        
      endrule;
    
      rule "cacheL1_1_E_store"
        cbe.State = cacheL1_1_E 
      ==>
        FSM_Access_cacheL1_1_E_store(adr, m);
        
      endrule;
    
      rule "cacheL1_1_I_store"
        cbe.State = cacheL1_1_I & network_ready() 
      ==>
        FSM_Access_cacheL1_1_I_store(adr, m);
        
      endrule;
    
      rule "cacheL1_1_I_load"
        cbe.State = cacheL1_1_I & network_ready() 
      ==>
        FSM_Access_cacheL1_1_I_load(adr, m);
        
      endrule;
    
      rule "cacheL1_1_M_store"
        cbe.State = cacheL1_1_M 
      ==>
        FSM_Access_cacheL1_1_M_store(adr, m);
        
      endrule;
    
      rule "cacheL1_1_M_evict"
        cbe.State = cacheL1_1_M & network_ready() 
      ==>
        FSM_Access_cacheL1_1_M_evict(adr, m);
        
      endrule;
    
      rule "cacheL1_1_M_load"
        cbe.State = cacheL1_1_M 
      ==>
        FSM_Access_cacheL1_1_M_load(adr, m);
        
      endrule;
    
      rule "cacheL1_1_S_load"
        cbe.State = cacheL1_1_S 
      ==>
        FSM_Access_cacheL1_1_S_load(adr, m);
        
      endrule;
    
      rule "cacheL1_1_S_evict"
        cbe.State = cacheL1_1_S & network_ready() 
      ==>
        FSM_Access_cacheL1_1_S_evict(adr, m);
        
      endrule;
    
      rule "cacheL1_1_S_store"
        cbe.State = cacheL1_1_S & network_ready() 
      ==>
        FSM_Access_cacheL1_1_S_store(adr, m);
        
      endrule;
    
    
      endalias;
    endruleset;
    endruleset;
    
  ----Backend/Murphi/MurphiModular/Rules/GenEventRuleSet
    ruleset m:OBJSET_directoryL1_1 do
    ruleset adr:Address do
      alias cbe:i_directoryL1_1[m].cb[adr] do
    
      rule "directoryL1_1_E__C__V_acq_eventL1_2"
        cbe.State = directoryL1_1_E__C__V & CheckRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr) 
      ==>
        FSM_Access_directoryL1_1_E__C__V_acq_eventL1_2(adr, m);
      endrule;
    
      rule "directoryL1_1_I__C__O_acq_eventL1_2"
        cbe.State = directoryL1_1_I__C__O & CheckRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr) 
      ==>
        FSM_Access_directoryL1_1_I__C__O_acq_eventL1_2(adr, m);
      endrule;
    
      rule "directoryL1_1_I__C__V_acq_eventL1_2"
        cbe.State = directoryL1_1_I__C__V & CheckRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr) 
      ==>
        FSM_Access_directoryL1_1_I__C__V_acq_eventL1_2(adr, m);
      endrule;
    
      rule "directoryL1_1_M__C__V_acq_eventL1_2"
        cbe.State = directoryL1_1_M__C__V & CheckRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr) 
      ==>
        FSM_Access_directoryL1_1_M__C__V_acq_eventL1_2(adr, m);
      endrule;
    
      rule "directoryL1_1_S__C__V_acq_eventL1_2"
        cbe.State = directoryL1_1_S__C__V & CheckRemoteEvent_directoryL1_1(directoryL1_1_acq_eventL1_2, m, adr) 
      ==>
        FSM_Access_directoryL1_1_S__C__V_acq_eventL1_2(adr, m);
      endrule;
    
    
      endalias;
    endruleset;
    endruleset;
    
    ruleset m:OBJSET_directoryL1_1 do
    ruleset adr:Address do
      alias cbe:i_directoryL1_1[m].cb[adr] do
    
    rule "directoryL1_1_M__C__V_UnlockAtomicEvent_"
      cbe.State = directoryL1_1_M__C__V
    ==>
      UnlockAtomicEvent_directoryL1_1(m, adr);
    endrule;
    rule "directoryL1_1_E__C__V_UnlockAtomicEvent_"
      cbe.State = directoryL1_1_E__C__V
    ==>
      UnlockAtomicEvent_directoryL1_1(m, adr);
    endrule;
    rule "directoryL1_1_S__C__V_UnlockAtomicEvent_"
      cbe.State = directoryL1_1_S__C__V
    ==>
      UnlockAtomicEvent_directoryL1_1(m, adr);
    endrule;
    rule "directoryL1_1_I__C__V_UnlockAtomicEvent_"
      cbe.State = directoryL1_1_I__C__V
    ==>
      UnlockAtomicEvent_directoryL1_1(m, adr);
    endrule;
    rule "directoryL1_1_I__C__O_UnlockAtomicEvent_"
      cbe.State = directoryL1_1_I__C__O
    ==>
      UnlockAtomicEvent_directoryL1_1(m, adr);
    endrule;
    
      endalias;
    endruleset;
    endruleset;
    
    ruleset m:OBJSET_cacheL1_2 do
    ruleset adr:Address do
      alias cbe:i_cacheL1_2[m].cb[adr] do
    
      rule "cacheL1_2_I_acq_eventL1_2"
        cbe.State = cacheL1_2_I & CheckRemoteEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr) 
      ==>
        FSM_Access_cacheL1_2_I_acq_eventL1_2(adr, m);
      endrule;
    
      rule "cacheL1_2_I_acquire_GetV_Ack_acq_eventL1_2"
        cbe.State = cacheL1_2_I_acquire_GetV_Ack & CheckInitEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr) 
      ==>
        ServeInitEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr);
        FSM_Access_cacheL1_2_I_acquire_GetV_Ack_acq_eventL1_2(adr, m);
      endrule;
    
      rule "cacheL1_2_O_acq_eventL1_2"
        cbe.State = cacheL1_2_O & CheckRemoteEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr) 
      ==>
        FSM_Access_cacheL1_2_O_acq_eventL1_2(adr, m);
      endrule;
    
      rule "cacheL1_2_V_acq_eventL1_2"
        cbe.State = cacheL1_2_V & CheckRemoteEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr) 
      ==>
        FSM_Access_cacheL1_2_V_acq_eventL1_2(adr, m);
      endrule;
    
      rule "cacheL1_2_V_acquire_GetV_Ack_acq_eventL1_2"
        cbe.State = cacheL1_2_V_acquire_GetV_Ack & CheckInitEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr) 
      ==>
        ServeInitEvent_cacheL1_2(cacheL1_2_acq_eventL1_2, m, adr);
        FSM_Access_cacheL1_2_V_acquire_GetV_Ack_acq_eventL1_2(adr, m);
      endrule;
    
    
      endalias;
    endruleset;
    endruleset;
    
    ruleset m:OBJSET_cacheL1_2 do
    ruleset adr:Address do
      alias cbe:i_cacheL1_2[m].cb[adr] do
    
    rule "cacheL1_2_V_UnlockAtomicEvent_"
      cbe.State = cacheL1_2_V
    ==>
      UnlockAtomicEvent_cacheL1_2(m, adr);
    endrule;
    rule "cacheL1_2_O_UnlockAtomicEvent_"
      cbe.State = cacheL1_2_O
    ==>
      UnlockAtomicEvent_cacheL1_2(m, adr);
    endrule;
    rule "cacheL1_2_I_UnlockAtomicEvent_"
      cbe.State = cacheL1_2_I
    ==>
      UnlockAtomicEvent_cacheL1_2(m, adr);
    endrule;
    
      endalias;
    endruleset;
    endruleset;
    
  ----Backend/Murphi/MurphiModular/Rules/GenNetworkRule
    ruleset dst:Machines do
        ruleset src: Machines do
            alias msg:resp[dst][0] do
              rule "Receive resp"
                cnt_resp[dst] > 0
              ==>
            if IsMember(dst, OBJSET_cacheL1_1) then
              if FSM_MSG_cacheL1_1(msg, dst) then
                  Pop_resp(dst, src);
              endif;
            elsif IsMember(dst, OBJSET_directoryL1_1) then
              if FSM_MSG_directoryL1_1(msg, dst) then
                  Pop_resp(dst, src);
              endif;
            elsif IsMember(dst, OBJSET_cacheL1_2) then
              if FSM_MSG_cacheL1_2(msg, dst) then
                  Pop_resp(dst, src);
              endif;
            else error "unknown machine";
            endif;
    
              endrule;
            endalias;
        endruleset;
    endruleset;
    
    ruleset dst:Machines do
        ruleset src: Machines do
            alias msg:req[dst][0] do
              rule "Receive req"
                cnt_req[dst] > 0
              ==>
            if IsMember(dst, OBJSET_cacheL1_1) then
              if FSM_MSG_cacheL1_1(msg, dst) then
                  Pop_req(dst, src);
              endif;
            elsif IsMember(dst, OBJSET_directoryL1_1) then
              if FSM_MSG_directoryL1_1(msg, dst) then
                  Pop_req(dst, src);
              endif;
            elsif IsMember(dst, OBJSET_cacheL1_2) then
              if FSM_MSG_cacheL1_2(msg, dst) then
                  Pop_req(dst, src);
              endif;
            else error "unknown machine";
            endif;
    
              endrule;
            endalias;
        endruleset;
    endruleset;
    
    ruleset dst:Machines do
        ruleset src: Machines do
            alias msg:fwd[dst][0] do
              rule "Receive fwd"
                cnt_fwd[dst] > 0
              ==>
            if IsMember(dst, OBJSET_cacheL1_1) then
              if FSM_MSG_cacheL1_1(msg, dst) then
                  Pop_fwd(dst, src);
              endif;
            elsif IsMember(dst, OBJSET_directoryL1_1) then
              if FSM_MSG_directoryL1_1(msg, dst) then
                  Pop_fwd(dst, src);
              endif;
            elsif IsMember(dst, OBJSET_cacheL1_2) then
              if FSM_MSG_cacheL1_2(msg, dst) then
                  Pop_fwd(dst, src);
              endif;
            else error "unknown machine";
            endif;
    
              endrule;
            endalias;
        endruleset;
    endruleset;
    

--Backend/Murphi/MurphiModular/GenStartStates

  startstate
    System_Reset();
  endstartstate;

--Backend/Murphi/MurphiModular/GenInvariant
