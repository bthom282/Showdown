		xdef	_ikbd_isr
		xref	_ikbdisrC
		
_ikbd_isr:
			link	a6,#0
			movem.l	d0-d2/a0-a2,-(sp)
			jsr	_ikbdisrC
			movem.l	(sp)+,d0-d2/a0-a2
			unlk	a6
			rte