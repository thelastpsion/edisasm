	.model	small
	.8086
	.code
A9WControlRW		equ	0002h
  A9RControl record	A9MFrc2Is512KHzOr1KHz:1,A9MFrc2PreScale:1,\
    			A9MFrc1Is512KHzOr1Hz:1,A9MFrc1PreScale:1,\
    			A9MSoundEnable:1,A9MLcdEnable:1,\
    			A9MLowBatNMIEnable:1,A9MDoorNMIEnable:1,\
    			A9MZeroIsGrayMode:1,A9MArmStandBy:1,\
    			A9MDisableDMADivide:1,A9MRamDeviceSize:2,\
    			A9MDisableMemWait:1,A9MDisableIoWait:1,\
    			A9MDisableClockDivide:1
  A9VRam256KBits	equ	(0 shl A9MRamDeviceSize)
  A9VRam1MBits		equ	(1 shl A9MRamDeviceSize)
  A9VRam4MBits		equ	(2 shl A9MRamDeviceSize)
  A9VRam16MBits		equ	(3 shl A9MRamDeviceSize)
  A9XRamDeviceSizeMask	equ	(3 shl A9MRamDeviceSize)
A9WStatusR		equ	0004h
  A9RStatus record	A9MCold:1,A9MPowerFail:1,\
    			A9MReset:1,A9MNoBattery:1,\
    			A9MFifoFull:1,A9MSlaveOverrun:1,\
    			A9MSlaveControlFrame:1,A9MSlaveDataValid:1,\
    			A9MKeyboard:1,A9MSlaveClock:1,\
    			A9MMainsPresent:1,A9MDoorSwitch:1,\
    			A9MLowBatNMI:1,A9MDoorNMI:1,\
    			A9MProtectedModeNMI:1,A9MWatchDogNMI:1
  A9MLcdType		equ	8
  A9XLcdType		equ	0000111100000000b
A9WLcdSizeW		equ	0004h
  A9RLcdSize record	A9MLcdLineLength:5,A9MLcdNumberOfPixels:11
A9WLcdControlW		equ	0006h
  A9RLcdControl record	A9MLcdMode:2,A9MLcdACLineRate:5,A9MLcdPixelRate:5
  A9VSinglePage1	equ	(0 shl A9MLcdMode)
  A9VSinglePage2	equ	(1 shl A9MLcdMode)
  A9VSinglePage1And2	equ	(2 shl A9MLcdMode)
  A9VDualPage1And2	equ	(3 shl A9MLcdMode)
A9BInterruptStatusR	equ	0006h
A9BInterruptMaskRW	equ	0008h
  A9RInterrupts record	A9MFrc2:1,A9MFrc1:1,\
    			A9MExpIntB:1,A9MExpIntA:1,A9MExpIntC:1,\
    			A9MSlave:1,A9MTimer:1,A9MSound:1
A9BNmiClearW		equ	0009h
A9BNonSpecificEoiW	equ	000ah
A9BStartFlagClearW	equ	000bh
A9BTimerEoiW		equ	000ch
A9BSerialSlaveEoiW	equ	000dh
A9BFrc1EoiW		equ	000eh
A9BFrc2EoiW		equ	000fh
A9WResetWatchDogW	equ	0010h
A9WFrc1DataRW		equ	0012h
A9BProtectionOnW	equ	0014h
A9BProtectionOffR	equ	0014h
A9BProtectionOffW	equ	0015h
A9WProtectionUpperW	equ	0016h
A9WProtectionLowerW	equ	0018h
A9BSoundDataRW		equ	001ah
A9BSoundEoiW		equ	001ch
A9WFrc2DataRW		equ	001eh
A9WPortABDataRW		equ	0020h
  A9RPortABData record  A9MKeyIdX2:1,A9MNiCdDetect:1,\
    			A9MBatLevel2:1,A9MBatLevel1:1,A9MLiBatLevel:1,\
    			A9MKeyIdX1:1,A9MKeyIdX0:0,A9MKeyRowX8:1,\
    			A9MCradle:1,A9MKeyRowX:7
A9BPortADataRW		equ	0020h
A9BPortBDataRW		equ	0021h
A9WPortABDDRRW		equ	0022h
  A9VPortABDDR		equ	0000000000000000b
