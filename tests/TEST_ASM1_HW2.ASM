; this program is second hardware test - blink
; all commands takes 4us (see datasheet)
; so for 1 period blink we need 0.5 sec for one state
; 500'000 us / 4 us = 125k cycles

.ORG 0    ; page 0

        CLRA
;XXXX:   NOP             ; express test
;        NOP
;        OGI 1
;        OGI 0
;        JP XXXX

MAIN_LOOP:

        OGI 1           ; G=1

        CLRA            ; loop-x-3 (2+9552+3=)*13 = 124'241 cycles
        AISC 3          ; A+=3
LAB_03:
        XAD 0,2         ; STORE AT RAM 2
        CLRA            ; loop-x-3 (2+592+3=597)*16 = 9552 cycles
LAB_02:
        XAD 0,1         ; STORE AT RAM 1
        CLRA            ; loop-in-loop (2+32+3=37)*16 = 592 cycles
LAB_01:
        XAD 0,0         ; STORE AT RAM 0
        CLRA
LAB_00:                 ; simple loop take 2*16 cycles
        AISC 1
        JP LAB_00
        RC

        XAD 0,0         ; TAKE FROM RAM 0
        AISC 1          ; A++
        JP LAB_01       ; if A<16 - loop
        RC

        XAD 0,1         ; TAKE FROM RAM 1
        AISC 1          ; A++
        JP LAB_02       ; if A<16 - loop
        RC

        XAD 0,2         ; TAKE FROM RAM 2
        AISC 1          ; A++
        JP LAB_03       ; if A<16 - loop
        RC

        OGI 0           ; G=0

        CLRA            ; loop-x-3 (2+9552+3=)*13 = 124'241 cycles
        AISC 3          ; A+=3
LAB_13:
        XAD 0,2         ; STORE AT RAM 2
        CLRA            ; loop-x-3 (2+592+3=597)*16 = 9552 cycles
LAB_12:
        XAD 0,1         ; STORE AT RAM 1
        CLRA            ; loop-in-loop (2+32+3=37)*16 = 592 cycles
LAB_11:
        XAD 0,0         ; STORE AT RAM 0
        CLRA
LAB_10:                 ; simple loop take 2*16 cycles
        AISC 1
        JP LAB_10
        RC

        XAD 0,0         ; TAKE FROM RAM 0
        AISC 1          ; A++
        JP LAB_11       ; if A<16 - loop
        RC

        XAD 0,1         ; TAKE FROM RAM 1
        AISC 1          ; A++
        JP LAB_12       ; if A<16 - loop
        RC

        XAD 0,2         ; TAKE FROM RAM 2
        AISC 1          ; A++
        JP LAB_13       ; if A<16 - loop
        RC

        NOP             ; 64 byte
        NOP

        JMP MAIN_LOOP
