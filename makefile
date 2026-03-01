OBJ:= $(patsubst %.c, %.o, $(wildcard *.c))
Inverted.exe: $(OBJ)
	gcc -o $@ $^

clean:
	rm *.exe *.o