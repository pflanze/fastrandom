# fastrandom - fast random source for (over)writing disk partitions/images

Filling up the storage to be used as source for dmcrypt using the
output from `/dev/urandom` can take a long time since the latter is
quite slow. `openssl rand` is a few times faster, but I figured that
I'd like something still faster than that, here's the result.

It intends to be using [complementary-multiply-with-carry by George
Marsaglia](http://en.wikipedia.org/wiki/Multiply-with-carry#Complementary-multiply-with-carry_generators),
taking code posted on
[gamedev.net](http://www.gamedev.net/topic/512260-number-generator-cmwc-4096-and-implementation/).
On the latter page there has been discussion of not understanding that
implementation. So, don't rely on it producing unpredictable date,
please. In an attempt to ensure even distribution even if the used
algorithm is partially faulty, the program is mixing the result of the
Marsaglia generator (or ripoff?) with some output from `/dev/urandom`
(using bitwise XOR). This may be a moot exercise, though.

At least the resulting program is fast enough for my purpose, it
generates about 100MB/s on an Atom D510 @ 1.66GHz.

## Installation

This has been written and tested on Debian only.

Run

    make
    time ./fastrandom |head -c 100000000|wc -c

for testing, or

    make install

for installation.
