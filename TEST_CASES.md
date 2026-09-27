# IPv4 Parser Test Cases

Test 1

Input: connecting to 192.168.1.1 now
Expected: Extract 192.168.1.1 with no port.
Actual: Extracted 192.168.1.1 with no port.
Result: Pass

Test 2

Input: Server running at 10.0.0.1:8080
Expected: Extract 10.0.0.1 with port 8080.
Actual: Extracted 10.0.0.1 with port 8080.
Result: Pass

Test 3

Input: 192.168.01.1
Expected: Reject because of the leading zero.
Actual: Rejected.
Result: Pass

Test 4

Input: 192.168.1.1:99999
Expected: Reject because the port is greater than 65535.
Actual: Rejected.
Result: Pass

Test 5

Input: 192.168.1.1.
Expected: Reject because of the extra period after the address.
Actual: Rejected.
Result: Pass

Test 6

Input: 999.168.1.1
Expected: Reject because an octet is greater than 255.
Actual: Rejected.
Result: Pass

Test 7

Input: 192.168.1
Expected: Reject because there are only three octets.
Actual: Rejected.
Result: Pass

Test 8

Input: 192.168.1.1:
Expected: Reject because the port is missing.
Actual: Rejected.
Result: Pass

Test 9

Input: 192.168.1.1:080
Expected: Reject because of the leading zero in the port.
Actual: Rejected.
Result: Pass

Test 10

Input: 255.255.255.255:65535
Expected: Extract 255.255.255.255 with port 65535.
Actual: Extracted 255.255.255.255 with port 65535.
Result: Pass

Test 11

Input: 0.0.0.0:0
Expected: Extract 0.0.0.0 with port 0.
Actual: Extracted 0.0.0.0 with port 0.
Result: Pass

Test 12

Input: abc!!! 172.16.0.5 xyz??? hello
Expected: Extract 172.16.0.5 with no port.
Actual: Extracted 172.16.0.5 with no port.
Result: Pass

Test 13

Input: 192.168.1.1:abc
Expected: Reject because the port is invalid.
Actual: Rejected.
Result: Pass

Test 14

Input: 192.168.1.1.5
Expected: Reject because of the extra period.
Actual: Rejected.
Result: Pass

Test 15

Input: 192a168.1.1.1
Expected: Extract 168.1.1.1 with no port.
Actual: Extracted 168.1.1.1 with no port.
Result: Pass

Test 16

Input: 1192.168.1.1
Expected: Reject and do not extract 192.168.1.1 from the middle of the number.
Actual: Initially extracted 192.168.1.1. After changing the candidate boundary logic, the input was rejected.
Result: Pass

Test 17

Input: :192.168.1.1
Expected: Reject because of the stray colon before the address.
Actual: Rejected.
Result: Pass

Test 18

Input: END
Expected: Display Program terminated.
Actual: Displayed Program terminated.
Result: Pass

Compilation

Command used: g++ -Wall -Wextra -std=c++17 main.cpp -o ipv4_parser

Result: The program compiled without errors or warnings.
