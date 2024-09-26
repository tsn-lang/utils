#include <utils/MemoryPool.h>
#include <utils/Array.hpp>

namespace utils {
    MemoryPool::MemoryPool(u32 elementSize, u32 elementsPerPool, bool doZeroMem) {
        m_doZeroMem = doZeroMem;
        m_elementSize = elementSize;
        m_elementsPerPool = elementsPerPool;
    }

    MemoryPool::~MemoryPool() {
        reset();
    }

    void MemoryPool::reset() {
        for (u32 i = 0;i < m_pools.size();i++) {
            delete [] m_pools[i].mem;
        }
        m_pools.clear(true);
    }

    void* MemoryPool::alloc() {
        if (m_freeElems.size() > 0) return m_freeElems.pop();
        for (u32 i = 0;i < m_pools.size();i++) {
            Pool& p = m_pools[i];
            if (p.used == m_elementsPerPool) continue;
            void* mem = p.mem + (p.used * m_elementSize);
            p.used++;
            return mem;
        }

        createNewPool();
        Pool& p = m_pools.last();
        p.used++;
        return p.mem;
    }

    void MemoryPool::free(void* mem) {
        if (m_doZeroMem) memset(mem, 0, m_elementSize);
        m_freeElems.push((u8*)mem);
    }

    void MemoryPool::createNewPool() {
        m_pools.push({
            new u8[m_elementSize * m_elementsPerPool],
            0
        });

        if (m_doZeroMem) memset(m_pools.last().mem, 0, m_elementSize * m_elementsPerPool);
    }
};