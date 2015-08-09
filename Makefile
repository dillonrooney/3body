CFLAGS=-lm

.PHONY: clean test test_datatype_ax test_compare_ax test_pass

#main programs
#sources
naive/naive.c: headers/mpi_pass.h headers/compare_ax.h headers/mpi_io.h headers/datatype_ax.h

serial/serial_MPI.c: headers/mpi_io.h headers/datatype_ax.h
#binaries

#runs

#testing
#sources
test/test_pass.c: headers/datatype_ax.h headers/mpi_pass.h

test/test_datatype.c: headers/datatype_ax.h

test/test_compare_ax.c: headers/datatype_ax.h headers/compare_ax.h
#binaries
test/bin/pass: test/test_pass.c
	mpicc $(CFLAGS) test/test_pass.c -o test/bin/pass

test/bin/datatype_ax: test/test_datatype.c
	mpicc $(CFLAGS) test/test_datatype.c -o test/bin/datatype_ax

test/bin/compare_ax: test/test_compare_ax.c
	mpicc $(CFLAGS) test/test_compare_ax.c -o test/bin/compare_ax


#runs
test_pass:test/bin/pass
	mpirun -n 3 test/bin/pass

test_datatype_ax:test/bin/datatype_ax
	mpirun -n 3 test/bin/datatype_ax

test_compare_ax:test/bin/compare_ax
	mpirun -n 1 test/bin/compare_ax

test: test_datatype_ax test_compare_ax test_pass


clean:
	rm bin/*
	rm test/bin/*
