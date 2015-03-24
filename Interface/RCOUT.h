#pragma once

#include <stdint.h>

namespace HAL
{
	// channel index starts from 0
	class RCOUT
	{
	public:
		// total channel count
		virtual int get_channel_count();

		// return num channel written
		// generate an error if index overrun/underrun, and won't update any channel
		// return negative value to indicate an error
		virtual int write(int16_t *out, int start_channel, int max_count);
	};
}
