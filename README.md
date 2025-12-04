# Advent of Code

You can find all problem statements on this site: https://adventofcode.com/

In order to compile all solutions, run this from the project root:
```shell
cmake -Bbuild
cmake --build build
```
The executables will be located in `./build/dayXX/part_X`

All solutions expect a file `input.txt`.
You can put input files in `./build/dayXX` directories, and
CMake will automatically copy them into corresponding build directories.

Example:
```shell
echo -e "L68\nL30\nR48\nL5\nR60\nL55\nL1\nL99\nR14\nL82" > day_01/input.txt
cmake -Bbuild
cmake --build build --target day_01_part_1
cd build/day_01
./day_01_part_1
```
If everything went correctly, you should see `3` printed.
