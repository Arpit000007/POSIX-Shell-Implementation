output: Main.o env.o ls.o pinfo.o redirection.o search.o
	g++ Main.cpp env.cpp ls.cpp pinfo.cpp search.cpp redirection.cpp -o output

Main.o: Main.cpp
	g++ -c Main.cpp

env.o: env.cpp
	g++ -c env.cpp

ls.o: ls.cpp
	g++ -c ls.cpp

pinfo.o: pinfo.cpp
	g++ -c pinfo.cpp

search.o: search.cpp
	g++ -c search.cpp

clean:
	rm *.o