Scanner:
The first stage, the scanner, is usually based on a finite-state machine (FSM). It has encoded within it information on the possible sequences of characters that can be contained within any of the tokens it handles (individual instances of these character sequences are termed lexemes). For example, an integer lexeme may contain any sequence of numerical digit characters. In many cases, the first non-whitespace character can be used to deduce the kind of token that follows and subsequent input characters are then processed one at a time until reaching a character that is not in the set of characters acceptable for that token (this is termed the maximal munch, or longest match, rule). In some languages, the lexeme creation rules are more complex and may involve backtracking over previously read characters. For example, in C, one 'L' character is not enough to distinguish between an identifier that begins with 'L' and a wide-character string literal.

Source: https://en.wikipedia.org/wiki/Lexical_analysis#Scanner

--

Some characters are evaluated by Bash to have a non-literal meaning. Instead, these characters carry out a special instruction, or have an alternate meaning; they are called "special characters", or "meta-characters". 
Whitespace — this is a tab, newline, vertical tab, form feed, carriage return, or space. Bash uses whitespace to determine where words begin and end. The first word is the command name and additional words become arguments to that command.

1. '\t'	(horizontal tab)
2. '\n'	(new line)
3. '\v'	(vertical tab)
4. '\f'	(form feed)
5. '\r'	(carriage ret)
6. ' '	(space)

Source: https://mywiki.wooledge.org/BashGuide/SpecialCharacters

--

3.5.7 Word Splitting

The shell scans the results of parameter expansion, command substitution, and arithmetic expansion that did not occur within double quotes for word splitting.

The shell treats each character of $IFS as a delimiter, and splits the results of the other expansions into words using these characters as field terminators. If IFS is unset, or its value is exactly <space><tab><newline>, the default, then sequences of <space>, <tab>, and <newline> at the beginning and end of the results of the previous expansions are ignored, and any sequence of IFS characters not at the beginning or end serves to delimit words. If IFS has a value other than the default, then sequences of the whitespace characters space, tab, and newline are ignored at the beginning and end of the word, as long as the whitespace character is in the value of IFS (an IFS whitespace character). Any character in IFS that is not IFS whitespace, along with any adjacent IFS whitespace characters, delimits a field. A sequence of IFS whitespace characters is also treated as a delimiter. If the value of IFS is null, no word splitting occurs.

Explicit null arguments ("" or '') are retained and passed to commands as empty strings. Unquoted implicit null arguments, resulting from the expansion of parameters that have no values, are removed. If a parameter with no value is expanded within double quotes, a null argument results and is retained and passed to a command as an empty string. When a quoted null argument appears as part of a word whose expansion is non-null, the null argument is removed. That is, the word -d'' becomes -d after word splitting and null argument removal.

Note that if no expansion occurs, no splitting is performed.

Sources: https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#Word-Splitting

IFS

A list of characters that separate fields; used when the shell splits words as part of expansion.

local IFS=$' \t\n'    # normalize IFS

Example of IFS symbols: https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#A-Programmable-Completion-Example
IFS: https://en.wikipedia.org/wiki/Input_Field_Separators

DFA implementation in C: https://www.youtube.com/watch?v=MAQUNynQu_E