%define PAGE_SIZE 0x1000
%define SIZEOF_STRUCT_PERCPU 0x18

%define KERNEL_TEXT_BASE 0xFFFFFFFF80000000
%define KERNEL_PHYS_MAP_END 0x1000000

%define GDT_USER_DATA 0x20
%define GDT_USER_CODE 0x28
%define GDT_TSS 0x30

%define NUM_SYSCALLS 2
%define ENOSYS 0xFFFFFFFFFFFFFFFF

; outb(port, val)
%macro outb 2
	mov al, %2
	mov dx, %1
	out dx, al
%endmacro

