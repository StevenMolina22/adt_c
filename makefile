VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CC = gcc

all: list bst hash
test: test-list test-bst test-hash

# run
list: build-list
	@./list pokedex.csv
	@rm ./list

bst: build-bst
	@./bst pokedex.csv
	@rm ./bst

hash: build-hash
	@./hash pokedex.csv
	@rm ./hash

build-list: src/utils/*.c src/list/*.c src/list.c
	@$(CC) $(CFLAGS) src/utils/*.c src/list/*.c src/list.c -o list

build-bst: src/utils/*.c src/bst/*.c src/bst.c
	@$(CC) $(CFLAGS) src/utils/*.c src/bst/*.c src/bst.c -o bst

build-hash: src/utils/*.c src/hash/*.c src/hash.c
	@$(CC) $(CFLAGS) src/utils/*.c src/hash/*.c src/hash.c -o hash


# test
test-list: build-test-list
	@valgrind $(VALGRIND_FLAGS) ./test_list
	@rm ./test_list

test-bst: build-test-bst
	@valgrind $(VALGRIND_FLAGS) ./test_bst
	@rm ./test_bst

test-hash: build-test-hash
	@valgrind $(VALGRIND_FLAGS) ./test_hash
	@rm ./test_hash

build-test-list: src/utils/*.c src/list/*.c src/test_list.c
	@$(CC) $(CFLAGS) src/utils/*.c src/list/*.c src/test_list.c -o test_list

build-test-bst: src/utils/*.c src/bst/*.c src/test_bst.c
	@$(CC) $(CFLAGS) src/utils/*.c src/bst/*.c src/test_bst.c -o test_bst

build-test-hash: src/utils/*.c src/hash/*.c src/test_hash.c
	@$(CC) $(CFLAGS) src/utils/*.c src/hash/*.c src/test_hash.c -o test_hash


# debug tests
debug-list: build-debug-list
	gdb ./test_list
	rm ./test_list

debug-bst: build-debug-bst
	gdb ./test_bst
	rm ./test_bst

debug-hash: build-debug-hash
	gdb ./test_hash
	rm ./test_hash

build-debug-list: src/utils/*.c src/list/*.c src/test_list.c
	$(CC) $(CFLAGS) -g src/utils/*.c src/list/*.c src/test_list.c -o test_list

build-debug-bst: src/utils/*.c src/bst/*.c src/test_bst.c
	$(CC) $(CFLAGS) -g src/utils/*.c src/bst/*.c src/test_bst.c -o test_bst

build-debug-hash: src/utils/*.c src/hash/*.c src/test_hash.c
	$(CC) $(CFLAGS) -g src/utils/*.c src/hash/*.c src/test_hash.c -o test_hash
