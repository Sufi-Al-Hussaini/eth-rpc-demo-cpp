#include <string>
#include <iostream>
#include <sstream>
#include <jsonrpccpp/client/connectors/httpclient.h>

#include "ethrpc.h"    // Generated using `jsonrpcstub eth.json --cpp-client=EthRpc`


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// Global constants
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

static const char *nodeRpcUrl = "127.0.0.1:8545";
//static const char *nodeRpcUrl = "https://mainnet.infura.io/v3/79a1b2c8f51c43f6a41c311e0cb83c8f";
static const char *ensAddress = "0x6090A6e47849629b7245Dfa1Ca21D94cd15878Ef";

// ////////////////////////////////////////////////////////`//////////
// //////////////////////////////////////////////////////////////////
// Function declarations
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

/// Get logs that match evHash via RPC
/// \param ethRpc JsonRpc Client instance
/// \param evHash Hash of event to filter
void rpc_get_logs(EthRpc &ethRpc);


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// Main
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    jsonrpc::HttpClient httpClient(nodeRpcUrl);
    EthRpc ethRpc(httpClient);
    try {
        rpc_get_logs(ethRpc);
    }
    catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
    }
    exit(EXIT_SUCCESS);
}


// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////
// Function definitions
// //////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////

void rpc_get_logs(EthRpc &ethRpc) {
    auto endBlk = std::stoul(ethRpc.eth_blockNumber(), nullptr, 16);
    auto startBlk = endBlk - 500;
    std::stringstream ss;
    ss << std::hex << std::showbase << startBlk;
    Json::Value params;
    params["fromBlock"] = ss.str();
    params["toBlock"] = "latest";
    params["address"] = ensAddress;
    Json::Value topics;
    params["topics"] = topics;

    auto logs = ethRpc.eth_getLogs(params);
    for (const auto &log: logs) {
        std::cout << "[" << log["blockNumber"] << "]: " << log["transactionHash"] << "\n";
        for (int i = 0; i < log["topics"].size(); ++i) {
            std::cout << "\t[" + std::to_string(i) + "]:" + log["topics"][i].asString() + "\n";
        }
        std::cout << "\n";
    }
}

