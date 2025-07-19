# Zephyr RTOS Kernel Services Samples

This directory contains a collection of Zephyr RTOS samples that demonstrate various kernel services. Each sample is a self-contained Zephyr project that can be built and run on the QEMU x86 target.

## Samples

* **threads:** Demonstrates the creation and use of threads.
* **scheduling:** Demonstrates preemptive scheduling.
* **cpu_idling:** Demonstrates the use of the CPU idling feature for power saving.
* **system_threads:** Demonstrates the creation of a system thread.
* **workqueue_threads:** Demonstrates how to submit work to a workqueue.
* **no_threads:** A simple application that does not use any threads.
* **interrupts:** Demonstrates how to register and handle an interrupt.
* **polling:** Demonstrates how to use the polling API to wait for an event.
* **semaphores:** Demonstrates how to use a semaphore for synchronization.
* **mutexes:** Demonstrates how to use a mutex to protect a shared resource.

## Prerequisites

To build and run these samples, you will need to have the Zephyr RTOS development environment set up. Please refer to the [Zephyr Getting Started Guide](https://docs.zephyrproject.org/latest/getting_started/index.html) for instructions on how to do this.

## Building and Running the Samples

To build and run a sample, navigate to the sample's directory and use the `west` tool to build and run the application. For example, to build and run the `threads` sample, you would run the following commands:

```sh
cd threads
west build -b qemu_x86 -p auto
west build -t run
```

You can replace `threads` with the name of any other sample directory.
