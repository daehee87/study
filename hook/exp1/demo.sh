#!/bin/bash
./make.sh
sleep 1
echo 'normal execution...'
./x
sleep 1
echo 'hooking getpid using LD_PRELOAD...'
LD_PRELOAD=./hook.so ./x
