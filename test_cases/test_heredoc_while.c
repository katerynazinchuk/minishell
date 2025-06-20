tchernia:~$ cat Makefile |
minishell> ls |
minishell> echo <<h
AST_PIPE:    
 AST_PIPE:    
  AST_COMMAND: [cat] [Makefile] 
  AST_COMMAND: [ls] 
 AST_COMMAND: [echo] <<'h' 
heredoc> nlnl
heredoc> ^C
tchernia:~$ 
exit
==32697== 
==32697== HEAP SUMMARY:
==32697==     in use at exit: 208,489 bytes in 239 blocks
==32697==   total heap usage: 1,230 allocs, 991 frees, 350,079 bytes allocated
==32697== 
==32697== 1 bytes in 1 blocks are definitely lost in loss record 1 of 68
==32697==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==32697==    by 0x48AEBAC: xmalloc (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==32697==    by 0x488C694: readline_internal_teardown (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==32697==    by 0x4896D2A: readline (in /usr/lib/x86_64-linux-gnu/libreadline.so.8.1)
==32697==    by 0x404BD5: write_heredoc_lines (heredoc.c:52)
==32697==    by 0x404DA5: expand_heredoc (heredoc.c:101)
==32697==    by 0x404F1E: heredoc_foreach_redir (utils_heredoc.c:21)
==32697==    by 0x404EA4: heredoc_foreach_ast (utils_heredoc.c:32)
==32697==    by 0x404ED3: heredoc_foreach_ast (utils_heredoc.c:36)
==32697==    by 0x404E46: heredoc (heredoc.c:118)
==32697==    by 0x406407: process_line (rewrite_main.c:85)
==32697==    by 0x406373: shell_loop (rewrite_main.c:73)
==32697== 
==32697== 15 bytes in 1 blocks are definitely lost in loss record 10 of 68
==32697==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==32697==    by 0x406AC7: ft_strjoin (ft_strjoin.c:24)
==32697==    by 0x404B4E: create_heredoc_filename (heredoc.c:33)
==32697==    by 0x404D34: expand_heredoc (heredoc.c:90)
==32697==    by 0x404F1E: heredoc_foreach_redir (utils_heredoc.c:21)
==32697==    by 0x404EA4: heredoc_foreach_ast (utils_heredoc.c:32)
==32697==    by 0x404ED3: heredoc_foreach_ast (utils_heredoc.c:36)
==32697==    by 0x404E46: heredoc (heredoc.c:118)
==32697==    by 0x406407: process_line (rewrite_main.c:85)
==32697==    by 0x406373: shell_loop (rewrite_main.c:73)
==32697==    by 0x4062AC: run_shell (rewrite_main.c:54)
==32697==    by 0x406259: main (rewrite_main.c:40)
==32697== 
==32697== LEAK SUMMARY:
==32697==    definitely lost: 16 bytes in 2 blocks
==32697==    indirectly lost: 0 bytes in 0 blocks
==32697==      possibly lost: 0 bytes in 0 blocks
==32697==    still reachable: 0 bytes in 0 blocks
==32697==         suppressed: 208,473 bytes in 237 blocks
==32697== 
==32697== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
--32697-- 
--32697-- used_suppression:     62 <Readline> readline.supp:2 suppressed: 204,167 bytes in 221 blocks
--32697-- used_suppression:      4 <Readline/AddHistory> readline.supp:10 suppressed: 4,306 bytes in 16 blocks
==32697== 
==32697== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
make: *** [Makefile:89: valgrind] Error 130