SRC = $(wildcard src/*.c)
SRC_OBJ = $(SRC:src/%.c=obj/%.o)

TEST_SRC = $(wildcard test/*.c)
TEST_BIN = $(TEST_SRC:test/%.c=bin/%)

LIB_NAME = libdotp.so
FADD_FLAGS = $(ADD_FLAGS) -Wl,-rpath='$$ORIGIN'

all: lib obj bin lib/$(LIB_NAME) $(TEST_BIN) 

bin/test_%: obj/test_%.o bin/$(LIB_NAME)
	gcc $(FADD_FLAGS) -lssl -lm -o $@ $< -L./lib -l:$(LIB_NAME)

bin/$(LIB_NAME): lib/$(LIB_NAME)
	cp lib/$(LIB_NAME) bin/$(LIB_NAME)

obj/%.o: test/%.c
	gcc $(FADD_FLAGS) -Wall -O -c $< -Iinclude -Isrc -o $@

obj/%.o: src/%.c
	gcc $(FADD_FLAGS) -Wall -O -c $< -Iinclude -o $@

lib/$(LIB_NAME): $(SRC_OBJ)
	gcc $(FADD_FLAGS) -lm -shared -o ./lib/$(LIB_NAME) $(SRC_OBJ)

lib:
	mkdir lib

obj:
	mkdir obj

bin:
	mkdir bin

clean:
	rm -f obj/* lib/* bin/*
