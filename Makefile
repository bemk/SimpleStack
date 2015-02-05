
OFILES:=stack.o test.o
HFILES:=stack.h
EXECUTABLE:=SimpleStack

.phony: all
all: $(OFILES) $(HFILES)
	gcc -o $(EXECUTABLE) $(OFILES)

clean:
	rm -fv $(OFILES) $(EXECUTABLE)
