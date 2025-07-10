// Plik: App/Src/app.c
#include "app.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "task.h"
#include "usb_device.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

osThreadId_t appTaskHandle;

#define RX_BUFF_SIZE 64
static uint8_t cdc_rx_buffer[RX_BUFF_SIZE];

const osThreadAttr_t appTask_attributes = {
    .name = "StartAppTask",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

void StartAppTask(void *argument) {
  uint32_t last_len = 0;

  for (;;) {
    uint32_t len = CDC_GetRxLength_FS();
    if (len > 0 && len != last_len) {
      memcpy(cdc_rx_buffer, CDC_GetRxBuffer_FS(), len);
      if (len < RX_BUFF_SIZE)
        cdc_rx_buffer[len] = '\0';

      // echo
      CDC_Transmit_FS(cdc_rx_buffer, len);
      last_len = len;
    }

    osDelay(10);
  }
}

void APP_Init(void) {
  appTaskHandle = osThreadNew(StartAppTask, NULL, &appTask_attributes);
}
