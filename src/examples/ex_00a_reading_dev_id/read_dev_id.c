/*! ----------------------------------------------------------------------------
 *  @file    read_dev_id.c
 *  @brief   This example just read DW IC's device ID. It can be used to verify
 *           the SPI comms are working correctly.
 *
 * @attention
 *
 * Copyright 2018-2020 (c) Decawave Ltd, Dublin, Ireland.
 *
 * All rights reserved.
 *
 * @author Decawave
 */
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/drivers/uart.h>
#include "dw3000.h"

#if defined(TEST_READING_DEV_ID)

extern void test_run_info(unsigned char *data);

/* Example application name and version to display on LCD screen/VCOM port. */
#define APP_NAME "READ DEV ID      "

/**
 * Application entry point.
 */
int read_dev_id(void)
{
    int err;
    uint32_t dev_id;

	dw3000_hw_init();
	dw3000_hw_reset();
	dw3000_hw_init_interrupt();
	dw3000_spi_speed_fast();

    k_sleep(K_SECONDS(1)); // Time needed for DW3000 to start up (transition from INIT_RC to IDLE_RC, or could wait for SPIRDY event)

    dwt_probe((struct dwt_probe_s*)&dw3000_probe_interf);

    /* Reads and validate device ID returns DWT_ERROR if it does not match expected else DWT_SUCCESS */
    if ((err = dwt_check_dev_id()) == DWT_SUCCESS)
    {
        while (1){
            dev_id = dwt_readdevid();
            printk((unsigned char *)"CHECK DEV ID OK : %x \r\n", dev_id);
        }
    }
    else
    {
        while (1)
            printk((unsigned char *)"DEV ID FAILED");
    }

    return err;
}

#endif
/*****************************************************************************************************************************************************
 * NOTES:
 ****************************************************************************************************************************************************/
