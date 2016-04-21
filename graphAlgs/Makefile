graphtest: graph.c graphtest.c
	clang -g -O0 -o graphtest graphtest.c graph.c

testgraph: graphtest
	./graphtest

graphiotest: graph.c graphio.c graphiotest.c
	clang -g -O0 -o graphiotest graphiotest.c graph.c graphio.c

testgraphio: graphiotest
	./graphiotest
#	valgrind --leak-check=yes ./graphtest

