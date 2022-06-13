#ifndef MEMORYMANAGER_H
#define MEMORYMANAGER_H

#include <cstddef>
#include <memory>


namespace Helpers {

/**
 * @brief Helper class for allocate memory with counter.
 */
class MemoryManager final {
    /**
     * @brief Size of allocated memory
     */
    size_t m_allocated{0U};
    /**
     * @brief Count of allocated units
     */
    size_t m_allocated_units{0U};

public:
    /**
     * @brief allocate
     * @param size
     * @return
     */
    void *allocate(size_t size) noexcept;

    /**
     * @brief free
     * @param ptr
     * @param size
     */
    void free(void * ptr, size_t size) noexcept;

    /**
     * @brief construct object
     * @tparam Type of cunstructed object
     * @param arguments for object constructor
     * @return pointer to constructed object
     */
    template <typename Type, typename ...Args>
    std::unique_ptr<Type> construct(Args &&... args) noexcept;

    /**
     * @brief allocated_units
     * @return
     */
    size_t allocated_units() const noexcept;

    /**
     * @brief allocated
     * @return
     */
    size_t allocated() const noexcept;
};

size_t MemoryManager::allocated() const noexcept
{
return m_allocated;
}

void *MemoryManager::allocate(size_t size) noexcept
{
    auto temp = ::malloc(size);
    if (temp != nullptr) {
        m_allocated += size;
        ++m_allocated_units;
    }
    return temp;
}

void MemoryManager::free(void *ptr, size_t size) noexcept
{
    if (ptr != nullptr) {
        ::free(ptr);
        m_allocated -= size;
        --m_allocated_units;
    }
}

size_t MemoryManager::allocated_units() const noexcept
{
    return m_allocated_units;
}

template<typename Type, typename ...Args>
std::unique_ptr<Type> MemoryManager::construct(Args &&...args) noexcept
{
    auto temp_ptr = static_cast<Type *>(allocate(sizeof(Type)));
    if (temp_ptr) {
        std::unique_ptr<Type> result{::new (temp_ptr) Type(std::forward(args)...)};
        return std::move(result);
    }
    return nullptr;
}

} // namespace Helpers

#endif // MEMORYMANAGER_H


