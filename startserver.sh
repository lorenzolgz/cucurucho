#!/bin/bash

cmake .
make servidor
mv servidor cmake-build-debug/servidor
cd cmake-build-debug
./servidor -c ../server/config/config.json
