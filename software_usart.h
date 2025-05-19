#ifndef __SOFTWARE_USART_H__
#define __SOFTWARE_USART_H__

#ifdef __cplusplus
extern 'C'{
#endif

#include "main.h"
	
#define BAUD_RATE_9600	104

#define TX_H	HAL_GPIO_WritePin(TX_GPIO_Port, TX_Pin, GPIO_PIN_SET)
#define TX_L	HAL_GPIO_WritePin(TX_GPIO_Port, TX_Pin, GPIO_PIN_RESET)
#define GET_RX	HAL_GPIO_ReadPin(RX_GPIO_Port, RX_Pin)


__weak void Delay_US(uint32_t us);
void Software_TX(uint32_t baudRate, uint8_t data);
void Software_RX(uint32_t baudRate, uint8_t *p, uint16_t timeout);

#ifdef __cplusplus
}
#endif
#endif /* __SOFTWARE_USART_H__ */
