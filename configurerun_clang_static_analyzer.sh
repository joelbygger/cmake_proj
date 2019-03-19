#!/bin/sh

# This script will invoke Clang static analyzer, via the scan-build tool.

# NOTE: This script must be executed on an empty folder. I.e. you may NOT have executed cmake (w/o scan-build) in this folder before!

DIR=build_static_analysis
# This is the version used, newer should work too.
SCAN_BUILD=scan-build
# Find the location of this executable, to make sure correct version is used. Maybe not needed?
CLANG=$(command -v clang)
OUTPUT_CLANG_ANALYZE=analysis_results

printf "This file should be sourced in project root.\n"

printf "Deleting folder (and all its contents): ${DIR}\n"
rm -rf $DIR
printf "Creating folder: ${DIR}\n"
mkdir $DIR
printf "Moving to folder and running CMake configuration as Debug, but wrapped in scan-build.\n\n"
cd $DIR

# Prepare all necessary sympbols etc.
# According to Clangs own documentation we should always run the tool on debug code, see https://clang-analyzer.llvm.org/scan-build.html.
$SCAN_BUILD --use-analyzer=$CLANG cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=/usr/bin/clang++-7 ..

#make clean

# And now run the world! I guess it works with command to compile in parallell.
$SCAN_BUILD -analyze-headers --use-analyzer=$CLANG -o $OUTPUT_CLANG_ANALYZE make day1 -j16
$SCAN_BUILD -analyze-headers --use-analyzer=$CLANG -o $OUTPUT_CLANG_ANALYZE make day2 -j16
$SCAN_BUILD -analyze-headers --use-analyzer=$CLANG -o $OUTPUT_CLANG_ANALYZE make day3 -j16
