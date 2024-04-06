	xdef	_vbl_isr
	xref	_vblisrC
	
_vbl_isr:
			movem.l	d0-d2/a0-a2,-(sp)
			jsr		_vblisrC
			movem.l	(sp)+,d0-d2/a0-a2
			rte