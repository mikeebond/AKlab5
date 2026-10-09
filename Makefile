obj-m := hello1.o hello2.o

ccflags-y += -I$(PWD)/inc

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
