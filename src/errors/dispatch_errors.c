#include "minishell.h"

/* if error_cose < 200 treat it as errno with perror 
	else its our error codes so we need dispatch table for it - if it possible cause 
	in dispatch we use or enum or from 0 and next is +1,
	for int 200 we can only make atoi and ther char 200 (?)*/