#include "no_os_rtc.h"
#include "rtc.h"
#include "errno.h"

/**
 * @brief Initialize the RTC peripheral.
 * @param device - The RTC descriptor.
 * @param init_param - The structure that contains the RTC initialization.
 * @return 0 in case of success, errno codes otherwise.
 */
int32_t rtc_init(struct rtc_desc **device, struct rtc_init_param *init_param)
{
	int32_t ret = 0;
	struct rtc_desc *dev;	
	sys_cfg_rtc_t sys_cfg;
	struct rtc_desc_maxim *rtc_maxim = (struct rtc_desc_maxim *)init_param->extra;	

	if(!init_param)
		return -EINVAL;
	
	dev = (struct rtc_desc *)calloc(1, sizeof(dev));
	if(!dev)
		return -ENOMEM;
	
	dev->id = init_param->id;
	dev->freq = init_param->freq;
	dev->load = init_param->load;
	dev->extra = rtc_maxim;

	sys_cfg.tmr = MXC_TMR0;
	if(RTC_Init(MXC_RTC, dev->load, rtc_maxim->ms_load, &sys_cfg) != E_NO_ERROR){
		ret = -1;
		goto error;
	}
	
	*device = dev;	

	return 0;

error:
	free(dev);
	
	return ret;
}

/**
 * @brief Free the resources allocated by rtc_init().
 * @param dev - The RTC descriptor.
 * @return 0 in case of success, errno codes otherwise.
 */
int32_t rtc_remove(struct rtc_desc *dev)
{	
	free(dev);
	return 0;
}

/**
 * @brief Start the real time clock.
 * @param dev - The RTC descriptor.
 * @return 0 in case of success, errno codes otherwise.
 */
int32_t rtc_start(struct rtc_desc *dev)
{	
	uint32_t temp_cnt;
	struct rtc_desc_maxim *rtc_maxim = (struct rtc_desc_maxim *)dev->extra;
	
	if(!dev)
		return -EINVAL;
	
	if(RTC_CheckBusy())
		return -EBUSY;
	rtc_maxim->rtc_regs->ctrl |= MXC_F_RTC_CTRL_RTCE;
	
	return 0;
}

/**
 * @brief Stop the real time clock.
 * @param dev - The RTC descriptor.
 * @return 0 in case of success, errno codes otherwise.
 */
int32_t rtc_stop(struct rtc_desc *dev)
{	
	uint32_t temp_cnt;
	struct rtc_desc_maxim *rtc_maxim = (struct rtc_desc_maxim *)dev->extra;
	
	if(!dev)
		return -EINVAL;
	
	if(RTC_CheckBusy())
		return -EBUSY;
	rtc_maxim->rtc_regs->ctrl &= ~MXC_F_RTC_CTRL_RTCE;
	
	return 0;
}

/**
 * @brief Get the current count for the real time clock.
 * @param dev - The RTC descriptor.
 * @param tmr_cnt - Pointer where the read counter will be stored.
 * @return 0 in case of success, errno codes otherwise.
 */
int32_t rtc_get_cnt(struct rtc_desc *dev, uint32_t *tmr_cnt)
{
	uint32_t temp_cnt;
	struct rtc_desc_maxim *rtc_maxim = (struct rtc_desc_maxim *)dev->extra;
	
	if(!dev)
		return -EINVAL;	

	do{
		if(!(rtc_maxim->rtc_regs->ctrl & MXC_F_RTC_CTRL_RDY))
			return -EBUSY;
		temp_cnt = RTC_GetSecond();
		if(!(rtc_maxim->rtc_regs->ctrl & MXC_F_RTC_CTRL_RDY))
			return -EBUSY;
		*tmr_cnt = RTC_GetSecond();		

	}while(temp_cnt != *tmr_cnt);

	return 0;
}

/**
 * @brief Set the current count for the real time clock.
 * @param dev - The RTC descriptor.
 * @param tmr_cnt - New value of the timer counter.
 * @return 0 in case of success, errno codes otherwise.
 */
int32_t rtc_set_cnt(struct rtc_desc *dev, uint32_t tmr_cnt)
{
	struct rtc_desc_maxim *rtc_maxim = (struct rtc_desc_maxim *)dev->extra;
	
	if(!dev)
		return -EINVAL;

	rtc_maxim->rtc_regs->ctrl |= MXC_F_RTC_CTRL_WE;
	rtc_maxim->sec = tmr_cnt;
	if(RTC_CheckBusy())
		return -EBUSY;
	rtc_maxim->rtc_regs->ctrl &= ~MXC_F_RTC_CTRL_WE;

	return 0;
}

