/*
    This program needs to be ran as root in debian 
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define PRU_ADDR        0x4A300000      // Start of PRU memory Page 184 am335x TRM
#define PRU_LEN         0x80000         // Length of PRU memory
#define PRU0_DRAM       0x00000         // Offset to DRAM
#define PRU1_DRAM       0x02000
#define PRU_SHAREDMEM   0x10000         // Offset to shared memory

unsigned int    *pru0DRAM_ptr;        // Points to the start of local DRAM
unsigned int    *pru1DRAM_ptr;        // Points to the start of local DRAM
unsigned int    *prusharedMem_ptr;    // Points to the start of the shared memory


int main(int argc, char *argv[]){
    unsigned int *pru;       // Points to start of PRU memory.
    int fd;

    pru0DRAM_ptr =     pru + PRU0_DRAM/4 + 0x200/4;   // Points to 0x200 of PRU0 memory
    pru1DRAM_ptr =     pru + PRU1_DRAM/4 + 0x200/4;   // Points to 0x200 of PRU1 memory
    prusharedMem_ptr = pru + PRU_SHAREDMEM/4; // Points to start of shared memory

    printf("Testing Memory blocks\n");

    fd = open ("/dev/mem", O_RDWR | O_SYNC);
    if (fd == -1) {
        printf ("ERROR: could not open /dev/mem. Did you try running it as root?\n\n");
        return 1;
    }
    pru = mmap (0, PRU_LEN, PROT_READ | PROT_WRITE, MAP_SHARED, fd, PRU_ADDR);
    if (pru == MAP_FAILED) {
        printf ("ERROR: could not map memory.\n\n");
        return 1;
    }
    close(fd);

    printf ("Using /dev/mem.\n");

    //infinite loop for testing pin states
    while(1){
        if(prusharedMem_ptr[0] == 0){
            printf("Pin state is low.\n");
            sleep(2);
        }
        else if(prusharedMem_ptr[0] == 1){
            printf("Pin state is high.\n");
            sleep(2);
        }
        else{
            printf("Pin state is: %X. An error at probably occured reading pin state.\n", prusharedMem_ptr[0]);
        }
    }

    if(munmap(pru, PRU_LEN)) {
        printf("munmap failed\n");
    }
    else {
        printf("munmap succeeded\n");
    }

    return 0;
}
