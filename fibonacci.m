lvalue n
push 100
:=
lvalue f0
push 0
:=
rvalue f0
print
lvalue f1
push 1
:=
rvalue f1
print
label t20
rvalue n
gofalse o20
lvalue fnew
rvalue f0
rvalue f1
+
:=
rvalue fnew
print
lvalue f0
rvalue f1
:=
lvalue f1
rvalue fnew
:=
lvalue n
rvalue n
push 1
-
:=
goto t20
label o20
halt
