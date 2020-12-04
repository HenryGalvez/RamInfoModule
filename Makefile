obj-m := ram.o

KERNELDIR ?= /lib/modules/$(shell uname -r)/build

all default: modules
install: modules_install

modules modules_install help clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) $@


clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
	
test_uno:
	sudo dmesg -C
	sudo insmod ram.ko
	sudo cat /proc/ram
	sudo rmmod ram.ko
	sudo dmesg

