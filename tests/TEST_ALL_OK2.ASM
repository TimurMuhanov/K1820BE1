NOP
LBI 0,2 ; B=2
STII 0xf; RAM(B)=f
LBI 0,3 ; B=3
STII 101b   ; RAM(B)=0101
        .MAC    INPUT_MAC
            ININ
            AISC 1 ; skip next if C
        .ENDM
NOP
.INC TEST_ALL_OK1.ASM
NOP
LABX:   .EQU    MAIN_PROG=0x10
        .ORG    MAIN_PROG
INFLOOP:
        INPUT_MAC
        JP INFLOOP
IN_EQ_F:
        LBI 0,3 ; B=3
        OMG     ; RAM(B) ---> G
        XAD 0,3 ; RAM(B) <--> A
        LBI 0,2 ; B=2 // RAM(B)==0xf
        XOR     ; A=0101 <--> A=1010
        XAD 0,3 ; RAM(B) <--> A
        JP INFLOOP


; here tested:
; equs      +
; files     +
; labels    +
; lines     +
; macs      +
; names     +
; numbers   +
; orgs      +