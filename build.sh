#!/bin/bash

curr=$(dirname $(realpath $0))
bld_target=$curr/build

#rm -rd $bld_target

if [ -d $bld_target ]
then
  cd $bld_target
else
  mkdir $bld_target
  cd $bld_target
fi

cmake ..
make
cpack

exec $SHELL
