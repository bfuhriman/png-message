CC = gcc
CFLAGS = -Wall -lpng -std=c99 -I./hdr

all: bin/encode bin/decode

bin/encode: obj/encode.o obj/utils.o obj/hamming.o obj/file.o
	$(CC) $(CFLAGS) -o bin/encode obj/encode.o obj/utils.o obj/hamming.o obj/file.o

bin/decode: obj/decode.o obj/utils.o obj/hamming.o obj/file.o
	$(CC) $(CFLAGS) -o bin/decode obj/decode.o obj/utils.o obj/hamming.o obj/file.o

obj/encode.o: src/encode.c hdr/encode.h hdr/utils.h hdr/hamming.h hdr/file.h
	$(CC) $(CFLAGS) -c src/encode.c -o obj/encode.o

obj/decode.o: src/decode.c hdr/decode.h hdr/utils.h hdr/hamming.h hdr/file.h
	$(CC) $(CFLAGS) -c src/decode.c -o obj/decode.o

obj/utils.o: src/utils.c hdr/utils.h
	$(CC) $(CFLAGS) -c src/utils.c -o obj/utils.o

obj/hamming.o: src/hamming.c hdr/hamming.h
	$(CC) $(CFLAGS) -c src/hamming.c -o obj/hamming.o

obj/file.o: src/file.c hdr/file.h
	$(CC) $(CFLAGS) -c src/file.c -o obj/file.o

clean:
	rm -f bin/* obj/*.o *.o
