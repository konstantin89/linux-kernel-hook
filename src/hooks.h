#ifndef __HOOKS_H
#define __HOOKS_H

#include <linux/syscalls.h>
#include "types.h"

typedef asmlinkage int (*sys_mkdir_t)(const char *, int);
typedef asmlinkage int (*sys_open_t)(const char *, int);

asmlinkage int mkdir_hook(const char *, int);

asmlinkage int open_hook(const char *, int flags);

#endif