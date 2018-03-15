#pragma once

#include <stdint.h>
#include <stdbool.h>

#include "types.h"
#include "util.h"

struct percpu {
	struct task *current; // Currently running task
	virtaddr_t rsp_scratch;
	virtaddr_t tss;
	struct task *run_queue;
	uint32_t id;
};

void percpu_init(void);

#define __percpu(var) (((struct percpu *)NULL)->var)
#define __percpu_type(var) typeof(__percpu(var))
#define __percpu_marker(var)	((volatile __percpu_type(var) *)&__percpu(var))

#define percpu_get(var) ({						\
	__percpu_type(var) res;						\
	asm ("mov %%gs:%1, %0"  					\
	     : "=r" (res)						\
	     : "m" (*__percpu_marker(var))                              \
	);                                                              \
	res; })

#define __percpu_set(suffix, var, val)					\
({									\
	asm ("mov" suffix " %1, %%gs:%0"				\
	     : "=m" (*__percpu_marker(var))				\
	     : "ir" (val));						\
})

#define percpu_set(var, val)						\
({									\
	switch (sizeof(__percpu_type(var))) {				\
	case 1: __percpu_set("b", var, val); break;			\
	case 2: __percpu_set("w", var, val); break;			\
	case 4: __percpu_set("l", var, val); break;			\
	case 8: __percpu_set("q", var, val); break;			\
	default: _static_assert(false);				        \
	}								\
}) 
