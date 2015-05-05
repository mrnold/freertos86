CC     := sdcc
AS     := sdasz80
LD     := sdldz80
BUILD  := $(CURDIR)/build
CALC   := 86

CFLAGS := -mz80       \
	--compile-only    \
	--no-std-crt0     \
	--reserve-regs-iy \
	--opt-code-speed  \
	--max-allocs-per-node 30000

LDFLAGS := -m -w -x -i -b _DATA=0x0000

INCLUDE := \
	-I$(CURDIR)/kernel/freertos/include \
	-I$(CURDIR)/kernel/ti$(CALC)
export

.PHONY: kernel launcher apps clean
all: kernel launcher apps

apps:
	make -C apps

kernel:
	make -C kernel

launcher:
	make -C launcher

clean:
	make -C kernel clean
	make -C launcher clean
	make -C apps clean
