nothing: client.out server.out
	echo making
client.out: client.cpp
	g++ client.cpp -o client.out
server.out: main.o User.o System.o
	g++ *.o -o server.out
main.o: System.o System.h main.cpp
	g++ main.cpp -c
System.o: System.cpp System.h headers.h
	g++ System.cpp -c
headers.h: Board.h Card.h comment.h Date.h List.h User.h
	echo header
User.o: Board.o User.h User.cpp
	g++ User.cpp -c
Board.o: List.o Board.h Board.cpp
	g++ Board.cpp -c
List.o: Card.o List.h List.cpp
	g++ List.cpp -c
Card.o: Card.cpp Date.o comment.h Card.h
	g++ Card.cpp -c
Date.o: Date.cpp Date.h
	g++ Date.cpp -c




.PHONY:
clean: 
	rm *.o *.out