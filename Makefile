all : bin/rush_hour_test 


bin/rush_hour_test : obj/rush_hour_test.o obj/plateau.o obj/vehicule.o  
	g++ -o bin/rush_hour_test obj/rush_hour_test.o obj/plateau.o obj/vehicule.o
	
obj/rush_hour_test.o : src/rush_hour_test.cpp 
	g++ -c -o obj/rush_hour_test.o src/rush_hour_test.cpp 

obj/plateau.o : src/plateau.cpp src/plateau.h src/vehicule.h
	g++ -c -o obj/plateau.o src/plateau.cpp 

obj/vehicule.o : src/vehicule.cpp src/vehicule.h
	g++ -c -o obj/vehicule.o src/vehicule.cpp 

clean:
	rm -f obj/*.o
	rm -f bin/*

bin : 
	mkdir bin
