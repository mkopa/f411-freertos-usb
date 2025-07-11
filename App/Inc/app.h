#ifndef __APP_H
#define __APP_H

#ifdef __cplusplus
extern "C" {
#endif

#include "FreeRTOS.h"
#include "cmsis_os.h"
#include "main.h"
#include "stream_buffer.h"
#include "task.h"

extern StreamBufferHandle_t usbStreamBufferHandle;

void APP_Init(void);

#ifdef __cplusplus
}
#endif
#endif