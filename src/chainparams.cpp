// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2019-2022 Antoine Brûlé
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <arith_uint256.h>
#include <chainparams.h>
#include <consensus/merkle.h>

#include <base58.h>
#include <tinyformat.h>
#include <util.h>
#include <utilstrencodings.h>

#include <assert.h>

#include <chainparamsseeds.h>

static CBlock CreateGenesisBlock(const char* pszTimestamp, const CScript& genesisOutputScript, uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    CMutableTransaction txNew;
    txNew.nVersion = 1;
    txNew.vin.resize(1);
    txNew.vout.resize(1);
    txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
    txNew.vout[0].nValue = genesisReward;
    txNew.vout[0].scriptPubKey = genesisOutputScript;

    CBlock genesis;
    genesis.nTime = nTime;
    genesis.nBits = nBits;
    genesis.nNonce = nNonce;
    genesis.nVersion = nVersion;
    genesis.vtx.push_back(MakeTransactionRef(std::move(txNew)));
    genesis.hashPrevBlock.SetNull();
    genesis.hashMerkleRoot = BlockMerkleRoot(genesis);
    return genesis;
}

static CBlock CreateGenesisBlock(uint32_t nTime, uint32_t nNonce, uint32_t nBits, int32_t nVersion, const CAmount& genesisReward)
{
    const char* pszTimestamp = "28 Feb 2023 << Greek train crash, 57 dead people >> Fuck the politicians";
    const CScript genesisOutputScript = CScript() << ParseHex("04678afdb0fe5548271967f1a67130b7105cd6a828e03909a67962e0ea1f61deb649f6bc3f4cef38c4f35504e51ec112de5c384df7ba0b8d578a4c702b6bf11d5f") << OP_CHECKSIG;
    return CreateGenesisBlock(pszTimestamp, genesisOutputScript, nTime, nNonce, nBits, nVersion, genesisReward);
}

void CChainParams::UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    consensus.vDeployments[d].nStartTime = nStartTime;
    consensus.vDeployments[d].nTimeout = nTimeout;
}

