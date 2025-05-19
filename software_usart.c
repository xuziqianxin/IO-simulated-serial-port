/**
	* @Another				: xu_zi_qian_xin
  * @file           : software_usart.c
  * @brief          : usart base
  */

#include "software_usart.h"

/**
	* @brief	The delay function controls the baud rate
	*					You can redefine this function yourself
	*	@param[in] us Units of time
	*
	*/
__weak void Delay_US(uint32_t us)
{
  uint32_t starTval,tickn,delay,wait;
 
  starTval = SysTick->VAL;
  tickn = HAL_GetTick();
  delay =us * (SystemCoreClock/1000000);
  if(delay > starTval)
  {
		while(HAL_GetTick() == tickn)
		{
			;
		}
    wait = (SystemCoreClock/1000) + starTval - delay;
		while(wait < SysTick->VAL)
		{
			;
		}
  }
  else
  {
		wait = starTval - delay;
		while(wait < SysTick->VAL && HAL_GetTick() == tickn)
		{
			;
		}
  }
}

/**
	* @brief Send data
	* @param[in] baudRate The value of this parameter should be a macro
	* @param[in] data Content sent(1 bit)
	*
	*/
void Software_TX(uint32_t baudRate, uint8_t data)
{
	TX_H;
	Delay_US(baudRate);
	TX_L;
	Delay_US(baudRate);
	for(uint8_t i = 0; i < 8; i++)
	{
		if(data & 0x01)
		{
			TX_H;
		}
		else
		{
			TX_L;
		}
		data = data >> 1;
		Delay_US(baudRate);
	}

	Delay_US(baudRate);
	TX_H;
	Delay_US(baudRate);
}

/**
	* @brief Receives data
	* @param[in] baudRate The value of this parameter should be a macro
	* @param[in] p The address at which the content variable was received
	* @param[in] timeout The timeout period in 1us
	*/
void Software_RX(uint32_t baudRate, uint8_t *p, uint16_t timeout)
{
	uint8_t data = 0;
	for(uint16_t i = 0; i < timeout; i++)
	{
		if(!GET_RX)
		{
			Delay_US(1);
			Delay_US(baudRate + (baudRate/2));
			for(uint8_t i = 0; i < 8; i++)
			{
				data += (GET_RX << i);
				Delay_US(baudRate);
			}
			*p = data;
			break;
		}
	}
}
