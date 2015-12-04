#include <nrf.h>

#define PPI_CHANNEL (0)
#define PIN_GPIO    (11)

int main(void)
{
  // Configure PIN_GPIO as output
  NRF_GPIO->DIRSET = (1UL << PIN_GPIO);
  
  // Configure GPIOTE->TASKS_OUT[0] to toggle PIN_GPIO
  NRF_GPIOTE->CONFIG[0] = (GPIOTE_CONFIG_MODE_Task       << GPIOTE_CONFIG_MODE_Pos) |
                          (GPIOTE_CONFIG_OUTINIT_Low     << GPIOTE_CONFIG_OUTINIT_Pos) |
                          (GPIOTE_CONFIG_POLARITY_Toggle << GPIOTE_CONFIG_POLARITY_Pos) |
                          (PIN_GPIO                      << GPIOTE_CONFIG_PSEL_Pos);
  
  // Configure TIMER0 to generate EVENTS_COMPARE[0] every 1000us.
  NRF_TIMER0->BITMODE = TIMER_BITMODE_BITMODE_32Bit << TIMER_BITMODE_BITMODE_Pos;
  NRF_TIMER0->SHORTS = TIMER_SHORTS_COMPARE0_CLEAR_Enabled << TIMER_SHORTS_COMPARE0_CLEAR_Pos;
  NRF_TIMER0->PRESCALER = 4;
  NRF_TIMER0->CC[0] = 1000;
  NRF_TIMER0->TASKS_START = 1;
  
  
  // Configure PPI channel with connection between TIMER->EVENTS_COMPARE[0] and GPIOTE->TASKS_OUT[0]
  NRF_PPI->CH[PPI_CHANNEL].EEP = (uint32_t)&NRF_TIMER0->EVENTS_COMPARE[0];
  NRF_PPI->CH[PPI_CHANNEL].TEP = (uint32_t)&NRF_GPIOTE->TASKS_OUT[0];
  
  // Enable PPI channel
  NRF_PPI->CHENSET = (1UL << PPI_CHANNEL);
  
  
  while (1)
  {
    __WFE();
  }
}
