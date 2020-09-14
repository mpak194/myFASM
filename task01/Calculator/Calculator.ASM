format PE console

entry start

include 'win32a.inc'

section '.data' data readable writable
        strA db 'Enter A: ', 0
        strB db 'Enter B: ', 0
        strOp db 'Enter operation: ', 0

        resStr db 'Result: %d', 0
        resMod db '/%d', 0

        spaceStr db ' %d', 0
        emptyStr db '%d', 0

        infinity db 'infinity', 0
        point db ',', 0

        A dd ?
        B dd ?
        C dd ?

        NULL = 0

section '.code' code readable executable
        start:
                push strA
                call [printf]

                ; Ввод А.
                push A
                push spaceStr
                call [scanf]

                push strB
                call [printf]

                ; Ввод В.
                push B
                push spaceStr
                call [scanf]

                ; Ввод операции.
                push strOp
                call [printf]

                call [getch]

                cmp eax, 43 ; Сумма.
                jne notAdd
                    mov ecx, [A]
                    add ecx, [B] ; A + B.

                    push ecx
                    push resStr
                    call [printf]

                    jmp finish

                notAdd:

                cmp eax, 45 ; Разность.
                jne notSub
                    mov ecx, [A]
                    sub ecx, [B] ; A - B.

                    push ecx
                    push resStr
                    call [printf]

                    jmp finish

                notSub:

                cmp eax, 42 ; Умножение.
                jne notMul
                    mov ecx, [A]
                    imul ecx, [B] ; A * B.

                    push ecx
                    push resStr
                    call [printf]

                    jmp finish

                notMul:

                cmp eax, 37 ; Остаток.
                jne notMod
                    mov eax, [A]
                    mov ecx, [B]
                    mov edx, 0

                    cmp [B], 0 ; Провера деления на 0.
                    jne notNullDiv
                        push infinity
                        call [printf]

                        jmp finish
                    notNullDiv:
                        div ecx
                        mov [C], edx

                        push eax
                        push resStr
                        call [printf]

                        push [C]
                        push spaceStr
                        call [printf]

                        push [B]
                        push resMod
                        call [printf]

                        jmp finish
                notMod:

                cmp eax, 47 ; Деление.
                jne notDiv
                    mov eax, [A]
                    mov ecx, [B]
                    mov edx, 0

                    cmp [B], 0 ; Проверка деления на 0.
                    jne notNullDiv1
                        push infinity
                        call [printf]

                        jmp finish
                    notNullDiv1:
                        div ecx ;
                        mov [C], edx

                        push eax
                        push resStr
                        call [printf]

                        push point
                        call [printf]

                        mov ebx, 0
                        lp:
                                mov eax, [C]
                                mov ecx, [B]
                                imul eax, 10

                                mov edx, 0
                                div ecx
                                mov [C], edx

                                push eax
                                push emptyStr
                                call [printf]

                        add ebx, 1
                        cmp ebx, 3
                        jne lp
                        jmp finish

                notDiv:

                finish:
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
