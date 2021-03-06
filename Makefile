CFLAGS=-lm

.PHONY: clean test test_datatype_ax test_compare_ax test_pass test_split

#main programs
#sources
naive/naive.c: headers/mpi_pass.h headers/compare_ax.h headers/mpi_io.h headers/datatype_ax.h headers/timing.h
	touch naive/naive.c
no_duplicates/no_duplicates.c: headers/mpi_pass.h headers/compare_ax.h headers/mpi_io.h headers/datatype_ax.h headers/timing.h
	touch no_duplicates/no_duplicates.c

serial/serial_MPI.c: headers/mpi_io.h headers/datatype_ax.h
	touch serial/serial_MPI.c
#binaries
bin/naive: naive/naive.c
	mpicc naive/naive.c -o bin/naive $(CFLAGS)
bin/statsNaive: naive/naive.c naive/compareStats.c headers/compare_ax_stats.h
	mpicc naive/compareStats.c -o bin/statsNaive $(CFLAGS)
bin/no_duplicates: no_duplicates/no_duplicates.c
	mpicc no_duplicates/no_duplicates.c -o bin/no_duplicates $(CFLAGS)
#runs

#testing
#sources
test/test_pass.c: headers/datatype_ax.h headers/mpi_pass.h
	touch test/test_pass.c

test/test_datatype.c: headers/datatype_ax.h
	touch test/test_datatype.c
test/test_compare_ax.c: headers/datatype_ax.h headers/compare_ax.h
	touch test/test_compare_ax.c
test/test_split.c: headers/split.h
	touch test/test_split.c
test/test_cla.c: headers/cla.h
	touch test/test_cla.c
	
#binaries
test/bin/pass: test/test_pass.c
	mpicc $(CFLAGS) test/test_pass.c -o test/bin/pass

test/bin/datatype_ax: test/test_datatype.c
	mpicc $(CFLAGS) test/test_datatype.c -o test/bin/datatype_ax

test/bin/compare_ax: test/test_compare_ax.c
	mpicc $(CFLAGS) test/test_compare_ax.c -o test/bin/compare_ax

test/bin/split: test/test_split.c
	gcc test/test_split.c -o test/bin/split
test/bin/cla: test/test_cla.c
	gcc test/test_cla.c -o test/bin/cla
test/bin/timing: test/test_timing.c headers/timing.h
	mpicc $(CFLAGS) test/test_timing.c -o test/bin/timing

#runs
test_pass:test/bin/pass
	mpirun -n 3 test/bin/pass

test_datatype_ax:test/bin/datatype_ax
	mpirun -n 2 test/bin/datatype_ax

test_compare_ax:test/bin/compare_ax
	mpirun -n 1 test/bin/compare_ax
	
test_split:test/bin/split
	./test/bin/split v
test_cla:test/bin/cla
	#test for failure if given invalid input
	./test/bin/cla; test $$? -eq 1
	echo "printing file to read:"
	cat test/test.ini
	./test/bin/cla test/test.ini
	
test_timing: test/bin/timing
	mpirun -n 1 test/bin/timing test/test.ini

test: test_datatype_ax test_compare_ax test_pass test_split

#others
clean:
	rm bin/*
	rm test/bin/*
