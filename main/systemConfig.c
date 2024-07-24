

#include "IoTFullStack.h"

#include "systemConfig.h"

#define TAG						"systemConfig"

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



static systemConfig sysConfing;


esp_err_t systemConfigLoadWiFi()
{
    size_t len;
    uint8_t json[1024] = {0};
    if (nvsLoad(configPartition, "wifi", "wifi", (char *)json, &len) != ESP_OK)
	{
        ESP_LOGE(TAG, "systemConfigLoadWiFi json not exist.");
        return ESP_ERR_NOT_FOUND;
    }

    cJSON *root = cJSON_Parse((char *)json);
    jsonGetString(root, "ssid", sysConfing.wifi.ssid);
    jsonGetString(root, "password", sysConfing.wifi.password);

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

    cJSON *root = cJSON_Parse((char *)json);
    jsonGetString(root, "clientId", sysConfing.mqtt.clientId);
    jsonGetString(root, "url", sysConfing.mqtt.url);
    jsonGetInt(root, "version", &sysConfing.mqtt.version);
    jsonGetString(root, "userName", sysConfing.mqtt.userName);
    jsonGetString(root, "password", sysConfing.mqtt.password);

    cJSON *lastwill = cJSON_GetObjectItem(root, "lastwill");
    jsonGetString(lastwill, "topic", sysConfing.mqtt.lastwill.topic);
    jsonGetString(lastwill, "message", sysConfing.mqtt.lastwill.message);
    jsonGetInt(lastwill, "qos", &sysConfing.mqtt.lastwill.qos);
    jsonGetInt(lastwill, "retain", &sysConfing.mqtt.lastwill.retain);

    cJSON_Delete(root);
    return ESP_OK;
}
