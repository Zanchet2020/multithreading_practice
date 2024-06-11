vector_adder: vector_adder.c
	cc vector_adder.c -o bin/vector_adder -lm -pthread


merge_sort: merge_sort.c
	cc merge_sort.c -o bin/merge_sort -lm -lpthread
