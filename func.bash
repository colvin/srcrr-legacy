function src() {
	: ${SRCRR:="srcrr"}
	eval $( $SRCRR $@ )
}

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
