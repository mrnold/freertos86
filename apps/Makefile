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

DEMOBLD := '$(BUILD)/apps/demo'
MKDEMOBLDDIR := $(shell python -c \
	"import os; 0 if os.path.exists($(DEMOBLD)) else os.makedirs($(DEMOBLD))")

demo.$(EXT): $(BUILD)/apps/demo/demo.bin
	python ../tools/binto86p.py ti86 $^ $@

$(BUILD)/apps/demo/demo.bin: $(BUILD)/apps/demo/demo.ihx
	python ../tools/ihxtobin.py $^
	python ../tools/trim.py $(BUILD)/apps/demo/demo.map $@ $(CODELOC)

$(BUILD)/apps/demo/demo.ihx: $(BUILD)/apps/demo/demo.rel
	$(LD) $(LDFLAGS) $@ $^

$(BUILD)/apps/demo/demo.rel: demo/demo.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^

clean:
	python -c "import shutil; shutil.rmtree('$(BUILD)/apps', True)"
