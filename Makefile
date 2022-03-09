output: main.o stl_knn_par.o stl_knn_seq.o utils.o
	g++ main.o stl_knn_par.o stl_knn_seq.o utils.o -pthread -o  output
main.o: main.cpp
	g++ -c main.cpp
stl_knn_par.o: src/stl_knn_par.cpp
	g++ -c src/stl_knn_par.cpp
stl_knn_seq.o: src/stl_knn_seq.cpp
	g++ -c src/stl_knn_seq.cpp
utils.o: src/utils.cpp
	g++ -c src/utils.cpp
utimer.o: src/utimer.cpp
	g++ -c src/utimer.cpp

clean:
	rm *.o output
	rm *.out