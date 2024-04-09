	xdef	_vbl_isr
	xref	_vblisrC
	
_vbl_isr:
			link	a6,#0
			movem.l	d0-d2/a0-a2,-(sp)
			jsr		_vblisrC
			movem.l	(sp)+,d0-d2/a0-a2
			unlk	a6
			rte