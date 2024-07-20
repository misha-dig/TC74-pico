#/bin/bash
# Checking folder existing path
[ -d "build" ] && echo "A directory of 'build' exists. Nothing to add." || echo "The directory build does not exist. It will create automatical." && mkdir build  
cd build # Create directory of 'build'
cmake .. # Configurate code for building code by using cmake software 
make -j4 # Build our code
# Upload the binary file into Raspberry Pi Pico via Picoprobe with the SWD interface.
openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program pico_tc74.elf verify reset exit"