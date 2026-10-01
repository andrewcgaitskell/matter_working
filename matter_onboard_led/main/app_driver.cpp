/*
   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <esp_log.h>
#include <stdlib.h>
#include <string.h>

#include <esp_matter.h>
#include "bsp/esp-bsp.h"

#include <app_priv.h>

/* added to enable onboard led to be controlled */

#include <driver/gpio.h>


using namespace chip::app::Clusters;
using namespace esp_matter;

static const char *TAG = "app_driver";
extern uint16_t light_endpoint_id;

/* deleted set power, saturation and temperature functions for onboard led control */

/* added from here for onboard led control */

#define LED_GPIO     GPIO_NUM_15   // XIAO ESP32-C6 user LED, active low
#define LED_ON_LEVEL 0

static esp_err_t app_driver_light_set_power(esp_matter_attr_val_t *val)
{
    gpio_set_level(LED_GPIO, val->val.b ? LED_ON_LEVEL : !LED_ON_LEVEL);
    return ESP_OK;
}

esp_err_t app_driver_attribute_update(app_driver_handle_t driver_handle, uint16_t endpoint_id, uint32_t cluster_id,
                                      uint32_t attribute_id, esp_matter_attr_val_t *val)
{
    if (endpoint_id == light_endpoint_id && cluster_id == OnOff::Id &&
        attribute_id == OnOff::Attributes::OnOff::Id) {
        return app_driver_light_set_power(val);
    }
    return ESP_OK;
}

esp_err_t app_driver_light_set_defaults(uint16_t endpoint_id)
{
    esp_matter_attr_val_t val = esp_matter_invalid(NULL);
    attribute_t *attribute = attribute::get(endpoint_id, OnOff::Id, OnOff::Attributes::OnOff::Id);
    attribute::get_val(attribute, &val);
    return app_driver_light_set_power(&val);
}

app_driver_handle_t app_driver_light_init()
{
    gpio_config_t cfg = {};
    cfg.pin_bit_mask = 1ULL << LED_GPIO;
    cfg.mode = GPIO_MODE_OUTPUT;
    gpio_config(&cfg);
    gpio_set_level(LED_GPIO, !LED_ON_LEVEL);
    return NULL;
}

/* to here */


static void app_driver_button_toggle_cb(void *arg, void *data)
{
    ESP_LOGI(TAG, "Toggle button pressed");
    uint16_t endpoint_id = light_endpoint_id;
    uint32_t cluster_id = OnOff::Id;
    uint32_t attribute_id = OnOff::Attributes::OnOff::Id;

    attribute_t *attribute = attribute::get(endpoint_id, cluster_id, attribute_id);

    esp_matter_attr_val_t val = esp_matter_invalid(NULL);
    attribute::get_val(attribute, &val);
    val.val.b = !val.val.b;
    attribute::update(endpoint_id, cluster_id, attribute_id, &val);
}

app_driver_handle_t app_driver_button_init()
{
    /* Initialize button */
    button_handle_t btns[BSP_BUTTON_NUM];
    ESP_ERROR_CHECK(bsp_iot_button_create(btns, NULL, BSP_BUTTON_NUM));
    ESP_ERROR_CHECK(iot_button_register_cb(btns[0], BUTTON_PRESS_DOWN, NULL, app_driver_button_toggle_cb, NULL));
    
    return (app_driver_handle_t)btns[0];
}
