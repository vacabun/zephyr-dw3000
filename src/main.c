/*
 * Copyright (c) 2016 Intel Corporation.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/drivers/uart.h>

#if CONFIG_DEBUG_SWD == 1
#include "stm32f4xx_ll_system.h"
#endif

#include "dw3000_hw.h"
#include "dw3000_spi.h"
#include "deca_probe_interface.h"

BUILD_ASSERT(DT_NODE_HAS_COMPAT(DT_CHOSEN(zephyr_console), zephyr_cdc_acm_uart),
	     "Console device is not ACM CDC UART device");

void main(void)
{

	#if CONFIG_DEBUG_SWD == 1
		LL_DBGMCU_EnableDBGSleepMode();
	#endif

	const struct device *const dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_console));
	uint32_t dtr = 0;



	if (usb_enable(NULL)) {
		return;
	}

	/* Poll if the DTR flag was set */
	while (!dtr) {
		uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
		/* Give CPU resources to low priority threads. */
		k_sleep(K_MSEC(100));
	}

    dw3000_hw_init();
    dw3000_hw_reset();
    dw3000_hw_init_interrupt();
    dw3000_spi_speed_fast();

    int ret = dwt_probe((struct dwt_probe_s*)&dw3000_probe_interf);

	while (1) {
		if (ret < 0) {
            printk("DWT Probe failed\r\n");
        }
        else{
            printk("DWT Probe Succeed\r\n");
        }
		k_sleep(K_SECONDS(1));
	}
	while (1) {
        printk("Hello world!");
		k_sleep(K_SECONDS(1));
	}
}
