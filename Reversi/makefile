# name: ori hirshfeld
# id: 201085776
#name Amichai Wollin
# id: 300582392

a.out:	Board.o AIPlayer.o GameManager.o LocalPlayer.o main.o Player.o StandardLogic.o RemotePlayer.o
	g++	Board.o AIPlayer.o GameManager.o LocalPlayer.o main.o Player.o StandardLogic.o RemotePlayer.o

main.o:	main.cpp
	g++ -c main.cpp

Board.o:	Board.cpp Board.h
	g++ -c Board.cpp

AIPlayer.o:	AIPlayer.cpp AIPlayer.h
	g++ -c	AIPlayer.cpp

GameManager.o:	GameManager.cpp GameManager.h
	g++ -c GameManager.cpp

LocalPlayer.o:	LocalPlayer.cpp LocalPlayer.h
	g++ -c LocalPlayer.cpp

Player.o:	Player.cpp Player.h
	g++ -c Player.cpp

StandardLogic.o:	StandardLogic.cpp StandardLogic.h
	g++ -c StandardLogic.cpp

RemotePlayer.o:	RemotePlayer.cpp RemotePlayer.h
	g++ -c RemotePlayer.cpp

