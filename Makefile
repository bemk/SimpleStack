OFILES:=stack.o test.o
HFILES:=stack.h
EXECUTABLE:=SimpleStack

CC=clang
LD=clang

.phony: all clean
all: $(EXECUTABLE)

$(EXECUTABLE): $(OFILES) $(HFILES)
	$(LD) -o $@ $(OFILES)

clean:
	rm -fv $(OFILES) $(EXECUTABLE)

