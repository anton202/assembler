.entry	LIST
.extern	W
MAIN:	add	r3, LIST
LOOP:	prn	#48
	lea	W, r6
	inc	r6
	mov	r3
	sub	r1, r4 jdsfsj
	bne	END
	cmp	K, #-6
	bne	%END
	dec	W
.entry MAIN
	jmp	%LOOP
	add	L3, L3
ENDnsjnsjdnsjvnsjdfnsjfnsfjnsdjfksndfjn:	stop

STR:	.string "abcdfgsndgskfnskfdnsfdklanfaklnfafklnafknadfknafknafknafkanfkalnfakfn
LIST:	.data	6, -9
	.data	-100
K:	.data 31
.extern	L3
