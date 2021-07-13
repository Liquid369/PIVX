// Copyright (c) 2020 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_CONSENSUS_ZEROCOIN_VERIFY_H
#define PIVX_CONSENSUS_ZEROCOIN_VERIFY_H

#include "consensus/consensus.h"
#include "script/interpreter.h"
#include "zpivchain.h"

// Fake Serial attack Range
bool isBlockBetweenFakeSerialAttackRange(int nHeight);
// Public coin spend
bool CheckPublicCoinSpendEnforced(int blockHeight, bool isPublicSpend);
int CurrentPublicCoinSpendVersion();
bool CheckPublicCoinSpendVersion(int version);
bool ContextualCheckZerocoinTx(const CTransactionRef& tx, CValidationState& state, const Consensus::Params& consensus, int nHeight);
bool ContextualCheckZerocoinSpend(const CTransaction& tx, const libzerocoin::CoinSpend* spend, int nHeight);
bool ContextualCheckZerocoinSpendNoSerialCheck(const CTransaction& tx, const libzerocoin::CoinSpend* spend, int nHeight);

struct CoinSpendValues {
public:
    explicit CoinSpendValues(const CBigNum& s, CAmount v) : serial(s), value(v) {}
    CBigNum serial;
    CAmount value;
};
// Returns nullopt if coin spend is invalid. Invalidity/DoS causes are treated inside the function.
Optional<CoinSpendValues> ParseAndValidateZerocoinSpend(const Consensus::Params& consensus,
                                                               const CTransaction& tx, int chainHeight,
                                                               CValidationState& state);

#endif //PIVX_CONSENSUS_ZEROCOIN_VERIFY_H
