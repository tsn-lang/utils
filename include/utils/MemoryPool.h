#pragma once
#include <utils/types.h>
#include <utils/Array.h>

namespace utils {
    class MemoryPool {
        public:
            MemoryPool(u32 elementSize, u32 elementsPerPool, bool doZeroMem);
            ~MemoryPool();

            void reset();
            void* alloc();
            void free(void* mem);

        protected:
            void createNewPool();
            
            struct Pool {
                u8* mem;
                u32 used;
            };

            bool m_doZeroMem;
            u32 m_elementSize;
            u32 m_elementsPerPool;
            Array<Pool> m_pools;
            Array<u8*> m_freeElems;
    };
};