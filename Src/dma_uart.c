/**
 * @file dma_uart.c
 * @brief This file provides some dma uart functions to use
 * @author TangSong404
 */
#include "dma_uart.h"

void dma_uart_receive_start(DMA_UART *dma_uart){
	HAL_UARTEx_ReceiveToIdle_DMA(dma_uart->uart,dma_uart->rx_Buffer,sizeof(dma_uart->rx_Buffer));
	__HAL_DMA_DISABLE_IT(dma_uart->dma,DMA_IT_HT);
}

void dma_uart_init(DMA_UART *dma_uart,DMA_HandleTypeDef* dma,UART_HandleTypeDef *uart,FIFO* txf,FIFO* rxf){
	dma_uart->uart = uart;
	dma_uart->dma = dma;
	dma_uart->txCplt = 1;
	fifo_init(rxf);
	fifo_init(txf);
	dma_uart->rx_fifo = rxf;
	dma_uart->tx_fifo = txf;
	dma_uart_receive_start(dma_uart);
}

void dma_uart_transmit(DMA_UART *dma_uart,uint8_t *pData,uint16_t Size){
	if(!Size)return;
	fifo_write(dma_uart->tx_fifo,pData,Size);
	if(dma_uart->txCplt){
		dma_uart->txCplt = 0;
		dma_uart_callback_Tx(dma_uart,dma_uart->uart);
	}
}

uint16_t dma_uart_fifo_tail_peek(DMA_UART *dma_uart,uint8_t* array,uint16_t len){
	return fifo_tail_peek(dma_uart->rx_fifo,array,len);
}

uint16_t dma_uart_fifo_read(DMA_UART *dma_uart,uint8_t* array,uint16_t len){
	return fifo_read(dma_uart->rx_fifo,array,len);
}

void dma_uart_fifo_clear(DMA_UART *dma_uart){
	fifo_clear(dma_uart->rx_fifo);
}

void dma_uart_callback_Rx(DMA_UART *dma_uart,UART_HandleTypeDef *uart,uint16_t Size){
	if(dma_uart->uart->Instance == uart->Instance){
		fifo_write(dma_uart->rx_fifo,dma_uart->rx_Buffer,Size);
		dma_uart_receive_start(dma_uart);
	}
}

void dma_uart_callback_Tx(DMA_UART *dma_uart,UART_HandleTypeDef *uart){
	if(dma_uart->uart->Instance == uart->Instance){
		uint8_t r = fifo_read(dma_uart->tx_fifo,dma_uart->tx_Buffer,TX_BUF_SIZE);
		if(r)HAL_UART_Transmit_DMA(dma_uart->uart,dma_uart->tx_Buffer,r);
		else dma_uart->txCplt = 1;
	}
}
