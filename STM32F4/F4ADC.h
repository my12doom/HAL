#pragma once
#include <HAL/Interface/IADC.h>
#include "stm32F4xx_gpio.h"
#include "stm32F4xx_adc.h"

namespace STM32F4
{
	class F4ADC:public HAL::IADC
	{
	private:
		ADC_TypeDef* ADCx;
		uint8_t ADC_Channel;
	public:
		F4ADC(ADC_TypeDef* ADCx,uint8_t ADC_Channe);
		int ADC1_SelectChannel();
		~F4ADC(){};
		virtual int read();
	};
}
