/*
 * basic_interrupts - Interrupts demo
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

//The correct place to call request_irq is when the device is first opened, before the
//hardware is instructed to generate interrupts.
//The place to call free_irq is the last
//time the device is closed, after the hardware is told not to interrupt the processor any
//more.
//For what it’s worth, the i386 and x86_64 architectures define a function for querying
//the availability of an interrupt line:
//int can_request_irq(unsigned int irq, unsigned long flags);
//This function returns a nonzero value if an attempt to allocate the given interrupt succeeds.
//Note, however, that things can always change between calls to can_request_irq
//and request_irq






#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <linux/moduleparam.h>


int  IRQN = 19; 	/* replace this with the interrupt id of the device 
			you think will most interrupt  (try doing with eth!)  from /proc/interrups */


module_param(IRQN, int, 0); // we are giving an option to insert the interrupt handler 
				// at the irq you like 


int my_dev_id;
int counter;


static irqreturn_t my_interrupt(int i, void *data)
{
	printk(KERN_INFO "basic_interrupts: %s\n", __FUNCTION__);
	printk(KERN_INFO "basic_interrupts: Interrupt Handler called %d\n", counter);
	printk("Interrupt called within the process context %s", current->comm);
	printk("The data (int here) which was passed to the handler is %d",*(int*)(data));

	if ( !strncmp(current->comm,"sshd",128))
		printk("Being called from sshd \n \n");

	counter++;
	return IRQ_NONE;
}

static int __init basic_interrupts_init(void)
{
	printk(KERN_INFO "basic_interrupts: %s\n", __FUNCTION__);
	my_dev_id = 1337;
	counter = 1;
	if (request_irq(IRQN, my_interrupt, IRQF_SHARED, "basic_interrupts", &my_dev_id)) {
		printk(KERN_ERR "basic_interrupts: cannot register IRQ %d\n", IRQN);
		return -EIO;
	}
	else {
	}

	printk(KERN_INFO "basic_interrupts: registered IRQ %d\n", IRQN);
	return 0;
}

static void __exit basic_interrupts_exit(void)
{
	printk(KERN_INFO "basic_interrupts: %s\n", __FUNCTION__);
	free_irq(IRQN, &my_dev_id);
	return;
}

module_init(basic_interrupts_init);
module_exit(basic_interrupts_exit);

MODULE_LICENSE("Dual MIT/GPL");
MODULE_AUTHOR("Me");

