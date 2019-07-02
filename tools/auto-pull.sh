#!/bin/bash

cd $(dirname $0)/../
timeout 8 git pull
cd cmake-build-debug
make -j4
