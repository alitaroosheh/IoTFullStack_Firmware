/**
 * @file systemConfig.c
 * @author Ali Taroosheh (ali.taroosheh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-24
 * 
 * 
 */

#include "IoTFullStack.h"

#include "systemConfig.h"

#define TAG						"systemConfig"


static systemConfig confing;


static esp_err_t readWiFiConfig(uint8_t *json, wifiConfig *wifi)
{

    cJSON *root = cJSON_Parse((char *)json);
    jsonGetString(root, "ssid", wifi->ssid);
    jsonGetString(root, "password", wifi->password);

    cJSON_Delete(root);
    return ESP_OK;

}


esp_err_t systemConfigLoadWiFi()
{
    size_t len;
    uint8_t json[1024] = {0};
    if (nvsLoad(configPartition, "wifi", "wifi", (char *)json, &len) != ESP_OK)
	{
        ESP_LOGE(TAG, "systemConfigLoadWiFi json not exist.");
        return ESP_ERR_NOT_FOUND;
    }

    return readWiFiConfig(json, &confing.wifi);
}


static esp_err_t readMqttConfig(uint8_t *json, mqttConfig *mqtt)
{
    cJSON *root = cJSON_Parse((char *)json);
    jsonGetString(root, "clientId", mqtt->clientId);
    jsonGetString(root, "url", mqtt->url);
    jsonGetInt(root, "version", &mqtt->version);
    jsonGetString(root, "userName", mqtt->userName);
    jsonGetString(root, "password", mqtt->password);

    cJSON *lastwill = cJSON_GetObjectItem(root, "lastwill");
    jsonGetString(lastwill, "topic", mqtt->lastwill.topic);
    jsonGetString(lastwill, "message", mqtt->lastwill.message);
    jsonGetInt(lastwill, "qos", &mqtt->lastwill.qos);
    jsonGetInt(lastwill, "retain", &mqtt->lastwill.retain);

    cJSON_Delete(root);
    return ESP_OK;
}


esp_err_t systemConfigLoadMqtt()
{

    size_t volatile len;
    uint8_t json[10240] = {0};
    if (nvsLoad(configPartition, "mqtt", "mqtt", (char *)json, (size_t *)&len) != ESP_OK)
	{
        ESP_LOGE(TAG, "systemConfigLoadMqtt json not exist.");
        return ESP_ERR_NOT_FOUND;
    }

    return readMqttConfig(json, &confing.mqtt);

}
