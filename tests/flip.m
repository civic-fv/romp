const
    size: 4;
type
    board_index: 0..(size-1);
    row_t: array [board_index] of Boolean;
    board_t: array [board_index] of row_t;
var
    board: board_t;

StartState "setup"
    for i : board_index do
        for j : board_index do
            board[i][j] := false;
        endFor;
    endFor;
    board[size/2][size/2] := true;
EndStartState;

ruleset i : board_index;
        j : board_index do

    rule "do a flip!"
        board[i][j] ==>
    begin
        board[i][j] := false;
        if i > 0 then
            board[i-1][j] := !board[i-1][j];
        endif;
        if j > 0 then
            board[i][j-1] := !board[i][j-1];
        endif;
        if i < size-1 then
            board[i+1][j] := !board[i+1][j];
        endif;
        if j < size-1 then
            board[i][j+1] := !board[i][j+1];
        endif
    EndRule;

EndRuleset;

invariant "game still in play" 
    Exists i:board_index do 
        Exists j:board_index do
            board[i][j]
        endExists
    endExists;
