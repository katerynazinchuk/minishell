https://www.gnu.org/software/bash/manual/bash.html#Here-Documents
https://linuxize.com/post/bash-heredoc/
https://medium.com/@oduwoledare/heredoc-a-deep-dive-23c82992e522


Won't expand values inside:
cat << $SHELL''
cat << $SHELL""


strace -f bash -c $'cat << EOF
HIIIIIIIII
EOF
'

[pid 45446] pipe2([3, 4], 0)            = 0
[pid 45446] fcntl(4, F_GETPIPE_SZ)      = 65536
[pid 45446] write(4, "HIIIIIIIII\n", 11) = 11
[pid 45446] close(4)                    = 0
[pid 45446] dup2(3, 0)                  = 0
[pid 45446] close(3)                    = 0
[pid 45446] execve("/usr/bin/cat", ["cat"], 0x55be9c7810f0 /* 67 vars */) = 0


FOR INPUT BIGGER THAT 65536 BYTES - USE TEMP FILE
[pid 44167] openat(AT_FDCWD, "/tmp/sh-thd.E771Qw", O_RDWR|O_CREAT|O_EXCL, 0600) = 3
[pid 44167] fchmod(3, 0600)             = 0
[pid 44167] fcntl(3, F_SETFD, FD_CLOEXEC) = 0
[pid 44167] write(3, "gdfgdfgdfggdfgdfgdfggdfgdfgdfggd"..., 121001) = 121001
[pid 44167] openat(AT_FDCWD, "/tmp/sh-thd.E771Qw", O_RDONLY) = 4
[pid 44167] close(3)                    = 0
[pid 44167] unlink("/tmp/sh-thd.E771Qw") = 0
[pid 44167] fchmod(4, 0400)             = 0
[pid 44167] dup2(4, 0)                  = 0
[pid 44167] close(4)                    = 0
[pid 44167] execve("/usr/bin/cat", ["cat"], 0x556d07e26990 /* 67 vars */) = 0

<<h1<<h2<<h3<<h4<<h5<<h6<<h7<<h8<<h9<<h10<<h11<<h12<<h13<<h14<<h15<<h16<<h17


count lines:
$ <<eof
> 2
> 3
> 
bash: warning: here-document at line 1 delimited by end-of-file (wanted `eof')

$ <<eof
> 5
> 6
> 7
> 
bash: warning: here-document at line 4 delimited by end-of-file (wanted `eof')

$ <<eof
> 9
> 10
> 1
> 12
> 
bash: warning: here-document at line 8 delimited by end-of-file (wanted `eof')

$ <<eof
> 14
> 15
> 
bash: warning: here-document at line 13 delimited by end-of-file (wanted `eof')

$ <<eof
> 17
> eof

$ <<eof
> 20
> 21
> 
bash: warning: here-document at line 19 delimited by end-of-file (wanted `eof')
