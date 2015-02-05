
OFILES:=stack.o test.o
HFILES:=stack.h
EXECUTABLE:=SimpleStack

CC=clang

.phony: all
all: $(OFILES) $(HFILES)
	$(CC) -o $(EXECUTABLE) $(OFILES)

clean:
	rm -fv $(OFILES) $(EXECUTABLE)
