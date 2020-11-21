#! /bin/bash

echo "******************"
echo "SERIAL VERSION"
echo "******************"
./rainfall_seq 8 50 0.5 4096 ../input_file/measurement_4096x4096.in | head -n 3
echo "\n"

echo "******************"
echo "PARALLEL VERSION THREAD 1"
echo "******************"
./rainfall_pt 1 50 0.5 4096 ../input_file/measurement_4096x4096.in | head -n 3
echo "\n"

echo "******************"
echo "PARALLEL VERSION THREAD 2"
echo "******************"
./rainfall_pt 2 50 0.5 4096 ../input_file/measurement_4096x4096.in | head -n 3
echo "\n"

echo "******************"
echo "PARALLEL VERSION THREAD 4"
echo "******************"
./rainfall_pt 4 50 0.5 4096 ../input_file/measurement_4096x4096.in | head -n 3
echo "\n"

echo "******************"
echo "PARALLEL VERSION THREAD 8"
echo "******************"
./rainfall_pt 8 50 0.5 4096 ../input_file/measurement_4096x4096.in | head -n 3
echo "\n"