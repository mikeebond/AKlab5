#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_AUTHOR("Mykhailo Bondarchuk");
MODULE_DESCRIPTION("Hello module 1 - exports print function and manages list");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_time_list {
	struct list_head list;
	ktime_t time_before;
	ktime_t time_after;
};

static LIST_HEAD(hello_time_head);

void print_hello(void)
{
	struct hello_time_list *ptr;

	ptr = kmalloc(sizeof(*ptr), GFP_KERNEL);
	if (!ptr) {
		pr_err("Memory allocation failed\n");
		return;
	}

	ptr->time_before = ktime_get();
	pr_info("Hello, world!\n");
	ptr->time_after = ktime_get();

	list_add_tail(&ptr->list, &hello_time_head);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("Module hello1 loaded.\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_time_list *md, *tmp;

	list_for_each_entry_safe(md, tmp, &hello_time_head, list) {
		ktime_t duration = ktime_sub(md->time_after, md->time_before);
		pr_info("Time taken for print (ns): %lld\n", ktime_to_ns(duration));
		list_del(&md->list);
		kfree(md);
	}

	pr_info("Module hello1 unloaded.\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
