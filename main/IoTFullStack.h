/**
 * @file IoTFullStack.h
 * @author Ali Taroosheh (ali.taroosheh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-02
 * 
 * 
 */

#pragma once

#include <stdio.h>
#include <bme68x.h>
#include <string.h>
#include "common.h"
#include "I2CHelper.h"
#include "IAQHelper.h"
#include "WiFiHelper.h"
#include "NVSHelper.h"
#include "IOHelper.h"
#include "Utilities.h"
#include "math.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "lwip/err.h"
#include "lwip/sys.h"
#include "mqtt_client.h"


#define configPartition       	"config_nvs"

