#include <nrf.h>

int main(void)
{
  // Start LFCLK (32kHz) crystal oscillator. If you don't have crystal on your board, choose RCOSC instead.
  NRF_CLOCK->LFCLKSRC = CLOCK_LFCLKSRC_SRC_Xtal << CLOCK_LFCLKSRC_SRC_Pos;
  NRF_CLOCK->TASKS_LFCLKSTART = 1;
  while (NRF_CLOCK->EVENTS_LFCLKSTARTED == 0);
  NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
  
  
  // 32kHz timer period
  NRF_RTC0->PRESCALER = 0;
  
  //  30.5ms us compare value, generates EVENTS_COMPARE[0]
  NRF_RTC0->CC[0] = 1000;
  
  // Enable EVENTS_COMPARE[0] generation
  NRF_RTC0->EVTENSET = RTC_EVTENSET_COMPARE0_Enabled << RTC_EVTENSET_COMPARE0_Pos;
  // Enable IRQ on EVENTS_COMPARE[0]
  NRF_RTC0->INTENSET = RTC_INTENSET_COMPARE0_Enabled << RTC_INTENSET_COMPARE0_Pos;  
  
  // Enable RTC IRQ and start the RTC
  NVIC_EnableIRQ(RTC0_IRQn);
  NRF_RTC0->TASKS_START = 1;

  while (1)
  {
    __WFE();
  }
}

// This IRQ handler will trigger every 30.5 ms
void RTC0_IRQHandler(void)
{
  volatile uint32_t dummy;
  if (NRF_RTC0->EVENTS_COMPARE[0] == 1)
  {
    NRF_RTC0->EVENTS_COMPARE[0] = 0;
    
    // Increment compare value with 30.5 ms from current time.
    NRF_RTC0->CC[0] = NRF_RTC0->COUNTER + 1000; 
    
    // Read back event register so ensure we have cleared it before exiting IRQ handler.
    dummy = NRF_RTC0->EVENTS_COMPARE[0];
  }
}
