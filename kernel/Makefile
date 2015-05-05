# Variables that need to be set in order to build FreeRTOS:
#  CC: C compiler, sdcc
#  AS: Assembler, sdasz80
#  LD: Linker, sdldz80
#  BUILD: Build output folder
#  CFLAGS: global compiler options
#  LDFLAGS: global linker options
#  INCLUDE: global include folders
#  CALC: calculator model, currently 86 only

ifeq ($(CALC), 86)
	EXT=86p
	CODELOC=0x8100
	INCLUDE += -Iti86
	PORTDIR=ti86
endif

PORTBLD := '$(BUILD)/kernel/$(PORTDIR)'
MKPORTBLDDIR := $(shell python -c \
	"import os; 0 if os.path.exists($(PORTBLD)) else os.makedirs($(PORTBLD))")
RTOSBLD := '$(BUILD)/kernel/freertos'
MKRTOSBLDDIR := $(shell python -c \
	"import os; 0 if os.path.exists($(RTOSBLD)) else os.makedirs($(RTOSBLD))")

freertos.$(EXT): $(BUILD)/kernel/kernel.bin
	python ../tools/binto86p.py ti$(CALC) $^ $@

$(BUILD)/kernel/kernel.bin: $(BUILD)/kernel/kernel.ihx
	python ../tools/ihxtobin.py $^
	python ../tools/trim.py $(BUILD)/kernel/kernel.map $@ $(CODELOC)

FREERTOSREL += $(BUILD)/kernel/freertos/tasks.rel
FREERTOSREL += $(BUILD)/kernel/freertos/queue.rel
FREERTOSREL += $(BUILD)/kernel/freertos/list.rel
FREERTOSREL += $(BUILD)/kernel/$(PORTDIR)/port.rel
FREERTOSREL += $(BUILD)/kernel/$(PORTDIR)/heap_1.rel
$(BUILD)/kernel/kernel.ihx: $(FREERTOSREL)
	$(CC) -mz80 --no-std-crt0 --reserve-regs-iy --opt-code-speed --out-fmt-ihx --code-loc $(CODELOC) --data-loc 0 -o $@ $^

$(BUILD)/kernel/freertos/tasks.rel: freertos/tasks.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^
$(BUILD)/kernel/freertos/queue.rel: freertos/queue.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^
$(BUILD)/kernel/freertos/list.rel: freertos/list.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^
$(BUILD)/kernel/$(PORTDIR)/port.rel: $(PORTDIR)/port.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^
$(BUILD)/kernel/$(PORTDIR)/heap_1.rel: $(PORTDIR)/heap_1.c
	$(CC) $(INCLUDE) $(CFLAGS) -o $@ $^

clean:
	python -c "import shutil; shutil.rmtree('$(BUILD)/kernel', True)"