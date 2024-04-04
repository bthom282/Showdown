		xdef	_ikbd_isr
		xref	_ikbd_isr_c
		
_ikbd_isr:
			movem.l	d0-d2/a0-a2,-(sp)
			jsr	_ikbd_isr_c
			movem.l	(sp)+,d0-d2/a0-a2
			rte