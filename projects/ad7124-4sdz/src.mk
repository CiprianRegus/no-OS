################################################################################
#									       #
#     Shared variables:							       #
#	- PROJECT							       #
#	- DRIVERS							       #
#	- INCLUDE							       #
#	- PLATFORM_DRIVERS						       #
#	- NO-OS								       #
#									       #
################################################################################

SRCS += $(PROJECT)/src/ad7124-4sdz.c
SRCS += $(DRIVERS)/api/spi.c \
	$(DRIVERS)/adc/ad7124/ad7124.c \
	$(DRIVERS)/adc/ad7124/ad7124_regs.c				
SRCS +=	$(PLATFORM_DRIVERS)/axi_io.c \
	$(PLATFORM_DRIVERS)/xilinx_spi.c \
	$(PLATFORM_DRIVERS)/delay.c
INCS += $(DRIVERS)/adc/ad7124/ad7124.h \
	$(DRIVERS)/adc/ad7124/ad7124_regs.h

INCS +=	$(PLATFORM_DRIVERS)/spi_extra.h \
	$(PLATFORM_DRIVERS)/irq_extra.h \
	$(PLATFORM_DRIVERS)/uart_extra.h \
	$(PLATFORM_DRIVERS)/gpio_extra.h
INCS +=	$(INCLUDE)/no_os/axi_io.h \
	$(INCLUDE)/no_os/spi.h \
	$(INCLUDE)/no_os/gpio.h \
	$(INCLUDE)/no_os/error.h \
	$(INCLUDE)/no_os/delay.h \
	$(INCLUDE)/no_os/irq.h \
	$(INCLUDE)/no_os/uart.h \
	$(INCLUDE)/no_os/util.h
