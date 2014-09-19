#include "ble_app.h"

#include "bleal/bleal.h"
#include "bleal/hwal.h"
#include "bleal/log.h"

#include <string.h>

void ble_app_initialize(void)
{
    bleal_uart_init();

    bleal_log("a\nb\nc\nd\ne\nf\n");
    bleal_initialize();
}

void ble_app_start_adv(void)
{
    bleal_ad_data_t ad[2];
    memset(ad, 0, sizeof(ad));
    ad[0].type = BLEAL_AD_DATA_TYPE_FLAGS;
    ad[0].field.flags = BLEAL_LE_ONLY_GENERAL_MODE;

    const char* name = "ble al demo";
    bleal_log("local name:%s\n", name);

    ad[1].type = BLEAL_AD_DATA_TYPE_SHORTENED_LOCAL_NAME;
    ad[1].field.p_local_name = (uint8_t *)name;
    ad[1].num = strlen(name);

    bleal_ad_params_t params;
    memset(&params, 0, sizeof(params));
    params.type = BLEAL_AD_TYPE_ADV_NONCONN_IND;
    params.adv_interval = 160; // 100 ms;
    bleal_start_advertising(&params, ad, 2, NULL, 0);
}

void ble_app_stop_adv(void)
{
}
