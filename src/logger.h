#ifndef __LOGGER_H
#define __LOGGER_H

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>


#define log_info(format, args...)  printk(KERN_INFO "[ ] lkh " format, ##args);

#define log_error(format, args...)  printk(KERN_ERR "[X] lkh " format, ##args);

#endif