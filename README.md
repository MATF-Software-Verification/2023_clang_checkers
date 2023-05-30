# 2023_clang_checkers

Implementation of new Clang checkers
### AssignmentInConditionChecker
Checks for assignment statement in branch condition

### InfiniteLoopChecker
Checks for infinite loop without break or return statement, or unreachable break and return statement


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

### Check C code
```bash
./2023_clang_checkers/llvm-project/build/bin/clang --analyze --analyzer-no-default-checks -Xanalyzer -analyzer-checker=alpha.unix.[Checker-name] [path-to-file]
```

### Check C++ code
```bash
./2023_clang_checkers/llvm-project/build/bin/clang++ --analyze --analyzer-no-default-checks -Xanalyzer -analyzer-checker=alpha.unix.[Checker-name] [path-to-file]
```

## Tests

Test examples are available in **Tests** directory for each checker, with script runTests.sh for running all tests.


```bash
./runTests
```


## Authors

- Svetlana Bićanin 1082/2022
- Lucija Miličić 1076/2022
- Aleksandra Pešić 1077/2022
