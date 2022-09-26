PROG = cwdof
SRCS = cwdof.c
OBJS = cwdof.o

PREFIX ?= /usr/local
MANPREFIX ?= ${PREFIX}/man

all: ${PROG}

${PROG}: ${OBJS}
	${CC} ${LDFLAGS} -o $@ ${OBJS}

.c.o:
	${CC} ${CFLAGS} ${CPPFLAGS} -c $<

clean:
	-rm ${OBJS} ${PROG}

install: all
	install -D -m 755 ${PROG} ${DESTDIR}${PREFIX}/bin/${PROG}
	install -D -m 644 ${PROG}.1 ${DESTDIR}${MANPREFIX}/man1/${PROG}.1

uninstall:
	rm -f ${DESTDIR}/${PREFIX}/bin/${PROG}
	rm -f ${DESTDIR}/${MANPREFIX}/man1/${PROG}.1

.PHONY: all clean install uninstall
