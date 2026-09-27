; this program is third and final hardware test - keyboard controller
; keyboard is matrix 16x8
; port G connected to demultiplexer, which connected to matrix via diodes
; port L connected to matrix with pull-up resistors
; port SO used as TX of UART 9600 baud

;   RAM description:
; 0-F - low nibble of bytes
; 10-1F - high nibble of bytes
; 20 - line counter of kb
; 21 - counter for delay 1ms
; 22:23 - input = new [low:high]
; 24:25 - xored for detect changes [low:high]
; 26 - store nibble for serial

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

        CLRA            ; wait ~2ms
        AISC 2          ; (16-2)*(2+32+3)*4us=7*37*4=2072 us
LW0:    XAD 2,1         ; store delay counter
        CLRA            ; basic counter
LW01:   AISC 1
        JP LW01
        XAD 2,1         ; restore delay counter
        AISC 1          ; delay counter++
        JP LW0

        ; LOAD NEW
        LBI 2,3         ; read matrix
        INL             ; M(0x23)=high
        XAD 2,2         ; M(0x22)=low

        ; LOAD OLD
        LDD 2,0         ; A=M(2,0)=counter
        LBI 0,0         ; B=0 (low nibble)
        CAB             ; B(3:0)=A
        LD 1            ; A=M(B), B^=0x10 (--> high)
        XAD 2,4         ; M(0x24)=A --- 0x24 - old low
        LD 1            ; A=M(B), B^=0x10 (load high)
        XAD 2,5         ; M(0x25)=A --- old high

        ; STORE NEW
        ; B = 0,counter
        LDD 2,2         ; A=M(0x22)
        X 1             ; A <-> M(B) , B^=0x10
        ; B = 1,counter
        LDD 2,3         ; A=M(0x23)
        X 0             ; A <-> M(B) , B^=0x00

        ; XOR OLD AND NEW
        LDD 2,5         ; A=M(0x25)
        LBI 2,3         ; B=0x23    --- new high
        XOR             ; A^=M(B)
        XAD 2,5         ; M(2,5)=A
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

; send byte

        .ORG 0x80       ; pages 2-3 for subroutine
SEND0:                  ; send was changed zero bit 0bccccx000
        CLRA
        AISC 0
        LBI 2,2         ; load low new
        SKMBZ 0
        AISC 8          ; if not zero x=1
        JP SENDE0
SEND1:
        CLRA
        AISC 1
        LBI 2,2         ; load low new
        SKMBZ 1
        AISC 8          ; if not zero x=1
        JP SENDE0
SEND2:
        CLRA
        AISC 2
        LBI 2,2         ; load low new
        SKMBZ 2
        AISC 8          ; if not zero x=1
        JP SENDE0
SEND3:
        CLRA
        AISC 3
        LBI 2,2         ; load low new
        SKMBZ 3
        AISC 8          ; if not zero x=1
        JP SENDE0
SEND4:
        CLRA
        AISC 4
        LBI 2,3         ; load high new
        SKMBZ 0
        AISC 8          ; if not zero x=1
        JP SENDE0
SEND5:
        CLRA
        AISC 5
        LBI 2,3         ; load high new
        SKMBZ 1
        AISC 8          ; if not zero x=1
        JP SENDE0
SEND6:
        CLRA
        AISC 6
        LBI 2,3         ; load high new
        SKMBZ 2
        AISC 8          ; if not zero x=1
        JP SENDE0
SEND7:
        CLRA
        AISC 7
        LBI 2,3         ; load high new
        SKMBZ 3
        AISC 8          ; if not zero x=1
        JP SENDE0

SENDE0:
        NOP
        ; store A
        XAD 2,6
        ; baud 9600 ---> 104 us per bit ---> 26 cycles
        ; start bit
        LEI 1
        ; wait 26-22 cycles
        NOP
        NOP
        NOP
        NOP
        JSR SENDNBL0
        LDD 2,0
        XAD 2,6
        JSR SENDNBL0
        ; wait 26-4=22 cycles = 2+20 ---> 20/2=10 ---> 16-10=6
        CLRA
        AISC 6
SENDE1:
        AISC 1
        JP SENDE1
        ; stop bit
        LEI 9
        ; wait 26-1-3-6-2-N-2=0 cycles ---> N=26-14=12 ---> (12-2)/2=5=16-11
        CLRA
        AISC 11
SENDE2:
        AISC 1
        JP SENDE2
        NOP
        RET

; send nibble of byte
.ORG 0x100

SENDNBL0:
        ; wait 26-10=16 cycles ---> (16-2)/2=7 ---> 16-7=9
        CLRA
        AISC 9
SENDNBL0L:
        AISC 1
        JP SENDNBL0L
        ; send B(0) bit
        LBI 2,6
        SKMBZ 0
        JP SENDNBLL0
        LEI 1
        JP SENDNBLH0
SENDNBLL0:
        LEI 9
        NOP
SENDNBLH0:
        ; wait 26-2-2-2*N-4 cycles ---> N=(26-8)/2=9 ---> 16-9=7
        CLRA
        AISC 7
SENDNBLH0L:
        AISC 1
        JP SENDNBLH0L
        ; send B(1) bit
        LBI 2,6
        SKMBZ 1
        JP SENDNBLL1
        LEI 1
        JP SENDNBLH1
SENDNBLL1:
        LEI 9
        NOP
SENDNBLH1:
        ; wait 26-2-2-2*N-4 cycles ---> N=(26-8)/2=9 ---> 16-9=7
        CLRA
        AISC 7
SENDNBLH1L:
        AISC 1
        JP SENDNBLH1L
        ; send B(2) bit
        LBI 2,6
        SKMBZ 2
        JP SENDNBLL2
        LEI 1
        JP SENDNBLH2
SENDNBLL2:
        LEI 9
        NOP
SENDNBLH2:
        ; wait 26-2-2-2*N-4 cycles ---> N=(26-8)/2=9 ---> 16-9=7
        CLRA
        AISC 7
SENDNBLH2L:
        AISC 1
        JP SENDNBLH2L
        ; send B(3) bit
        LBI 2,6
        SKMBZ 3
        JP SENDNBLL3
        LEI 1
        JP SENDNBLH3
SENDNBLL3:
        LEI 9
        NOP
SENDNBLH3:
        NOP
        RET
