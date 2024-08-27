#ifndef ESP01S_H
#define ESP01S_H
#include "dma_uart.h"
#include "main.h"
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#define ACK_TIMEOUT 2
#define ACK_ERROR 1
#define ACK_OK 0

#define WAIT_TIME 10000

//return is 0 init success
uint8_t esp01s_init(DMA_HandleTypeDef* dma,UART_HandleTypeDef *uart,GPIO_TypeDef *Port,uint16_t RST,uint16_t EN);
//used in void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
void esp01s_callback_Rx(UART_HandleTypeDef *uart,uint16_t Size);
//used in void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
void esp01s_callback_Tx(UART_HandleTypeDef *uart);

uint8_t esp01s_wifi(const char* ssid,const char* password);
uint8_t esp01s_udp(const char* ip,uint16_t port);
uint16_t esp01s_receive(uint8_t *pData,uint16_t len);
uint16_t esp01s_peek(uint8_t *pData,uint16_t len);
void esp01s_send(uint8_t *pData,uint16_t Size);

#endif
