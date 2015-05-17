# Variables that need to be set in order to build this demo:
#  CC: C compiler, sdcc
#  AS: Assembler, sdasz80
#  LD: Linker, sdldz80
#  BUILD: Build output folder
#  CFLAGS: global compiler options
#  LDFLAGS: global linker options
#  INCLUDE: global include folders
#  CODELOC: starting address for this program, like 0xD748

ifeq ($(CALC), 86)
	EXT=86p
	CODELOC=0xA500
	LDFLAGS += -b _CODE=$(CODELOC)
	PORTDIR=ti86
endif

DEMOBLD := '$(BUILD)/apps/demo'
MKDEMOBLDDIR := $(shell python -c \
	"import os; 0 if os.path.exists($(DEMOBLD)) else os.makedirs($(DEMOBLD))")

demoprog.$(EXT): $(BUILD)/apps/demo/demoprog.bin
	python ../../tools/binto86p.py ti86 $^ $@

$(BUILD)/apps/demo/demoprog.bin: $(BUILD)/apps/demo/demoprog.ihx
	python ../../tools/ihxtobin.py $^
	python ../../tools/trim.py $(BUILD)/apps/demo/demoprog.map $@ $(CODELOC)

DEMORELS += $(BUILD)/apps/syscall_external.rel
DEMORELS += $(BUILD)/apps/demo/demo.rel
$(BUILD)/apps/demo/demoprog.ihx: $(DEMORELS)
	$(LD) $(LDFLAGS) $@ $^

$(BUILD)/apps/demo/demo.rel:  demo.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^

SYSCALLSRC += ../../kernel/$(PORTDIR)/syscall_external.asm
SYSCALLSRC += ../../kernel/$(PORTDIR)/syscall.inc
$(BUILD)/apps/syscall_external.rel: $(SYSCALLSRC)
	$(AS) -I../../kernel/$(PORTDIR) -l -s -o $@ $<

clean:
	python -c "import shutil; shutil.rmtree('$(BUILD)/apps/demo', True)"
