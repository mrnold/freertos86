.module startup
.globl _portInit
.area _CODE
_portInit::
    call gsinit
    ret
.area _GSINIT
gsinit::
    ld bc, #l__INITIALIZER
    ld a, b
    or a, c
    jr z, gsinit_done
    ld de, #s__INITIALIZED
    ld hl, #s__INITIALIZER
    ldir
gsinit_done:
.area _GSFINAL
    ret