A9BPortADDRRW		equ	0022h
A9BPortBDDRRW		equ	0023h
A9WPortCDDataRW		equ	0024h
  A9RPortCDData record	A9MVccPacksEnable:1,A9MCodecEnable:1,\
    			A9MVccLcdEnable:1,A9MLcdPanelEnable:1,\
    			A9MLcdContrast:4,A9MVolume:2,\
    			A9MReproEnable:1,A9MAltDoorNMIEnable:1,\
    			A9MAmplifierEnable:1,A9MKeyIdEnable:1,\
    			A9MBuzVolX:1,A9MBacklightEnableX:1
  A9VVolumeLow		equ	(mask A9MVolume)
  A9VPortCDData		equ	0000111100000000b
  A9VPortCDDDR		equ	not (1111000011111111b)
A9BPortCDataRW		equ	0024h
A9BPortDDataRW		equ	0025h
A9WPortCDDDRRW		equ	0026h
A9BPortCDDRRW		equ	0026h
A9BPortDDDRRW		equ	0027h
A9BPageSelect6000RW	equ	0028h
A9BPageSelect7000RW	equ	0029h
A9BPageSelect8000RW	equ	002ah
A9BPageSelect9000RW	equ	002bh
  A9RControlExtraRW record A9MSlaveIntEnable:1,A9MClkDiv:2,\
    			A9MClockEnable5:1,A9MClockEnable4:1,\
    			A9MClockEnable3:1,A9MClockEnable2:1,\
    			A9MClockEnable1:1,A9MSoundDir:1,\
    			A9MExonDisable:1,A9MBuzzFromFrc1OrTog:1,\
    			A9MBuzzTog:1,A9MKeyCol:4
  A9VKeyColHigh		equ	0
  A9VKeyColLow		equ	1
  A9VKeyCol0		equ	8
  A9VClkDiv1		equ	(3 shl A9MClkDiv)
  A9VClkDiv2		equ	(2 shl A9MClkDiv)
  A9VClkDiv3		equ	(1 shl A9MClkDiv)
  A9VClkDiv4		equ	(0 shl A9MClkDiv)
A9WPumpControlRW	equ	002eh
  A9RPumpControl record A9MVhPumpDc:4,A9MVhPumpBat:4,\
    			A9MLcdPump:4,A9MPump2:4
  A9VVhPumpBat		equ	(14 shl A9MVhPumpBat)
  A9VVhPumpBatSoft	equ	(4 shl A9MVhPumpBat)
  A9VVhPumpBatMedium	equ	(8 shl A9MVhPumpBat)
  A9VVhPumpDC		equ	(2 shl A9MVhPumpDc)
  A9VVhPumpDCSoft	equ	(1 shl A9MVhPumpDc)
  A9VLcdPump		equ	(7 shl A9MLcdPump)
  A9VLcdPumpSoft	equ	(1 shl A9MLcdPump)
  A9VPacksPumpSoft	equ	(15 shl A9MPump2)
  A9VVhPumpDelay	equ	100	; Milliseconds
  A9VLcdPumpDelay	equ	5	; Milliseconds
  A9VCC3OnDelay		equ	1	; Milliseconds
  A9VCCPacksDelay	equ	20	; Milliseconds    
  A9VCC2Delay		equ	10	; Milliseconds
A9WRtcLSWRW		equ	0080h
A9WRtcMSWRW		equ	0082h
A9WNullFrameW		equ	0084h
A9BSlaveDataR		equ	0088h
A9BSerialDataRW		equ	008ah
A9BSerialControlW	equ	008ch
A9BChannelSelectRW	equ	008eh
  A9RChannelSelect record A9MMultiplexEnable:1,A9MSerialClockRate:2,\
    			A9MPack5Enable:1,A9MPack4Enable:1,\
    			A9MPack3Enable:1,A9MPack2Enable:1,\
    			A9MPack1Enable:1
  A9VSClkRateMedium	equ	(0 shl A9MSerialClockRate)
  A9VSClkRateSpecial	equ	(1 shl A9MSerialClockRate)
  A9VSClkRateSlow	equ	(2 shl A9MSerialClockRate)
  A9VSClkRateFast	equ	(3 shl A9MSerialClockRate)
