# Streebog bitslice 

Bitslice (bit-parallel) implementation of the Streebog (Stribog) algorithm from GOST 34.11—2018

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

Computer with Intel Core i5 8400 processor. Running on a single core, without parallelization.

**./Streebog_bitslice_test 1048576 504**    ->  The computing speed is 58 MBytes per second.

**./Streebog_bitslice_test 65536 65536**    ->  The computing speed is 174 MBytes per second.

**./Streebog_bitslice_test 256 10485760**    ->  The computing speed is 178 MBytes per second.

The slower calculation for short messages is explained by the fact that for short messages the 3rd stage of the Stribog algorithm is performed proportionally more. The third stage is more laborious than the second stage, because in the third stage, the compression function **g** is called three times, and in the second stage, the compression function is called only once.

## Author

Solovyev Anatoly Sergeevich

email: soloviov-anatoly@mail.ru

## LICENSE

**CC BY-ND-NC**

NonCommercial

Only non commercial use.

## Comment

The link to this repository is located in a paper

**Anatoly Sergeevich Solovyev and Denis Bonislavovich Fomin
Bitsliced implementations of the «Streebog» and «Kuznechik» algorithms**

published at the CTCRYPT 2025 conference.



