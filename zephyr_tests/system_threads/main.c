/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

void my_system_thread(void *p1, void *p2, void *p3)
{
	printk("My system thread is running!\n");
}

K_THREAD_DEFINE(my_system_thread_id, 1024, my_system_thread, NULL, NULL, NULL,
		K_PRIO_COOP(7), K_ESSENTIAL, K_NO_WAIT);

void main(void)
{
	printk("Main thread is running\n");
}
