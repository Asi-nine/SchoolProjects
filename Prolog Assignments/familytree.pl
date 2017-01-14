male(trevor).

male(mark).
female(bertha).

male(frank).
female(gertrude).
male(mike).
female(sarah).

male(peter).
female(nancy).
male(john).
female(anne).
male(doug).
female(eliza).
male(justin).
female(barbara).

parent(mark,trevor).
parent(bertha,trevor).
married(mark,bertha).

parent(frank,mark).
parent(gertrude,mark).
married(frank,gertrude).
parent(mike,bertha).
parent(sarah,bertha).
married(mike,sarah).

parent(peter,frank).
parent(nancy,frank).
married(peter,nancy).
parent(john,gertrude).
parent(anne,gertrude).
married(john,anne).
parent(doug,mike).
parent(eliza,mike).
married(doug,eliza).
parent(justin,sarah).
parent(barbara,sarah).
married(justin,barbara).

father(Father,Child):-male(Father),parent(Father,Child).
mother(Mother,Child):-female(Mother),parent(Mother,Child).
brother(A,B):-male(A),parent(Parent,A),parent(Parent,B),A\=B.
sibling(A,B):-parent(Parent,A),parent(Parent,B),A\=B.
grandson(Grandson,Grandparent):-male(Grandson),parent(Parent,Grandson),parent(Grandparent,Parent).
cousin(A,B):-parent(Parent_one,A),parent(Parent_two,B),sibling(Parent_two,Parent_one).

mother_in_law(Mother_in_law,Child):-mother(Mother_in_law,A),(married(A,Child);married(Child,A)).
descendent(A,B):-!,parent(B,A).
descendent(A,B):-parent(Parent,A),descendent(Parent,B). 

