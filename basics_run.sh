#!/bin/sh
# https://github.com/google/sanitizers/wiki/AddressSanitizerFlags

asan_opts="export ASAN_OPTIONS=\"symbolize=1:halt_on_error=0:detect_invalid_pointer_pairs=2:detect_stack_use_after_return=1:strict_string_checks=1:check_initialization_order=1:strict_init_order=1:print_stats=true:atexit=true:print_legend=true:print_scariness=true:report_globals=1:print_full_thread_history=true:alloc_dealloc_mismatch=true:new_delete_type_mismatch=true:print_summary=true:check_printf=true:detect_deadlocks=true:full_address_space=true:print_suppressions=true:decorate_proc_maps=true\""

# detect_leaks=1 to be sure leak sanitizer is active (if not running x86_64 on Linux)

# Common to ASAN, TSAN and MSAN.
strict_string_checks=true:full_address_space=true:decorate_proc_maps=true

# print_stats=true # Print various statistics after printing an error message or if atexit=1.
# atexit=true # If set, prints ASan exit stats even after program terminates successfully.
export ASAN_OPTIONS="halt_on_error=false:detect_invalid_pointer_pairs=2:detect_stack_use_after_return=true:check_initialization_order=true:strict_init_order=true:print_scariness=true:alloc_dealloc_mismatch=true"

./testsOfFramework/testTool_main
#./src/day1/day1 ../src/day1/input
#./src/day2/day2 ../src/day2/input
#./src/day3/day3 ../src/day3/input
#./src/day4/day4 ../src/day4/input
#./src/day5/day5 ../src/day5/input