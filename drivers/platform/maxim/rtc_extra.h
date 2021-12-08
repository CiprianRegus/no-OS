#ifndef RTC_EXTRA_H_
#define RTC_EXTRA_H_

#include <stdint.h>
#include "rtc_regs.h"

struct rtc_init_maxim {
	/** Load value for miliseconds */
	uint32_t ms_load;
};

struct rtc_desc_maxim {
	mxc_rtc_regs_t *rtc_regs;
};

#endif

