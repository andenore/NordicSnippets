#include <nrf.h>

#define BUTTON_GPIO  (13UL)
#define LED_GPIO  (17UL)

int main(void)
{
  // Configure the GPIO pin for LED 1 on the nRF52832 dev kit
  // as output with standard drive strength.
  NRF_GPIO->PIN_CNF[LED_GPIO] = (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) |
                                   (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) |
                                   (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
                                   (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
                                   (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);

  // Configure the GPIO pin for Button 1 on the nRF52832 dev kit
  // as input with pull-up resistor enabled.
  NRF_GPIO->PIN_CNF[BUTTON_GPIO] = (GPIO_PIN_CNF_DIR_Input << GPIO_PIN_CNF_DIR_Pos) |
                                   (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) |
                                   (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
                                   (GPIO_PIN_CNF_PULL_Pullup << GPIO_PIN_CNF_PULL_Pos) |
                                   (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);

  // Read the input value, and use it to set the output of the LED.
  // If the button is pressed, the LED turns on, otherwise it is off.
  while (1)
  {
    uint32_t volatile input;

	// Get the value set in the 13th bit and shift it to get 1 or 0
    input = (NRF_GPIO->IN >> BUTTON_GPIO) & 1UL;
	if(input)
		NRF_GPIO->OUTSET = (1UL << LED_GPIO);
    else
		NRF_GPIO->OUTCLR = (1UL << LED_GPIO);
  }
}