;
; Asic9 Dependent constants
;
ResetWatchDog		equ	A9WResetWatchDogW
SelectChannel1		equ	(mask A9MPack1Enable)
SelectChannel2		equ	(mask A9MPack2Enable)
SelectChannel3		equ	(mask A9MPack3Enable)
SelectChannel4		equ	(mask A9MPack4Enable)
SelectChannel5		equ	(mask A9MPack5Enable)
;
	public	_access
	public	_memcpy
	public	_getpsel0
	public	_setpsel0
	public	_getpsel1
	public	_setpsel1
	public	_getpsel2
	public	_setpsel2
	public	_memcpypsel0
	public	_memcpypsel1
	public	_memcpypsel2
	public	_getcs
	public	_getds

_getcs	proc	near
	push	cs
	pop	ax
	retn
_getcs	endp

_getds	proc	near
	push	ds
	pop	ax
	retn
_getds	endp


; Thanks to Patrick for memcpy :-)
; Thanks to Simon for the values of PSEL0..3 ;-)


_getpsel0	proc	near

	cli

	push	cx
	sub	cl,cl
	xchg	cl,[ss:20h]
	out	15h,al	; A9BProtectionOffW

	out	15h,al	; disable memory protection
	in	al,28h	; PSEL0
	and	ax,00ffh

	test	cl,cl
	jz	dontundo_gp0
	out	14h,al	; A9BProtectionOnW
dontundo_gp0:
	pop	cx
	sti
	retn
_getpsel0	endp
	
_setpsel0	proc	near
	cli

	push	cx
	sub	cl,cl
	xchg	cl,[ss:20h]
	out	15h,al	; A9BProtectionOffW

	and	ax,00ffh
	out	28h,al	; A9BPageSelect6000

	test	cl,cl
	jz	dontundo_sp0
	out	14h,al	; A9BProtectionOnW
dontundo_sp0:
	pop	cx

	sti
	retn
_setpsel0	endp


_getpsel1	proc	near

	cli

	push	cx
	sub	cl,cl
	xchg	cl,[ss:20h]
	out	15h,al	; A9BProtectionOffW

	out	15h,al	; disable memory protection
	in	al,28h	; PSEL0
	and	ax,00ffh

	test	cl,cl
	jz	dontundo_gp1
	out	14h,al	; A9BProtectionOnW
dontundo_gp1:
	pop	cx
	sti
	retn
_getpsel1	endp
	
_setpsel1	proc	near
	cli

	push	cx
	sub	cl,cl
	xchg	cl,[ss:20h]
	out	15h,al	; A9BProtectionOffW

	and	ax,00ffh
	out	28h,al	; A9BPageSelect6000

	test	cl,cl
	jz	dontundo_sp1
	out	14h,al	; A9BProtectionOnW
dontundo_sp1:
	pop	cx

	sti
	retn
_setpsel1	endp

_getpsel2	proc	near

	cli

	push	cx
	sub	cl,cl
	xchg	cl,[ss:20h]
	out	15h,al	; A9BProtectionOffW

	out	15h,al	; disable memory protection
	in	al,2ah	; PSEL2
	and	ax,00ffh

	test	cl,cl
	jz	dontundo_gp2
	out	14h,al	; A9BProtectionOnW
dontundo_gp2:
	pop	cx
	sti
	retn
_getpsel2	endp
	
_setpsel2	proc	near
	cli

	push	cx
	sub	cl,cl
	xchg	cl,[ss:20h]
	out	15h,al	; A9BProtectionOffW

	and	ax,00ffh
	out	2ah,al	; A9BPageSelect8000

	; may need out 14h,al to re-enable memory protection?
	; that's what HwRomBankSet does after out 0x2b,al (PSEL3)
	; HwRomBankSet doesn't touch the watchdog, and HwRomBankGet
	; doesn't in 0x2b - HwRomBankSet stores whatever it had written 
	; into the OS data segment; HwRomBankGet returns this value. 
	; You'd think that PSELx are write-only, but their name in OSSIBO.INC
	; is A9BPageSelectx000RW ...
	; No, A000:6251 is an IN AX,2A. A000:61F7 could be a memory 
	; copy routine. It does an out 0fh,al first (???)
	; 0f = A9BFrc2EoiW
	; Also A000:63BA routine outs to 18, 16, 2a
	; 16 = A9WProtectionUpperW, 18 = A9WProtectionLowerW
	; A000:F971 ins from 2C, ands this with CF and outs it to port 10 (?!?)
	; (A9WResetWatchDogW)
	; xors that with 10 and outs that to 2C (repeated, to toggle bit 4)
	; 
	test	cl,cl
	jz	dontundo_sp2
	out	14h,al	; A9BProtectionOnW
