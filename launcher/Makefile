# Variables that need to be set in order to build the launcher:
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
	CODELOC=0xD748
	LDFLAGS += -b _CODE=$(CODELOC)
endif

LNCHBLD := '$(BUILD)/launcher'
MKLNCHBLDDIR := $(shell python -c \
	"import os; 0 if os.path.exists($(LNCHBLD)) else os.makedirs($(LNCHBLD))")

launcher.$(EXT): $(BUILD)/launcher/launcher.bin
	python ../tools/binto86p.py ti86 $^ $@

$(BUILD)/launcher/launcher.bin: $(BUILD)/launcher/launcher.ihx
	python ../tools/ihxtobin.py $^
	python ../tools/trim.py $(BUILD)/launcher/launcher.map $@ $(CODELOC)

$(BUILD)/launcher/launcher.ihx: $(BUILD)/launcher/startup.rel $(BUILD)/launcher/launcher.rel
	$(LD) $(LDFLAGS) $@ $^

$(BUILD)/launcher/launcher.rel: launcher.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^

$(BUILD)/launcher/startup.rel: startup.asm
	$(AS) -p -g -o $@ $^

clean:
	python -c "import shutil; shutil.rmtree('$(BUILD)/launcher', True)"
