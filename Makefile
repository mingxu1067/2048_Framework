CC = g++
CFLAGS = -Wc++11-extensions -Wmissing-declarations

SRCEXT = cpp
BINDIR = bin
EXEC = 2048
INCDIR = include
INC = -I ./$(INCDIR)
BUILD = build
LIB_NAME = game2048_lib
SRCDIR = src
OBJDIR = obj
TEST = test

game2048:
	@mkdir -p $(BINDIR)
	$(CC) -o $(BINDIR)/$(EXEC) $(SRCDIR)/*.$(SRCEXT) $(INC) $(CFLAGS)

game2048_obj: main.o game.o linked-list.o

game2048_lib: game2048_obj
	@mkdir -p $(BUILD)/$(LIB_NAME)
	$(AR) rvs $(BUILD)/$(LIB_NAME)/$@.a $(OBJDIR)/game.o $(OBJDIR)/linked-list.o
	cp -r $(INCDIR) $(BUILD)/$(LIB_NAME)

main.o: $(SRCDIR)/main.$(SRCEXT)
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $(OBJDIR)/$@ $< $(INC) $(CFLAGS)

game.o: $(SRCDIR)/game.$(SRCEXT)
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $(OBJDIR)/$@ $< $(INC) $(CFLAGS)

linked-list.o: $(SRCDIR)/linked-list.$(SRCEXT)
	@mkdir -p $(OBJDIR)
	$(CC) -c -o $(OBJDIR)/$@ $< $(INC) $(CFLAGS)

run:
	./$(BINDIR)/$(EXEC)

clean:
	$(RM) -r $(BUILD) $(OBJDIR) $(BINDIR)