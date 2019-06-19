default: build

build: $(CURDIR)/srcrr

$(CURDIR)/srcrr:
	clang -o $(CURDIR)/srcrr srcrr.c

install: build
	install -o root -g wheel -m 775 $(CURDIR)/srcrr /usr/local/bin/

clean:
	-rm srcrr

.PHONY: test
test:
	./test.sh
