# PRU running example.
### A lot of information is taken from this great example online. https://www.glennklockwood.com/embedded/beaglebone-pru.html
### The code is based off of: https://github.com/glennklockwood/beaglebone-pru/tree/main/button
#### This repo is mostly used as a simple explaination to quickly get the PRU running.
### This program is tested and ran on a beaglebone black running debian 9.5

## ***Important note:*** 
## If remoteproc1 in /sys/class/remoteproc does not exist, or you know you were using UIO drivers, you must enable remoteproc drivers.

If remoteproc1 doesn't exist at first:

    Change /boot/uEnv.txt file
        under ###PRUSS OPTIONS:
            uncommented:
                uboot_overlay_pru=/lib/firmware/AM335X-PRU-RPROC-4-14-TI-00A0.dtbo

            recommented:
                uboot_overlay_pru=/lib/firmware/AM335X-PRU-UIO-00A0.dtbo

        reboot BBB
    remoteproc1 should now exist in /sys/class/remoteproc

## To configure pins
    config-pin p8_15 pruin
    config-pin p9_31 pruout

## To create PRU 
    make
### Check to ensure am335x-pru0-fw was created.

## To run PRU:
### Check if PRU is running. 
    cat /sys/class/remoteproc/remoteproc1/state
### If it is running, stop it.
    echo stop > /sys/class/remoteproc/remoteproc1/state
### Load the PRU with the firmware/PRU code
    cp am335x-pru0-fw /lib/firmware/am335x-pru0-fw
### Ensure it was loaded correctly.
    cat /sys/class/remoteproc/remoteproc1/firmware
### Start the PRU program.
    echo start > /sys/class/remoteproc/remoteproc1/state

## Create stand alone .c code executable.
    gcc host.c -o host

# Make sure the stand alone .c code is running as root.
