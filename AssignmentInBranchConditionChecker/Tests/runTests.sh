#!/bin/bash
set -x;
CLANG_PATH=../../llvm-project/build/bin/clang++ 

for source in *.cpp;do 
    $CLANG_PATH --analyze --analyzer-no-default-checks -Xanalyzer -analyzer-checker=alpha.unix.AssignmentInConditionChecker $source
done