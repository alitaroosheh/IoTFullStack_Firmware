

#include "IoTFullStack.h"

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

typedef struct systemConfig
{
    uint8_t version[6];
    uint8_t ssid[32];
    uint8_t password[128];
    mqttConfig mqtt;
}systemConfig;

static systemConfig sysConfing;

#define json			"json"
#define nsMqtt			"mqtt"

inline esp_err_t getConfigJson()
{
    size_t len;
    if (nvsLoad(configPartition, json, json, (char *)sysConfing.version, &len) != ESP_OK)
	{
        return ESP_ERR_NOT_FOUND;
    }
}

esp_err_t loadConfig()
{
    size_t len;
    if (nvsLoad(configPartition, nsWiFi, "version", (char *)sysConfing.version, &len) != ESP_OK)
	{
        return ESP_ERR_NOT_FOUND;
    }

    if (nvsLoad(configPartition, nsWiFi, "ssid", (char *)sysConfing.ssid, &len) != ESP_OK)
    {
        return ESP_ERR_NOT_FOUND;
    }

    if (nvsLoad(configPartition, nsWiFi, "password", (char *)sysConfing.password, &len) != ESP_OK)
    {
        return ESP_ERR_NOT_FOUND;
    }


    if (nvsLoad(configPartition, nsMqtt, "clientID", (char *)sysConfing.mqtt.clientId, &len) != ESP_OK)
    {
        return ESP_ERR_NOT_FOUND;
    }

    if (nvsLoad(configPartition, nsMqtt, "url", (char *)sysConfing.mqtt.url, &len) != ESP_OK)
    {
        return ESP_ERR_NOT_FOUND;
    }

    if (nvsLoad(configPartition, nsMqtt, "user", (char *)sysConfing.mqtt.userName, &len) != ESP_OK)
    {
        return ESP_ERR_NOT_FOUND;
    }

    if (nvsLoad(configPartition, nsMqtt, "password", (char *)sysConfing.mqtt.password, &len) != ESP_OK)
    {
        return ESP_ERR_NOT_FOUND;
    }

    char sVersion[5] = {0};
    if (nvsLoad(configPartition, nsMqtt, "version", sVersion, &len) != ESP_OK)
    {
        return ESP_ERR_NOT_FOUND;
    }
    else
    {
        sysConfing.mqtt.version = atoi(sVersion);
    }

    
    if (nvsLoad(configPartition, nsMqtt, "lastwill", (char *)sysConfing.mqtt.lastwill.topic, &len) != ESP_OK)
    {
        return ESP_ERR_NOT_FOUND;
    }

    return ESP_OK;
}