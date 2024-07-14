
--------------------------------------------------------------------------------
-- RUN: romp %s -o /dev/stdout | c++ - -o /dev/null
--------------------------------------------------------------------------------

Const
	N: 4;
	MaxPID: N+1;
	FileTableSize: 2;
	MaxFileID: 2;
	-- Assume that no more than N processes are ever in play.
	-- It should be fair to assume that the lack of any interesting races
	-- found at N or less implies the lack of similar races greater than
	-- N processes, assuming infinite memory and other resources.

Type
	ProcIndex: 1..N;
	SleepChannel: 0..N;	-- Arbitrary: Set to the same as N (+ 0), since up to N processes can sleep.
	PIDCount: 0..MaxPID;	-- Up to MaxPID process IDs
	FileRefCount: 1..FileTableSize;
	state: Enum {
		UNUSED,	-- No process exists with this ID.
		RUNNING, -- This process is currently running
		RUNNABLE, -- This should be fair to schedule.
		SLEEPING, -- This process is waiting for something to finish (typically a timer)
		ZOMBIE,	-- This process is dead, but needs to be cleaned up by it's parent.
		KILLED,	-- This process has been killed, and needs cleanup. (and was formerly a zombie.)
	};

	FileTable: Array[FileRefCount] of 0..MaxFileID;	-- 8 entries of a file ID.

Var
	WaitLock : boolean;
	PIDs: Array[ProcIndex] Of PIDCount;
	ProcLocks: Array[ProcIndex] of boolean;
	ProcChannels: Array[ProcIndex] of SleepChannel;
	Parents: Array[ProcIndex] of PIDCount;
	States: Array[ProcIndex] Of state;
	PrevStates: Array[ProcIndex] Of state;
	ProcessFileTable: Array[ProcIndex] of FileTable;

	NextPID: PIDCount;

	function allocpid() : PIDCount
		var NewPID: PIDCount;
		var FoundPID: boolean;
	Begin
		FoundPID := false;
		NewPID := 1;
		while (FoundPID = false) do
			if (States[NewPID] = UNUSED) then
				FoundPID := false;
				return NewPID;
			else
				NewPID := NewPID + 1;
			end
		end
	End;

	function allocproc(i : ProcIndex)
	Begin
		for z:ProcIndex Do
			if (States[z] == UNUSED) then
				PIDs[z] := allocpid();
				Parents[z] := PIDs[i];
				States[z] := RUNNABLE;
				PrevStates[z] := UNUSED;
				ProcChannels[z] := 0;
				ProcLocks[z] := false;
			End;
		End;
	End;

	function fork(i : ProcIndex)
	Begin
		-- Not yet implemented: Increment file references
		allocproc(i);
	End;

	function exit(i : ProcIndex)
	Begin
		-- Not yet implemented: Decremenet all file references
		States[i] := ZOMBIE;
		PrevStates[i] := RUNNING;
	End;

	function open(i : ProcIndex; z : FileRefCount)
	Begin
		-- The entire file struct is not needed: only use reference counts.
		if (ProcessFileTable[i][z] < MaxFileID) then
			ProcessFileTable[i][z] := ProcessFileTable[i][z] + 1;
		end;
	End;

	function pipealloc(i : ProcIndex; i2 : ProcIndex; z : FileRefCount; z2 : FileRefCount)
	Begin
		-- Open a file on both ends
		open(i, z);
		open(i2, z2);
	End;

	-- This function does not exactly exist in xv6, but we need to close open fds somehow.
	function fd_dealloc(i : ProcIndex; z : FileRefCount)
	Begin
		-- The entire file struct is not needed: only use reference counts.
		if (ProcessFileTable[i][z] > 0) then
			ProcessFileTable[i][z] := ProcessFileTable[i][z] - 1;
		end;
	End;

	function sleep(i : ProcIndex; c : SleepChannel)
	Begin
		-- The current proc lock needs to be acquired.
		ProcLocks[i] := true;

		-- The global wait lock needs to be released.
		WaitLock := false;

		-- The current channel is set.
		ProcChannels[i] := c;

		-- The process is marked asleep.
		States[i] := SLEEPING;
		PrevStates[i] := RUNNING;

		-- Note that sched() invokes a coroutine, where this
		-- code only executes when this process is later woken up.
		-- This will be modelled as a separate function...
	End;

	function fini_sleep(i : ProcIndex)
	Begin
		-- Following from line 549 in the original proc.c code...
		ProcChannels[i] := 0;

		-- The process lock is then released.
		ProcLocks[i] := false;

		-- The global wait lock is re-acquired. This is needed
		-- since an invariant in the C code is that after sleep
		-- is called, the wait lock is still held to avoid races.
		-- This is done as so:
		WaitLock := true;
	End;

	function wakeup(i : ProcIndex; c : SleepChannel)
	Begin
		for z:ProcIndex Do
			if (z != i) then
				ProcLocks[z] := true;
				if (States[z] == SLEEPING && ProcChannels[z] == c) then
					fini_sleep(z);
					States[z] := RUNNABLE;
				end;
				ProcLocks[z] := false;
			End;
		End;
	End;

	function cleanup_fds(i : ProcIndex)
	Begin
		For fileindex := 1 to FileTableSize Do
			while (ProcessFileTable[i][fileindex] != 0) do
				fd_dealloc(i, fileindex);
			end
		End
	End

