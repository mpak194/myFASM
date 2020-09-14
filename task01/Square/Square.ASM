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

                ; ¬‚Ó‰ ¿.
                push A
                push spaceStr
                call [scanf]

                mov ecx, [A]
                imul ecx, [A] ; A * A.

                push ecx
                push spaceStr
                call [printf]


                call[getch]
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
