lvalue i
push 100000
:=
lvalue aprev
push 7
:=
lvalue n
push 1
:=
label t14
rvalue i
gofalse o14
lvalue n
rvalue n
push 1
+
:=
lvalue k
rvalue n
:=
lvalue m
rvalue aprev
:=
label t34
rvalue m
gofalse o34
lvalue t
rvalue m
:=
lvalue m
rvalue k
rvalue m
mod
:=
lvalue k
rvalue t
:=
goto t34
label o34
lvalue anew
rvalue aprev
rvalue k
+
:=
lvalue i
rvalue i
push 1
-
:=
rvalue anew
rvalue aprev
-
push 1
-
gofalse 74
rvalue anew
rvalue aprev
-
print
label 74
lvalue aprev
rvalue anew
:=
goto t14
label o14
halt
