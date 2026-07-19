; 2-3 pages - jp in this 2-3 pages
; 0,1,4-... - jp only in one page
; jp not jump in last word
;
; jsrp jump only to 2 page
; jsrp can not be called in pages 2-3
; jsrp not jump in last word

.ORG 0    ; page 0
LAB_00:

.ORG 0x3f ; end of page 0
LAB_3f:

.ORG 0x40 ; page 1
LAB_40:

.ORG 0x7f ; end of page 1
LAB_7f:

.ORG 0x80 ; page 2
LAB_80:

.ORG 0xbf ; end of page 2
LAB_bf:

.ORG 0xC0 ; page 3
LAB_C0:

.ORG 0xff ; end of page 3
LAB_ff:

.ORG 0x100 ; page 4
LAB_100: