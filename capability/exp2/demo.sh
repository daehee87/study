#!/bin/bash
./make.sh
sleep 1
echo 'creating a file with zero permission'
echo hey > noperm
chmod 000 noperm
sleep 1
ls -al
sleep 1
echo 'now, try open this with our sample program'
sleep 1
./x noperm
sleep 1
echo 'adding capability CAP_DAC_OVERRIDE to our program'
sleep 1
sudo setcap 'cap_dac_override=+ep' x
getcap x
sleep 1
echo 'now, try open the file again...'
./x noperm
rm -f noperm
