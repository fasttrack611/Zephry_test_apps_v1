// Delayed work + timer interrupt demo in Zephyr RTOS
#include <zephyr/kernel.h>         // Core kernel APIs: timers, work items
#include <zephyr/sys/printk.h>     // Lightweight logging via printk

// Work item declarations (delayed execution objects)
struct k_work_delayable work1;
struct k_work_delayable work2;

// Shared work handler triggered after timer expiry
void deferred_work_handler(struct k_work *work) {
    if (work == &work1.work) {
        printk(" Deferred work from Timer 1\n");
    } else if (work == &work2.work) {
        printk(" Deferred work from Timer 2\n");
    } else {
        printk(" Unknown work source\n");
    }
}

// Timer 1 ISR-like callback
void timer1_expiry(struct k_timer *timer) {
    printk(" Timer 1 interrupt fired\n");
    // Schedule deferred execution (work1) after 500ms
    k_work_schedule(&work1, K_MSEC(500));
}

// Timer 2 ISR-like callback
void timer2_expiry(struct k_timer *timer) {
    printk(" Timer 2 interrupt fired\n");
    // Schedule deferred execution (work2) after 1000ms
    k_work_schedule(&work2, K_MSEC(1000));
}

// Static timer definitions with callbacks
K_TIMER_DEFINE(timer1, timer1_expiry, NULL);  // Only expiry callback used
K_TIMER_DEFINE(timer2, timer2_expiry, NULL);

int main(void) {
    printk(" Zephyr multi-interrupt + delayed work demo started\n");

    // Initialize delayable work items and assign shared handler
    k_work_init_delayable(&work1, deferred_work_handler);
    k_work_init_delayable(&work2, deferred_work_handler);

    // Start timers:
    // - timer1: first fire after 1s, then every 3s
    // - timer2: first fire after 2s, then every 4s
    k_timer_start(&timer1, K_SECONDS(1), K_SECONDS(3));
    k_timer_start(&timer2, K_SECONDS(2), K_SECONDS(4));

    // Main thread sleeps — actual activity occurs in timer + work context
    while (1) {
        k_sleep(K_SECONDS(10));  // Sleep long enough to observe cycles
    }

    return 0;
}