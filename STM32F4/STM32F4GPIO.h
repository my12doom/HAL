#include "GPIO.h"
#include "stm32F4xx_gpio.h"
using namespace HAL;
namespace STM32F4
{
	class F4GPIO:GPIO
	{
	public:
		GPIO_TypeDef* GPIOx;
		uint32_t GPIO_Pin;  
		GPIOMode_TypeDef GPIO_Mode;
		F4GPIO(GPIO_TypeDef* GPIOx,uint32_t GPIO_Pin,GPIOMode_TypeDef GPIO_Mode);
	    ~F4GPIO(){};
		virtual void set_mode(GPIO_MODE mode);
		virtual bool read();					// high = true, low = false
		virtual void write(bool newvalue);		// high = true, low = false
		virtual void toggle();
	};
}
