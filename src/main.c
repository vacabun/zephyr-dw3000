/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/drivers/uart.h>

// use swd debug
#if CONFIG_DEBUG_SWD == 1
#include "stm32f4xx_ll_system.h"
#endif

#include "dw3000.h"

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
			 "Console device is not ACM CDC UART device");

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define DEFAULT_STACKSIZE 4096

#ifdef TEST_READING_DEV_ID
void read_dev_id(void *p1, void *p2, void *p3);
static K_THREAD_STACK_DEFINE(read_dev_id_stack, DEFAULT_STACKSIZE);
static struct k_thread read_dev_id_thread;
#endif

#ifdef TEST_SS_AES_TWR_INITIATOR
void ss_aes_twr_initiator(void *p1, void *p2, void *p3);
static K_THREAD_STACK_DEFINE(ss_aes_twr_initiator_stack, DEFAULT_STACKSIZE);
static struct k_thread ss_aes_twr_initiator_thread;
#endif

void main(void)
{
	// swd debug
#if CONFIG_DEBUG_SWD == 1
	LL_DBGMCU_EnableDBGSleepMode();
#endif

	/* usb config */
	const struct device *const dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
	uint32_t dtr = 0;
	if (usb_enable(NULL))
		return;
	// Poll if the DTR flag was set
	while (!dtr)
	{
		uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
		// Give CPU resources to low priority threads.
		k_sleep(K_MSEC(100));
	}

#ifdef TEST_READING_DEV_ID
	k_thread_create(&read_dev_id_thread, read_dev_id_stack, DEFAULT_STACKSIZE, read_dev_id,
					NULL, NULL, NULL, K_PRIO_COOP(7), 0, K_NO_WAIT);
#endif

#ifdef TEST_SS_AES_TWR_INITIATOR
	k_thread_create(&ss_aes_twr_initiator_thread, ss_aes_twr_initiator_stack, DEFAULT_STACKSIZE, ss_aes_twr_initiator,
					NULL, NULL, NULL, K_PRIO_COOP(7), 0, K_NO_WAIT);
#endif
	// void ss_aes_twr_initiator(void *p1, void *p2, void *p3);
	// ss_aes_twr_initiator(NULL, NULL, NULL);

	// while (1) {
	//     printk("Hello world!");
	// 	k_sleep(K_SECONDS(1));
	// }
}
