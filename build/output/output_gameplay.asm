;--------------------------------------------------------
; File Created by SDCC : free open source ANSI-C Compiler
; Version 4.0.7 #12016 (MINGW64)
;--------------------------------------------------------
	.module output_gameplay
	.optsdcc -mgbz80
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _song_gameplay0
	.globl _song_gameplay_Data
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
;--------------------------------------------------------
; ram data
;--------------------------------------------------------
	.area _DATA
_song_gameplay_Data::
	.ds 4
;--------------------------------------------------------
; absolute external ram data
;--------------------------------------------------------
	.area _DABS (ABS)
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area _HOME
	.area _GSINIT
	.area _GSFINAL
	.area _GSINIT
;music\output\output_gameplay.c:73: const unsigned char * song_gameplay_Data[] = {
	ld	hl, #_song_gameplay_Data
	ld	(hl), #<(_song_gameplay0)
	inc	hl
	ld	(hl), #>(_song_gameplay0)
	ld	hl, #(_song_gameplay_Data + 0x0002)
	xor	a, a
	ld	(hl+), a
	ld	(hl), a
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area _HOME
	.area _HOME
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area _CODE
	.area _CODE
_song_gameplay0:
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8b	; 139
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x9a	; 154
	.db #0x3a	; 58
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x85	; 133
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x9a	; 154
	.db #0x3a	; 58
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8b	; 139
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x85	; 133
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x98	; 152
	.db #0x3a	; 58
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x9a	; 154
	.db #0x3a	; 58
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8b	; 139
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x20	; 32
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x2a	; 42
	.db #0x85	; 133
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x85	; 133
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8b	; 139
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x82	; 130
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x85	; 133
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x9d	; 157
	.db #0x3a	; 58
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8b	; 139
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x9c	; 156
	.db #0x3a	; 58
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x85	; 133
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x9a	; 154
	.db #0x3a	; 58
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x98	; 152
	.db #0x3a	; 58
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8b	; 139
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x9a	; 154
	.db #0x3a	; 58
	.db #0x85	; 133
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8b	; 139
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x20	; 32
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x85	; 133
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x01	; 1
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x87	; 135
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x8c	; 140
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x20	; 32
	.db #0x8b	; 139
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x00	; 0
	.db #0x85	; 133
	.db #0x18	; 24
	.db #0x00	; 0
	.db #0x8a	; 138
	.db #0x82	; 130
	.db #0x02	; 2
	.db #0x00	; 0
	.db #0x24	; 36
	.db #0x00	; 0
	.db #0x00	; 0
	.area _CABS (ABS)
