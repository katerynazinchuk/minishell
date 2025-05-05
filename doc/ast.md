                         __ PIPELINE__
                     ___/              \____
                    /                       \
            COMMAND                    __ PIPELINE _
          /        \                  /             \
    ARGUMENTS   REDIRECTIONS      COMMAND         _ COMMAND __
        |          |     |           |           /            \
       cat        <<     >       ARGUMENTS    ARGUMENTS   REDIRECTIONS
                   |     |         |   |      |   |   |        |
                 "..."  file      wc  -c      tr  -d " "       >
                                                               |
                                                             file2

Notable differences from yours:

    Commands are composed of a list of arguments and a list of redirections.
    Redirections have a type (<, >, >>, etc.) and a either a string or a file as source/target.
    The EOF heredoc is converted to a plain string node ("..." above). A here document is ultimately just syntactical sugar for a string. If I were doing it I'd handle EOF at the lexing stage and turn it into a simple string for the parser to handle. EOF wouldn't show up in the AST.

It's a rough sketch, but the idea is to represent the components in a more logical manner. The way you drew yours, > and << look like binary operators with the other pieces as operands. That's how you'd parse a C program, but not a shell command.


https://stackoverflow.com/questions/52666511/create-an-ast-from-bash-in-c