// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2013-2014 The Kuberbitcoin developers
// Copyright (c)      2014 The Inutoshi developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

#include <stdint.h>

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    // How many times we expect transactions after the last checkpoint to
    // be slower. This number is a compromise, as it can't be accurate for
    // every system. When reindexing from a fast disk with a slow CPU, it
    // can be up to 20, while when downloading from a slow network with a
    // fast multicore CPU, it won't be much higher than 1.
    static const double SIGCHECK_VERIFICATION_FACTOR = 5.0;

    struct CCheckpointData {
        const MapCheckpoints *mapCheckpoints;
        int64_t nTimeLastCheckpoint;
        int64_t nTransactionsLastCheckpoint;
        double fTransactionsPerDay;
    };

    bool fEnabled = true;

    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (       0, uint256("0xb0422f5a081f5ff5b2261653ce7816edd171ebf21e758273aa937bdd96f480c9"))
        (       500, uint256("e5714f2682d36865a81e9283598b743e494a49a3ac7e64947e875f7824b5fd63"))
        (       1000, uint256("90d9336757b513603e404f2aa1930d22c3ae9b8660b548b98fb83a131cf1de67"))
        (       1200, uint256("8aa2a203e6880bae5d7b8fd3f2cb1edfe09552764a8d2e5e7ba6495a318cdc2a"))
        (       1500, uint256("a2e97ab23cf967f4cb81457f414c1b5867de1f22af3af33efe539795a00c5b37")) 
        (       2000, uint256("ee44db00ee1c7306ce11f7701641fe9ce7cd20bde3b7b6f2d4626ec554df195e"))     
        (       2500, uint256("26e56b4743e0f943fc11cbd47b0b4482f2f71f9bab5dfde63139ba4d9c02a82e"))     
        (       3000, uint256("3edf1ef26d1653b3630175c15c8eac9fc89ae6dfe75b9cdf4a0e925be3e2deef"))     
        (       3500, uint256("a4a835b9a009a72c1dc8fc174e537f2f2b379a2aa5ccfccb7949e5ffb030a09c"))     
        (       4000, uint256("4687c1e2b467a10b3836ef0eda9e8f5826704f13f9f1defc0572acb5892e3826"))     
        (       4500, uint256("7f4b6d34a3fc3cdee514c8a96e57841494d6ff56a2efd2072a71b4913a263a40"))  
        (       6000, uint256("6b4592a1b75224f845b454af69575a78533c8be5544ea63064f50e02e3f07482"))  
        (       6500, uint256("bda9259f94036fca32a132cd07440ae48b386cb572dc5ed57cb4406e6168e48f"))  
        (       7500, uint256("ca28acf98fe4f66e9c2e86133253ec461b070a516944f74ed9f49f8149626513"))  
        (       8000, uint256("662465ea2229272969aaf0b3139a55916934659ca41b7661b7980b9e55f8a072")) 
        ;
        
    static const CCheckpointData data = {
        &mapCheckpoints,
        1500877754, // * UNIX timestamp of last checkpoint block
        1995092,    // * total number of transactions between genesis and last checkpoint
                  //   (the tx=... number in the SetBestChain debug.log lines)
        1800.0     // * estimated number of transactions per day after checkpoint
    };

    static MapCheckpoints mapCheckpointsTestnet = 
        boost::assign::map_list_of
        (     0, uint256("523f8a9f38bb5998df20870d8e306a15e75e60935ee37b66df0fd36584a0e48a"))
        ;
    static const CCheckpointData dataTestnet = {
        &mapCheckpointsTestnet,
        1385836559,
        1,
        960.0
    };

    static MapCheckpoints mapCheckpointsRegtest =
        boost::assign::map_list_of
        ( 0, uint256("3d2160a3b5dc4a9d62e7e66a295f70313ac808440ef7400d6c0772171ce973a5"))
    ;
    static const CCheckpointData dataRegtest = {
        &mapCheckpointsRegtest,
        0,
        0,
        0
    };
    


    const CCheckpointData &Checkpoints() {
        if (Params().NetworkID() == CChainParams::TESTNET)
            return dataTestnet;
        else if (Params().NetworkID() == CChainParams::MAIN)
            return data;
        else
            return dataRegtest;
    }

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (!fEnabled)
            return true;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    // Guess how far we are in the verification process at the given block index
    double GuessVerificationProgress(CBlockIndex *pindex, bool fSigchecks) {
        if (pindex==NULL)
            return 0.0;

        int64_t nNow = time(NULL);

        double fSigcheckVerificationFactor = fSigchecks ? SIGCHECK_VERIFICATION_FACTOR : 1.0;
        double fWorkBefore = 0.0; // Amount of work done before pindex
        double fWorkAfter = 0.0;  // Amount of work left after pindex (estimated)
        // Work is defined as: 1.0 per transaction before the last checkpoint, and
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
        if (!fEnabled)
            return 0;

        const MapCheckpoints& checkpoints = *Checkpoints().mapCheckpoints;

        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (!fEnabled)
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
