# Build and Execute
## Build
```sh
git clone https://github.com/cho0h5/mips-simulator.git
cd mips-simulator
make
```
Then, you can see `mipsvm` binary file.

## Execute
In testcase directory, there are test mips binary code.
You can test this virtual cpu with these test code.
```sh
./mipsvm testcase/print_1234_hello.bin    # print integer and charachers
./mipsvm testcase/sum1to100.bin    # sum 1 to 100 and print result
./mipsvm testcase/factorial6.bin    # calculate factorial 6
```

## Test Environment
- OS: macOS 14.0 arm64
- g++: Apple clang version 15.0.0
