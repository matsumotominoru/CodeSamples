;jump to label @1
jmp short @1

;compare ebx and 1
cmp ebx, 1
;if ebx is lower than 1, jump to label @2
jl short @2

;compare eax and 2
cmp eax, 2
;if eax is lower than 2 or equal to 2, jump to label @3
jle short @3

;compare eax and 3
cmp eax, 3
;if eax is greater than 3 or equal to 3, jump to label @4
jge short @4

;compare ebx and 1
cmp ebx, 1
;if ebx equals to 1, jump to label @2
je short @2

;compare ebx and 1
cmp ebx, 1
;if ebx equals to 1, jump to label @2
jz short @2

;compare ebx and 1
cmp ebx, 1
;if ebx does not equal to 1, jump to label @2
jne short @2

;compare ebx and 1
cmp ebx, 1
;if ebx does not equal to 1, jump to label @2
jnz short @2

test eax, eax
;is equivalent to 
cmp eax, 0
;the result of cmp opecode is stored to flag register, for example, zf flag register stores whether two values are same.


;Symbols reference
;https://learn.microsoft.com/en-us/cpp/assembler/masm/symbols-reference
@@:
;Defines a code label recognizable only between label1 and label2, where label1 is either start of code or the previous @@: label, and label2 is either end of code or the next @@: label. 

@B
;The location of the previous @@: label.

@F
;The location of the next @@: label.

