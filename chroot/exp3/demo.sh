#!/bin/bash
./make.sh
sleep 1
echo 'mkdir jail...'
mkdir jail
sleep 1
echo 'chroot into jail... but there is pre-open dfd outside jail'
sudo ./x
rmdir jail
