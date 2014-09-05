# Bluetooth Low Energy Soc Hardware Abstraction Layer related

INCLUDEPATHS += -I"bleal" -I"config"
C_SOURCE_PATHS += bleal
C_SOURCE_FILES += bleal.c hwal.c

# BLE AL for nRF51822
INCLUDEPATHS += -I"bleal/Soc/nrf51822"
C_SOURCE_PATHS += bleal/SoC/nrf51822
C_SOURCE_FILES += bleal_interface.c bleal_nrf51822.c blea_nrf51822_scheduler.c

TARGET_CHIP := NRF51822_QFAA_CA
BOARD := BOARD_PCA10001

#Uncomment correct line if you have s110 programmed on the chip.
DEVICE_VARIANT := xxaa
#DEVICE_VARIANT := xxab

USE_SOFTDEVICE := S110
#USE_SOFTDEVICE := S210

HOME = /Users/hongbo.yang/
SDK_PATH = $(HOME)Developer/prjs/embeded/nrf/nrf51_sdk_v6_0_0_43681/nrf51822/
SOFTDEVICE_HEX_PATH = $(HOME)Developer/prjs/embeded/nrf/s110_nrf51822_7.0.0/s110_nrf51822_7.0.0_softdevice.hex
BUILD_SCRIPTS_PATH = $(HOME)Developer/prjs/embeded/prjs/nrf51822/build_scripts/
TEMPLATE_PATH = $(BUILD_SCRIPTS_PATH)

CFLAGS += -DBLE_STACK_SUPPORT_REQD
# debug: CFLAGS+=-DENABLE_DEBUG_LOG_SUPPORT # app module uses no flow control

C_SOURCE_FILES += main.c scheduler.c hardware.c timer.c gpiote.c 

C_SOURCE_FILES += sys_handler.c

# ble related sources
INCLUDEPATHS += -I"./"
C_SOURCE_PATHS += ble
C_SOURCE_FILES += ble_app.c ble_app_gatts.c

ifeq ($(MAKECMDGOALS),debug)
    C_SOURCE_FILES += uart.c
endif

# nrf_delay
# C_SOURCE_FILES += nrf_delay.c

# nrf_assert
# C_SOURCE_FILES += nrf_assert.c

# nrf_ecb
# C_SOURCE_FILES += nrf_ecb.c

# nrf_nvmc
# C_SOURCE_FILES += nrf_nvmc.c

# nrf_soc
# C_SOURCE_FILES += nrf_soc.c

# spi_master
# C_SOURCE_FILES += spi_master.c

# spi_slave
# C_SOURCE_FILES += spi_slave.c

# twi_master
# C_SOURCE_FILES += twi_hw_master.c
# C_SOURCE_FILES += twi_sw_master.c

# simple_uart
C_SOURCE_FILES += simple_uart.c

# sd_common
C_SOURCE_FILES += softdevice_handler.c

# app_common
# C_SOURCE_FILES += app_button.c
# C_SOURCE_FILES += app_fifo.c
# C_SOURCE_FILES += app_gpiote.c
C_SOURCE_FILES += app_scheduler.c
C_SOURCE_FILES += app_timer.c
# C_SOURCE_FILES += app_trace.c
# C_SOURCE_FILES += app_uart.c
# C_SOURCE_FILES += app_uart_fifo.c
# C_SOURCE_FILES += crc16.c
# C_SOURCE_FILES += hci_mem_pool.c
# C_SOURCE_FILES += hci_slip.c
# C_SOURCE_FILES += hci_transport.c
# C_SOURCE_FILES += pstorage.c # need pstorage_platform.h

# ble
C_SOURCE_FILES += ble_advdata.c
# C_SOURCE_FILES += ble_advdata_parser.c
# C_SOURCE_FILES += ble_conn_params.c
# C_SOURCE_FILES += ble_debug_assert_handler.c
# C_SOURCE_FILES += ble_dtm.c
# C_SOURCE_FILES += ble_error_log.c
# C_SOURCE_FILES += ble_flash.c
# C_SOURCE_FILES += ble_racp.c
# C_SOURCE_FILES += ble_radio_notification.c
# C_SOURCE_FILES += ble_sensorsim.c

# ble/ble_services
# C_SOURCE_FILES += ble_ans_c.c
# C_SOURCE_FILES += ble_bas.c
# C_SOURCE_FILES += ble_bps.c
# C_SOURCE_FILES += ble_cscs.c
# C_SOURCE_FILES += ble_dfu.c
# C_SOURCE_FILES += ble_dis.c
# C_SOURCE_FILES += ble_gls.c
# C_SOURCE_FILES += ble_gls_db.c
# C_SOURCE_FILES += ble_hids.c
# C_SOURCE_FILES += ble_hrs.c
# C_SOURCE_FILES += ble_hts.c
# C_SOURCE_FILES += ble_ias.c
# C_SOURCE_FILES += ble_ias_c.c
# C_SOURCE_FILES += ble_lls.c
# C_SOURCE_FILES += ble_rscs.c
# C_SOURCE_FILES += ble_sc_ctrlpt.c
# C_SOURCE_FILES += ble_srv_common.c
# C_SOURCE_FILES += ble_tps.c

# ble/device_manager/experimental
# C_SOURCE_FILES += device_manager_central.c

OUTPUT_FILENAME := main

include $(TEMPLATE_PATH)Makefile.common

