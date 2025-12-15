#!/usr/bin/env bash

cmake -H. -Bbuild && make -C build
ln -sf ./build/compile_commands.json compile_commands.json
