#!/usr/bin/env bash

set -e

CURDIR=$(pwd)

PREFIX=$(readlink -f $(dirname $0))

: ${SRCRR:="./srcrr"}
export SRCPATH="$PREFIX/test/one:$PREFIX/test/two"

. "$PREFIX"/func.bash

src foo
if [ -n "$TESTVAL" ]
then
	echo "PASS: TESTVAL is set"
else
	echo "FAIL: not set: TESTVAL"
	exit 1
fi
if [ "$TESTVAL" = "one/foo" ]
then
	echo "PASS: TESTVAL matches expected 'one/foo'"
else
	echo "FAIL: no match for TESTVAL: expected 'one/foo', got '$TESTVAL'"
	exit 1
fi

cd $CURDIR
unset TESTVAL

src bar
if [ -n "$TESTVAL" ]
then
	echo "PASS: TESTVAL is set"
else
	echo "FAIL: not set: TESTVAL"
	exit 1
fi
if [ "$TESTVAL" = "two/bar" ]
then
	echo "PASS: TESTVAL matches expected 'two/bar'"
else
	echo "FAIL: no match for TESTVAL: expected 'two/bar', got '$TESTVAL'"
	exit 1
fi
