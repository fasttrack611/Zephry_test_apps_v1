/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

#define STACKSIZE 1024
#define PRIORITY 7

K_THREAD_STACK_DEFINE(thread_a_stack_area, STACKSIZE);
K_THREAD_STACK_DEFINE(thread_b_stack_area, STACKSIZE);
K_THREAD_STACK_DEFINE(thread_c_stack_area, STACKSIZE);

struct k_thread thread_a_data;
struct k_thread thread_b_data;
struct k_thread thread_c_data;

void thread_a(void *dummy1, void *dummy2, void *dummy3)
{
	ARG_UNUSED(dummy1);
	ARG_UNUSED(dummy2);
	ARG_UNUSED(dummy3);

	printk("Thread A started\n");

	k_sleep(K_MSEC(500));

	printk("Thread A finished\n");
}

void thread_b(void *dummy1, void *dummy2, void *dummy3)
{
	ARG_UNUSED(dummy1);
	ARG_UNUSED(dummy2);
	ARG_UNUSED(dummy3);

	printk("Thread B started\n");

	k_sleep(K_MSEC(1000));

	printk("Thread B finished\n");
}

void thread_c(void *dummy1, void *dummy2, void *dummy3)
{
	ARG_UNUSED(dummy1);
	ARG_UNUSED(dummy2);
	ARG_UNUSED(dummy3);

	printk("Thread C started\n");

	k_sleep(K_MSEC(1500));

	printk("Thread C finished\n");
}

void main(void)
{
	k_thread_create(&thread_a_data, thread_a_stack_area,
			K_THREAD_STACK_SIZEOF(thread_a_stack_area),
			thread_a, NULL, NULL, NULL,
			PRIORITY, 0, K_NO_WAIT);

	k_thread_create(&thread_b_data, thread_b_stack_area,
			K_THREAD_STACK_SIZEOF(thread_b_stack_area),
			thread_b, NULL, NULL, NULL,
			PRIORITY, 0, K_NO_WAIT);

	k_thread_create(&thread_c_data, thread_c_stack_area,
			K_THREAD_STACK_SIZEOF(thread_c_stack_area),
			thread_c, NULL, NULL, NULL,
			PRIORITY, 0, K_NO_WAIT);
}
