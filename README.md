# Streebog-bitslice 

Bitslice (bit-parallel) implementation of the Streebog algorithm from GOST 34.11—2012

## Compilation

### Linux

Download the repository to your local disk and go to the **Streebog-bitslice** directory.

At the command prompt from **Streebog-bitslice** directory, type

**make**

After running make, a file named **Streebog_bitslice_test** should be created in the current directory.

### In other operating systems

Compile files from the repository in a convenient way.

## Run

### Linux

At the command prompt, type for example

**./Streebog_bitslice_test 256 1048576**

where

the first parameter is number of messages, in our example, **256** messages,
the second parameter is the message length in bits, in our example, **1048576** bits.

## Testbench

Computer with Intel Core i5 8400 processor.

**./Streebog_bitslice_test 1048576 504**    ->  The computing speed is 58 MBytes per second.

**./Streebog_bitslice_test 256 10485760**    ->  The computing speed is 178 MBytes per second.

