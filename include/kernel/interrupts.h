#pragma once

#include <stdint.h>
#include "types.h"

#define IST_NONE 0
#define IST_NMI 1
#define IST_DOUBLE_FAULT 2

struct stack_regs {
	// These registers are not generally saved by the caller
	uint64_t r15;
	uint64_t r14;
	uint64_t r13;
	uint64_t r12;
	uint64_t rbp;
	uint64_t rbx;
	// These registers are always saved when entering C code
	uint64_t r11;
	uint64_t r10;
	uint64_t r9;
	uint64_t r8;
	uint64_t rax;
	uint64_t rcx;
	uint64_t rdx;
	uint64_t rsi;
	uint64_t rdi;
	// Contains error code and interrupt number for exceptions
	// Contains syscall number for syscalls
	// Contains just the interrupt number otherwise
	uint64_t info;
	// Interrupt stack frame
	uint64_t rip;
	uint64_t cs;
	uint64_t rflags;
	uint64_t rsp;
	uint64_t ss;
};

struct idt_entry {
	uint16_t offset_low;
	uint16_t selector;
	uint8_t ist_index;
	uint8_t type_attr;
	uint16_t offset_mid;
	uint32_t offset_high;
	uint32_t __zero;
};

extern struct idt_entry idt64[256];

void exception_handler(struct stack_regs *);

void idt_init(void);
void idt_set_isr(uint8_t index, virtaddr_t entry, uint8_t ist, uint8_t type_attr);

void load_idt(void);

void irq_init(void);
void irq_handler(struct stack_regs *);
