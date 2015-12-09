#include <nrf.h>
#include <stdint.h>

static void nvmc_wait_until_ready(void)
{
	while (NRF_NVMC->READY != NVMC_READY_READY_Ready)
	{
		// Wait until NVMC is done with its current operation.
	}
	return;
}

int main(void)
{
	static const uint32_t test_data               = 0x0ul;
	static const uint32_t uicr_customer_address_0 = 0x10001080ul;
	static const uint32_t code_flash_page_address = 0x20000ul;
	
	static uint32_t code_flash_address            = 0x1FFF8ul;


	// Erase the UICR.
	nvmc_wait_until_ready();
	NRF_NVMC->CONFIG        = NVMC_CONFIG_WEN_Een;
	NRF_NVMC->ERASEUICR     = NVMC_ERASEUICR_ERASEUICR_Erase;
	nvmc_wait_until_ready();
	NRF_NVMC->CONFIG        = NVMC_CONFIG_WEN_Ren;

	// Write 0x0ul to four consecutive registers in Code Flash. Registers 0x1FFF8ul, 0x1FFFCul, 0x20000ul, 0x20004ul.
	nvmc_wait_until_ready();
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;

	static uint32_t i;
	for (i = 0; i < 4; i++)
	{
		*((uint32_t *) code_flash_address) = test_data;
		nvmc_wait_until_ready();
		code_flash_address += 0x04ul;
	}
	
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;

	// Now erase page 32 in Code Flash (the page starting at address 0x20000 and ending at address 0x21000).
	nvmc_wait_until_ready();
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Een;
	NRF_NVMC->ERASEPAGE = code_flash_page_address;
	nvmc_wait_until_ready();
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;

	// Write a value to an address in UICR.
	nvmc_wait_until_ready();
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen;
	*((uint32_t *) uicr_customer_address_0) = test_data;
	nvmc_wait_until_ready();
	NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren;

	while(1) {
		__WFE();
	}
}