dontundo_sp2:
	pop	cx

	sti
	retn
_setpsel2	endp
;
; Here is HwRomBankSet:
;>00000000  1E                push ds
;>00000001  53                push bx
;>00000002  51                push cx
;>00000003  2AC9              sub cl,cl
;>00000005  36860E2000        xchg cl,[ss:0x20]
;>0000000A  BBB004            mov bx,0x4b0
;>0000000D  8EDB              mov ds,bx
;>0000000F  E615              out 0x15,al	; A9BProtectionOffW
;>00000011  8B1E0004          mov bx,[0x400]
;>00000015  8AE0              mov ah,al
;>00000017  86673D            xchg ah,[bx+0x3d]
;>0000001A  E62B              out 0x2b,al	; A9BPageSelect9000RW
;>0000001C  86C4              xchg al,ah
;>0000001E  2AE4              sub ah,ah
;>00000020  36880E2000        mov [ss:0x20],cl
;>00000025  84C9              test cl,cl
;>00000027  7402              jz 0x2b
;>00000029  E614              out 0x14,al	; A9BProtectionOnW
						; aka A9BProtectionOffR
;>0000002B  59                pop cx
;>0000002C  5B                pop bx
;>0000002D  1F                pop ds
;>0000002E  CF                iret

; original
;_access	proc	near
;
;	push	es
;	push	ax
;	cli
;	pop	es
;	mov	al,es:[bx]
;	pop	es
;	sti
;	retn
;_access	endp

_access	proc	near

	push	cx
	sub	cl,cl
	xchg	cl,[ss:20h]
	out	15h,al	; A9BProtectionOffW

	push	es
	push	ax
	cli
	pop	es
	mov	al,es:[bx]
	pop	es

	test	cl,cl
	jz	dontundo
	out	14h,al	; A9BProtectionOnW
dontundo:
	pop	cx
	sti
	retn
_access	endp
	
;	end _access

_memcpy	proc	near
	push	si
	push	di	; save these
	push	es
	push	ds
	push	dx
	push	cx
	push	bx
	push	ax

	push	cx	; save cx

	 mov	cl,4
	 shl	ax,cl	; ax = segment / 4, so mult by 4

	pop	cx	; restore cx, the number of bytes to copy

	push	bx	; si=bx = offset to read
	pop	si

	push	dx	; di=dx = destination buffer
	pop	di

; Patrick clears decimal here, not sure why :-~
	cld
	cli

	push	ds
	pop	es	; es=ds = process's normal ds

	push	ax	; ds=ax = source segment
	pop	ds

	rep	movsb	; memcpy(ds:si, es:di, cx)
	pop	ax
	pop	bx
	pop	cx
	pop	dx
	pop	ds
	pop	es
	pop	di	; save these
	pop	si

	sti
	retn
_memcpy	endp



_memcpypsel0	proc	near
	push	si
	push	di	; save these
	push	es

			; save parameters

	push	ds	; DEST SEGMENT (PROCESS NORMAL DS)
	push	dx	; DEST OFFSET
	push	cx	; LENGTH
	push	bx	; SOURCE OFFSET
	push	ax	; PSEL0

	push	bx	; si=bx = offset to read
	pop	si

	push	dx	; di=dx = destination buffer offset
	pop	di

; Patrick clears decimal here, not sure why :-~
	; cld
	cli

	push	ds	; es=ds = process's normal ds
	pop	es	; (should be this anyway)


			; setup psel0=al

			; save old SS:20 (memory protection status)
	push	cx	; save count
	sub	cl,cl
	xchg	cl,[ss:20h]
	mov	ss20,cx
	out	15h,al	; A9BProtectionOffW
	pop	cx	; restore count

	push	ax	; save current PSEL2
	in	al,28h	; A9BPageSelect6000
	mov	oldpsel0,ax
	pop	ax

			; set new PSEL0
	and	ax,00ffh
	out	28h,al	; A9BPageSelect6000


	push	ds	; save process DS
	push	6000h	; source segment (ds) is always 6000
	pop	ds
	rep	movsb	; memcpy(6000:si, es:di, cx)
	pop	ds	; restore process DS

	push	ax	; restore old PSEL0
	mov	ax,oldpsel0
	out	28h,al	; A9BPageSelect6000
	pop	ax
	

	push	cx
	mov	cx,ss20
	test	cl,cl
	jz	dontundo_mp0
	out	14h,al	; A9BProtectionOnW
