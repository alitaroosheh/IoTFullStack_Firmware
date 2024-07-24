/**
 * @file systemConfig.h
 * @author Ali Taroosheh (ali.taroosheh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-24
 * 
 * 
 */


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

typedef struct 
{
    uint8_t topic[128];
    uint8_t message[128];
    uint8_t qos;
    bool retain;
}lastwillConfig;

typedef struct 
{
    uint8_t clientCert[4096];
    uint8_t serverCert[4096];
}certConfig;



typedef struct 
{
    uint8_t clientId[32];
    uint8_t url[256];
    esp_mqtt_protocol_ver_t version;
    uint8_t userName[128];
    uint8_t password[128];
    lastwillConfig lastwill;
    certConfig cert;
}mqttConfig;

typedef struct 
{
    uint8_t ssid[128];
    uint8_t password[128];
}wifiConfig;

typedef struct systemConfig
{
    uint8_t version[6];
    wifiConfig wifi;
    mqttConfig mqtt;
}systemConfig;


esp_err_t                   systemConfigLoadWiFi                                      ();
esp_err_t                   systemConfigLoadMqtt                                      ();