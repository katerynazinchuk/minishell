3.1.2 Quoting

Quoting is used to remove the special meaning of certain characters or words to the shell. Quoting can be used to disable special treatment for special characters, to prevent reserved words from being recognized as such, and to prevent parameter expansion.

Each of the shell metacharacters (see Definitions) has special meaning to the shell and must be quoted if it is to represent itself. When the command history expansion facilities are being used (see History Expansion), the history expansion character, usually ‘!’, must be quoted to prevent history expansion. See Bash History Facilities, for more details concerning history expansion.

There are three quoting mechanisms: the escape character, single quotes, and double quotes.

    Escape Character
    Single Quotes
    Double Quotes
    ANSI-C Quoting
    Locale-Specific Translation


3.1.2.1 Escape Character

A non-quoted backslash ‘\’ is the Bash escape character. It preserves the literal value of the next character that follows, with the exception of newline. If a \newline pair appears, and the backslash itself is not quoted, the \newline is treated as a line continuation (that is, it is removed from the input stream and effectively ignored).

3.1.2.2 Single Quotes

Enclosing characters in single quotes (‘'’) preserves the literal value of each character within the quotes. A single quote may not occur between single quotes, even when preceded by a backslash. 

3.1.2.3 Double Quotes

Enclosing characters in double quotes (‘"’) preserves the literal value of all characters within the quotes, with the exception of ‘$’, ‘`’, ‘\’, and, when history expansion is enabled, ‘!’. When the shell is in POSIX mode (see Bash POSIX Mode), the ‘!’ has no special meaning within double quotes, even when history expansion is enabled. The characters ‘$’ and ‘`’ retain their special meaning within double quotes (see Shell Expansions). The backslash retains its special meaning only when followed by one of the following characters: ‘$’, ‘`’, ‘"’, ‘\’, or newline. Within double quotes, backslashes that are followed by one of these characters are removed. Backslashes preceding characters without a special meaning are left unmodified. A double quote may be quoted within double quotes by preceding it with a backslash. If enabled, history expansion will be performed unless an ‘!’ appearing in double quotes is escaped using a backslash. The backslash preceding the ‘!’ is not removed. 

Sources:
https://www.gnu.org/software/bash/manual/html_node/Quoting.html
https://stackoverflow.com/questions/6697753/difference-between-single-and-double-quotes-in-bash