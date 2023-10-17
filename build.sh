#!/usr/bin/env bash

bazel build //:test_uniform --config=clang_conf
bazel build //:test_trapezoid --config=clang_conf
bazel build //:hw --config=clang_conf
