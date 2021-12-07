#include "no_os/spi.h"
#include "spi.h"

int32_t spi_init(struct spi_desc **desc, const struct spi_init_param *param)
{
	if(!param)
		return -EINVAL;
	
	struct spi_desc *descriptor = (struct spi_desc *)calloc(1, sizeof(*descriptor));
	if(!descriptor)
		return -ENOMEM;
	
	descriptor->device_id = param->device_id;
	descriptor->max_speed_hz = param->max_speed_hz;
	descriptor->chip_select = param->chip_select;
	descriptor->mode = param->mode;
	descriptor->bit_order = param->bit_order;
	descriptor->platform_ops = *maxim_spi_ops;
	descriptor->extra = param->extra;
	
	
	
	return 0;
}

int32_t spi_remove(struct spi_desc *desc)
{
	return 0;
}

int32_t spi_write_and_read(struct spi_desc *desc,
			   uint8_t *data,
			   uint16_t bytes_number)
{
	return 0;
}

int32_t spi_transfer(struct spi_desc *desc, struct spi_msg *msgs, uint32_t len)
{
	return 0;
}

struct spi_platform_ops maxim_spi_ops = {
	.init = &spi_init,
	.write_and_read = &spi_write_and_read,
	.spi_transfer = &spi_transfer,
	.spi_remove = &spi_remove
};

