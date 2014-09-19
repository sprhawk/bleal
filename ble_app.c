#include "ble_app.h"

#include "bleal/bleal.h"
#include "bleal/hwal.h"
#include "bleal/log.h"

#include <string.h>

#include "config.h"

void ble_app_start_adv(void);
void ble_app_stop_adv(void);

void ble_app_initialize(void)
{
    bleal_uart_init();

    bleal_log("a\nb\nc\nd\ne\nf\n");
    bleal_initialize();

    bleal_device_parameters_t dev_params;
    memset(&dev_params, 0, sizeof(dev_params));

    const char* name = BLE_DEVICE_NAME;
    const uint16_t name_len = strlen(name);

    bleal_log("device name:%s\n", name);

    // setup device parameters;
    dev_params.p_device_name = (uint8_t *)name;
    dev_params.device_name_len = name_len;
    dev_params.appearance = BLEAL_APPEARANCE_UNKNOWN;
    dev_params.connection.min_connection_interval = BLE_CONN_MIN_INTERVAL ;
    dev_params.connection.max_connection_interval = BLE_CONN_MAX_INTERVAL ;
    dev_params.connection.slave_latency = BLE_CONN_SLAVE_LATENCY;
    dev_params.connection.connection_supervision_timeout = BLE_CONN_SUPERVISION_TIMEOUT;

    bleal_setup_ble_device(&dev_params);
}

void ble_app_start(void)
{
    ble_app_start_adv();
}

void ble_app_start_adv(void)
{
    bleal_ad_data_t ad[4];

    memset(ad, 0, sizeof(ad));

    ad[0].type = BLEAL_AD_DATA_TYPE_FLAGS;
    ad[0].field.flags = BLEAL_LE_ONLY_GENERAL_MODE;

    ad[1].type = BLEAL_AD_DATA_TYPE_COMPLETE_LOCAL_NAME;
    ad[1].num = 0;
    // ad[1].num = strlen(BLE_DEVICE_NAME);
    // ad[1].field.p_local_name = BLE_DEVICE_NAME;

    ad[2].type = BLEAL_AD_DATA_TYPE_COMPLETE_16BIT_SERVICE_UUIDS;
    bleal_uuid16_t uuids[1] = {0x1804};
    ad[2].field.p_uuid16_list = uuids;
    ad[2].num = sizeof(uuids) / sizeof(bleal_uuid16_t);

    ad[3].type = BLEAL_AD_DATA_TYPE_TX_POWER_LEVEL;
    ad[3].num = 0;
    // ad[3].num = 1;
    // ad[3].field.tx_power = -20;

    bleal_ad_params_t params;
    memset(&params, 0, sizeof(params));
    params.type = BLEAL_AD_TYPE_ADV_IND;
    params.adv_interval = 160; // 100 ms;
    bleal_start_advertising(&params, ad, sizeof(ad)/sizeof(bleal_ad_data_t), NULL, 0);
}

void ble_app_stop_adv(void)
{
    bleal_stop_advertising();
}
