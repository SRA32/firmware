AS_SRC := $(shell find src -type f -name "*.s")
C_SRC := $(shell find src -type f -name "*.c")

OBJ := $(patsubst src/%.s,out/%.o,$(AS_SRC))
OBJ += $(patsubst src/%.c,out/%.o,$(C_SRC))

QFLAGS := -m 2G -serial stdio -kernel out/firmware.bin \
	-drive file=test.img,format=raw,if=none,id=hd0

all: out/firmware.bin

out/firmware.o: $(OBJ) sra32.ld
	sra32-elf-ld -nostdlib $(OBJ) -o $@ -Tsra32.ld

out/firmware.bin: out/firmware.o
	sra32-elf-objcopy -O binary $< $@
	rm -f $<

out/%.o: src/%.s
	@mkdir -p $(dir $@)
	sra32-elf-as $< -o $@

out/%.o: src/%.c
	@mkdir -p $(dir $@)
	sra32-elf-gcc -Iinclude -nostdlib -c $< -o $@

run-mon:
	../builds/qemu/qemu-system-sra32 -m 2G -monitor stdio -kernel out/firmware.bin

run:
	../builds/qemu/qemu-system-sra32 $(QFLAGS)

clean:
	rm $(shell find ./out -name "*.o")
	rm out/firmware.bin