CC = gcc
CFLAGS = -Wall -g
LDFLAGS =

SRC_DIR = .
OBJ_DIR = .

SRC_FILES = $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
EXECUTABLE = shortestPath

VAL = valgrind --tool=memcheck --log-file=memcheck.txt --leak-check=full --verbose

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: $(EXECUTABLE)
	./$(EXECUTABLE) inputs/input1.txt NodeA NodeE

test1:
	./$(EXECUTABLE) inputs/input1.txt NodeA NodeE > output1
	diff -w output1 expected/expected1

test2:
	./$(EXECUTABLE) inputs/input2.txt a e > output2
	diff -w output2 expected/expected2

test3:
	./$(EXECUTABLE) inputs/input3.txt D B > output3
	diff -w output3 expected/expected3

test4:
	./$(EXECUTABLE) inputs/input4.txt C E > output4
	diff -w output4 expected/expected4

testall:  test1 test2 test3 test4

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE) output? memcheck.txt

testmemory: $(EXECUTABLE)
	$(VAL) ./$(EXECUTABLE) inputs/input4.txt C A