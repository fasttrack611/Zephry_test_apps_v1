/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

void main(void)
{
	printk("CPU Idling sample started\n");

	while (1) {
		printk("Going to sleep for 1 second...\n");
		k_cpu_idle();
		printk("Woke up!\n");
		k_sleep(K_SECONDS(1));
	}
}
