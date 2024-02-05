#!/bin/bash

./build/app/bin/chlor -h
echo "----------------------------"
./build/app/bin/chlor -d 1.5 25 1 3 1.15 0.645

exec $SHELL
