all : bin/rush_hour_test 


bin/rush_hour_test : obj/rush_hour_test.o obj/plateau.o obj/vehicule.o obj/State.o
	g++ -o bin/rush_hour_test obj/rush_hour_test.o obj/plateau.o obj/vehicule.o obj/State.o -ggdb
	
obj/rush_hour_test.o : src/rush_hour_test.cpp 
	g++ -c -o obj/rush_hour_test.o src/rush_hour_test.cpp -ggdb

obj/State.o : src/State.cpp src/State.hpp src/plateau.hpp
	g++ -c -o obj/State.o src/State.cpp -ggdb

obj/plateau.o : src/plateau.cpp src/plateau.hpp src/vehicule.hpp
	g++ -c -o obj/plateau.o src/plateau.cpp -ggdb

obj/vehicule.o : src/vehicule.cpp src/vehicule.hpp
	g++ -c -o obj/vehicule.o src/vehicule.cpp -ggdb

clean:
	rm -f obj/*.o
	rm -f bin/*

bin : 
	mkdir bin
