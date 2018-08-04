#ifndef __LOGGER_H
#define __LOGGER_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>


#define log_info(format, ...) do{ printk(KERN_INFO format, ##__VA_ARGS__); }while(0);

#define log_error(format, ...) do{ printk(KERN_ERR format, ##__VA_ARGS__); }while(0);

#endif