#include <linux/module.h>
#include "hooks.h"
#include "sys_hook.h"
#include "logger.h"

extern struct sys_hook *lkh_sys_hook;

asmlinkage int mkdir_hook(const char *path, int mode)
{
    sys_mkdir_t sys_mkdir;

    log_info("api=[mkdir], pid=[%d], path=[%s], mode=[%d]", 
        current->pid, path, mode);
    
    sys_mkdir = (sys_mkdir_t)sys_hook_get_orig64(lkh_sys_hook, __NR_mkdir);

    return sys_mkdir(path, mode);
}

asmlinkage int open_hook(const char *pathname, int flags)
{
    sys_open_t sys_open;

    log_info("api=[open], pid=[%d], pathname=[%s], flags=[%d]", 
        current->pid, pathname, flags);
    
    sys_open = (sys_open_t)sys_hook_get_orig64(lkh_sys_hook, __NR_open);

    return sys_open(pathname, flags);
}
