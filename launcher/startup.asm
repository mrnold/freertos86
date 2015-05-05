; Launcher startup code
; Just needs to jump to main
   .module startup 
   .globl _startup
   .globl _main
   .area _CODE
   _startup:
      jp _main
