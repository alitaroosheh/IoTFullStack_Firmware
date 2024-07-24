
#pragma once

#include <stdio.h>
#include <string.h>
#include "common.h"
#include "NVSHelper.h"
#include "Utilities.h"
#include "math.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "mqtt_client.h"
#include "cJSON.h"



#define jsonGetString(root,key,output) { \
    if(!cJSON_GetObjectItem(root, key)) \
    { \
        ESP_LOGE(TAG, "jsonGetString %s not exist.", key); \
        return ESP_ERR_NOT_FOUND; \
    } \
    else \
    { \
        strcpy((char *)output, cJSON_GetObjectItem(root, key)->valuestring); \
        ESP_LOGI(TAG, "key: %s", output); \
    } \
}


#define jsonGetInt(root,key,output) { \
    if(!cJSON_GetObjectItem(root, key)) \
    { \
        ESP_LOGE(TAG, "jsonGetInt %s not exist.", key); \
        return ESP_ERR_NOT_FOUND; \
    } \
    else \
    { \
        *output = cJSON_GetObjectItem(root, key)->valueint; \
        ESP_LOGI(TAG, "key: %"PRId32 "", (uint32_t)output); \
    } \
}




esp_err_t                   systemConfigLoadWiFi                                      ();
esp_err_t                   systemConfigLoadMqtt                                      ();