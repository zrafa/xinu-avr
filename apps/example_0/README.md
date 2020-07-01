
Quick start
-----------

# get the repository
git clone http://github.com/zrfa/xinu-avr
cd xinu-avr/

# copy an example app to main
rm -rf main/
cp -r apps/example_0/ main/
cd compile/

# build
make clean
make 	# it will give you an error. Sorry, just try again
make 	# yes, again

# flash and test
make flash 
screen /dev/ttyUSB0  # it could be /dev/ttyACM0 or whatever. Check dmesg

