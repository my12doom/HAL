#pragma once

#include <stdint.h>
#include <HAL/Interface/Interfaces.h>
#include <HAL/Interface/IMagnetometer.h>

namespace sensors
{
	class HMC5983 : public devices::IMagnetometer
	{
	public:
		HMC5983();
		~HMC5983(){}

		int init(HAL::ISPI *SPI, HAL::IGPIO *CS);
		int init(HAL::II2C *i2c);
		int axis_config(int x, int y, int z, int negtivex, int netgtivey, int negtivez);

		int read(short *data);
		int read_reg(uint8_t reg, void *out, int count);
		int write_reg_core(uint8_t reg, uint8_t data);
		int write_reg(uint8_t reg, uint8_t data);

		// IMagnetometer
		virtual int read(devices::mag_data *out);
		virtual bool healthy();

	protected:
		HAL::II2C *i2c;
		HAL::ISPI *spi;
		HAL::IGPIO *CS;

		int axis[3];
		int negtive[3];
		bool m_healthy;
	};
}
