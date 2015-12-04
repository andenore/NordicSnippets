#include <nrf.h>

int main(void)
{
  volatile uint8_t random_value;
  
  // Enable digital error correction
  NRF_RNG->CONFIG = RNG_CONFIG_DERCEN_Enabled << RNG_CONFIG_DERCEN_Pos;
  
  // Enable shortcut to stop the RNG after generating one value.
  NRF_RNG->SHORTS = RNG_SHORTS_VALRDY_STOP_Enabled << RNG_SHORTS_VALRDY_STOP_Pos;
  
  // Clear any existing VALRDY events and start generating new value
  NRF_RNG->EVENTS_VALRDY = 0;
  NRF_RNG->TASKS_START = 1;
  
  // Wait while the new random value is generated
  while (NRF_RNG->EVENTS_VALRDY == 0);
  NRF_RNG->EVENTS_VALRDY = 0;
  
  // Put generated random value into a variable.
  random_value = NRF_RNG->VALUE;
  
  while (1)
  {
    __WFE();
  }
}
