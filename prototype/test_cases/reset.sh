#!/bin/sh

echo file 1 > test1
echo file 2 > test2
echo file 3 > test3

# Test cases
(cat test1 | cat | tr a-z A-Z > test2)
