.macro define_syscall name address
    _'name .gblequ address
.endm
.include /syscall.inc/
