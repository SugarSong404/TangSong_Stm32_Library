#ifndef ZF_ASSISTANT_H
#define ZF_ASSISTANT_H
#include "esp01s.h"
#include "stdarg.h"

extern UART_HandleTypeDef huart2;
extern DMA_HandleTypeDef hdma_usart2_rx;
#define ESP_DMA hdma_usart2_rx
#define ESP_UART huart2

#define SSID "abcdp"
#define PASSWORD "cptbtptp"
#define REMOTE_IP "192.168.50.246"
#define REMOTE_PORT 8082

#define ESP_Port GPIOB
#define ESP_EN_PIN GPIO_PIN_4
#define ESP_RST_PIN GPIO_PIN_5

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size);
void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart);

#define MAX_CH_NUM 10

uint8_t vofa_init(void);
void vofa_justfloat(uint8_t channels, ...);
void vofa_rawdata(uint8_t* pData,uint16_t len);
void vofa_firewater(const char *format, ...);
void vofa_parameters(void);
extern float params[MAX_CH_NUM];

#endif
