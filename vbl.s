	xdef	_vbl_isr
	xref	_vbl_isr_c
	
_vbl_isr:
			movem.l	d0-d2/a0-a2, -(sp)
			jsr		_vbl_isr_c
			movem.l	(sp)+
			rte