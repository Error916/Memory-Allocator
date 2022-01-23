CFLAGS= -ggdb -Wall -Wextra -std=c11 -pedantic -O3
LIBS= -lpthread
SRC= src/main.c src/memall.c
ifeq ($(PREFIX),)
    PREFIX := /usr/local
endif

main: $(SRC)
	$(CC) $(CFLAGS) -o main $(SRC) $(LIBS)

install: main
	sudo install -d $(DESTDIR)$(PREFIX)/bin/ || su -c="install -d $(DESTDIR)$(PREFIX)/bin/"
	sudo install -m 644 main $(DESTDIR)$(PREFIX)/bin/ || su -c="install -m 644 main $(DESTDIR)$(PREFIX)/bin/"
	sudo chmod +x $(DESTDIR)$(PREFIX)/bin/main

clean:
	rm main
