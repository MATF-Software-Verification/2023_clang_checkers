# AssingmentInConditionChecker

Checks for assignment statement in branch condition

## Installation

Clone repository including submodules:

```bash
git clone --recurse-submodules git@github.com:MATF-Software-Verification/2023_clang_checkers.git
```

Build LLVM and clang:

```bash
cd 2023_clang_checkers/llvm-project/
mkdir build
cd build
cmake -DLLVM_ENABLE_PROJECTS=clang -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" ../llvm
make
```
For more information: [Clang - Getting Started](https://clang.llvm.org/get_started.html)

## Usage

### C
```bash
./vs/2023_clang_checkers/llvm-project/build/bin/clang --analyze --analyzer-no-default-checks -Xanalyzer -analyzer-checker=alpha.unix.ProbaChecker test.c
```

### C++
```bash
./vs/2023_clang_checkers/llvm-project/build/bin/clang++ --analyze --analyzer-no-default-checks -Xanalyzer -analyzer-checker=alpha.unix.ProbaChecker test.cpp
```
