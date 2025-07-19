#include <zephyr.h>
#include <sys/printk.h>
#include <sys/poll.h>

/* Declare signals, FIFO, and semaphore */
static struct k_poll_signal signal1;
static struct k_poll_signal signal2;
K_FIFO_DEFINE(my_fifo);
K_SEM_DEFINE(my_sem, 0, 1);

void main(void)
{
    struct k_poll_event events[4];

    k_poll_signal_init(&signal1);
    k_poll_signal_init(&signal2);

    /* Initialize poll events for signals */
    k_poll_event_init(&events[0], K_POLL_TYPE_SIGNAL, K_POLL_MODE_NOTIFY_ONLY, &signal1);
    k_poll_event_init(&events[1], K_POLL_TYPE_SIGNAL, K_POLL_MODE_NOTIFY_ONLY, &signal2);

    /* Initialize poll event for FIFO */
    k_poll_event_init(&events[2], K_POLL_TYPE_FIFO_DATA_AVAILABLE, K_POLL_MODE_NOTIFY_ONLY, &my_fifo);

    /* Initialize poll event for semaphore */
    k_poll_event_init(&events[3], K_POLL_TYPE_SEM_AVAILABLE, K_POLL_MODE_NOTIFY_ONLY, &my_sem);

    printk("Polling multiple events: signals, FIFO, and semaphore\n");

    /* Simulate raising events */
    k_sleep(K_MSEC(500));
    k_poll_signal_raise(&signal1, 0);

    k_sleep(K_MSEC(500));
    k_poll_signal_raise(&signal2, 0);

    k_sleep(K_MSEC(500));
    k_fifo_put(&my_fifo, "data"); // Put arbitrary data into FIFO

    k_sleep(K_MSEC(500));
    k_sem_give(&my_sem); // Release semaphore

    printk("Waiting for events...\n");
    k_poll(events, ARRAY_SIZE(events), K_FOREVER);

    for (int i = 0; i < ARRAY_SIZE(events); i++) {
        if (events[i].state != K_POLL_STATE_NOT_READY) {
            printk("Event %d received!\n", i + 1);
            k_poll_event_reset(&events[i]);
        }
    }
}
