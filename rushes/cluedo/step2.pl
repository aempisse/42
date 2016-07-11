rue([
	maison(_,_,_,_,_) ,
	maison(_,_,_,_,_) ,
	maison(_,_,_,_,_) ,
	maison(_,_,_,_,_) ,
	maison(_,_,_,_,_)
		]).

appartient(X,[X|_]).
appartient(X,[_|T]) :- appartient(X,T).

droite(A,B,[A,B|_]).
droite(A,B,[_|T]) :- droite(A,B,T).

cote(A,B,[A,B|_]).
cote(A,B,[B,A|_]).
cote(A,B,[_|T]) :- cote(A,B,T).

solution(Rue) :-
	rue(Rue),
	appartient(maison(rouge,anglais,_,_,_),Rue),
	appartient(maison(_,suedois,chien,_,_),Rue),
	appartient(maison(_,danois,_,the,_),Rue),
	droite(maison(verte,_,_,_,_),maison(blanche,_,_,_,_),Rue),
	appartient(maison(verte,_,_,cafe,_),Rue),
	appartient(maison(_,_,oiseaux,_,pall_mall),Rue),
	appartient(maison(jaune,_,_,_,dunhill),Rue),
	Rue = [_,_,maison(_,_,_,lait,_),_,_],
	Rue = [maison(_,norvegien,_,_,_)|_],
	cote(maison(_,_,_,_,blend),maison(_,_,chats,_,_),Rue),
	cote(maison(_,_,cheval,_,_),maison(_,_,_,_,dunhill),Rue),
	appartient(maison(_,_,_,biere,blue_master),Rue),
	appartient(maison(_,allemand,_,_,prince),Rue),
	cote(maison(_,norvegien,_,_,_),maison(bleue,_,_,_,_),Rue),
	cote(maison(_,_,_,_,blend),maison(_,_,_,eau,_),Rue),
	appartient(maison(_,_,poisson,_,_),Rue).
