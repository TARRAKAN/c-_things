#!/bin/bash

g++ \
  -O0 \
  -I googletest/googletest/include \
  -std=c++17 \
  -o main \
  test.cpp \
  ~/googletest/build/lib/libgtest.a \
  ~/googletest/build/lib/libgtest_main.a \
  -lpthread \
;
