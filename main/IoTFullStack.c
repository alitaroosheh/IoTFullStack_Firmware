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

#define TAG "IoTFullStack"

/// @brief app_main: starting point of the application.
/// @param
void app_main(void)
{

  esp_err_t ret = nvs_flash_init();
  if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    ret = nvs_flash_init();
  }

  ESP_ERROR_CHECK(ret);

  uint32_t loopInterval = 5000;

  esp_err_t err = nvs_flash_init();
  if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND)
  {
    ESP_ERROR_CHECK(nvs_flash_erase());
    err = nvs_flash_init();
  }
  ESP_ERROR_CHECK(err);

  WiFiInit();

  ESP_LOGI(TAG, "Start STA Mode");
  wifi_config_t wifiConfigSTA = {0};
  strcpy((char *)wifiConfigSTA.sta.ssid, "sta-wifi");
  strcpy((char *)wifiConfigSTA.sta.password, "password");
  ret = WiFiStartSTA(wifiConfigSTA, 5 * 1000);
  ESP_LOGI(TAG, "WiFiStartSTA: %d", ret);

  xTaskCreate(&IAQTask, "IAQTask", configMINIMAL_STACK_SIZE * 2, (void *)&loopInterval, 5, NULL);

  while (true)
  {
    vTaskDelay(10000 / portTICK_PERIOD_MS);
  }
}