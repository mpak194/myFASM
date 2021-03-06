format PE console

entry start

include 'win32a.inc'

section '.data' data readable writable
        strA db 'Enter A: ', 0
        spaceStr db '%d', 0

        A dd ?

        NULL = 0

section '.code' code readable executable
        start:
                push strA
                call [printf]

                ; ���� �.
                push A
                push spaceStr
                call [scanf]

                ; ����� ���� ����� �� 0 �� ���������� �����.
                mov ebx, 0
                lp:
                         push ebx
                         push spaceStr
                         call [printf]

                    add ebx, 1
                    cmp ebx, [A]
                    jne lp
                    jmp finish


                finish:
                        call [getch]

                        push NULL
                        call [ExitProcess]

section '.idata' import data readable

        library kernel, 'kernel32.dll',\
                msvcrt, 'msvcrt.dll'

        import kernel,\
               ExitProcess, 'ExitProcess'

        import msvcrt,\
               printf, 'printf',\
               scanf, 'scanf',\
               getch, '_getch'