#include <nrf.h>

#define PIN_MCK    (13)
#define PIN_SCK    (14)
#define PIN_LRCK   (15)
#define PIN_SDOUT  (16)

int main(void)
{
  // Sine table (stereo, so every value is duplicated)
  int16_t sine_table[] = { 0, 0, 23170, 23170, 32767, 32767, 23170, 23170, 0, 0, -23170, -23170, -32768, -32768, -23170, -23170};
  
  // Enable transmission
  NRF_I2S->CONFIG.TXEN = (I2S_CONFIG_TXEN_TXEN_ENABLE << I2S_CONFIG_TXEN_TXEN_Pos);
  
  // Enable MCK generator
  NRF_I2S->CONFIG.MCKEN = (I2S_CONFIG_MCKEN_MCKEN_ENABLE << I2S_CONFIG_MCKEN_MCKEN_Pos);
  
  // MCKFREQ = 4 MHz
  NRF_I2S->CONFIG.MCKFREQ = I2S_CONFIG_MCKFREQ_MCKFREQ_32MDIV11  << I2S_CONFIG_MCKFREQ_MCKFREQ_Pos;
  
  // Ratio = 64 
  NRF_I2S->CONFIG.RATIO = I2S_CONFIG_RATIO_RATIO_64X << I2S_CONFIG_RATIO_RATIO_Pos;
    
  // Master mode, 16Bit, left aligned
  NRF_I2S->CONFIG.MODE = I2S_CONFIG_MODE_MODE_MASTER << I2S_CONFIG_MODE_MODE_Pos;
  NRF_I2S->CONFIG.SWIDTH = I2S_CONFIG_SWIDTH_SWIDTH_16BIT << I2S_CONFIG_SWIDTH_SWIDTH_Pos;
  NRF_I2S->CONFIG.ALIGN = I2S_CONFIG_ALIGN_ALIGN_LEFT << I2S_CONFIG_ALIGN_ALIGN_Pos;
  
  // Format = I2S
  NRF_I2S->CONFIG.FORMAT = I2S_CONFIG_FORMAT_FORMAT_I2S << I2S_CONFIG_FORMAT_FORMAT_Pos;
  
  // Use stereo 
  NRF_I2S->CONFIG.CHANNELS = I2S_CONFIG_CHANNELS_CHANNELS_STEREO << I2S_CONFIG_CHANNELS_CHANNELS_Pos;
  
  // Configure pins
  NRF_I2S->PSEL.MCK = (PIN_MCK << I2S_PSEL_MCK_PIN_Pos);
  NRF_I2S->PSEL.SCK = (PIN_SCK << I2S_PSEL_SCK_PIN_Pos); 
  NRF_I2S->PSEL.LRCK = (PIN_LRCK << I2S_PSEL_LRCK_PIN_Pos); 
  NRF_I2S->PSEL.SDOUT = (PIN_SDOUT << I2S_PSEL_SDOUT_PIN_Pos);
  
  NRF_I2S->ENABLE = 1;
  
  // Configure data pointer
  NRF_I2S->TXD.PTR = (uint32_t)&sine_table[0];
  NRF_I2S->RXTXD.MAXCNT = sizeof(sine_table) / sizeof(uint32_t);
  
  // Start transmitting I2S data
  NRF_I2S->TASKS_START = 1;
  
  
  // Since we are not updating the TXD pointer, the sine wave will play over and over again.
  // The TXD pointer can be updated after the EVENTS_TXPTRUPD arrives.
  while (1)
  {
    __WFE();
  }
}
