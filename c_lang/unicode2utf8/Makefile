
CC = gcc

.SUFFIXES: .c .o

.c.o:
	$(CC) -c -o $@ $^


all: ConvUnicode2Utf8
	@echo "All"

ConvUnicode2Utf8: ConvUnicode2Utf8.o
	@echo $@
	$(CC) -o $@ $^

ConvUnicode2Utf8.o: ConvUnicode2Utf8.c

clean:
	-rm ConvUnicode2Utf8 *.o
