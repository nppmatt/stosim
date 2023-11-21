#!/usr/bin/env bash

#bazel build //:test --config=clang_conf
bazel build //:hw18 --config=clang_conf
bazel build //:hw4 --config=clang_conf
