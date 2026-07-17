.MAC NAME
F1_2
.ENDM
F1_4
;.MAC NAME ; similar name ---- ok
F1_6
;.ENDM
.INC TEST_MAC1.ASM
.MAC NAME2 ; similar name in other file ---- ok
F1_10
.ENDM
;.INC TEST_MAC2.ASM
F1_13
;.MAC ; empty name ---- ok
F1_15
;.ENDM
F1_17
;.MAC 123 ; wrong name - it is number !
F1_18
;.ENDM
F1_21
.MAC EXTERNAL ; mac in mac ---- ok
F1_23
.MAC INTERNAL
F1_25
.ENDM
.ENDM
F1_28
;.ENDM ; ENDM without MAC ---- ok
F1_30
;.MAC HA ; MAC without ENDM ---- ok
F1_32