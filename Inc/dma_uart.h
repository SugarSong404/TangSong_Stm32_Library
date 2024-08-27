#ifndef DMA_UART_H
#define DMA_UART_H
#include <stdint.h>
#include "fifo.h"
#include "main.h"

#define RX_BUF_SIZE 32
#define TX_BUF_SIZE 32

typedef struct {
		DMA_HandleTypeDef* dma; //dma handle
		UART_HandleTypeDef *uart; //uart handle
		uint8_t tx_Buffer[TX_BUF_SIZE];	//read data from tx_fifo and transimit by dma
		uint8_t rx_Buffer[RX_BUF_SIZE];	//receive data from dma and write to rx_fifo
		uint8_t txCplt; //if transmit data should be wait
		FIFO* rx_fifo;	//receive fifo
		FIFO* tx_fifo;	//transmit fifo
}DMA_UART;

//Steps:
//1.you should register callback in correct HAL library CallBack Functions
//2.init the dma_uart , now the data start to be received and  write to fifo
//3 to read datas from fifo ,you should call dma_uart_fifo_read. or call clear to clear fifo
//4.you can use transmit func to send datas

//used in void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
void dma_uart_callback_Rx(DMA_UART *dma_uart,UART_HandleTypeDef *uart,uint16_t Size);
//used in HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
void dma_uart_callback_Tx(DMA_UART *dma_uart,UART_HandleTypeDef *uart);

void dma_uart_init(DMA_UART *dma_uart,DMA_HandleTypeDef* dma,UART_HandleTypeDef *uart,FIFO* txf,FIFO* rxf);
void dma_uart_transmit(DMA_UART *dma_uart,uint8_t *pData,uint16_t Size);

void dma_uart_fifo_clear(DMA_UART *dma_uart);
uint16_t dma_uart_fifo_read(DMA_UART *dma_uart,uint8_t* array,uint16_t len);
uint16_t dma_uart_fifo_tail_peek(DMA_UART *dma_uart,uint8_t* array,uint16_t len);


#endif
