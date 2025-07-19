/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <sys/printk.h>
#include <zephyr/pm/pm.h>

#define STACKSIZE 1024
#define THREAD_PRIORITY 7

// Thread function to display system time
void system_time_thread(void *thread_name, void *p2, void *p3)
{
    while (1) {
        uint64_t uptime = k_uptime_get();
        printk("Thread %s: System uptime: %llu ms\n", (char *)thread_name, uptime);
        k_sleep(K_SECONDS(1));
    }
}

// Power management thread: demonstrates explicit power management calls
void power_management_thread(void *p1, void *p2, void *p3)
{
    while (1) {
        printk("Power Management Thread: Forcing system to soft-off state for demonstration...\n");
        // This is just for demonstration; in real use, you'd let Zephyr manage PM automatically
        // pm_state_force(0, &(struct pm_state_info){PM_STATE_SOFT_OFF, 0, 0});
        k_sleep(K_SECONDS(10)); // Wait before next demonstration
    }
}

// Define three system time threads
K_THREAD_DEFINE(system_time_thread1_id, STACKSIZE, system_time_thread, "T1", NULL, NULL, THREAD_PRIORITY, 0, 0);
K_THREAD_DEFINE(system_time_thread2_id, STACKSIZE, system_time_thread, "T2", NULL, NULL, THREAD_PRIORITY, 0, 0);
K_THREAD_DEFINE(system_time_thread3_id, STACKSIZE, system_time_thread, "T3", NULL, NULL, THREAD_PRIORITY, 0, 0);

// Define power management thread
K_THREAD_DEFINE(power_management_thread_id, STACKSIZE, power_management_thread, NULL, NULL, NULL, THREAD_PRIORITY+1, 0, 0);

void main(void)
{
    printk("Main thread is running\n");
}
