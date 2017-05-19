CFLAGS = -Werror -std=c99 -O2
DEPS=main.c circular-buf.c min-heap.c
PRGM=accel

MAIN: $(DEPS)
	$(CC) $(CFLAGS) $(DEPS) -o $(PRGM)

clean:
	rm *.o $(PRGM)
