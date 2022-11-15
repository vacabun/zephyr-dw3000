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

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart), "Console device is not ACM CDC UART device");

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define DEFAULT_STACKSIZE 2048

#if defined(TEST_READING_DEV_ID) || defined(TEST_AES_SS_TWR_INITIATOR) || defined(TEST_AES_SS_TWR_RESPONDER)
#define TEST_STACKSIZE 2048
#define _TEST_
#include <examples/example.h>
void (*test_fun)(void *, void *, void *);
static K_THREAD_STACK_DEFINE(test_stack, TEST_STACKSIZE);
static struct k_thread test_thread;
#endif // TEST_READING_DEV_ID TEST_AES_SS_TWR_INITIATOR TEST_AES_SS_TWR_RESPONDER

#if defined(DEVICE_TAG)
#include <device/tag/tag.h>
static K_THREAD_STACK_DEFINE(tag_initiator_stack, DEFAULT_STACKSIZE);
static struct k_thread tag_initiator_thread;
#endif //DEVICE_TAG

void main(void)
{
	// swd debug
#if CONFIG_DEBUG_SWD == 1
	LL_DBGMCU_EnableDBGSleepMode();
#endif

	/* usb config */
	if (usb_enable(NULL))
		return;
	k_sleep(K_MSEC(100));

#if defined(_TEST_)
#if defined(TEST_READING_DEV_ID)
	test_fun = read_dev_id;
#endif // TEST_READING_DEV_ID

#if defined(TEST_AES_SS_TWR_INITIATOR)
	test_fun = ss_aes_twr_initiator;
#endif // TEST_AES_SS_TWR_INITIATOR

#if defined(TEST_AES_SS_TWR_RESPONDER)
	test_fun = ss_aes_twr_responder;
#endif // TEST_AES_SS_TWR_RESPONDER

	k_thread_create(&test_thread, test_stack, TEST_STACKSIZE, test_fun,
					NULL, NULL, NULL, K_PRIO_COOP(7), 0, K_NO_WAIT);
#endif //_TEST_

#if defined(DEVICE_TAG)
	k_thread_create(&tag_initiator_thread, tag_initiator_stack, DEFAULT_STACKSIZE, tag_initiator,
					NULL, NULL, NULL, K_PRIO_COOP(7), 0, K_NO_WAIT);
#endif
}
