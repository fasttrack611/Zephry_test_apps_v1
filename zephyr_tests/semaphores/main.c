/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

K_SEM_DEFINE(my_sem, 0, 1);

void thread_a(void *dummy1, void *dummy2, void *dummy3)
{
	printk("Thread A waiting for semaphore\n");
	k_sem_take(&my_sem, K_FOREVER);
	printk("Thread A got semaphore\n");
}

void thread_b(void *dummy1, void *dummy2, void *dummy3)
{
	printk("Thread B giving semaphore\n");
	k_sem_give(&my_sem);
}

K_THREAD_STACK_DEFINE(thread_a_stack_area, 1024);
K_THREAD_STACK_DEFINE(thread_b_stack_area, 1024);
struct k_thread thread_a_data;
struct k_thread thread_b_data;

void main(void)
{
	k_thread_create(&thread_a_data, thread_a_stack_area,
			K_THREAD_STACK_SIZEOF(thread_a_stack_area),
			thread_a, NULL, NULL, NULL,
			7, 0, K_NO_WAIT);

	k_thread_create(&thread_b_data, thread_b_stack_area,
			K_THREAD_STACK_SIZEOF(thread_b_stack_area),
			thread_b, NULL, NULL, NULL,
			7, 0, K_MSEC(500));
}
