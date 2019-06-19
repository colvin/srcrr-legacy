default: build

build:
	clang -o srcrr srcrr.c

clean:
	-rm srcrr

.PHONY: test
test:
	./test.sh
