CC = cc
CFLAGS = -g -Wall

PROG = suggest
HDRS = engine.h
SRCS = engine.c suggest.c

OBJDIR = object

OBJS = $(OBJDIR)/engine.o $(OBJDIR)/suggest.o $(OBJDIR)/levenshtein.o

# compiling rules
$(OBJDIR)/levenshtein.o:
	$(MAKE) -C levenshtein.c
	cp levenshtein.c/levenshtein.o $(OBJDIR)
# WARNING: *must* have a tab before each definition
$(PROG): $(OBJS) $(OBJDIR)
	$(CC) $(CFLAGS) $(OBJS) -o $(PROG)

$(OBJDIR)/suggest.o: suggest.c $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c suggest.c -o $(OBJDIR)/suggest.o

$(OBJDIR)/engine.o: engine.c $(HDRS) $(OBJDIR)
	$(CC) $(CFLAGS) -c engine.c -o $(OBJDIR)/engine.o


$(OBJDIR):
	mkdir $(OBJDIR)

clean:
	rm -f $(PROG) $(OBJS)



