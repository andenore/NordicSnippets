#include <nrf.h>
#include <stdint.h>

int main(void)
{
	static const uint32_t code_flash_address      = 0x20000ul;
	static const uint32_t uicr_customer_address_0 = 0x10001080ul;
	static const uint32_t test_data               = 0x0ul;

	// Erase the entire Code Flash area.
	while (NRF_NVMC->READY != NVMC_READY_READY_Ready);
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Een;
	NRF_NVMC->ERASEALL = NVMC_ERASEALL_ERASEALL_Erase;

	// Erase the UICR (page in NVM).
	while (NRF_NVMC->READY != NVMC_READY_READY_Ready);
	NRF_NVMC->ERASEUICR = NVMC_ERASEUICR_ERASEUICR_Erase;
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;

	// Write a value to an address in Code Flash.
	while (NRF_NVMC->READY != NVMC_READY_READY_Ready);
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
	*((uint32_t *) code_flash_address) = test_data;
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;

	// Erase that value by erasing the page it resides in.

	// Write a value to an address in UICR.
	while (NRF_NVMC->READY != NVMC_READY_READY_Ready << NVMC_READY_READY_Pos);
	NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos);
	*((uint32_t *) uicr_customer_address_0) = test_data;
	NRF_NVMC->CONFIG = (NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos);

	while(1) {
		__WFE();
	}
}