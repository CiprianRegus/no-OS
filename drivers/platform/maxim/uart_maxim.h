#include "uart.h"

struct maxim_uart_desc {
	uint32_t port;
	uart_cfg_t *maxim_desc;
};

struct maxim_uart_init_param {
	uint32_t port;
	uart_parity_t parity;
	uart_size_t size;
	uart_stop_t stop;
	uart_flow_ctrl_t flow;
	uart_flow_pol_t pol;
};