class CMainParams : public CChainParams
{
public:
    CMainParams()
    {
        strNetworkID = "main";
        consensus.nSubsidyHalvingInterval = 4200000;
        consensus.BIP16Height = 0;

        consensus.BIP34Height = 71000000;

        consensus.BIP34Hash = uint256S("fa09d204a83a768ed5a7c8d441fa62f2043abf420cff1226c7b4329aeb9d51cf");
        consensus.BIP65Height = 91868400;

        consensus.BIP66Height = 81187900;

        consensus.powLimit = uint256S("00000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit2 = uint256S("00007ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 4440;
        consensus.nPowTargetSpacing = 60;

        consensus.nPowTargetSpacing2 = 25;

        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 222;

        consensus.nMinerConfirmationWindow = 296;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1199145601;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1230767999;

        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1681749846 + 5259486;

        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1681749846 + 31536000 + 5259486;

        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;

        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;

        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE_1_1].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE_1_1].nStartTime = 1681749846 + 5259486;

        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE_1_1].nTimeout = 1681749846 + 31536000 + 5259486;

        consensus.powForkTime = 1683302629;

        consensus.lastScryptBlock = 0;

        consensus.powLimitSHA = uint256S("00000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.slowStartBlocks = 125;

        consensus.totalMoneySupplyHeight = 6215968;

        consensus.minBeeCost = 10000;

        consensus.beeCostFactor = 500;

        consensus.beeCreationAddress = "CReateLitecoinCashWorkerBeeXYs19YQ";

        consensus.hiveCommunityAddress = "KJt5CcinFTjfk5Vutb3qPgxFKSBnVgYNzH";

        consensus.hiveCommunityAddress2 = "KJt5CcinFTjfk5Vutb3qPgxFKSBnVgYNzH";
        consensus.communityContribFactor = 10;

        consensus.beeGestationBlocks = 48 * 51;

        consensus.beeLifespanBlocks = 48 * 24 * 29, 75;

        consensus.powLimitHive = uint256S("0ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.powLimitHive2 = uint256S("7ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.minHiveCheckBlock = 1;

        consensus.hiveTargetAdjustAggression = 30;

        consensus.hiveBlockSpacingTarget = 4;

        consensus.hiveNonceMarker = 192;

        consensus.minK = 1;

        consensus.maxK = 8;

        consensus.maxK2 = 7;

        consensus.maxHiveDiff = 0.001;

        consensus.maxHiveDiff2 = 0.006;

        consensus.maxKPow = 5;

        consensus.powSplit1 = 0.000833;

        consensus.powSplit2 = 0.000416;

        consensus.powSplit12 = 0.005;

        consensus.powSplit22 = 0.0025;

        consensus.maxConsecutiveHiveBlocks = 4;

        consensus.hiveDifficultyWindow = 24;

        consensus.variableBeecost = true;

        consensus.variableForkBlock = 5000000;

        consensus.isTestnet = false;
        consensus.ratioForkBlock = 5000000;
        consensus.beeLifespanBlocks2 = 48 * 24 * 29, 75;
        consensus.beeLifespanBlocks3 = 48 * 24 * 29, 75;
        consensus.remvariableForkBlock = 5000000;

        consensus.nMinimumChainWork = uint256S("0x000000000000000000000000000000000000000000000000000007339e2df009");

        consensus.defaultAssumeValid = uint256S("0x9f705e9d3726701131f4de08f8415cb0c9a78cc606c061ca3b56eea2de693d4b");

        pchMessageStart[0] = 0xca;
        pchMessageStart[1] = 0xff;
        pchMessageStart[2] = 0x77;
        pchMessageStart[3] = 0x78;
        nDefaultPort = 6644;
        nPruneAfterHeight = 100000;

        genesis = CreateGenesisBlock(1683302629, 111141, 0x1e0ffff0, 1, 50 * COIN * COIN_SCALE);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x000044f47682004b1e3ef9a5fc3a513e099f5231a62d7f8614495f47ad1dad1a"));
        assert(genesis.hashMerkleRoot == uint256S("0xfae971f1631f4c2c582d02b8875cfbfb4725db6277ed6ad975029a84646d6026"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 28);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 5);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1, 45);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 176);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x88, 0xB2, 0x1E};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x88, 0xAD, 0xE4};

        bech32_hrp = "crnc";

        vFixedSeeds.clear();
        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_main, pnSeed6_main + ARRAYLEN(pnSeed6_main));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("0x000044f47682004b1e3ef9a5fc3a513e099f5231a62d7f8614495f47ad1dad1a")},
                {50802, uint256S("0x3d601d28d6529d926b5858bd498163730dfa6c2daf25b2e01561fd3e9ba8ad5c")},
                {118670, uint256S("0x9f705e9d3726701131f4de08f8415cb0c9a78cc606c061ca3b56eea2de693d4b")},
            }};

        chainTxData = ChainTxData{
            1685696043,

            328234,

            0.1273731270031677

        };
    }
};

