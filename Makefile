#obj-m represents loadable modules.
obj-m := lkh.o

KVERSION = $(shell uname -r)

lkh-objs += src/module.o
lkh-objs += src/sys_hook.o
lkh-objs += src/hooks.o

ccflags-y := -I$(src)

all:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) modules
	

clean:
	make -C /lib/modules/$(KVERSION)/build M=$(PWD) clean
