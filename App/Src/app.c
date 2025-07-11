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
osSemaphoreId_t usbRxSemaphoreHandle;
circ_buffer_t usb_rx_buffer;

const osThreadAttr_t appTask_attributes = {
    .name = "StartAppTask",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

void StartAppTask(void *argument) {
  uint8_t rx_byte;
  uint8_t local_buffer[APP_RX_DATA_SIZE];
  uint16_t len = 0;

  for (;;) {
    // Czekaj na sygnał od przerwania USB (bez końca)
    if (osSemaphoreAcquire(usbRxSemaphoreHandle, osWaitForever) == osOK) {

      // Opróżnij cały bufor kołowy
      len = 0;
      while (circ_buffer_read(&usb_rx_buffer, &rx_byte)) {
        if (len < APP_RX_DATA_SIZE) {
          local_buffer[len++] = rx_byte;
        }
      }

      // Jeśli odczytano dane, wykonaj echo
      if (len > 0) {
        CDC_Transmit_FS(local_buffer, len);
      }
    }
  }
}

void APP_Init(void) {
  circ_buffer_init(&usb_rx_buffer);

  usbRxSemaphoreHandle = osSemaphoreNew(1, 0, NULL);

  appTaskHandle = osThreadNew(StartAppTask, NULL, &appTask_attributes);
}