class CTestNetParams : public CChainParams
{
public:
    CTestNetParams()
    {
        strNetworkID = "test";
        consensus.nSubsidyHalvingInterval = 1050000;
        consensus.BIP16Height = 0;

        consensus.BIP34Height = 14600000;
        consensus.BIP34Hash = uint256S("000000042bcd56d6ea0509230b76fe850f0a40a9110f7dba979fd5d707e47c8a");

        consensus.BIP65Height = 14600000;
        consensus.BIP66Height = 14600000;
        consensus.powLimit = uint256S("00000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.powLimit2 = uint256S("0007fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3840;

        consensus.nPowTargetSpacing = 60;
        consensus.nPowTargetSpacing2 = 25;
        consensus.fPowAllowMinDifficultyBlocks = false;
        consensus.fPowNoRetargeting = false;
        consensus.nRuleChangeActivationThreshold = 192;

        consensus.nMinerConfirmationWindow = 256;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 1683303184;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = 1683303184 + 31536000;

        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 1683303184;

        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = 1683303184 + 31536000;

        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;

        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE].bit = 7;
        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;

        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE_1_1].bit = 9;
        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE_1_1].nStartTime = 1683303184;

        consensus.vDeployments[Consensus::DEPLOYMENT_HIVE_1_1].nTimeout = 1683303184 + 31536000;

        consensus.powForkTime = 1683303184;

        consensus.lastScryptBlock = 0;

        consensus.powLimitSHA = uint256S("00000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.slowStartBlocks = 125;

        consensus.totalMoneySupplyHeight = 6215968;

        consensus.minBeeCost = 10000;

        consensus.beeCostFactor = 500;

        consensus.beeCreationAddress = "tEstNetCreateLCCWorkerBeeXXXYq6T3r";

        consensus.hiveCommunityAddress = "t9ctP2rDfvnqUr9kmo2nb1LEDpu1Lc5sQn";

        consensus.communityContribFactor = 10;

        consensus.beeGestationBlocks = 48 * 0.2;

        consensus.beeLifespanBlocks = 48 * 24 * 14;

        consensus.powLimitHive = uint256S("0ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.powLimitHive2 = uint256S("7ffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.minHiveCheckBlock = 1;

        consensus.hiveTargetAdjustAggression = 30;

        consensus.hiveBlockSpacingTarget = 4;

        consensus.hiveNonceMarker = 192;

        consensus.minK = 1;

        consensus.maxK = 8;

        consensus.maxHiveDiff = 0.002;

        consensus.maxKPow = 5;

        consensus.powSplit1 = 0.001;

        consensus.powSplit2 = 0.0005;

        consensus.maxConsecutiveHiveBlocks = 2;

        consensus.hiveDifficultyWindow = 24;

        consensus.variableBeecost = true;
        consensus.variableForkBlock = 5000000;

        consensus.isTestnet = true;
        consensus.ratioForkBlock = 5000000;

        consensus.beeLifespanBlocks2 = 48 * 24 * 21;
        consensus.beeLifespanBlocks3 = 48 * 24 * 21;
        consensus.remvariableForkBlock = 5000000;

        consensus.nMinimumChainWork = uint256S("0x0000000000000000000000000000000000000000000000000000000000000000");

        consensus.defaultAssumeValid = uint256S("0x0000c41a07b28416e7d1c873826edcec41e59ec960c4215877b540b7a3068f60");

        pchMessageStart[0] = 0x3e;
        pchMessageStart[1] = 0x88;
        pchMessageStart[2] = 0x55;
        pchMessageStart[3] = 0x22;
        nDefaultPort = 56644;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1683303184, 13886, 0x1e0ffff0, 1, 50 * COIN * COIN_SCALE);

        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x0000c41a07b28416e7d1c873826edcec41e59ec960c4215877b540b7a3068f60"));
        assert(genesis.hashMerkleRoot == uint256S("0xfae971f1631f4c2c582d02b8875cfbfb4725db6277ed6ad975029a84646d6026"));

        vFixedSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 127);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1, 107);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "tcrnc";

        vFixedSeeds = std::vector<SeedSpec6>(pnSeed6_test, pnSeed6_test + ARRAYLEN(pnSeed6_test));

        fDefaultConsistencyChecks = false;
        fRequireStandard = true;
        fMineBlocksOnDemand = false;

        checkpointData = {
            {
                {0, uint256S("0x0000c41a07b28416e7d1c873826edcec41e59ec960c4215877b540b7a3068f60")},
            }};

        chainTxData = ChainTxData{
            1683303184,
            0,
            0.0};
    }
};

