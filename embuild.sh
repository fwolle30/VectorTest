#!/bin/bash

~/Projects/emsdk/emsdk activate latest
source ~/Projects/emsdk/emsdk_env.sh

cd ./build
rm -rf *

emcmake cmake -G 'Unix Makefiles' ..
emmake make