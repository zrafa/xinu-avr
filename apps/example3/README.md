
Quick start
-----------

1. get the repository
```
# get the repository
git clone http://github.com/zrfa/xinu-avr
cd xinu-avr/
```

2. copy the example3 app to main
```
# copy an example app to main
rm -rf main/
cp -r apps/example3/ main/
```

3. build
```
# build
cd compile/
make clean
make
```

4. flash and test
```
# flash and test
make flash 
screen /dev/ttyUSB0  # it could be /dev/ttyACM0 or whatever. Check dmesg
```
