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

SRC_DIRS += $(PROJECT)/src
SRCS += $(DRIVERS)/api/spi.c \
	$(DRIVERS)/api/irq.c \
	$(DRIVERS)/api/gpio.c \
	$(DRIVERS)/afe/ad4110/ad4110.c
				
SRCS += $(PLATFORM_DRIVERS)/xilinx_spi.c \
	$(PLATFORM_DRIVERS)/xilinx_irq.c \
	$(PLATFORM_DRIVERS)/xilinx_gpio.c \
	$(PLATFORM_DRIVERS)/xilinx_gpio_irq.c \
	$(PLATFORM_DRIVERS)/delay.c \
	$(NO-OS)/util/list.c

INCS += $(DRIVERS)/afe/ad4110/ad4110.h

INCS +=	$(PLATFORM_DRIVERS)/spi_extra.h \
	$(PLATFORM_DRIVERS)/irq_extra.h \
	$(PLATFORM_DRIVERS)/gpio_extra.h \
	$(PLATFORM_DRIVERS)/gpio_irq_extra.h

INCS += $(INCLUDE)/no_os/spi.h \
	$(INCLUDE)/no_os/gpio.h \
	$(INCLUDE)/no_os/error.h \
	$(INCLUDE)/no_os/delay.h \
	$(INCLUDE)/no_os/irq.h \
	$(INCLUDE)/no_os/util.h \
	$(INCLUDE)/no_os/print_log.h \
	$(INCLUDE)/no_os/list.h
