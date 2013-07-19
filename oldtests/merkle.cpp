//#include <bitcoin/storage/postgresql_storage.hpp>
#include <bitcoin/utility/assert.hpp>
#include <bitcoin/utility/sha256.hpp>
#include <bitcoin/utility/logger.hpp>
#include <bitcoin/transaction.hpp>
#include <bitcoin/error.hpp>
#include <iostream>
#include <memory>

using std::shared_ptr;
using namespace libbitcoin;

void recv_block(std::error_code ec, libbitcoin::message::block block)
{
    if (ec)
    {
        std::cerr << ec.message() << "\n";
        return;
    }
    BITCOIN_ASSERT(block.transactions.size() == 2);
    libbitcoin::hash_digest h1 = libbitcoin::hash_transaction(block.transactions[0]),
            h2 = libbitcoin::hash_transaction(block.transactions[1]);
    libbitcoin::hash_digest merkle = libbitcoin::generate_merkle_root(block.transactions);
    BITCOIN_ASSERT((merkle == libbitcoin::hash_digest{0x7d, 0xac, 0x2c, 0x56, 0x66, 0x81, 0x5c, 0x17, 0xa3, 0xb3, 0x64, 0x27, 0xde, 0x37, 0xbb, 0x9d, 0x2e, 0x2c, 0x5c, 0xce, 0xc3, 0xf8, 0x63, 0x3e, 0xb9, 0x1a, 0x42, 0x05, 0xcb, 0x4c, 0x10, 0xff}));
}

typedef std::vector<libbitcoin::hash_digest> hash_list;
namespace libbitcoin {
    hash_digest build_merkle_tree(hash_list& merkle);
}

void test_build_merkle()
{
    // Block 100000
    hash_list tx_hashes;
    tx_hashes.push_back(libbitcoin::hash_digest{0x8c, 0x14, 0xf0, 0xdb, 0x3d, 0xf1, 0x50, 0x12, 0x3e, 0x6f, 0x3d, 0xbb, 0xf3, 0x0f, 0x8b, 0x95, 0x5a, 0x82, 0x49, 0xb6, 0x2a, 0xc1, 0xd1, 0xff, 0x16, 0x28, 0x4a, 0xef, 0xa3, 0xd0, 0x6d, 0x87});
    tx_hashes.push_back(libbitcoin::hash_digest{0xff, 0xf2, 0x52, 0x5b, 0x89, 0x31, 0x40, 0x2d, 0xd0, 0x92, 0x22, 0xc5, 0x07, 0x75, 0x60, 0x8f, 0x75, 0x78, 0x7b, 0xd2, 0xb8, 0x7e, 0x56, 0x99, 0x5a, 0x7b, 0xdd, 0x30, 0xf7, 0x97, 0x02, 0xc4});
    tx_hashes.push_back(libbitcoin::hash_digest{0x63, 0x59, 0xf0, 0x86, 0x81, 0x71, 0xb1, 0xd1, 0x94, 0xcb, 0xee, 0x1a, 0xf2, 0xf1, 0x6e, 0xa5, 0x98, 0xae, 0x8f, 0xad, 0x66, 0x6d, 0x9b, 0x01, 0x2c, 0x8e, 0xd2, 0xb7, 0x9a, 0x23, 0x6e, 0xc4});
    tx_hashes.push_back(libbitcoin::hash_digest{0xe9, 0xa6, 0x68, 0x45, 0xe0, 0x5d, 0x5a, 0xbc, 0x0a, 0xd0, 0x4e, 0xc8, 0x0f, 0x77, 0x4a, 0x7e, 0x58, 0x5c, 0x6e, 0x8d, 0xb9, 0x75, 0x96, 0x2d, 0x06, 0x9a, 0x52, 0x21, 0x37, 0xb8, 0x0c, 0x1d});
    libbitcoin::hash_digest merkle_root = libbitcoin::build_merkle_tree(tx_hashes);
    BITCOIN_ASSERT((merkle_root == libbitcoin::hash_digest{0xf3, 0xe9, 0x47, 0x42, 0xac, 0xa4, 0xb5, 0xef, 0x85, 0x48, 0x8d, 0xc3, 0x7c, 0x6, 0xc3, 0x28, 0x22, 0x95, 0xff, 0xec, 0x96, 0x9, 0x94, 0xb2, 0xc0, 0xd5, 0xac, 0x2a, 0x25, 0xa9, 0x57, 0x66}));
}

void test_match_merkles(std::error_code ec, libbitcoin::message::block block)
{
    BITCOIN_ASSERT(block.merkle == libbitcoin::generate_merkle_root(block.transactions));
}

void test_sha256()
{
    data_chunk in{'h', 'e', 'l', 'l', 'o'};
    //log_debug() << encode_hex(libbitcoin::generate_sha256_hash(in));
    //BITCOIN_ASSERT((libbitcoin::generate_sha256_hash(in) == libbitcoin::hash_digest{0x95, 0x95, 0xc9, 0xdf, 0x90, 0x07, 0x51, 0x48, 0xeb, 0x06, 0x86, 0x03, 0x65, 0xdf, 0x33, 0x58, 0x4b, 0x75, 0xbf, 0xf7, 0x82, 0xa5, 0x10, 0xc6, 0xcd, 0x48, 0x83, 0xa4, 0x19, 0x83, 0x3d, 0x50}));
    BITCOIN_ASSERT((libbitcoin::generate_sha256_hash(in) == libbitcoin::hash_digest{0x50, 0x3d, 0x83, 0x19, 0xa4, 0x83, 0x48, 0xcd, 0xc6, 0x10, 0xa5, 0x82, 0xf7, 0xbf, 0x75, 0x4b, 0x58, 0x33, 0xdf, 0x65, 0x03, 0x86, 0x06, 0xeb, 0x48, 0x51, 0x07, 0x90, 0xdf, 0xc9, 0x95, 0x95}));
}

int main()
{
    test_sha256();
    test_build_merkle();

    //psql_ptr psql(new postgresql_storage("bitcoin", "genjix", ""));
    //psql->fetch_block_by_height(170, recv_block);
    //psql->fetch_block_by_height(2, test_match_merkles);
    return 0;
}

