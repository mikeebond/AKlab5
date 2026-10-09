#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include "hello1.h"

MODULE_AUTHOR("Mykhailo Bondarchuk");
MODULE_DESCRIPTION("Hello module 2 - parameter logic and calls print_hello");
MODULE_LICENSE("Dual BSD/GPL");

static uint print_count = 1;
module_param(print_count, uint, 0444);
MODULE_PARM_DESC(print_count, "Number of times to print");

static int __init hello2_init(void)
{
	uint i;

	if (print_count == 0 || (print_count >= 5 && print_count <= 10)) {
		pr_warn("Warning: count is 0 or between 5 and 10.\n");
	} else if (print_count > 10) {
		pr_err("Error: count is greater than 10.\n");
		return -EINVAL;
	}

	for (i = 0; i < print_count; i++) {
		print_hello();
	}

	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Module hello2 unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
