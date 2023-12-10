#!/usr/bin/env bash

#bazel build //:test --config=clang_conf
bazel build //:hw24a --config=clang_conf
bazel build //:hw24b --config=clang_conf
bazel build //:hw24c --config=clang_conf
bazel build //:hw24d --config=clang_conf
bazel build //:hw2a --config=clang_conf
bazel build //:hw2b --config=clang_conf
bazel build //:hw2c --config=clang_conf
bazel build //:hw2d --config=clang_conf
bazel build //:hw2e --config=clang_conf

