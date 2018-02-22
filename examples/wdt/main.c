#include <nrf.h>
#include <stdint.h>

int main(void)
{
	const static uint32_t WDT_BASE_ADDRESS = 0x40010000ul;
	const static uint32_t WDT_TASKS_START  = 0x000;
	const static uint32_t WDT_CRV          = 0x504;
	const static uint32_t WDT_CONFIG       = 0x50C;
	const static uint32_t WDT_RREN         = 0x508;
	const static uint32_t WDT_RR0          = 0x600;
	
	*((uint32_t *) (WDT_BASE_ADDRESS | WDT_CRV))         = 0x0Ful; // timeout = (CRV+1) / 32768. This is the shortest timeout possible.
	// *((uint32_t *) (WDT_BASE_ADDRESS | WDT_CONFIG))      = 0x09ul; // Configure the WDT to keep counting down even when the CPU is halted by the debugger.
	*((uint32_t *) (WDT_BASE_ADDRESS | WDT_RREN))        = 0x01ul; // Enable reload register 0 to feed the dog.
	
	*((uint32_t *) (WDT_BASE_ADDRESS | WDT_TASKS_START)) = 0x01ul; // WDT will automatically start the LFCLK source if it is not already being generated.
	
	for(;;)
	{
		// infinite loop.
		*((uint32_t *) (WDT_BASE_ADDRESS | WDT_RR0))       = 0x6E524635; // Kick the dog to prevent it from issuing a watch dog reset.
	}
}
