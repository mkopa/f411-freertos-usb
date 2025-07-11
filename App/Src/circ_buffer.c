#include "circ_buffer.h"

void circ_buffer_init(circ_buffer_t *cb) {
  cb->head = 0;
  cb->tail = 0;
}

bool circ_buffer_write(circ_buffer_t *cb, uint8_t data) {
  uint16_t next_head = (cb->head + 1) % CIRC_BUFFER_SIZE;
  if (next_head == cb->tail) {
    return false; // Bufor jest pełny
  }
  cb->buffer[cb->head] = data;
  cb->head = next_head;
  return true;
}

bool circ_buffer_read(circ_buffer_t *cb, uint8_t *data) {
  if (cb->head == cb->tail) {
    return false; // Bufor jest pusty
  }
  *data = cb->buffer[cb->tail];
  cb->tail = (cb->tail + 1) % CIRC_BUFFER_SIZE;
  return true;
}