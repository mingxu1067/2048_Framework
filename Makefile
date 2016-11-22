CC = g++
EXEC = bin/2048
CFLAGS = -Wc++11-extensions -Wmissing-declarations

SRCEXT = cpp
INC = -I ./include
SRCDIR = src
OBJDIR = obj
TEST = test

game2048:
	$(CC) -o $(EXEC) $(SRCDIR)/*.$(SRCEXT) $(INC) $(CFLAGS)

game2048_obj: main.o game.o linked-list.o

main.o: $(SRCDIR)/main.$(SRCEXT)
	$(CC) -c -o $(OBJDIR)/$@ $< $(INC) $(CFLAGS)

game.o: $(SRCDIR)/game.$(SRCEXT)
	$(CC) -c -o $(OBJDIR)/$@ $< $(INC) $(CFLAGS)

linked-list.o: $(SRCDIR)/linked-list.$(SRCEXT)
	$(CC) -c -o $(OBJDIR)/$@ $< $(INC) $(CFLAGS)

run: $(EXEC)
	./$(EXEC)

clean:
	$(RM) $(EXEC) $(OBJDIR)/*.o