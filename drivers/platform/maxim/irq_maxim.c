#include <stdint.h>
#include <stdlib.h>
#include <errno.h>
#include "no_os/irq.h"
#include "irq_maxim_extra.h"
#include "nvic_table.h"

static struct callback_desc *irq_callback_desc;
const struct irq_platform_ops maxim_irq_ops;

static void irq_callback(void)
{
	irq_callback_desc->callback(irq_callback_desc->ctx, 0,
				    irq_callback_desc->config);
}

int32_t irq_ctrl_init(struct irq_ctrl_desc **desc,
		      const struct irq_init_param *param)
{
	if(!desc || !param)
		return -EINVAL;

	*desc = (struct irq_ctrl_desc *)calloc(1, sizeof(**desc));
	struct maxim_irq_ctrl_desc *callback_desc = (struct maxim_irq_ctrl_desc *)calloc(1,
			    sizeof(*callback_desc));

	if(!*desc || !irq_callback_desc)
		return -ENOMEM;

	(*desc)->irq_ctrl_id = param->irq_ctrl_id;
	(*desc)->platform_ops = &maxim_irq_ops;

	return 0;
}

int32_t irq_ctrl_remove(struct irq_ctrl_desc *desc)
{
	for(uint32_t i = 0; i < MXC_IRQ_COUNT; i++) {
		NVIC_DisableIRQ(i);
	}

	free(desc->extra);
	free(desc);
	free(irq_callback_desc);

	return 0;
}

int32_t irq_register_callback(struct irq_ctrl_desc *desc, uint32_t irq_id,
			      struct callback_desc *callback_desc)
{
	if(!desc || irq_id > MXC_IRQ_COUNT - 1)
		return -EINVAL;

	NVIC_SetVector(irq_id, &irq_callback);

	return 0;
}

int32_t irq_unregister(struct irq_ctrl_desc *desc, uint32_t irq_id)
{
	if(!desc || irq_id > MXC_IRQ_COUNT - 1)
		return -EINVAL;


	return 0;
}

int32_t irq_trigger_level_set(struct irq_ctrl_desc *desc, uint32_t irq_id,
			      enum irq_trig_level trig)
{

	return 0;
}

int32_t irq_global_enable(struct irq_ctrl_desc *desc)
{
	if(!desc)
		return -EINVAL;

	for(uint32_t i = 0; i < MXC_IRQ_COUNT; i++) {
		NVIC_EnableIRQ(i);
	}

	return 0;
}

int32_t irq_global_disable(struct irq_ctrl_desc *desc)
{
	if(!desc)
		return -EINVAL;

	for(uint32_t i = 0; i < MXC_IRQ_COUNT; i++) {
		NVIC_DisableIRQ(i);
	}

	return 0;
}

int32_t irq_enable(struct irq_ctrl_desc *desc, uint32_t irq_id)
{
	if(!desc || irq_id > MXC_IRQ_COUNT - 1)
		return -EINVAL;

	NVIC_EnableIRQ(irq_id);

	return 0;
}

int32_t irq_disable(struct irq_ctrl_desc *desc, uint32_t irq_id)
{
	if(!desc || irq_id > MXC_IRQ_COUNT - 1)
		return -EINVAL;

	NVIC_ClearPendingIRQ(irq_id);
	NVIC_DisableIRQ(irq_id);

	return 0;
}


const struct irq_platform_ops maxim_irq_ops = {
	.init = &irq_ctrl_init,
	.register_callback = &irq_register_callback,
	.unregister = &irq_unregister,
	.global_enable = &irq_global_enable,
	.global_disable = &irq_global_disable,
	.enable = &irq_enable,
	.disable = &irq_disable,
	.remove = &irq_ctrl_remove
};

