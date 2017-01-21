/*
 * atomic - atomic integer demo
 *
 * Written in 2012 by Prashant P Shah <pshah.mumbai@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE
 */


// We do not as of now, have a format specifier  to print atomic_t variables and 
// their 64 bit variants using the printk , hence expect messages while compiling
//ref: https://patchwork.kernel.org/patch/9429167/


#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/atomic.h>
#include <linux/interrupt.h>

//
//#define DEBUG(m) printk("myatomic: " m " current value = %d\n", atomic_read(&atom));


#define	MODULE_NAME "Atomic"


#define	DEBUG(format, arg...)	\
do {	\
	printk(KERN_INFO "%s[%d, %s]:"format"\n", MODULE_NAME, \
			__LINE__, __FUNCTION__, ##arg);	\
} while(0)



static int __init myatomic_init(void)
{
	atomic_t atom;
	printk(KERN_INFO "myatomic: %s\n", __FUNCTION__);

	atomic_set(&atom, -100);	/* initialize */
	DEBUG("atomic_set %d",atomic_read(&atom));
	atomic_inc(&atom);
	DEBUG("atomic_inc %d",atomic_read(&atom));
	atomic_dec(&atom);
	DEBUG("atomic_dec %d", atomic_read(&atom));
	atomic_add(100, &atom);
	DEBUG("atomic_add %d", atomic_read(&atom));
	atomic_sub(100, &atom);
	DEBUG("atomic_sub %d", atomic_read(&atom));
	if (atomic_sub_and_test(-100, &atom)) {
		DEBUG("atomic_sub_and_test, We substracted -100 from -100  %d", atomic_read(&atom));
	}
	if (atomic_inc_and_test(&atom)) {
		DEBUG("atomic_inc_and_test %d", atomic_read(&atom));
	}
	if (atomic_dec_and_test(&atom)) {
		DEBUG("atomic_dec_and_test %d", atomic_read(&atom));
	}

	return 0;
}

static void __exit myatomic_exit(void)
{
	printk(KERN_INFO "myatomic: %s\n", __FUNCTION__);
}

module_init(myatomic_init);
module_exit(myatomic_exit);

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Me");

