#include "stdafx.h"
#pragma hdrstop


class mempool_t {
    size_t m_block_size;
    size_t m_num_blocks;

    char* m_block_alloc; // for the simplicty: 'A'-allocated, 'F'-free, we can use bitset to save memory
    void* m_stack_mem;
    uint8_t** m_block_stack; // fixed-size stack for quickest searching of free m_block_stack
    uint8_t* m_pool;

public:

    mempool_t(size_t block_size, size_t num_blocks) :
        m_block_size(block_size),
        m_num_blocks(num_blocks)
    {
        m_block_alloc = (char*)malloc(sizeof(*m_block_alloc) * m_num_blocks + 1); // +1 for debug status, we can see string like "AAFFA"
        m_stack_mem = malloc(sizeof(void*) * (m_num_blocks + 1));
        m_pool = (uint8_t*)malloc(m_num_blocks * m_block_size);

        std::memset(m_block_alloc, 0, sizeof(*m_block_alloc) * m_num_blocks + 1);
        m_block_stack = (uint8_t**)m_stack_mem;
        *m_block_stack = nullptr;

        for (size_t i = 0; i < m_num_blocks; ++i) {
            ++m_block_stack;
            *m_block_stack = m_pool + i * block_size;
            m_block_alloc[i] = 'F';
        }
    }

    ~mempool_t() {
        free(m_pool);
        free(m_stack_mem);
        free(m_block_alloc);
    }

    void* allocate_block() {
        if (*m_block_stack == nullptr)
            throw std::runtime_error("No blocks available");

        uint8_t* ptr = *m_block_stack;
        m_block_alloc[(ptr - m_pool) / m_block_size] = 'A';
        --m_block_stack;
        return ptr;
    }

    void free_block(void* vptr) {
        uint8_t* ptr = (uint8_t*)vptr;
        if (ptr == nullptr ||
            ptr < m_pool ||
            ((ptr - m_pool) % m_block_size) != 0 ||  // needs to aligned by block size
            (ptr > m_pool + (m_num_blocks - 1) * m_block_size) || // we cannot handle addresses exceed mem pool
            m_block_alloc[(ptr - m_pool) / m_block_size] == 'F') // this block is free already
            throw std::runtime_error("Cannot free block");

        m_block_alloc[(ptr - m_pool) / m_block_size] = 'F';
        ++m_block_stack;
        *m_block_stack = ptr;
    }

    const char* get_state() const {
        return m_block_alloc;
    }
};

static void testMemPool() 
{
    cout << "\n   >>> testMemPool <<<";
    size_t bs = 10; // block size
    size_t bn = 5;  // block num
    mempool_t mp1(bs, bn);
    vector<char*> blocks;

    for (size_t i = 0; i <= bn; ++i) // +1 block size to test overallocation
    {
        try {
            cout << "\n allocate block " << i + 1 << ", pool state: " << mp1.get_state() << ", :";
            char* ptr = (char*)mp1.allocate_block();
            string str = string(bs - 1, '1' + (char)i);
            strcpy(ptr, str.c_str());
            blocks.push_back(ptr);
            cout << (void*)ptr << ", copy value: " << str << ", pool state: " << mp1.get_state();
        }
        catch (std::exception e) {
            cout << "!!! Exception: " << e.what();
        }
    }

    cout << "\n\n Read blocks: ";
    for (auto block : blocks) {
        cout << "\nblock: " << (void*)block << ", value: " << block;
    }

    try {
        cout << "\n\n release wrong addres: ";
        mp1.free_block(blocks[1] + 1); // not aligned address
    }
    catch (std::exception e) {
        cout << e.what();
    }

    try {
        cout << "\n\n release lower addres " << (void*)(blocks[bn - 1] - 10) << ": ";
        mp1.free_block(blocks[bn - 1] - 10); // byeond of mem pool
    }
    catch (std::exception e) {
        cout << e.what();
    }

    try {
        cout << "\n\n release bigger addres " << (void*)(blocks[0] + 10) << ": ";
        mp1.free_block(blocks[0]+10); // byeond of mem pool
    }
    catch (std::exception e) {
        cout << e.what();
    }

    cout << "\n\n release second block :" << (void*)blocks[1] ;
    mp1.free_block(blocks[1]);
    cout << " pool state: " << mp1.get_state();

    cout << "\n\n allocate new block ";
    char* ptr = (char*)mp1.allocate_block();
    cout << (void*)ptr;
    strcpy(ptr, string(bs - 1, '#').c_str());
    cout << ", new value: " << ptr;
    cout << "\n pool state: " << mp1.get_state();

    cout << "\n\n Read blocks: ";
    for (auto block : blocks) {
        cout << "\nblock: " << (void*)block << ", value: " << block;
    }

    cout << "\n pool state: " << mp1.get_state();

    cout << "\n\n Release blocks: ";
    for (auto block : blocks) {
        cout << "\nblock: " << (void*)block;
        mp1.free_block(block);
        cout << " pool state: " << mp1.get_state();
    }

    cout << "\n\n Try to release blocks again: ";
    for (auto block : blocks) {
        try {
            cout << "\nblock: " << (void*)block;
            mp1.free_block(block);
        }
        catch (std::exception e) {
            cout << " !!! cannot release block";
        }
    }

}

int main11(int argc, char** argv)
{
    cout << "\n *** main-11 ***";
    testMemPool();
    return 0;

}