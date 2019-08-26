# srcrr
# Copyright (c) 2019, Colvin Wellborn

default: build

build: $(CURDIR)/srcrr

$(CURDIR)/srcrr: srcrr.c
	clang -o $(CURDIR)/srcrr srcrr.c

install: build
	install -o root -g wheel -m 775 $(CURDIR)/srcrr /usr/local/bin/
	mkdir -p /usr/local/share/man/man1
	install -o root -g wheel -m 775 $(CURDIR)/srcrr.1 /usr/local/share/man/man1/srcrr.1

install-inc:
	install -m 600 $(CURDIR)/srcrr.inc.bash $(HOME)/.srcrr.inc

clean:
	-rm srcrr

.PHONY: test
test: $(CURDIR)/srcrr
	./test.sh
