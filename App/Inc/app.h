#ifndef __APP_H
#define __APP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "circ_buffer.h"
#include "cmsis_os.h"
#include "main.h"
#include "task.h"

extern osSemaphoreId_t usbRxSemaphoreHandle;
extern circ_buffer_t usb_rx_buffer;

void APP_Init(void);

#ifdef __cplusplus
}
#endif
#endif