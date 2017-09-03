# Thank you https://github.com/no92 for cleaning this up a lot!
ISO		:= build/byteos.iso
KERNEL		:= build/byteos.elf
OS		:= $(shell uname -s)

AS		:= nasm
EMU		:= qemu-system-x86_64
AR		:= x86_64-elf-ar
CC		:= x86_64-elf-gcc
OBJDUMP		:= x86_64-elf-objdump
OBJCOPY		:= x86_64-elf-objcopy

CFLAGS		?= -O1 -g
CFLAGS		+= -ffreestanding -mno-red-zone -mcmodel=kernel -Iinclude -Iinclude/kernel -std=gnu11
CFLAGS		+= -Wall -Wbad-function-cast -Werror -Wextra -Wparentheses -Wmissing-braces -Wmissing-declarations
CFLAGS		+= -Wmissing-field-initializers -Wmissing-prototypes -Wnested-externs -Wpointer-arith -Wpedantic
CFLAGS		+= -Wredundant-decls -Wshadow -Wstrict-prototypes -Wswitch-default -Wswitch-enum -Wuninitialized -Wunreachable-code
CFLAGS		+= -Wunused
ASFLAGS		:= -f elf64 -F dwarf -g -w+all -Werror
EMUFLAGS	:= -net none -serial stdio -cdrom $(ISO)

KERNEL_OBJ	:= $(addsuffix .o,$(shell find kernel -name '*.c' -o -name '*.asm'))
DEPFILES	:= $(patsubst %.o,%.d,$(KERNEL_OBJ))

LIBK_OBJ	:= $(addsuffix .o,$(shell find libk -name '*.c' -o -name '*.asm'))
DEPFILES	+= $(patsubst %.o,%.d,$(LIBK_OBJ))

ifeq ($(OS),Linux)
	EMUFLAGS += -M accel=kvm:tcg
endif

.PHONY: all clean run debug disassemble copy-all copy-ds copy-cansid
.SUFFIXES: .o .c .asm

all: $(ISO)

run: $(ISO)
	@$(EMU) $(EMUFLAGS)

clean:
	@$(RM) -r build
	@$(RM) iso/boot/byteos.elf
	@$(RM) $(KERNEL_OBJ) $(LIBK_OBJ)
	@$(RM) $(DEPFILES)

debug: $(ISO)
	@$(EMU) $(EMUFLAGS) -d cpu_reset -no-reboot -s -S &
	@../../../deps/bin/gdb
	@pkill qemu

disassemble: $(KERNEL)
	@$(OBJDUMP) --no-show-raw-insn -d -Mintel $(KERNEL) | source-highlight -s asm -f esc256 | less -eRiMX

copy-all: copy-ds copy-cansid

copy-ds:
	@cp ../ds/include/ds/*.h ./include/kernel/ds
	@cp ../ds/src/*.c ./kernel/ds

copy-cansid:
	@cp ../cansid/cansid.c ./kernel/drivers/vga_tmode
	@cp ../cansid/cansid.h ./include/kernel/drivers/
	@cat ./kernel/drivers/vga_tmode/cansid.c | sed 's/cansid.h/drivers\/cansid.h/g' > temp.c
	@mv temp.c ./kernel/drivers/vga_tmode/cansid.c

iso/boot/byteos.elf: $(KERNEL)
	@cp $< $@

build/:
	@mkdir build

build/libk.a: $(LIBK_OBJ)
	@$(AR) rcs $@ $(LIBK_OBJ)

$(ISO): build/ iso/boot/byteos.elf
	@printf "\t\e[32;1mCreating\e[0m $(ISO)\n"
	@grub-mkrescue -o $@ iso 2> /dev/null
	@printf "\t\e[32;1;4mDone\e[0m\n"

$(KERNEL): $(KERNEL_OBJ) build/libk.a
	@printf "\t\e[32;1mLinking\e[0m $(KERNEL)\n"
	@$(CC) -T linker.ld -o $@ $(KERNEL_OBJ) $(LDFLAGS) -n -nostdlib -Lbuild -lk -lgcc
	@$(OBJCOPY) --only-keep-debug $(KERNEL) build/byteos.sym
	@$(OBJCOPY) --strip-debug $(KERNEL)
	@grub-file --is-x86-multiboot2 $@

kernel/%.asm.o: kernel/%.asm
	@printf "\t\e[32;1mAssembling\e[0m $<\n"
	@$(AS) $(ASFLAGS) -MD $(addsuffix .d,$<) $< -o $@

kernel/%.c.o: kernel/%.c
	@printf "\t\e[32;1mCompiling\e[0m $<\n"
	@$(CC) -c $< -o $@ -MD $(CFLAGS)

libk/%.c.o: libk/%.c
	@$(CC) -c $< -o $@ -MD $(CFLAGS)

-include $(DEPFILES)
