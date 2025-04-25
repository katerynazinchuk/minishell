1. export a="a"
> echo $a$a$a
> aaa

2. export a="a "
> echo $a$a$a
> a a a

3. export a=" a"
> echo $a$a$a
> a a a

4. export a=" a "
> echo $a$a$a
> a a a

5. export a="a1 a2 a3"
> echo $a$a$a
> a1 a2 a3a1 a2 a3a1 a2 a3

6. export a="a1 a2 a3 "
> echo $a$a$a
> a1 a2 a3 a1 a2 a3 a1 a2 a3

7. export a=" a1 a2 a3"
> echo ""$a$a$a
> a1 a2 a3 a1 a2 a3 a1 a2 a3

8. export a=" a1 a2 a3 "
> echo $a$a$a
> a1 a2 a3 a1 a2 a3 a1 a2 a3

9. export a="a1        a2          a3"
> echo $a$a$a
> a1 a2 a3a1 a2 a3a1 a2 a3