GCC=gcc
OMPCC=-fopenmp

all: pi_openmp

pi_openmp: pi_openmp.c
	$(GCC) $< -o $@ $(OMPCC)


clean:
	@rm *~

.PHONY: clean
