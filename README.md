# Streebog-bitslice 

Bitslice (bit-parallel) implementation of the Streebog algorithm from GOST 34.11—2012

## Compilation

At the command prompt, type 

make

After running make, a file named Streebog_bitslice_test should be created in the current directory.

## Run

At the command prompt, type for example

./Streebog_bitslice_test 256 1048576

where

the first parameter is number of messages, in our example, 256,
the second parameter is the message length in bits, in our example, 1048576 bits.
