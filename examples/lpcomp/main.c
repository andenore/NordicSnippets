#include <nrf.h>

#define USE_ANADETECT  

void lpcomp_init(void)
{
    //Ain2 (p0.4) as Vin+ input
    NRF_LPCOMP->PSEL = (LPCOMP_PSEL_PSEL_AnalogInput2 << LPCOMP_PSEL_PSEL_Pos);   
    
    // 4/8 Vdd is Vin-
    NRF_LPCOMP->REFSEL = (LPCOMP_REFSEL_REFSEL_Ref4_8Vdd<< LPCOMP_REFSEL_REFSEL_Pos);
   
    //Enable 50 mV hysteresis (+- 25 mV)
    NRF_LPCOMP->HYST = (LPCOMP_HYST_HYST_Hyst50mV << LPCOMP_HYST_HYST_Pos);
    
#ifdef USE_ANADETECT
        //Enable ANADETECT on upward crossing to wake up the system from power off.
        NRF_LPCOMP->ANADETECT =(LPCOMP_ANADETECT_ANADETECT_Up << LPCOMP_ANADETECT_ANADETECT_Pos);
#endif

    //Enable
    NRF_LPCOMP->ENABLE = (LPCOMP_ENABLE_ENABLE_Enabled << LPCOMP_ENABLE_ENABLE_Pos);

    //Start the comparator
    NRF_LPCOMP->TASKS_START=1;
    while(!NRF_LPCOMP->EVENTS_READY);   
}

int main(void)
{
    *(volatile uint32_t *)0x40013540 = (*(volatile uint32_t *)0x10000324 & 0x00001F00) >> 8; //PAN fix

    
    //Configure GPIO pin as output with standard drive strength.
    NRF_GPIO->PIN_CNF[22] = (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos) |
                                (GPIO_PIN_CNF_DRIVE_S0S1 << GPIO_PIN_CNF_DRIVE_Pos) |
                                (GPIO_PIN_CNF_INPUT_Connect << GPIO_PIN_CNF_INPUT_Pos) |
                                (GPIO_PIN_CNF_PULL_Disabled << GPIO_PIN_CNF_PULL_Pos) |
                                (GPIO_PIN_CNF_SENSE_Disabled << GPIO_PIN_CNF_SENSE_Pos);
    
    lpcomp_init();
    
    //Set GPIO p0.22 output high if result==1 low else.
    while(1)
    {
        NRF_LPCOMP->TASKS_SAMPLE=1;
        if(NRF_LPCOMP->RESULT== 1)
        {
            NRF_GPIO->OUTSET=(1 << 22);
        }
        else
        {
            NRF_GPIO->OUTCLR=(1 << 22);
            
#ifdef USE_ANADETECT
            //go to system off when voltage falls below the reference voltage.
            NRF_POWER->SYSTEMOFF = (POWER_SYSTEMOFF_SYSTEMOFF_Enter << POWER_SYSTEMOFF_SYSTEMOFF_Pos); 
#endif            
        }
    }        
}
