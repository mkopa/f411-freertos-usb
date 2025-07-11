#include "app.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "stream_buffer.h"
#include "task.h"
#include "usb_device.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

#define STREAM_BUFFER_SIZE 256
#define STREAM_BUFFER_TRIGGER_LEVEL 1

osThreadId_t appTaskHandle;

StreamBufferHandle_t usbStreamBufferHandle;
static uint8_t ucStreamBufferStorage[STREAM_BUFFER_SIZE];
static StaticStreamBuffer_t xStreamBufferStruct;

const osThreadAttr_t appTask_attributes = {
    .name = "StartAppTask",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

void StartAppTask(void *argument) {
  uint8_t local_buffer[APP_RX_DATA_SIZE];
  size_t received_bytes;

  for (;;) {
    received_bytes =
        xStreamBufferReceive(usbStreamBufferHandle, (void *)local_buffer, sizeof(local_buffer), portMAX_DELAY);

    if (received_bytes > 0) {
      CDC_Transmit_FS(local_buffer, received_bytes);
    }
  }
}

void APP_Init(void) {
  usbStreamBufferHandle = xStreamBufferCreateStatic(sizeof(ucStreamBufferStorage), STREAM_BUFFER_TRIGGER_LEVEL,
                                                    ucStreamBufferStorage, &xStreamBufferStruct);

  configASSERT(usbStreamBufferHandle != NULL);

  appTaskHandle = osThreadNew(StartAppTask, NULL, &appTask_attributes);
}