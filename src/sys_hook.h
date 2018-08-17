#pragma once

#include <linux/list.h>
#include "types.h"
#include "utils.h"

enum sys_hook_type {
    SHT_X86,
    SHT_X64,
};

struct sys_hook_ent {
    unsigned int syscall_id;
    uintptr_t original;
    uintptr_t hooked;
    enum sys_hook_type type;

    struct list_head list; 
};

struct sys_hook {
    unsigned int *x86_sct;
    unsigned long long *x64_sct;
    struct sys_hook_ent hook_list_head;
};



#define CR0_WRITE_PROTECT   (1 << 16)

struct sys_hook * sys_hook_init(uintptr_t k32, uintptr_t k64);

bool_t sys_hook_add64(struct sys_hook *, unsigned int syscall_id, void *func);

bool_t sys_hook_del64(struct sys_hook *, unsigned int syscall_id);

uintptr_t sys_hook_get_orig64(struct sys_hook *, unsigned int syscall_id);

void sys_hook_free(struct sys_hook *hook);
