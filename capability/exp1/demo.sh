#!/bin/bash
./make.sh
sleep 1
echo 'open port 3000 with no capability as non-root'
./x 3000
sleep 1
echo 'now, open port 1 with no capability as non-root'
./x 1
sleep 1
echo 'adding capability CAP_NET_BIND_SERVICE'
sudo setcap 'cap_net_bind_service=+ep' x
getcap x
echo 'now, open port 1 with no capability as non-root again'
./x 1

