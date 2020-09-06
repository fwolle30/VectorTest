#!/bin/bash

~/Projects/emsdk/emsdk activate latest
source ~/Projects/emsdk/emsdk_env.sh

cd public
emrun --no_browser VectorTest.html