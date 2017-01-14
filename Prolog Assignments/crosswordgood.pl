
word(dog,[d,o,g]).
word(run,[r,u,n]).
word(top,[t,o,p]).
word(five,[f,i,v,e]).
word(four,[f,o,u,r]).
word(lost,[l,o,s,t]).
word(mess,[m,e,s,s]).
word(unit,[u,n,i,t]).
word(baker,[b,a,k,e,r]).
word(forum,[f,o,r,u,m]).
word(green,[g,r,e,e,n]).
word(super,[s,u,p,e,r]).
word(prolog,[p,r,o,l,o,g]).
word(vanish,[v,a,n,i,s,h]).
word(wonder,[w,o,n,d,e,r]).
word(yellow,[y,e,l,l,o,w]).

solution(H1,H3,V1,V3,V5) :-
    word(H1, [L1,L2,L3,L4,L5]),
    word(H3, [L9,L10,L11,L12,L13,L14]),
    word(V1, [L1,L6,L9,L15]),
    word(V3, [L3,L7,L11]),
    word(V5, [L5,L8,L13,L16]).

