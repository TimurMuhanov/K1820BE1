;.EQU ; empty
;.EQU DEF0 ; without '='
;.EQU =1 ; without name
;.EQU DEF1= ; without number
;.EQU 1=2 ; wrong name - it is number

;.EQU DEF2=2 ; similar names
;.EQU DEF2=3

;.EQU DEF3=0b123 ; wrong number
;.equ DEF4=0x123h ; wrong number

;.EQU DEF14=(((123)) ; wrong brackets 1
;.EQU DEF15=(123)) ; wrong brackets 2

;.EQU DEF5=LAB0 ; wrong definision 1
.EQU DEF6=() ; wrong definision 2
;.EQU DEF7='' ; wrong definision 3
;.EQU DEF8=' ; wrong definision 4
;.EQU DEF9="" ; wrong definision 5
;.EQU DEF10=1+ ; wrong definision 6
;.EQU DEF11=*1 ; wrong definision 7
;.EQU DEF12=(/1) ; wrong definision 8
;.EQU DEF13='a'' ; wrong definision 9