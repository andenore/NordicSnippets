#include <nrf.h>

int main(void)
{
  volatile uint32_t temperature;
  
  // Start HFCLK crystal oscillator, since that will give highest accuracy
  NRF_CLOCK->TASKS_HFCLKSTART = 1;
  while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0);
  NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
  
  // Trigger temperature measurement
  NRF_TEMP->TASKS_START = 1;
  
  // Wait until measurement is finished
  while (NRF_TEMP->EVENTS_DATARDY == 0);
  NRF_TEMP->EVENTS_DATARDY = 0;
  
  // Read temperature and convert to celcius (rounding down)
  temperature = (int32_t)NRF_TEMP->TEMP / 4;
    
  while (1)
  {
    __WFE();
  }
}
