#ifndef _ANTHOR_H_
#define _ANTHOR_H_

#if defined(DEVICE_ANCHOR)

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/usb/usb_device.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/shell/shell.h>
#include <zephyr/logging/log.h>

#include "dw3000.h"

#include <shared_data/config_options.h>
#include <shared_data/shared_defines.h>
#include <shared_data/shared_functions.h>
#include <MAC_802_15_4/mac_802_15_4.h>



void anthor_tx_done_cb(const dwt_cb_data_t *cb_data);
void anthor_rx_ok_cb(const dwt_cb_data_t *cb_data);
void anthor_rx_timeout_cb(const dwt_cb_data_t *cb_data);
void anthor_rx_err_cb(const dwt_cb_data_t *cb_data);
void anthor_spi_err_cb(const dwt_cb_data_t *cb_data);
void anthor_spi_ready_cb(const dwt_cb_data_t *cb_data);
void anthor_dual_spi_cb(const dwt_cb_data_t *cb_data);

void anthor_responder(void *p1, void *p2, void *p3);

#endif

#endif
