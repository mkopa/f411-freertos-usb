#ifndef __CIRC_BUFFER_H
#define __CIRC_BUFFER_H

#include <stdbool.h>
#include <stdint.h>

#define CIRC_BUFFER_SIZE 256 // Możesz dostosować rozmiar

typedef struct {
  uint8_t buffer[CIRC_BUFFER_SIZE];
  volatile uint16_t head;
  volatile uint16_t tail;
} circ_buffer_t;

void circ_buffer_init(circ_buffer_t *cb);
bool circ_buffer_write(circ_buffer_t *cb, uint8_t data);
bool circ_buffer_read(circ_buffer_t *cb, uint8_t *data);

#endif