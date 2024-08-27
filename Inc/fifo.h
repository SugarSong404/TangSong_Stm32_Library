#ifndef FIFO_H
#define FIFO_H
#include <stdint.h>
#include <stdlib.h>

#define FIFO_SIZE 1024
typedef struct {
    uint8_t data[FIFO_SIZE];
    uint16_t front;
    uint16_t rear;
}FIFO;

FIFO* fifo_init(FIFO* fifo);
void fifo_clear(FIFO* fifo);
uint8_t fifo_empty(FIFO* fifo);
uint8_t fifo_full(FIFO* fifo);
uint8_t fifo_write(FIFO* fifo, uint8_t* datas, uint16_t len);
uint8_t fifo_read(FIFO* fifo, uint8_t* datas, uint16_t len);
uint8_t fifo_tail_peek(FIFO* fifo, uint8_t* datas, uint16_t len);

#endif
