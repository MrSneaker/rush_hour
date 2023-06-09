all : bin/rush_hour
test : bin/rush_hour_test

SDL2=`sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer


bin/rush_hour : obj/rush_hour.o obj/plateau.o obj/vehicule.o obj/State.o obj/Graphe.o obj/Affichage.o obj/Image.o obj/Puzzle.o
	g++ -o bin/rush_hour obj/rush_hour.o obj/plateau.o obj/vehicule.o obj/State.o obj/Graphe.o obj/Affichage.o obj/Image.o obj/Puzzle.o -ggdb $(SDL2)

bin/rush_hour_test : obj/rush_hour_test.o obj/plateau.o obj/vehicule.o obj/State.o obj/Graphe.o obj/Puzzle.o
	g++ -o bin/rush_hour_test obj/rush_hour_test.o obj/plateau.o obj/vehicule.o obj/State.o obj/Graphe.o obj/Puzzle.o -ggdb
	
obj/rush_hour.o : src/rush_hour.cpp
	g++ -c -o obj/rush_hour.o src/rush_hour.cpp -ggdb

obj/rush_hour_test.o : src/rush_hour_test.cpp 
	g++ -c -o obj/rush_hour_test.o src/rush_hour_test.cpp -ggdb

obj/State.o : src/State.cpp src/State.hpp src/plateau.hpp
	g++ -c -o obj/State.o src/State.cpp -ggdb

obj/Graphe.o : src/Graphe.cpp src/Graphe.hpp src/State.hpp
	g++ -c -o obj/Graphe.o src/Graphe.cpp -ggdb

obj/Affichage.o : src/Affichage.cpp src/Affichage.hpp src/plateau.hpp src/Image.hpp src/Puzzle.hpp
	g++ -c -o obj/Affichage.o src/Affichage.cpp -ggdb  $(SDL2)

obj/Puzzle.o : src/Puzzle.cpp src/Puzzle.hpp src/plateau.hpp
	g++ -c -o obj/Puzzle.o src/Puzzle.cpp -ggdb

obj/Image.o : src/Image.cpp src/Image.hpp
	g++ -c -o obj/Image.o src/Image.cpp -ggdb  $(SDL2)

obj/plateau.o : src/plateau.cpp src/plateau.hpp src/vehicule.hpp
	g++ -c -o obj/plateau.o src/plateau.cpp -ggdb

obj/vehicule.o : src/vehicule.cpp src/vehicule.hpp
	g++ -c -o obj/vehicule.o src/vehicule.cpp -ggdb

clean:
	rm -f obj/*.o
	rm -f bin/*

bin : 
	mkdir bin
