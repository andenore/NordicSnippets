#include <nrf.h>

#define PIN_GPIO  (11UL)

int main(void)
{
  // Configure GPIO pin as output with standard drive strength.
  NRF_GPIO->PIN_CNF[PIN_GPIO] = (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) |
                                (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) |
                                (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
                                (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
                                (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);
  
  
  // Toggle GPIO ON/OFF.
  while (1)
  {
    uint32_t tmo;
    
    tmo = 300;
    while (tmo--);
    NRF_GPIO->OUTSET = (1UL << PIN_GPIO);    
    
    tmo = 300;
    while (tmo--);
    NRF_GPIO->OUTCLR = (1UL << PIN_GPIO);    
  }
}

