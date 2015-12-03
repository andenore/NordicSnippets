#include <nrf.h>

#define PWM_PIN (11UL)


int16_t buf[] = {(1 << 15) | 1500}; // Inverse polarity (bit 15), 1500us duty cycle

int main(void)
{
  // Start accurate HFCLK (XOSC)
  NRF_CLOCK->TASKS_HFCLKSTART = 1;
  while (NRF_CLOCK->EVENTS_HFCLKSTARTED == 0) ;
  NRF_CLOCK->EVENTS_HFCLKSTARTED = 0;
  
  // Configure PWM_PIN as output, and set it to 0
  NRF_GPIO->DIRSET = (1 << PWM_PIN);
  NRF_GPIO->OUTCLR = (1 << PWM_PIN);
  
  
  NRF_PWM0->PRESCALER   = PWM_PRESCALER_PRESCALER_DIV_16; // 1 us
  NRF_PWM0->PSEL.OUT[0] = PWM_PIN;
  NRF_PWM0->MODE        = (PWM_MODE_UPDOWN_Up << PWM_MODE_UPDOWN_Pos);
  NRF_PWM0->DECODER     = (PWM_DECODER_LOAD_Common       << PWM_DECODER_LOAD_Pos) | 
                          (PWM_DECODER_MODE_RefreshCount << PWM_DECODER_MODE_Pos);
  NRF_PWM0->LOOP        = (PWM_LOOP_CNT_Disabled << PWM_LOOP_CNT_Pos);
  
  NRF_PWM0->COUNTERTOP = 20000; // 20ms period
  
  
  NRF_PWM0->SEQ[0].CNT = ((sizeof(buf) / sizeof(uint16_t)) << PWM_SEQ_CNT_CNT_Pos);
  NRF_PWM0->SEQ[0].ENDDELAY = 0;
  NRF_PWM0->SEQ[0].PTR = (uint32_t)&buf[0];
  NRF_PWM0->SEQ[0].REFRESH = 0;
  NRF_PWM0->SHORTS = 0;
  
  NRF_PWM0->ENABLE = 1;
  NRF_PWM0->TASKS_SEQSTART[0] = 1;
  
  while (1) 
  {
    __WFE();
  }
}
