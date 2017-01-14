word(X) :-
maplist(X,
[
[d,o,g],[r,u,n],[t,o,p],[f,i,v,e],[f,o,u,r],[l,o,s,t],[m,e,s,s],[u,n,i,t],
[b,a,k,e,r],[f,o,r,u,m],[g,r,e,e,n],[s,u,p,e,r],[p,r,o,l,o,g],[v,a,n,i,s,h],
[w,o,n,d,e,r],[y,e,l,l,o,w]
]).

solution(H1,H2,H3,H4,V1,V2,V3,V4,V5,V6) :-
    H1 = [L1,L2,L3,L4,L5,_],
    H2 = [L6,_,L7,_,L8,_,],
    H3 = [L9,L10,L11,L12,L13,L14],
    H4 = [L15,_,_,_,L16,_],
    V1 = [L1,L6,L9,L15],
    V2 = [L2,_,L10,_],
    V3 = [L3,L7,L11,_],
    V4 = [L4,_,L12,_],
    V5 = [L5,L8,L13,L16],
    V6 = [_,_,L14,_],
	maplist(word, [H1,H2,H3,H4,V1,V2,V3,V4,V5,V6]).
