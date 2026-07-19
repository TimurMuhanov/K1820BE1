.ORG 0x100
        CLRA    ; A=0
        LBI 0,0 ; B=0
        STII 1  ; RAM(B)=1, B++
        LBI 0,0 ; B=0
        AISC 6  ; A+=6
LAB0:   ASC     ; A+RAM(B)+C, if C - skip
        JP LAB0 ; loop 10 times
