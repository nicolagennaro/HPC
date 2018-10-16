CC=gcc
MPICC=mpicc

mat_size=10
procs=5
filename="matrix.bin"

MPIexe=matmult
Cexe = readmatbin

all: $(Cexe) $(MPIexe)

$(Cexe): %: %.c
	$(CC) $< -o $@

$(MPIexe): %: %.c
	$(MPICC) $< -o $@

run:
	@mpirun -np $(procs) matmult $(mat_size)
	@./readmatbin $(filename) $(mat_size)

clean:
	@rm *~ $(MPIexe) $(Cexe) matrix.bin

.PHONY: clean
