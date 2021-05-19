#!/bin/bash

debugfs="/sys/kernel/debug"
echo nop > $debugfs/tracing/current_tracer
echo 0 > $debugfs/tracing/tracing_on

echo function_graph > $debugfs/tracing/current_tracer
#echo funcgraph-abstime > $debugfs/tracing/trace_options

gcc -o test_write test_write.c
echo 1 > $debugfs/tracing/tracing_on
taskset -c 0 ./test_write start
echo 0 > $debugfs/tracing/tracing_on

cat $debugfs/tracing/per_cpu/cpu0/trace_pipe > ./trace.txt
echo nop > $debugfs/tracing/current_tracer
echo "end"
