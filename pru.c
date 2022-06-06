#include <stdint.h>
#include <rsc_types.h>  /* provides struct resource_table */

#define CYCLES_PER_SECOND 200000000 /* PRU has 200 MHz clock */

#define P9_31 (1 << 0) /* R30 at 0x1 = pru1_pru0_pru_r30_0 = ball A13 = P9_31 */
#define P8_15 (1 << 15) // R31 as input

#define SHARE_MEM 0x00010000
volatile uint32_t *shared = (unsigned int *) SHARE_MEM;

volatile register uint32_t __R30, __R31; /* output register for PRU */

void main() {
    while(1){
		if(__R31 & P8_15){ //If input is high
			shared[0] = 1;
		}
		else{
			shared[0] = 0;
		}
	}
}

/* required by PRU */
#pragma DATA_SECTION(pru_remoteproc_ResourceTable, ".resource_table")
#pragma RETAIN(pru_remoteproc_ResourceTable)
struct my_resource_table {
    struct resource_table base;
    uint32_t offset[1];
} pru_remoteproc_ResourceTable = { 1, 0, 0, 0, 0 };

