# Computer Club Simulator

## Quick Compilation

### With GCC
```bash
g++ -Iinclude samples/main.cpp -o computer_club
```
### With Clang
```bash
clang++ -Iinclude samples/main.cpp -o computer_club
```
### With CMake + Ninja
```bash
mkdir build && cd build
cmake -G Ninja ..
ninja
```
### Running the Program
```bash
./computer_club <input_file>

# Example 
./computer_club test1.txt
```
### Running more tests
- There is the script `run_all_tests.sh` for running additional tests
```
chmod +x run_all_tests.sh
./run_all_tests.sh
```
### Test Scenarios
- data/test1.txt - main example from requirements
- data/test2_zero_computers.txt - computer count is zero
- data/test3_one_client.txt - single client scenario
- data/test4_bad_id.txt - invalid event (should fail)
- data/test5_closed_club.txt - clients try to leave after closing
- data/test6_all_leave.txt - all clients leave the club well
- data/test7_queue_overflow.txt - queue management test

### Google Tests (Optional)
- Building with Google Tests via CMake + Ninja
```
mkdir build_tests && cd build_tests
cmake -G Ninja ..
ninja

./run_all_tests
```