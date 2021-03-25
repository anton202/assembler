MAIN:   add  r3, LIST
LOOP:   prn  #48
	lea  STR, r6
	inc  r6
	mov  r3, K
	
	sub  r1, r3
	
	bne  END
	dec  K
	jmp %LOOP
END:    stop
SRT:    .string "abcd"
LIST:   .data  6 , -9
	.data -100
.entry K
K:      .data  31
.extern val1