Ruleset i: ProcIndex; i2: ProcIndex; fi : FileRefCount; fi2 : FileRefCount Do
	Rule "A process can fork"
		States[i] = RUNNING ==>
		Begin
			-- Find the first available process control block
			fork(i);
		End;

	Rule "A runnable process can become running"
		States[i] = RUNNABLE ==>
		Begin
			States[i] := RUNNING;
			PrevStates[i] := RUNNABLE;
		End;

	Rule "A running process can become runnable"
		States[i] = RUNNING ==>
		Begin
			States[i] := RUNNABLE;
			PrevStates[i] := RUNNING;
		End;

	Rule "A running process can open a file"
		States[i] = RUNNING ==>
		Begin
			open(i, fi);
		End;

	Rule "A running process can open a pipe with another process"
		States[i] = RUNNING && (States[i2] = RUNNING || States[i2] == RUNNABLE) ==>
		Begin
			pipealloc(i, i2, fi, fi2);
			sleep(i2, i2);
		End;

	Rule "A running process can close a file"
		States[i] = RUNNING && ProcessFileTable[i][fi] > 0 ==>
		Begin
			fd_dealloc(i, fi);
		End;

	Rule "A running process can sleep"
		States[i] = RUNNING ==>
		Begin
			-- When doing so, the channel for sleeping has to be selected.
			-- This precise method is arbitrary, so using the PID guarantees
			-- that the state space does not explode as a result of allowing
			-- any arbitrary 64-bit integer.
			WaitLock := true;
			sleep(i, i);
			WaitLock := false;
		End;

	Rule "Any sleeping process can be woken up"
		States[i] = SLEEPING ==>
		Begin
			wakeup(i, i);
		End;

	Rule "A sleeping process can become runnable"
		States[i] = SLEEPING ==>
		Begin
			fini_sleep(i);
			States[i] := RUNNABLE;
			PrevStates[i] := SLEEPING;
		End;

	Rule "A sleeping process can become a zombie (unless it is init)"
		States[i] = RUNNING ==>
		Begin
			cleanup_fds(i);
			-- Assume init is well-behaving, and does not crash.
			if (PIDs[i] != 1) then
				fini_sleep(i);
				States[i] := ZOMBIE;
				PrevStates[i] := SLEEPING;
				WaitLock := false;
			end;
		End;

	Rule "A running process can become a zombie (unless it is init)"
		States[i] = RUNNING ==>
		Begin
			cleanup_fds(i);
			-- Assume init is well-behaving, and does not crash.
			if (PIDs[i] != 1) then
				exit(i);
			end;
		End;

	Rule "A zombie can be cleaned up"
		States[i] = ZOMBIE ==>
		Begin
			States[i] := KILLED;
			PrevStates[i] := ZOMBIE;
		End;

	Rule "A killed process can be reused as a new process"
		States[i] = KILLED ==>
		Begin
			States[i] := UNUSED;
			PrevStates[i] := KILLED;
		End;

	Startstate
	Begin
		NextPID := 1;
		for k:ProcIndex Do
			-- Ensure every process is initially unused.
			PIDs[k] := k+1;	-- Every process gets a unique ID from [1, N].
			ProcLocks[k] := false;
			States[k] := UNUSED;
			PrevStates[k] := KILLED;
			ProcChannels[k] := 0;
			Parents[k] := 0;
			for z:FileRefCount Do
				ProcessFileTable[k][z] := 0;
			End;
		End;

		-- Except PID 1, which must always be present and not dead.
		-- On a unix system, this corresponds to init.
		PIDs[1] := 1;
		Parents[1] := 0;
		States[1] := RUNNING;
		PrevStates[1] := RUNNABLE;

		-- Global wait lock is not held.
		WaitLock := false;
	End;
End



-- Ideally, these invariants should hold for all time!

Invariant "A process cannot suddenly die"
	Forall k:ProcIndex Do
		States[k] = KILLED -> PrevStates[k] = ZOMBIE
	End

Invariant "A zombie process cannot be (seriously) scheduled"
	Forall k:ProcIndex Do
		States[k] = RUNNING -> PrevStates[k] != ZOMBIE
	End

Invariant "A zombie process cannot be (seriously) scheduleable"
	Forall k:ProcIndex Do
		States[k] = RUNNABLE -> PrevStates[k] != ZOMBIE
	End

Invariant "A process which is currently running had to be runnable or sleeping before."
	Forall k:ProcIndex Do
		States[k] = RUNNING -> PrevStates[k] = RUNNABLE | PrevStates[k] = SLEEPING
	End

Invariant "No two processes can ever have the same PID."
	Forall k1:ProcIndex Do
	Forall k2:ProcIndex Do
		k1 != k2 -> PIDs[k1] != PIDs[k2]
	End
	End

Invariant "Any process sleeping must have a non-zero channel"
	Forall k:ProcIndex Do
		ProcChannels[k] != 0 -> States[k] == SLEEPING
	End

Invariant "Any process not sleeping must have a zero channel"
	Forall k:ProcIndex Do
		ProcChannels[k] == 0 -> States[k] != SLEEPING
	End

Invariant "No process can be its own parent."
	Forall k:ProcIndex Do
		Parents[k] != PIDs[k]
	End

Invariant "No process has negative file references."
	Forall k:ProcIndex Do
		Forall z:FileRefCount Do
			ProcessFileTable[k][z] >= 0
		End
	End

Invariant "No dead process has open file references."
	Forall k:ProcIndex Do
		Forall z:FileRefCount Do
			(States[k] == ZOMBIE || States[k] == UNUSED || States[k] == KILLED) -> ProcessFileTable[k][z] = 0
		End
	End