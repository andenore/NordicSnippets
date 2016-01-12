#include <nrf.h>

void single_ended_comp_init(void)
{
    //Ain2 (p0.4) is input
    NRF_COMP->PSEL = (COMP_PSEL_PSEL_AnalogInput2 << COMP_PSEL_PSEL_Pos);   
    
    //Vdd is reference voltage
    NRF_COMP->REFSEL = (COMP_REFSEL_REFSEL_VDD << COMP_REFSEL_REFSEL_Pos);
   
    //Trigger halfway to reference voltage with a hysterersis of +- 1/64*Vref
    //(32+1)*Vref/64 going up
    //(30+1)*Vref/64 going down
    NRF_COMP->TH = (30<< COMP_TH_THDOWN_Pos) | (32 << COMP_TH_THUP_Pos);
    
    //Single ended mode. Normal Speed
    NRF_COMP->MODE = (COMP_MODE_MAIN_SE<< COMP_MODE_MAIN_Pos);
    NRF_COMP->MODE |= (COMP_MODE_SP_Normal << COMP_MODE_SP_Pos);
    
    //Enable
    NRF_COMP->ENABLE = (COMP_ENABLE_ENABLE_Enabled << COMP_ENABLE_ENABLE_Pos);

    //Start the comparator
    NRF_COMP->TASKS_START=1;
    while(!NRF_COMP->EVENTS_READY);   
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
    
    single_ended_comp_init();
    
    //Set GPIO p0.22 output high if result==1 low else.
    while(1)
    {
        NRF_COMP->TASKS_SAMPLE=1;
        if(NRF_COMP->RESULT== 1)
        {
            NRF_GPIO->OUTSET=(1 << 22);
        }
        else
        {
             NRF_GPIO->OUTCLR=(1 << 22);
        }
    }        
}
