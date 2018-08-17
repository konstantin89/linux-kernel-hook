#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include "sys_hook.h"
#include "hooks.h"
#include "logger.h"
#include "utils.h"

#define SUCCESS_CODE 0
#define ERROR_CODE 1

/* Module parameter macros */
static char *kbase32 = NULL, *kbase64 = NULL;
module_param(kbase32, charp, 0);
MODULE_PARM_DESC(kbase32, "Base address of the x86 syscall table, in hex");
module_param(kbase64, charp, 0);
MODULE_PARM_DESC(kbase64, "Base address of the x64 syscall table, in hex");

struct sys_hook *lkh_sys_hook;


static int __init module_entry(void)
{
    uintptr_t k32, k64;

    log_info("Loading");
    
    if (kbase32 == NULL || kbase32[0] == '\0') 
    {
        log_error("Failed to get x86 syscall table");
        return ERROR_CODE;
    } 
    else if (kbase64 == NULL || kbase64[0] == '\0') 
    {
        log_error("Failed to get x64 syscall table");
        return ERROR_CODE;
    }

    if ((k32 = hex_addr_to_pointer(kbase32)) == 0) 
    {
        log_error("Invalid x86 syscall address %p", (void *)k32);
        return ERROR_CODE;
    } 
    else if ((k64 = hex_addr_to_pointer(kbase64)) == 0) 
    {
        log_error("Invalid x64 syscall address %p", (void *)k64);
        return ERROR_CODE;
    }

    if ((lkh_sys_hook = sys_hook_init(k32, k64)) == NULL) 
    {
        log_error("Failed to initialize sys_hook");
        return ERROR_CODE;
    }

    sys_hook_add64(lkh_sys_hook, __NR_mkdir, (void *)mkdir_hook);
    sys_hook_add64(lkh_sys_hook, __NR_open, (void *)open_hook);


    log_info("Module loaded");
    return 0;
}

static void __exit module_cleanup(void)
{
    sys_hook_free(lkh_sys_hook);

    log_info("Module unloaded");
}

/* Declare the entry and exit points of our module */
module_init(module_entry);
module_exit(module_cleanup);

/* Module info */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("github:jha,github:konstantin89");
MODULE_DESCRIPTION("Linux Kernel Hook");
