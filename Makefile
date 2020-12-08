CC=clang
CFLAGS=-Wall -g
BINS=programm

all: ${BINS}

programm: main.c utils.o city.o area.o street.o -lm
	${CC} ${CFLAGS} -o $@ $^

utils.o: utils.c utils.h
	${CC} ${CFLAGS} -c $<

area.o: area.c area.h
	${CC} ${CFLAGS} -c $<

city.o: city.c city.h
	${CC} ${CFLAGS} -c $<

street.o: street.c street.h
	${CC} ${CFLAGS} -c $<

clean:
	rm -rf *.o ${BINS}

