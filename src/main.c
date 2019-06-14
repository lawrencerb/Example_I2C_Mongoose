#include "mgos.h"
#include "mgos_config.h"
#include "mgos_mcp23xxx.h"

mgos_timer_id toggle_timer;
struct mgos_mcp23xxx *d;

// static void button_cb(int pin, void *user_data) {
//   struct mgos_mcp23xxx *d = (struct mgos_mcp23xxx *)user_data;
//   LOG(LL_INFO, ("GPIO[%d] callback, value=%d", pin, mgos_mcp23xxx_gpio_read(d, pin)));
//   mgos_mcp23xxx_gpio_toggle(d, pin+8);
// }

static void toggle_cb(void *arg){
  mgos_mcp23xxx_gpio_toggle(d, 0);
  (void)arg;
}

enum mgos_app_init_result mgos_app_init(void) {
  //int i;

  if (!(d = mgos_mcp23017_create(mgos_i2c_get_global(), mgos_sys_config_get_mcp23xxx_i2caddr(),
                                mgos_sys_config_get_mcp23xxx_int_gpio()))) {
    LOG(LL_ERROR, ("Could not create MCP230XX"));
    return MGOS_APP_INIT_ERROR;
  }

  //for(i=0; i<4; i++) mgos_mcp23xxx_gpio_setup_input(d, i, MGOS_GPIO_PULL_UP);
  //for(i=8; i<16; i++) mgos_mcp23xxx_gpio_set_mode(d, i, MGOS_GPIO_MODE_OUTPUT);
  mgos_mcp23xxx_gpio_set_mode(d, 0, MGOS_GPIO_MODE_OUTPUT);
  mgos_mcp23xxx_gpio_setup_output(d, 0, 1);
  mgos_mcp23xxx_gpio_write(d, 0, 1);

  mgos_set_timer(1000, MGOS_TIMER_REPEAT, toggle_cb, NULL);

  //mgos_mcp23xxx_gpio_set_button_handler(d, 0, MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_NEG, 10, button_cb, d);
  //mgos_mcp23xxx_gpio_set_button_handler(d, 1, MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_POS, 10, button_cb, d);
  //mgos_mcp23xxx_gpio_set_button_handler(d, 2, MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_ANY, 10, button_cb, d);
  //mgos_mcp23xxx_gpio_set_button_handler(d, 3, MGOS_GPIO_PULL_UP, MGOS_GPIO_INT_EDGE_ANY, 10, button_cb, d);

  return MGOS_APP_INIT_SUCCESS;
}