
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




esp_err_t                   systemConfigLoadWiFi                                      ();
esp_err_t                   systemConfigLoadMqtt                                      ();