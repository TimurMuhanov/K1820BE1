; this program is third and final hardware test - keyboard controller
; keyboard is matrix 16x8
; port G connected to demultiplexer, which connected to matrix via diodes
; port L connected to matrix with pull-up resistors
; port SO used as TX of UART 9600 baud

.ORG 0    ; page 0
        CLRA
        LEI 9           ; SO=1, L-HZ
LBI     0,0             ; init low nibble
LABI0:  STII 0FH        ; M(B)=F, B++
        AISC 1
        JP LABI0
LBI     1,0             ; init high nibble
LABI1:  STII 0FH        ; M(B)=F, B++
        AISC 1
        JP LABI1
LBI     2,0             ; M(0x20)=0
        STII 0

MAIN_LOOP:
        XAD 2,0         ; counter++
        AISC 1
        NOP
        XAD 2,0
        LBI 2,0         ; output to G counter
        OMG

        CLRA            ; wait ~1ms
        AISC 9          ; (16-9)*(2+32+3)*4us=7*37*4=1036us
LW0:    XAD 2,1         ; store delay counter
        CLRA            ; basic counter
LW01:   AISC 1
        JP LW01
        XAD 2,1         ; restore delay counter
        AISC 1          ; delay counter++
        JP LW0

        LBI 2,3         ; read matrix
        INL             ; M(0x23)=high
        XAD 2,2         ; M(0x22)=low

        ; XOR OLD AND NEW
        LDD 2,0         ; A=M(2,0)=counter
        LBI 0,0         ; B=0 (low nibble)
        CAB             ; B(3:0)=A
        LD 1            ; A=M(B), B^=0x10 (--> high)
        XAD 2,4         ; M(0x24)=A --- 0x24 - old low
        LD 1            ; A=M(B), B^=0x10 (load high)
        LBI 2,3         ; B=0x23    --- new high
        XOR             ; A^=M(B)
        XAD 2,5         ; M(2,5)=A  --- 0x23 - xored high
        LDD 2,4         ; A=M(2,4)  --- old low
        LBI 2,2         ; B=0x22    --- new low
        XOR             ; A^=M(B)
        XAD 2,4         ; M(2,5)=A  --- 0x24 - xored low
        
        ; CHECK ALL XORED
        CLRA
        LBI 2,4
        SKMBZ 0
        JSRP SEND0
        LBI 2,4
        SKMBZ 1
        JSRP SEND1
        LBI 2,4
        SKMBZ 2
        JSRP SEND2
        LBI 2,4
        SKMBZ 3
        JSRP SEND3
        LBI 2,5
        SKMBZ 0
        JSRP SEND4
        LBI 2,5
        SKMBZ 1
        JSRP SEND5
        LBI 2,5
        SKMBZ 2
        JSRP SEND6
        LBI 2,5
        SKMBZ 3
        JSRP SEND7

        JMP MAIN_LOOP

        .ORG 0x80       ; pages 2-3 for subroutine
SEND0:                  ; send was changed zero bit 0bx000cccc
        CLRA
        AISC 0
        LBI 2,2         ; load low new
        SKMBZ 0
        AISC 8          ; if not zero x=1
        JP SENDE0
SEND1:
SEND2:
SEND3:
SEND4:
SEND5:
SEND6:
SEND7:
SENDE0:
        NOP