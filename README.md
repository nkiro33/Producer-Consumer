# Producer-Consumer
# CONSUMER PRODUCER PROBLEM
## Goal:
#### SOLVE THE CONSUMER PRODUCER PROBLEM USING SEMAPHORES FOR ACCESSING THE SHARED MEMORY BUFFER
## Structure Used
- Semaphores from System V library
- Shared memory from System V library
<br>

## Description:
#### Shared memory is represented by a consecutive amount of bytes decided and created by the consumer on its call `./consumer (size)`. We access these bytes as a string where we save only characters in it.
#### Shared memory string is in the form of (commodity,price) each in a separate line in the same string to prevent multiple pointers.
#### The producer uses this memory by tokenizing the first line and removing that line from the whole string.
#### The consumer uses this memory by concatenating a new line to the string.
<br>


