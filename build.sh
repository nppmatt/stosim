#!/usr/bin/env bash

#bazel build //:test --config=clang_conf
bazel build //:hw10 --config=clang_conf
bazel build //:hw13 --config=clang_conf
