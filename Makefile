SRCDIR = src
OBJDIR = obj
BINDIR = bin
LIBDIR = lib
INC = -Iinclude
LIB =
CFLAGS = -std=c11 -Wall -Wextra -O3

RTESTSRC = replacechr.test.c replacechr.c
RTESTOBJ = ${RTESTSRC:%.c=${OBJDIR}/%.o}
RTESTBIN = ${BINDIR}/replacechr.test

FTESTSRC = findchr.test.c findchr.c
FTESTOBJ = ${FTESTSRC:%.c=${OBJDIR}/%.o}
FTESTBIN = ${BINDIR}/findchr.test

LIBFR = ${LIBDIR}/libfr.a

.PHONY: clean all lib tests

lib: ${LIBFR}

tests: ${RTESTBIN} ${FTESTBIN}

all: lib tests

.prep:
	mkdir -p ${OBJDIR} ${BINDIR} ${LIBDIR}
	touch .prep

clean:
	rm -rf ${OBJDIR} ${BINDIR} ${LIBDIR} .prep

${LIBFR}: ${OBJDIR}/findchr.o ${OBJDIR}/replacechr.o
	ar rcs $@ $^

${OBJDIR}/%.test.o: ${SRCDIR}/tests/%.test.c .prep Makefile
	${CC} -o $@ -c ${INC} ${CFLAGS} $<

${OBJDIR}/%.o: ${SRCDIR}/%.c .prep Makefile
	${CC} -o $@ -c ${INC} ${CFLAGS} $<

${RTESTBIN}: ${RTESTOBJ}
	${CC} -o $@ ${INC} ${CFLAGS} ${RTESTOBJ} ${LIB}

${FTESTBIN}: ${FTESTOBJ}
	${CC} -o $@ ${INC} ${CFLAGS} ${FTESTOBJ} ${LIB}
