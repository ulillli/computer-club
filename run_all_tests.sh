#!/bin/bash

cd "$(dirname "$0")"
echo "=== Сompilation ==="
echo "Compiler: GCC:"
g++ -std=c++17 -Iinclude samples/main.cpp -o computer_club 2>&1
if [ $? -eq 0 ]; then
    echo "   GCC: good"
else
    echo "   GCC: error"
    exit 1
fi

PROGRAM="./computer_club"

echo ""
echo "Main test:"
echo "========================================"
$PROGRAM test1.txt

echo ""
echo "Others tests:"
echo "========================================"

TESTS=(
    "test2_zero_computers.txt"
    "test3_one_client.txt"
    "test4_bad_id.txt" 
    "test5_closed_club.txt"
    "test6_all_leave.txt"
    "test7_queue_overflow.txt"
)

for test in "${TESTS[@]}"; do
    echo ""
    echo "Тест: $test"
    echo "----------------"
    OUTPUT=$($PROGRAM "$test" 2>&1)
    echo "$OUTPUT"
done

echo ""
echo "=== Testing is over ==="