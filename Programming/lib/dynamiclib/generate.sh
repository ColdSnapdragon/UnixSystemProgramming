#!/bin/bash

gcc -shared -o libmymath.so resource/*.o

gcc a.c -o a.out -I ./inc -Wall -l mymath -L ./lib 
