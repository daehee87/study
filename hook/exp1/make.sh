#!/bin/bash
gcc -o x x.c 
gcc -o hook.so hook.c  -fPIC -shared -ldl
