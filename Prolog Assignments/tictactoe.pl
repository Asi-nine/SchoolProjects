:- dynamic x/1, o/1.

ordered_line(1,5,9). 
ordered_line(3,5,7).
ordered_line(1,2,3). 
ordered_line(4,5,6). 
ordered_line(7,8,9). 
ordered_line(1,4,7). 
ordered_line(2,5,8). 
ordered_line(3,6,9).

line(A,B,C) :- ordered_line(A,B,C). 
line(A,B,C) :- ordered_line(A,C,B). 
line(A,B,C) :- ordered_line(B,A,C). 
line(A,B,C) :- ordered_line(B,C,A). 
line(A,B,C) :- ordered_line(C,A,B). 
line(A,B,C) :- ordered_line(C,B,A).

move(A) :- good(A), empty(A).

empty(A) :- \+ full(A).

full(A) :- x(A).
full(A) :- o(A).

good(A) :- win(A).        % a cell where we win
good(A) :- block_win(A).  % a cell where we block the opponent from a win
good(A) :- split(A).      % a cell where we can make a split to win
good(A) :- block_split(A).% a cell where we block the opponent from a split 
good(A) :- build(A).      % choose a cell to get a line 


win(A) :- x(B), x(C), line(A,B,C).

block_win(A) :- o(B), o(C), line(A,B,C).

split(A) :- x(B), x(C), \+ (B = C), line(A,B,D), line(A,C,E), empty(D), empty(E). 


block_split(A) :- o(B), o(C), \+ (B = C), line(A,B,D), line(A,C,E), empty(D), empty(E).

build(A) :- x(B), line(A,B,C), empty(C).

good(5).                  % choose a cell in a good location 
good(1). 
good(3). 
good(7). 
good(9). 
good(2). 
good(4). 
good(6). 
good(8).


