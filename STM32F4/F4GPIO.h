#pragma once
#include <HAL/Interface/IGPIO.h>
#include "stm32F4xx_gpio.h"

namespace STM32F4
{
	class F4GPIO: public HAL::IGPIO
	{
	public:
		F4GPIO(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin);
	    ~F4GPIO(){};
		virtual void set_mode(HAL::GPIO_MODE mode);
		virtual bool read();					// high = true, low = false
		virtual void write(bool newvalue);		// high = true, low = false
		virtual void toggle();
	private:
		GPIO_TypeDef* GPIOx;
		uint32_t GPIO_Pin;  
		GPIOMode_TypeDef GPIO_Mode;
	};
}
