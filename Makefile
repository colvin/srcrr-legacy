default: build

build: $(CURDIR)/srcrr

$(CURDIR)/srcrr:
	clang -o $(CURDIR)/srcrr srcrr.c

install: build
	install -o root -g wheel -m 775 $(CURDIR)/srcrr /usr/local/bin/
	mkdir -p /usr/local/share/man/man1
	install -o root -g wheel -m 775 $(CURDIR)/srcrr.1 /usr/local/share/man/man1/srcrr.1

clean:
	-rm srcrr

.PHONY: test
test:
	./test.sh
