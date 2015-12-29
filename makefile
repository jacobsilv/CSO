C = gcc
FLAGS = -Wall -g

all: prime bouncy sum wordcount
	@

run-ex1: prime
	./prime 1000

run-ex2: bouncy
	./bouncy 99

run-ex3: sum
	./sum

run-ex4: wordcount
	./wordcount bible.txt

%.c:
	$(CC) $(FLAGS) $*.c -o $*

handin:
	tar -cvf lab0.tar.gz *.c submit.py my.info bible.txt makefile


clean:
	-rm -rf prime 
	-rm -rf bouncy
	-rm -rf sum
	-rm -rf wordcount


