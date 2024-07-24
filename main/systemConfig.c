/**
 * @file systemConfig.c
 * @author Ali Taroosheh (ali.taroosheh@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2024-07-24
 * 
 * 
 */


#include "systemConfig.h"


#define TAG						"systemConfig"


static systemConfiguration config;
static char partition[32];


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
    if (nvsLoad(partition, "wifi", "wifi", (char *)json, &len) != ESP_OK)
	{
        ESP_LOGE(TAG, "systemConfigLoadWiFi json not exist.");
        return ESP_ERR_NOT_FOUND;
    }

    return readWiFiConfig(json, &config.wifi);

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
    if (nvsLoad(partition, "mqtt", "mqtt", (char *)json, (size_t *)&len) != ESP_OK)
	{
        ESP_LOGE(TAG, "systemConfigLoadMqtt json not exist.");
        return ESP_ERR_NOT_FOUND;
    }

    return readMqttConfig(json, &config.mqtt);

}


esp_err_t readSystemConfig()
{
    
    size_t volatile len;
    uint8_t json[100] = {0};
    if (nvsLoad(partition, "system", "system", (char *)json, (size_t *)&len) != ESP_OK)
	{
        ESP_LOGE(TAG, "readSystemConfig json not exist.");
        return ESP_ERR_NOT_FOUND;
    }

    cJSON *root = cJSON_Parse((char *)json);
    jsonGetString(root, "version", config.version);
    cJSON_Delete(root);
    return ESP_OK;

}

esp_err_t systemConfig(char *configPartition)
{
    esp_err_t err;
    strcpy((char *)partition, (char *) configPartition);

    if((err = readSystemConfig()) != ESP_OK) return err;
    if((err = systemConfigLoadWiFi()) != ESP_OK) return err;
    if((err = systemConfigLoadMqtt()) != ESP_OK) return err;
    return ESP_OK;
}
