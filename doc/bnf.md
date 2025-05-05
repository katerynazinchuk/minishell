<PIPELINE>		::=	<PIPELINE> '|' <PIPELINE>
				|	<COMMAND>

<COMMAND-BLOCK>	::=	<STRING>
				|	<REDIRECTION>

<COMMAND>		::=	<COMMAND-BLOCK>
				|	<COMMAND> <COMMAND-BLOCK>

<REDIRECTION>	::=	'>' <STRING>
				|	'<' <STRING>
				|	'>>' <STRING>
				|	'<<' <STRING>

https://pubs.opengroup.org/onlinepubs/009604499/utilities/xcu_chap02.html