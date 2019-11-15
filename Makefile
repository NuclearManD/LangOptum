CC = gcc
FLAGS = -Iinclude -Wall -Wextra -Werror -Wno-unused-result

testbench:
	mkdir -p bin
	mkdir -p build
	$(CC) -c $(FLAGS) -O3 src/main.c -o build/main.o
	$(CC) -c $(FLAGS) -O3 src/emulator.c -o build/emulator.o
	$(CC) -c $(FLAGS) -O3 src/argparse.c -o build/argparse.o
	$(CC) -c $(FLAGS) -O3 src/memory.c -o build/memory.o
	$(CC) -c $(FLAGS) -O3 src/system.c -o build/system.o
	$(CC) -c $(FLAGS) -O3 src/flow_and_shape.c -o build/flow_and_shape.o
	$(CC) -c $(FLAGS) -O3 src/strings.c -o build/strings.o
	$(CC) $(FLAGS) -O3 build/*.o -o bin/emu-emuarch
debug:
	mkdir -p bin
	mkdir -p build
	$(CC) -c $(FLAGS) -g src/main.c -o build/main.o
	$(CC) -c $(FLAGS) -g src/emulator.c -o build/emulator.o
	$(CC) -c $(FLAGS) -g src/argparse.c -o build/argparse.o
	$(CC) -c $(FLAGS) -g src/memory.c -o build/memory.o
	$(CC) -c $(FLAGS) -g src/system.c -o build/system.o
	$(CC) -c $(FLAGS) -g src/flow_and_shape.c -o build/flow_and_shape.o
	$(CC) -c $(FLAGS) -g src/strings.c -o build/strings.o
	$(CC) $(FLAGS) -g build/*.o -o bin/emu-emuarch
clean:
	rm -rf build
fclean: clean
	rm -rf bin
re: fclean testbench
