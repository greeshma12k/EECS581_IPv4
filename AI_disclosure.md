# AI Disclosure

## General Disclosure

I used ChatGPT (GPT-5.6 Luna) for this assignment. I consulted ChatGPT on September 25 and September 26, 2026.

The assignment allowed AI to be used for all or part of the code generation, so I used it as a programming aid while still reviewing, modifying, and testing the code myself.

## Code Attribution

I used ChatGPT to help generate parts of the initial C++ implementation based on the assignment requirements. The AI-assisted parts included the general structure of the IPv4 parser, the helper functions for parsing octets and ports, some of the validation logic, and the conversion of the IPv4 address into its decimal value.

I reviewed the initial AI-generated code, made changes, and tested it against the assignment requirements and different inputs.

I wrote and modified parts of the final implementation myself, especially while working through the edge cases and debugging the behavior of the parser. I also made sure that the implementation followed the restrictions in the assignment, including manually accumulating digits instead of using the prohibited numeric conversion functions.

## Modifications and Debugging

One issue I found while testing was with:

`1192.168.1.1`

An earlier version of the program incorrectly extracted `192.168.1.1` from the middle of the input. I used ChatGPT to help me understand why the parser was allowing a candidate to start there. I then modified the candidate-boundary logic so that a candidate cannot start immediately after a digit, period, or colon.

I retested the input after making the change, and the final version correctly rejected it.

I also checked the behavior of:

`192a168.1.1.1`

The final program correctly extracts `168.1.1.1` because the `a` is treated as a garbage character separating the possible candidates.

I also reviewed the handling of leading zeros, invalid octet values, invalid ports, extra periods, extra colons, and other edge cases. I made changes as needed based on the assignment requirements and my testing.

## Testing

I compiled the program using:

`g++ -Wall -Wextra -std=c++17 main.cpp -o ipv4_parser`

The final version compiled without errors or warnings.

I ran the program myself and tested multiple valid and invalid inputs. My tests included normal IPv4 addresses, addresses with ports, leading-zero cases, invalid ranges, invalid ports, extra punctuation, noisy text, and partial-match cases.

The test results are documented in `TEST_CASES.md`.

## Verification Statement

I understand every line of the submitted code. Although I used AI to help generate parts of the implementation, I reviewed the code, made modifications, investigated unexpected behavior, and tested the final program myself. I did not blindly copy and submit the AI output.

The issue with `1192.168.1.1` was identified and fixed during testing. I did not identify any known unresolved bugs in the final version based on the tests I performed.

## AI Prompt Record

The prompts below document the prompts I used in my ChatGPT conversation during the assignment.

### Prompt 1

"I'm working on this IPv4 parser assignment. Can you help me write the C++ code based on these requirements? I need to manually parse the IP and optional port and make sure all the validation rules are followed."

### Prompt 2

"I'm confused about the leading zero rule. How should I make the program reject something like 192.168.01.1 but still allow 0.0.0.0?"

### Prompt 3

"How should I check the port part? Like if I have 192.168.1.1:8080 it should work, but what about 99999 or 080?"

### Prompt 4

"I have a question about finding the IP in noisy text. What should happen with something like 192a168.1.1.1? And what about 1192.168.1.1?"

### Prompt 5

"My program is finding 192.168.1.1 inside 1192.168.1.1, but I think that should be invalid. What's causing that and how should I fix it?"

### Prompt 6

"What are some good test cases I should run for this assignment? I want to make sure I'm testing the weird cases too?"

### Prompt 7

"Does my test case file need to be a table, or can I just list the input, expected result, actual result, and pass/fail?"
