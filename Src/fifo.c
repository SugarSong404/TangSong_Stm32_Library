/**
 * @file fifo.c
 * @brief This file provides a circular fifo struct and its functions. 
 * @author TangSong404
 */
#include "fifo.h"

FIFO* fifo_init(FIFO* fifo) {
    fifo->front = 0;
    fifo->rear = 0;
    return fifo;
}

void fifo_clear(FIFO* fifo){
	fifo->front = 0;
	fifo->rear = 0;
}

uint8_t fifo_empty(FIFO* fifo) {
  return fifo->front == fifo->rear;
}

uint8_t fifo_full(FIFO* fifo) {
  return ((fifo->rear + 1) & (FIFO_SIZE-1)) == fifo->front;
}

uint8_t fifo_write(FIFO* fifo, uint8_t* datas, uint16_t len) {
  uint16_t i;
  uint16_t bytes_written = 0;
  for (i = 0; i < len; i++) {
    if (fifo_full(fifo)) {
      break;
    }
    fifo->data[fifo->rear] = datas[i];
    fifo->rear = (fifo->rear + 1) & (FIFO_SIZE-1);
    bytes_written++;
  }
  return bytes_written;
}

uint8_t fifo_read(FIFO* fifo, uint8_t* datas, uint16_t len){
  uint16_t i;
  uint16_t bytes_read = 0;

  for (i = 0; i < len; i++) {
    if (fifo_empty(fifo)) {
      break;
    }
    datas[i] = fifo->data[fifo->front];
    fifo->front = (fifo->front + 1) & (FIFO_SIZE-1);
    bytes_read++;
  }
  return bytes_read;
}


uint8_t fifo_tail_peek(FIFO* fifo, uint8_t* datas, uint16_t len) {
  uint16_t i;
  uint16_t bytes_read = 0;
  uint16_t current = fifo->rear;
  for (i = 0; i < len; i++) {
    if (fifo_empty(fifo)||bytes_read==len) {
      break;
    }
    current = (current == 0) ? (FIFO_SIZE - 1) : (current - 1);
    datas[len-1-i] = fifo->data[current];
    bytes_read++;
  }
  return bytes_read;
}
