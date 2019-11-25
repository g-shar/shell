#!/bin/sh

var=("echo hello world")

output=$(./rshell ${var})

echo "Output: \"${output}\"" > output.txt

