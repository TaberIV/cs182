# topo sort - without depth-first search
topocycle: graph.c dfs.c topocycletest.c
	clang -g -O0 -o topocycletest graph.c topocycletest.c

testtopocycle: topocycle
	./topocycletest
