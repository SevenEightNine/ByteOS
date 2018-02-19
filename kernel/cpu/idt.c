#include "types.h"
#include "mm.h"
#include "libk.h"
#include "interrupts.h"
#include "drivers/apic.h"

#define ISR_NAME(index) isr_stub_ ## index

#define IDT_INSTALL(index, ist) ({ \
	void ISR_NAME(index)(void); \
	idt_set_isr(index, ISR_NAME(index), ist, 0x8E); })

void idt_set_isr(uint8_t index, virtaddr_t entry, uint8_t ist, uint8_t type_attr)
{
	kassert(ist == 0 || index < 32);
	uintptr_t p = (uintptr_t)entry;
	struct idt_entry e = {
		.offset_low = (p & 0xFFFF),
		.selector = 0x08,  // Kernel code segment
		.ist_index = ist,
		.type_attr = type_attr,
		.offset_mid = ((p & 0xFFFF0000) >> 16),
		.offset_high = ((p & 0xFFFFFFFF00000000) >> 32)
	};
	idt64[index] = e;
}

void idt_init(void)
{
	IDT_INSTALL(0, IST_NONE);
	IDT_INSTALL(1, IST_NONE);
	IDT_INSTALL(2, IST_NMI);
	IDT_INSTALL(3, IST_NONE);
	IDT_INSTALL(4, IST_NONE);
	IDT_INSTALL(5, IST_NONE);
	IDT_INSTALL(6, IST_NONE);
	IDT_INSTALL(7, IST_NONE);
	IDT_INSTALL(8, IST_DOUBLE_FAULT);
	IDT_INSTALL(9, IST_NONE);
	IDT_INSTALL(10, IST_NONE);
	IDT_INSTALL(11, IST_NONE);
	IDT_INSTALL(12, IST_NONE);
	IDT_INSTALL(13, IST_NONE);
	IDT_INSTALL(14, IST_NONE);
	IDT_INSTALL(15, IST_NONE);
	IDT_INSTALL(16, IST_NONE);
	IDT_INSTALL(17, IST_NONE);
	IDT_INSTALL(18, IST_NONE);
	IDT_INSTALL(19, IST_NONE);
	IDT_INSTALL(20, IST_NONE);
	IDT_INSTALL(21, IST_NONE);
	IDT_INSTALL(22, IST_NONE);
	IDT_INSTALL(23, IST_NONE);
	IDT_INSTALL(24, IST_NONE);
	IDT_INSTALL(25, IST_NONE);
	IDT_INSTALL(26, IST_NONE);
	IDT_INSTALL(27, IST_NONE);
	IDT_INSTALL(28, IST_NONE);
	IDT_INSTALL(29, IST_NONE);
	IDT_INSTALL(30, IST_NONE);
	IDT_INSTALL(31, IST_NONE);
	IDT_INSTALL(32, IST_NONE);
	IDT_INSTALL(33, IST_NONE);
	IDT_INSTALL(34, IST_NONE);
	IDT_INSTALL(35, IST_NONE);
	IDT_INSTALL(36, IST_NONE);
	IDT_INSTALL(37, IST_NONE);
	IDT_INSTALL(38, IST_NONE);
	IDT_INSTALL(39, IST_NONE);
	IDT_INSTALL(40, IST_NONE);
	IDT_INSTALL(41, IST_NONE);
	IDT_INSTALL(42, IST_NONE);
	IDT_INSTALL(43, IST_NONE);
	IDT_INSTALL(44, IST_NONE);
	IDT_INSTALL(45, IST_NONE);
	IDT_INSTALL(46, IST_NONE);
	IDT_INSTALL(47, IST_NONE);
	IDT_INSTALL(48, IST_NONE);
	IDT_INSTALL(49, IST_NONE);
	IDT_INSTALL(50, IST_NONE);
	IDT_INSTALL(51, IST_NONE);
	IDT_INSTALL(52, IST_NONE);
	IDT_INSTALL(53, IST_NONE);
	IDT_INSTALL(54, IST_NONE);
	IDT_INSTALL(55, IST_NONE);
	IDT_INSTALL(56, IST_NONE);
	IDT_INSTALL(57, IST_NONE);
	IDT_INSTALL(58, IST_NONE);
	IDT_INSTALL(59, IST_NONE);
	IDT_INSTALL(60, IST_NONE);
	IDT_INSTALL(61, IST_NONE);
	IDT_INSTALL(62, IST_NONE);
	IDT_INSTALL(63, IST_NONE);
	IDT_INSTALL(64, IST_NONE);
	IDT_INSTALL(65, IST_NONE);
	IDT_INSTALL(66, IST_NONE);
	IDT_INSTALL(67, IST_NONE);
	IDT_INSTALL(68, IST_NONE);
	IDT_INSTALL(69, IST_NONE);
	IDT_INSTALL(70, IST_NONE);
	IDT_INSTALL(71, IST_NONE);
	IDT_INSTALL(72, IST_NONE);
	IDT_INSTALL(73, IST_NONE);
	IDT_INSTALL(74, IST_NONE);
	IDT_INSTALL(75, IST_NONE);
	IDT_INSTALL(76, IST_NONE);
	IDT_INSTALL(77, IST_NONE);
	IDT_INSTALL(78, IST_NONE);
	IDT_INSTALL(79, IST_NONE);
	IDT_INSTALL(80, IST_NONE);
	IDT_INSTALL(81, IST_NONE);
	IDT_INSTALL(82, IST_NONE);
	IDT_INSTALL(83, IST_NONE);
	IDT_INSTALL(84, IST_NONE);
	IDT_INSTALL(85, IST_NONE);
	IDT_INSTALL(86, IST_NONE);
	IDT_INSTALL(87, IST_NONE);
	IDT_INSTALL(88, IST_NONE);
	IDT_INSTALL(89, IST_NONE);
	IDT_INSTALL(90, IST_NONE);
	IDT_INSTALL(91, IST_NONE);
	IDT_INSTALL(92, IST_NONE);
	IDT_INSTALL(93, IST_NONE);
	IDT_INSTALL(94, IST_NONE);
	IDT_INSTALL(95, IST_NONE);
	IDT_INSTALL(96, IST_NONE);
	IDT_INSTALL(97, IST_NONE);
	IDT_INSTALL(98, IST_NONE);
	IDT_INSTALL(99, IST_NONE);
	IDT_INSTALL(100, IST_NONE);
	IDT_INSTALL(101, IST_NONE);
	IDT_INSTALL(102, IST_NONE);
	IDT_INSTALL(103, IST_NONE);
	IDT_INSTALL(104, IST_NONE);
	IDT_INSTALL(105, IST_NONE);
	IDT_INSTALL(106, IST_NONE);
	IDT_INSTALL(107, IST_NONE);
	IDT_INSTALL(108, IST_NONE);
	IDT_INSTALL(109, IST_NONE);
	IDT_INSTALL(110, IST_NONE);
	IDT_INSTALL(111, IST_NONE);
	IDT_INSTALL(112, IST_NONE);
	IDT_INSTALL(113, IST_NONE);
	IDT_INSTALL(114, IST_NONE);
	IDT_INSTALL(115, IST_NONE);
	IDT_INSTALL(116, IST_NONE);
	IDT_INSTALL(117, IST_NONE);
	IDT_INSTALL(118, IST_NONE);
	IDT_INSTALL(119, IST_NONE);
	IDT_INSTALL(120, IST_NONE);
	IDT_INSTALL(121, IST_NONE);
	IDT_INSTALL(122, IST_NONE);
	IDT_INSTALL(123, IST_NONE);
	IDT_INSTALL(124, IST_NONE);
	IDT_INSTALL(125, IST_NONE);
	IDT_INSTALL(126, IST_NONE);
	IDT_INSTALL(127, IST_NONE);
	IDT_INSTALL(128, IST_NONE);
	IDT_INSTALL(129, IST_NONE);
	IDT_INSTALL(130, IST_NONE);
	IDT_INSTALL(131, IST_NONE);
	IDT_INSTALL(132, IST_NONE);
	IDT_INSTALL(133, IST_NONE);
	IDT_INSTALL(134, IST_NONE);
	IDT_INSTALL(135, IST_NONE);
	IDT_INSTALL(136, IST_NONE);
	IDT_INSTALL(137, IST_NONE);
	IDT_INSTALL(138, IST_NONE);
	IDT_INSTALL(139, IST_NONE);
	IDT_INSTALL(140, IST_NONE);
	IDT_INSTALL(141, IST_NONE);
	IDT_INSTALL(142, IST_NONE);
	IDT_INSTALL(143, IST_NONE);
	IDT_INSTALL(144, IST_NONE);
	IDT_INSTALL(145, IST_NONE);
	IDT_INSTALL(146, IST_NONE);
	IDT_INSTALL(147, IST_NONE);
	IDT_INSTALL(148, IST_NONE);
	IDT_INSTALL(149, IST_NONE);
	IDT_INSTALL(150, IST_NONE);
	IDT_INSTALL(151, IST_NONE);
	IDT_INSTALL(152, IST_NONE);
	IDT_INSTALL(153, IST_NONE);
	IDT_INSTALL(154, IST_NONE);
	IDT_INSTALL(155, IST_NONE);
	IDT_INSTALL(156, IST_NONE);
	IDT_INSTALL(157, IST_NONE);
	IDT_INSTALL(158, IST_NONE);
	IDT_INSTALL(159, IST_NONE);
	IDT_INSTALL(160, IST_NONE);
	IDT_INSTALL(161, IST_NONE);
	IDT_INSTALL(162, IST_NONE);
	IDT_INSTALL(163, IST_NONE);
	IDT_INSTALL(164, IST_NONE);
	IDT_INSTALL(165, IST_NONE);
	IDT_INSTALL(166, IST_NONE);
	IDT_INSTALL(167, IST_NONE);
	IDT_INSTALL(168, IST_NONE);
	IDT_INSTALL(169, IST_NONE);
	IDT_INSTALL(170, IST_NONE);
	IDT_INSTALL(171, IST_NONE);
	IDT_INSTALL(172, IST_NONE);
	IDT_INSTALL(173, IST_NONE);
	IDT_INSTALL(174, IST_NONE);
	IDT_INSTALL(175, IST_NONE);
	IDT_INSTALL(176, IST_NONE);
	IDT_INSTALL(177, IST_NONE);
	IDT_INSTALL(178, IST_NONE);
	IDT_INSTALL(179, IST_NONE);
	IDT_INSTALL(180, IST_NONE);
	IDT_INSTALL(181, IST_NONE);
	IDT_INSTALL(182, IST_NONE);
	IDT_INSTALL(183, IST_NONE);
	IDT_INSTALL(184, IST_NONE);
	IDT_INSTALL(185, IST_NONE);
	IDT_INSTALL(186, IST_NONE);
	IDT_INSTALL(187, IST_NONE);
	IDT_INSTALL(188, IST_NONE);
	IDT_INSTALL(189, IST_NONE);
	IDT_INSTALL(190, IST_NONE);
	IDT_INSTALL(191, IST_NONE);
	IDT_INSTALL(192, IST_NONE);
	IDT_INSTALL(193, IST_NONE);
	IDT_INSTALL(194, IST_NONE);
	IDT_INSTALL(195, IST_NONE);
	IDT_INSTALL(196, IST_NONE);
	IDT_INSTALL(197, IST_NONE);
	IDT_INSTALL(198, IST_NONE);
	IDT_INSTALL(199, IST_NONE);
	IDT_INSTALL(200, IST_NONE);
	IDT_INSTALL(201, IST_NONE);
	IDT_INSTALL(202, IST_NONE);
	IDT_INSTALL(203, IST_NONE);
	IDT_INSTALL(204, IST_NONE);
	IDT_INSTALL(205, IST_NONE);
	IDT_INSTALL(206, IST_NONE);
	IDT_INSTALL(207, IST_NONE);
	IDT_INSTALL(208, IST_NONE);
	IDT_INSTALL(209, IST_NONE);
	IDT_INSTALL(210, IST_NONE);
	IDT_INSTALL(211, IST_NONE);
	IDT_INSTALL(212, IST_NONE);
	IDT_INSTALL(213, IST_NONE);
	IDT_INSTALL(214, IST_NONE);
	IDT_INSTALL(215, IST_NONE);
	IDT_INSTALL(216, IST_NONE);
	IDT_INSTALL(217, IST_NONE);
	IDT_INSTALL(218, IST_NONE);
	IDT_INSTALL(219, IST_NONE);
	IDT_INSTALL(220, IST_NONE);
	IDT_INSTALL(221, IST_NONE);
	IDT_INSTALL(222, IST_NONE);
	IDT_INSTALL(223, IST_NONE);
	IDT_INSTALL(224, IST_NONE);
	IDT_INSTALL(225, IST_NONE);
	IDT_INSTALL(226, IST_NONE);
	IDT_INSTALL(227, IST_NONE);
	IDT_INSTALL(228, IST_NONE);
	IDT_INSTALL(229, IST_NONE);
	IDT_INSTALL(230, IST_NONE);
	IDT_INSTALL(231, IST_NONE);
	IDT_INSTALL(232, IST_NONE);
	IDT_INSTALL(233, IST_NONE);
	IDT_INSTALL(234, IST_NONE);
	IDT_INSTALL(235, IST_NONE);
	IDT_INSTALL(236, IST_NONE);
	IDT_INSTALL(237, IST_NONE);
	IDT_INSTALL(238, IST_NONE);
	IDT_INSTALL(239, IST_NONE);
	IDT_INSTALL(240, IST_NONE);
	IDT_INSTALL(241, IST_NONE);
	IDT_INSTALL(242, IST_NONE);
	IDT_INSTALL(243, IST_NONE);
	IDT_INSTALL(244, IST_NONE);
	IDT_INSTALL(245, IST_NONE);
	IDT_INSTALL(246, IST_NONE);
	IDT_INSTALL(247, IST_NONE);
	IDT_INSTALL(248, IST_NONE);
	IDT_INSTALL(249, IST_NONE);
	IDT_INSTALL(250, IST_NONE);
	IDT_INSTALL(251, IST_NONE);
	IDT_INSTALL(252, IST_NONE);
	IDT_INSTALL(253, IST_NONE);
	IDT_INSTALL(254, IST_NONE);
	IDT_INSTALL(255, IST_NONE);
}
