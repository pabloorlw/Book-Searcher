a.out: libro.o aparicion.o interprete.o TablaHash.o arbol.o main.o coleccion.o
	g++ libro.o aparicion.o interprete.o TablaHash.o arbol.o main.o coleccion.o

libro.o: libro.cpp libro.hpp
	g++ -c libro.cpp

aparicion.o: aparicion.cpp aparicion.hpp libro.hpp 
	g++ -c aparicion.cpp

coleccion.o: coleccion.cpp coleccion.hpp libro.hpp aparicion.hpp TablaHash.hpp arbol.hpp
	g++ -c coleccion.cpp

interprete.o: interprete.cpp interprete.hpp libro.hpp coleccion.hpp
	g++ -c interprete.cpp

TablaHash.o: TablaHash.cpp TablaHash.hpp libro.hpp
	g++ -c TablaHash.cpp

arbol.o: arbol.cpp arbol.hpp aparicion.hpp
	g++ -c arbol.cpp

main.o: main.cpp interprete.hpp
	g++ -c main.cpp

