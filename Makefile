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

clean:
	rm -f $(OBJ_DIR)/*.o $(EXECUTABLE)

testmemory: $(EXECUTABLE)
	$(VAL) ./$(EXECUTABLE) inputs/input2.txt a e