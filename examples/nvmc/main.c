#include <nrf.h>

int main(void)
{
	// Erase the entire Code Flash area.
	while (NRF_NVMC->READY != NVMC_READY_READY_Ready << NVMC_READY_READY_Pos);
	NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Een << NVMC_CONFIG_WEN_Pos);
	NRF_NVMC->ERASEALL = (NVMC_ERASEALL_ERASEALL_Erase << NVMC_ERASEALL_ERASEALL_Pos);


	// Erase the UICR (page in NVM).
	while (NRF_NVMC->READY != NVMC_READY_READY_Ready << NVMC_READY_READY_Pos);
	NRF_NVMC->ERASEUICR = (NVMC_ERASEUICR_ERASEUICR_Erase << NVMC_ERASEUICR_ERASEUICR_Pos);
	NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);

	// Write a value to an address in Code Flash.

	// Erase that value by erasing the page it resides in.

	// Write a value to an address in UICR.

	while(1) {
		__WFE();
	}
}