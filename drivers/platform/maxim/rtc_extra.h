#ifndef RTC_EXTRA_H_
#define RTC_EXTRA_H_

#include<stdint.h>

struct rtc_init_maxim{
	/** Load value for miliseconds */
	uint32_t ms_load;
};

struct rtc_desc_maxim{
	mxc_regs_rtc_t *rtc_regs;
};

#endif

