#include "no_os/gpio.h"
#include "gpio.h"
#include "gpio_regs.h"

int32_t gpio_get(struct gpio_desc **desc,
		 const struct gpio_init_param *param)
{
	if(!param || param->number >= N_PINS)
		return -EINVAL;

	struct gpio_desc *descriptor = (struct gpio_desc *)calloc(1, sizeof(*descriptor));
	if(!(*desc))
		return -ENOMEM;

	descriptor->number = param->number;
	descriptor->platform_ops = &gpio_platform_ops;
	descriptor->extra = (gpio_cfg_t *)param->extra;
	
	*desc = descriptor;	

	return 0;
}

int32_t gpio_get_optional(struct gpio_desc **desc,
			  const struct gpio_init_param *param)
{
	if(param == NULL){
		*desc = NULL;
		return 0;
	}
	
	return gpio_get(desc, param);
}

int32_t gpio_remove(struct gpio_desc *desc)
{
	free(desc->extra);
	free(desc);

	return 0;
}

int32_t gpio_direction_input(struct gpio_desc *desc)
{	
	gpio_cfg_t *maxim_extra = (gpio_cfg_t *)desc->extra;
	
	if(!desc || !maxim_extra || maxim_extra->port >= N_PORTS)
		return -EINVAL;

	maxim_extra->mask = (uint32_t)(1UL << desc->number);
	maxim_extra->func = GPIO_FUNC_IN;
	GPIO_Config(maxim_extra);
	
	return 0;
}

int32_t gpio_direction_output(struct gpio_desc *desc, uint8_t value)
{	
	gpio_cfg_t *maxim_extra = (gpio_cfg_t *)desc->extra;
	
	if(!desc || !maxim_extra || maxim_extra->port >= N_PORTS)
		return -EINVAL;

	maxim_extra->mask = (uint32_t)(1UL << desc->number);
	maxim_extra->func = GPIO_FUNC_OUT;
	GPIO_Config(maxim_extra);
	
	if(value == 0)
		GPIO_OutClr(maxim_extra);
	else
		GPIO_OutSet(maxim_extra);

	return 0;
}

int32_t gpio_get_direction(struct gpio_desc *desc, uint8_t *direction)
{
	gpio_cfg_t *maxim_extra = (gpio_cfg_t *)desc->extra;
	if(!desc || !maxim_extra)
		return -EINVAL;
	
	if(maxim_extra->func == GPIO_FUNC_OUT)
		*direction = GPIO_OUT;
	else if(maxim_extra->func == GPIO_FUNC_IN)
		*direction = GPIO_IN;
	else
		return -EINVAL;
	
	return 0;
}

int32_t gpio_set_value(struct gpio_desc *desc, uint32_t value)
{
	gpio_cfg_t *maxim_extra = (gpio_cfg_t *)desc->extra;
	
	if(!desc)
		return -EINVAL;

	switch(value){
	case GPIO_LOW:
		GPIO_OutSet(maxim_extra);
		break;
	case GPIO_HIGH:
		GPIO_OutClr(maxim_extra);
		break;
	case GPIO_HIGH_Z:
		mxc_gpio_regs_t *gpio_regs = MXC_GPIO_GET_GPIO(maxim_extra->port);
		gpio_regs->en &= ~desc->mask;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

int32_t gpio_get_value(struct gpio_desc *desc, uint32_t *value)
{
	gpio_cfg_t *maxim_extra = (gpio_cfg_t *)desc->extra;
	if(!desc || maxim_extra)
		return -EINVAL;
	
	if(maxim_extra->func == GPIO_FUNC_IN)
		*value = GPIO_InGet(maxim_extra);
	else if(maxim_extra->func == GPIO_FUNC_OUT)
		*value = GPIO_OutGet(maxim_extra);
	else
		return -EINVAL;
	
	return 0;
}

gpio_platform_ops = {
	.gpio_ops_get = &gpio_get,
	.gpio_ops_get_optional = &gpio_get_optional,
	.gpio_ops_remove = &gpio_remove,
	.gpio_ops_direction_input = &gpio_direction_input,
	.gpio_ops_direction_output = &gpio_direction_output,
	.gpio_ops_get_direction = &gpio_get_direction,
	.gpio_ops_set_value = &gpio_set_value,
	.gpio_ops_get_value = &gpio_get_value
};

