; Listing generated by Microsoft (R) Optimizing Compiler Version 19.28.29333.0 

	TITLE	c:\users\matsumotominoru\desktop\visual studio 2019\c++_console\assembly\func1\consoleapplication1\consoleapplication1.cpp
	.686P
	.XMM
	include listing.inc
	.model	flat

INCLUDELIB OLDNAMES

PUBLIC	?a4@@3HA					; a4
PUBLIC	?b3@@3HA					; b3
PUBLIC	?a2@@3HA					; a2
PUBLIC	?b1@@3HA					; b1
PUBLIC	?a1@@3HA					; a1
PUBLIC	?b4@@3HA					; b4
PUBLIC	?b2@@3HA					; b2
PUBLIC	?a3@@3HA					; a3
PUBLIC	?b5@@3HA					; b5
PUBLIC	?a5@@3HA					; a5
EXTRN	@__security_check_cookie@4:PROC
?b3@@3HA DD	01H DUP (?)				; b3
?b1@@3HA DD	01H DUP (?)				; b1
?b4@@3HA DD	01H DUP (?)				; b4
?b2@@3HA DD	01H DUP (?)				; b2
?b5@@3HA DD	01H DUP (?)				; b5
_BSS	ENDS
?a4@@3HA DD	04H					; a4
?a2@@3HA DD	02H					; a2
?a1@@3HA DD	01H					; a1
?a3@@3HA DD	03H					; a3
?a5@@3HA DD	05H					; a5
_DATA	ENDS
PUBLIC	_main
; Function compile flags: /Odtp
; File C:\Users\MatsumotoMinoru\Desktop\Visual Studio 2019\C++_Console\Assembly\func1\ConsoleApplication1\ConsoleApplication1.cpp
;	COMDAT _main
_TEXT	SEGMENT
_c10$ = -40						; size = 4
_c9$ = -36						; size = 4
_c8$ = -32						; size = 4
_c7$ = -28						; size = 4
_c6$ = -24						; size = 4
_c5$ = -20						; size = 4
_c4$ = -16						; size = 4
_c3$ = -12						; size = 4
_c2$ = -8						; size = 4
_c1$ = -4						; size = 4
_main	PROC						; COMDAT

; 12   : {

	push	ebp
	mov	ebp, esp
	sub	esp, 40					; 00000028H

; 13   :     int c1, c2, c3, c4, c5, c6, c7, c8, c9, c10;
; 14   : 
; 15   :     c1 = 1;

	mov	DWORD PTR _c1$[ebp], 1

; 16   :     c2 = 2;

	mov	DWORD PTR _c2$[ebp], 2

; 17   :     c3 = 3;

	mov	DWORD PTR _c3$[ebp], 3

; 18   :     c4 = 4;

	mov	DWORD PTR _c4$[ebp], 4

; 19   :     c5 = 5;

	mov	DWORD PTR _c5$[ebp], 5

; 20   :     c6 = 6;

	mov	DWORD PTR _c6$[ebp], 6

; 21   :     c7 = 7;

	mov	DWORD PTR _c7$[ebp], 7

; 22   :     c8 = 8;

	mov	DWORD PTR _c8$[ebp], 8

; 23   :     c9 = 9;

	mov	DWORD PTR _c9$[ebp], 9

; 24   :     c10 = 10;

	mov	DWORD PTR _c10$[ebp], 10		; 0000000aH

; 25   : 
; 26   :     a1 = c1;

	mov	eax, DWORD PTR _c1$[ebp]
	mov	DWORD PTR ?a1@@3HA, eax			; a1

; 27   :     a2 = c2;

	mov	ecx, DWORD PTR _c2$[ebp]
	mov	DWORD PTR ?a2@@3HA, ecx			; a2

; 28   :     a3 = c3;

	mov	edx, DWORD PTR _c3$[ebp]
	mov	DWORD PTR ?a3@@3HA, edx			; a3

; 29   :     a4 = c4;

	mov	eax, DWORD PTR _c4$[ebp]
	mov	DWORD PTR ?a4@@3HA, eax			; a4

; 30   :     a5 = c5;

	mov	ecx, DWORD PTR _c5$[ebp]
	mov	DWORD PTR ?a5@@3HA, ecx			; a5

; 31   :     b1 = c6;

	mov	edx, DWORD PTR _c6$[ebp]
	mov	DWORD PTR ?b1@@3HA, edx			; b1

; 32   :     b2 = c7;

	mov	eax, DWORD PTR _c7$[ebp]
	mov	DWORD PTR ?b2@@3HA, eax			; b2

; 33   :     b3 = c8;

	mov	ecx, DWORD PTR _c8$[ebp]
	mov	DWORD PTR ?b3@@3HA, ecx			; b3

; 34   :     b4 = c9;

	mov	edx, DWORD PTR _c9$[ebp]
	mov	DWORD PTR ?b4@@3HA, edx			; b4

; 35   :     b5 = c10;

	mov	eax, DWORD PTR _c10$[ebp]
	mov	DWORD PTR ?b5@@3HA, eax			; b5

; 36   : 
; 37   : }

	xor	eax, eax
	mov	esp, ebp
	pop	ebp
	ret	0
_main	ENDP
_TEXT	ENDS
END