dontundo_mp0:
	pop	cx

	pop	ax
	pop	bx
	pop	cx
	pop	dx
	pop	ds
	pop	es
	pop	di	; save these
	pop	si
	sti
	retn
_memcpypsel0	endp


_memcpypsel1	proc	near
	push	si
	push	di	; save these
	push	es

			; save parameters

	push	ds	; DEST SEGMENT (PROCESS NORMAL DS)
	push	dx	; DEST OFFSET
	push	cx	; LENGTH
	push	bx	; SOURCE OFFSET
	push	ax	; PSEL1

	push	bx	; si=bx = offset to read
	pop	si

	push	dx	; di=dx = destination buffer offset
	pop	di

; Patrick clears decimal here, not sure why :-~
	; cld
	cli

	push	ds	; es=ds = process's normal ds
	pop	es	; (should be this anyway)


			; setup psel1=al

			; save old SS:20 (memory protection status)
	push	cx	; save count
	sub	cl,cl
	xchg	cl,[ss:20h]
	mov	ss20,cx
	out	15h,al	; A9BProtectionOffW
	pop	cx	; restore count

	push	ax	; save current PSEL1
	in	al,29h	; A9BPageSelect7000
	mov	oldpsel1,ax
	pop	ax

			; set new PSEL1
	and	ax,00ffh
	out	29h,al	; A9BPageSelect7000


	push	ds	; save process DS
	push	7000h	; source segment (ds) is always 7000
	pop	ds
	rep	movsb	; memcpy(7000:si, es:di, cx)
	pop	ds	; restore process DS

	push	ax	; restore old PSEL1
	mov	ax,oldpsel1
	out	29h,al	; A9BPageSelect7000
	pop	ax
	

	push	cx
	mov	cx,ss20
	test	cl,cl
	jz	dontundo_mp1
	out	14h,al	; A9BProtectionOnW
dontundo_mp1:
	pop	cx

	pop	ax
	pop	bx
	pop	cx
	pop	dx
	pop	ds
	pop	es
	pop	di	; save these
	pop	si
	sti
	retn
_memcpypsel1	endp

_memcpypsel2	proc	near
	push	si
	push	di	; save these
	push	es

			; save parameters

	push	ds	; DEST SEGMENT (PROCESS NORMAL DS)
	push	dx	; DEST OFFSET
	push	cx	; LENGTH
	push	bx	; SOURCE OFFSET
	push	ax	; PSEL2

	push	bx	; si=bx = offset to read
	pop	si

	push	dx	; di=dx = destination buffer offset
	pop	di

; Patrick clears decimal here, not sure why :-~
	; cld
	cli

	push	ds	; es=ds = process's normal ds
	pop	es	; (should be this anyway)


			; setup psel2=al

			; save old SS:20 (memory protection status)
	push	cx	; save count
	sub	cl,cl
	xchg	cl,[ss:20h]
	mov	ss20,cx
	out	15h,al	; A9BProtectionOffW
	pop	cx	; restore count

	push	ax	; save current PSEL2
	in	al,2ah	; A9BPageSelect8000
	mov	oldpsel2,ax
	pop	ax

			; set new PSEL2
	and	ax,00ffh
	out	2ah,al	; A9BPageSelect8000


	push	ds	; save process DS
	push	8000h	; source segment (ds) is always 8000
	pop	ds
	rep	movsb	; memcpy(8000:si, es:di, cx)
	pop	ds	; restore process DS

	push	ax	; restore old PSEL2
	mov	ax,oldpsel2
	out	2ah,al	; A9BPageSelect8000
	pop	ax
	

	push	cx
	mov	cx,ss20
	test	cl,cl
	jz	dontundo_mp2
	out	14h,al	; A9BProtectionOnW
dontundo_mp2:
	pop	cx

	pop	ax
	pop	bx
	pop	cx
	pop	dx
	pop	ds
	pop	es
	pop	di	; save these
	pop	si
	sti
	retn
_memcpypsel2	endp

	.data
ss20	dw	0
oldpsel0 dw	0
oldpsel1 dw	0
oldpsel2 dw	0

	end

