CC = g++
EXEC = 2048
CFLAGS = -Wc++11-extensions -Wmissing-declarations

game2048:
	$(CC) -o $(EXEC)  main.cpp game.cpp linked-list.cpp $(CFLAGS)

run: $(EXEC)
	./$(EXEC)

clean:
	rm $(EXEC)