/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>

struct k_work_q my_work_q;
K_THREAD_STACK_DEFINE(my_stack_area, 1024);

struct my_work_item {
	struct k_work work;
	int data;
};

void my_work_handler(struct k_work *work)
{
	struct my_work_item *item = CONTAINER_OF(work, struct my_work_item, work);
	printk("Work item processed with data: %d\n", item->data);
}

void main(void)
{
	k_work_q_start(&my_work_q, my_stack_area, K_THREAD_STACK_SIZEOF(my_stack_area), 5);

	struct my_work_item item1, item2;

	k_work_init(&item1.work, my_work_handler);
	item1.data = 1;
	k_work_submit_to_queue(&my_work_q, &item1.work);

	k_work_init(&item2.work, my_work_handler);
	item2.data = 2;
	k_work_submit_to_queue(&my_work_q, &item2.work);

	printk("Main thread finished\n");
}
