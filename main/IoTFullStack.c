
/**
 * @file IoTFullStack.c
 * @author Ali Taroosheh (ali.taroosheh@gmail.com)
 * @brief
 * @version 0.1
 * @date 2024-07-02
 *
 *
 */

#include "IoTFullStack.h"

#define TAG						"IoTFullStack"

/// @brief app_main: starting point of the application.
/// @param
void app_main(void)
{

	uint32_t loopInterval = 5000;

	nvsInit(configPartition, false);

	systemConfig(configPartition);

	wifiInit();

	
	ESP_LOGI(TAG, "IoT Full Stack application is running...");
	//vTaskDelay(3000 / portTICK_PERIOD_MS);


	wifi_config_t sta = {0};


	
	ESP_LOGI(TAG, "wifi STA SSID: \"%s\" password: \"%s\"", (char *)sta.sta.ssid, (char *)sta.sta.password);

	ESP_LOGI(TAG, "Start STA Mode");
	esp_err_t ret = wifiStartSTA(sta, 5 * 1000);
	ESP_LOGI(TAG, "WiFiStartSTA: %d", ret);

	xTaskCreate(&iaqTask, "IAQTask", configMINIMAL_STACK_SIZE * 2, (void *)&loopInterval, 5, NULL);

	while (true)
	{
		vTaskDelay(10000 / portTICK_PERIOD_MS);
	}
}