# Variables that need to be set in order to build this application:
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

BLD := '$(BUILD)/apps/powerctl'
BLDDIR := $(shell python -c \
	"import os; 0 if os.path.exists($(BLD)) else os.makedirs($(BLD))")

powerctl.$(EXT): $(BUILD)/apps/powerctl/powerctl.bin
	python ../../tools/binto86p.py ti86 $^ $@

$(BUILD)/apps/powerctl/powerctl.bin: $(BUILD)/apps/powerctl/powerctl.ihx
	python ../../tools/ihxtobin.py $^
	python ../../tools/trim.py $(BUILD)/apps/powerctl/powerctl.map $@ $(CODELOC)

RELS += $(BUILD)/apps/syscall_external.rel
RELS += $(BUILD)/apps/powerctl/powerctl.rel
$(BUILD)/apps/powerctl/powerctl.ihx: $(RELS)
	$(LD) $(LDFLAGS) $@ $^

$(BUILD)/apps/powerctl/powerctl.rel: powerctl.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^

SYSCALLSRC += ../../kernel/$(PORTDIR)/syscall_external.asm
SYSCALLSRC += ../../kernel/$(PORTDIR)/syscall.inc
$(BUILD)/apps/syscall_external.rel: $(SYSCALLSRC)
	$(AS) -I../../kernel/$(PORTDIR) -l -s -o $@ $<

clean:
	python -c "import shutil; shutil.rmtree('$(BUILD)/apps/powerctl', True)"
