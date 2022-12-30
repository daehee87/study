#!/bin/bash
./make.sh
sleep 1
echo 'mkdir jail...'
mkdir jail
sleep 1
echo 'chroot into jail... but there is pre-open dfd outside jail'
echo 'we will get a un-chrooted shell with this.'
echo 'note that unchrooting is to change process root back to actual / in file system'
sudo ./x
rmdir jail
