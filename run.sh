#!/bin/bash

./build/app/bin/chloro -h
echo "----------------------------"
./build/app/bin/chloro -df 1.5 25 1 3 1.15 0.645

exec $SHELL
