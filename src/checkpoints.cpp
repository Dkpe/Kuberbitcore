// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double fSigcheckVerificationFactor = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64 nTimeLastCheckpoint;
        int64 nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (       0, uint256("0x863626dadaef221e2e2f30ff3dacae44cabdae9e0028058072181b3fb675d94a"))
        (    1024, uint256("0xeca0b8fb242d1439c7a73fd1f317a1ecfc06401e5fd63e1e1a4c055c55824669"))
        (  100000, uint256("0x5f6fcaa0642972517040ca6a6d8472000ce5996c28ed04a0ecf12852c5e8a1c9"))
        (  200000, uint256("0x948e229b668685864f746a49ae33200011e941af57f17b19cef8baad018f73b3"))
        (  300000, uint256("0x4169603458272ba881a61c00e21f9e00bc525ceaa5bc5811daa1deea49f4517e"))
        (  400000, uint256("0x12a159199d557a3800076a0b67db8478f2a94096b7c146dda6e763d503d65122"))
        (  500000, uint256("0xebf29329a443d7fed6050dbffd64a95c4c3b028e71ddc789cde3cb85867d9f17"))
        (  600000, uint256("0x9b5747b5dbfac309c808b545e7dde1d1cc99afa9abc908079566bcbecc1f5edd"))
        (  700000, uint256("0x4fbb467d1c115a19c4eb7de562cced98817b17a0b6e0be99d94175f64153a599"))
        (  800000, uint256("0xc1a8cadcb1e8f0442b4fdaa177e2dfcd2aea04e09d90c193f7a9725fa93d01c7"))
        (  900000, uint256("0x7927dadcda0c91e6f7af9afcab6401856ec8e50ee8a10309ed429b8f25dbe6bd"))
        ( 1000000, uint256("0x4847a1c1344a8c70d79885b964bf7503bfe17bd46e772c3f615d9f53a6a06c18"))
        ( 1100000, uint256("0x9acbf26c43f75b5f12213970eaaaaafd47ef82820bd664d53b268dfba52b6132"))
        ( 1200000, uint256("0x93fd2b11243e71581c6002ce8e78778f9929af2e2a9c75224125399e00f7c189"))
        ( 1300000, uint256("0x7ca6adc31fa07476f2bec6b5e877a3996bd7820019009951fde8a2a27470892c"))
    ;
    static const CCheckpointData data = {
        &mapCheckpoints,
        1438273072, // * UNIX timestamp of last checkpoint block
        1401086,    // * total number of transactions between genesis and last checkpoint
                  //   (the tx=... number in the SetBestChain debug.log lines)
        2800.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
        (     0, uint256("0x"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1385836559,
        1,
        960.0
    };

    const CCheckpointData &Checkpoints() {
        if (fTestNet)
            return dataTestnet;
        else
            return data;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex) {
        if (pindex==NULL)
            return 0.0;

        int64 nNow = time(NULL);

        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkoint, and
        // fSigcheckVerificationFactor per transaction after.

        const CCheckpointData &data = Checkpoints();

        if (pindex->nChainTx <= data.nTransactionsLastCheckpoint) {
            double nCheapBefore = pindex->nChainTx;
            double nCheapAfter = data.nTransactionsLastCheckpoint - pindex->nChainTx;
            double nExpensiveAfter = (nNow - data.nTimeLastCheckpoint)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore;
            fWorkAfter = nCheapAfter + nExpensiveAfter*fSigcheckVerificationFactor;
        } else {
            double nCheapBefore = data.nTransactionsLastCheckpoint;
            double nExpensiveBefore = pindex->nChainTx - data.nTransactionsLastCheckpoint;
            double nExpensiveAfter = (nNow - pindex->nTime)/86400.0*data.fTransactionsPerDay;
            fWorkBefore = nCheapBefore + nExpensiveBefore*fSigcheckVerificationFactor;
            fWorkAfter = nExpensiveAfter*fSigcheckVerificationFactor;
        }

        return fWorkBefore / (fWorkBefore + fWorkAfter);
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL; // Testnet has no checkpoints
        if (!GetBoolArg("-checkpoints", true))
            return NULL;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
