#!/usr/bin/env bash

cmake -H. -Bbuild -DCMAKE_EXPORT_COMPILE_COMMANDS=ON && make -C build
