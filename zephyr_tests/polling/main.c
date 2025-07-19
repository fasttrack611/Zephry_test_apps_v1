/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <sys/poll.h>

static struct k_poll_signal signal;

void main(void)
{
	struct k_poll_event events[1];

	k_poll_signal_init(&signal);
	k_poll_event_init(&events[0], K_POLL_TYPE_SIGNAL,
			  K_POLL_MODE_NOTIFY_ONLY, &signal);

	printk("Polling sample started\n");

	/* In a real application, you would have another thread or interrupt
	 * call k_poll_signal_raise()
	 */
	k_sleep(K_SECONDS(1));
	k_poll_signal_raise(&signal, 0);

	printk("Waiting for event...\n");
	k_poll(events, 1, K_FOREVER);
	printk("Event received!\n");
}