class CRegTestParams : public CChainParams
{
public:
    CRegTestParams()
    {
        strNetworkID = "regtest";
        consensus.nSubsidyHalvingInterval = 150;
        consensus.BIP16Height = 0;

        consensus.BIP34Height = 100000000;

        consensus.BIP34Hash = uint256();
        consensus.BIP65Height = 1351;

        consensus.BIP66Height = 1251;

        consensus.powLimit = uint256S("7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");
        consensus.nPowTargetTimespan = 3.5 * 24 * 60 * 60;

        consensus.nPowTargetSpacing = 2.5 * 60;
        consensus.fPowAllowMinDifficultyBlocks = true;
        consensus.fPowNoRetargeting = true;
        consensus.nRuleChangeActivationThreshold = 108;

        consensus.nMinerConfirmationWindow = 144;

        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].bit = 28;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_TESTDUMMY].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].bit = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nStartTime = 0;
        consensus.vDeployments[Consensus::DEPLOYMENT_CSV].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].bit = 1;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nStartTime = Consensus::BIP9Deployment::ALWAYS_ACTIVE;
        consensus.vDeployments[Consensus::DEPLOYMENT_SEGWIT].nTimeout = Consensus::BIP9Deployment::NO_TIMEOUT;

        consensus.powForkTime = 1551819029;

        consensus.lastScryptBlock = 0;

        consensus.powLimitSHA = uint256S("000000ffffffffffffffffffffffffffffffffffffffffffffffffffffffffff");

        consensus.slowStartBlocks = 2000;

        consensus.totalMoneySupplyHeight = 6215968;

        consensus.hiveNonceMarker = 192;

        consensus.remvariableForkBlock = 118956;

        consensus.nMinimumChainWork = uint256S("0x00");

        consensus.defaultAssumeValid = uint256S("0x00");

        pchMessageStart[0] = 0xd9;
        pchMessageStart[1] = 0xf6;
        pchMessageStart[2] = 0xcc;
        pchMessageStart[3] = 0xea;
        nDefaultPort = 59444;
        nPruneAfterHeight = 1000;

        genesis = CreateGenesisBlock(1551819029, 1, 0x207fffff, 1, 50 * COIN * COIN_SCALE);
        consensus.hashGenesisBlock = genesis.GetHash();
        assert(consensus.hashGenesisBlock == uint256S("0x238a0bf5a26d0bb55bf257a6b180a49f1422c2270857bf53cbc49f8316eb88fd"));
        assert(genesis.hashMerkleRoot == uint256S("0xfe90e5f71db801cab3064947169305a13c8107e645f9387e211fd73f266a581a"));

        vFixedSeeds.clear();

        vSeeds.clear();

        fDefaultConsistencyChecks = true;
        fRequireStandard = false;
        fMineBlocksOnDemand = true;

        checkpointData = {
            {{0, uint256S("238a0bf5a26d0bb55bf257a6b180a49f1422c2270857bf53cbc49f8316eb88fd")}}};

        chainTxData = ChainTxData{
            0,
            0,
            0};

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1, 111);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1, 196);
        base58Prefixes[SCRIPT_ADDRESS2] = std::vector<unsigned char>(1, 58);
        base58Prefixes[SECRET_KEY] = std::vector<unsigned char>(1, 239);
        base58Prefixes[EXT_PUBLIC_KEY] = {0x04, 0x35, 0x87, 0xCF};
        base58Prefixes[EXT_SECRET_KEY] = {0x04, 0x35, 0x83, 0x94};

        bech32_hrp = "rcrnc";
    }
};

static std::unique_ptr<CChainParams> globalChainParams;

const CChainParams& Params()
{
    assert(globalChainParams);
    return *globalChainParams;
}

std::unique_ptr<CChainParams> CreateChainParams(const std::string& chain)
{
    if (chain == CBaseChainParams::MAIN)
        return std::unique_ptr<CChainParams>(new CMainParams());
    else if (chain == CBaseChainParams::TESTNET)
        return std::unique_ptr<CChainParams>(new CTestNetParams());
    else if (chain == CBaseChainParams::REGTEST)
        return std::unique_ptr<CChainParams>(new CRegTestParams());
    throw std::runtime_error(strprintf("%s: Unknown chain %s.", __func__, chain));
}

void SelectParams(const std::string& network)
{
    SelectBaseParams(network);
    globalChainParams = CreateChainParams(network);
}

void UpdateVersionBitsParameters(Consensus::DeploymentPos d, int64_t nStartTime, int64_t nTimeout)
{
    globalChainParams->UpdateVersionBitsParameters(d, nStartTime, nTimeout);
}
