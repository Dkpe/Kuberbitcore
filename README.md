

![alt text](https://i.imgur.com/foSTgt2.png)

# Kuberbitcoin Core [KBI]
 ================================

  
# Kuberbitcoin integration/staging tree
 ================================

Kuberbitcoin 1.9.4

Copyright (c) 2009-2013 Bitcoin Developers
Copyright (c) 2011-2013 Litecoin Developers
Copyright (c) 2020 Kuberbitcoin Developers
What is Kuberbitcoin?

A scrypt-based crypto currency that supports merged mining (as per USC code base).

Kuberbitcoin

Ticker :KBI

Algo :Scrypt

Type :Merged Auxpow Scrypt

Wallet Address Start :K

Merge Mined

Aux chain ID = 0x0041 (65) Chain ID after Block 1

Auxpow protocol start :1

Mining Target Span :12 Blocks / 48 Minutes

Block Space : 240 Sec4 Minutes

DefaultPort :10598

RPCPort :10599

Halving Constant :After 250000 Blocks (1250000 Minutes / 2.37 Years )

Transaction Confirmations:

50

Pow Reward :

(2)Even High Reward

(1)Odd Low Reward
 ![alt text](https://i.imgur.com/bftaxlA.png)


License
-------

Kuberbitcoin is released under the terms of the MIT license. See `COPYING` for more
information or see http://opensource.org/licenses/MIT.

Development process
-------------------

Developers work in their own trees, then submit pull requests when they think
their feature or bug fix is ready.

If it is a simple/trivial/non-controversial change, then one of the Kuberbitcoin
development team members simply pulls it.

If it is a *more complicated or potentially controversial* change, then the patch
submitter will be asked to start a discussion (if they haven't already) on the
[mailing list](http://sourceforge.net/mailarchive/forum.php?forum_name=bitcoin-development).

The patch will be accepted if there is broad consensus that it is a good thing.
Developers should expect to rework and resubmit patches if the code doesn't
match the project's coding conventions (see `doc/coding.txt`) or are
controversial.

The `master` branch is regularly built and tested, but is not guaranteed to be
completely stable. [Tags](https://github.com/bitcoin/bitcoin/tags) are created
regularly to indicate new official, stable release versions of Kuberbitcoin.

Testing
-------

Testing and code review is the bottleneck for development; we get more pull
requests than we can review and test. Please be patient and help out, and
remember this is a security-critical project where any mistake might cost people
lots of money.

### Automated Testing

Developers are strongly encouraged to write unit tests for new code, and to
submit new unit tests for old code.

Unit tests for the core code are in `src/test/`. To compile and run them:

    cd src; make -f makefile.unix test

Unit tests for the GUI code are in `src/qt/test/`. To compile and run them:

    qmake BITCOIN_QT_TEST=1 -o Makefile.test bitcoin-qt.pro
    make -f Makefile.test
    ./kuberbitcoin-qt_test

