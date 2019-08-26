# srcrr
# Copyright (c) 2019, Colvin Wellborn
# vim: ft=sh

function src() {
	: ${SRCRR:="srcrr"}
	case "$1" in
		-V)
			$SRCRR -V
			return;;
		-h)
			$SRCRR -h
			return;;
	esac
	eval $( $SRCRR $@ )
}

# Bash completion support for srcrr.
function _src_comp() {
	: ${SRCRR:="srcrr"}
	unset _src_words
	for proj in $( $SRCRR -l | sort -u )
	do
		_src_words+="$proj "
	done
	COMPREPLY+=( $( compgen -W "$_src_words" "${COMP_WORDS[1]}" ) )
}

complete -F _src_comp src
