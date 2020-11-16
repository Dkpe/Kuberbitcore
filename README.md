COMING SOON 

![alt text](https://i.imgur.com/foSTgt2.png)

Specifications


## General

- Kuberbitcoin

- Scrypt & SHA256D

- AUXPOW merge mine capability

- Optimized client

- Ticker :KBI

- Type :Merged Auxpow 

- Wallet Address Start :K

- Merge Mined

- Aux chain ID = 0x0041 (65) Chain ID after Block 1

- Auxpow protocol start :1

- DefaultPort :10598

- RPCPort :10599

- Halving Constant :After 250000 Blocks (1250000 Minutes / 2.37 Years )

- Transaction Confirmations: 85

- Relay Fee 7 KBI

- Pow Reward :

- (2)Even High Reward

(1)Odd Low Reward
 ![alt text](https://i.imgur.com/bftaxlA.png)

## Blocks
- Block size 10mb
- Signature operations per block maximum 100k
- 4 Minute block time * Algo

## Difficulty
- Dark Gravity Wave Algo

#
## Security
- Mined blocks mature after 85 confirms
- Kuberbitcoin is a fast currency but it does not compromise the safety of the blockchain in the process.

## Ports
Listen Port: 13580

RPC Port: 13581



## Conf Settings
If you are setting up a pool or want to solo mine in SHA add the following to the conf file

- algo=sha256d

If you want to set the daemon to scrypt, set the algo= to 

- algo=scrypt











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

