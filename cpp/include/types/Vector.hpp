#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "types/Exceptions.hpp"

#include <cstdlib>
#include <memory>
#include <cstring>
#include <initializer_list>

template <typename T>
class Vector {
    std::unique_ptr<T[]> memory = nullptr;
    size_t allocatedSize = 0;
    size_t count = 0;
public:
    Vector() : allocatedSize(0), count(0), memory(nullptr) {}
    
    Vector(size_t size, const T& value) {
        reserve(size);
        for (size_t i = 0; i < size; i++) push(value);
    }

    Vector(const Vector<T>& other) {
        if (other.size() > 0) {
            reserve(other.size());
            for (const auto& value: other) push(value);
        }
    }

    Vector(Vector<T>&& other) {
        if (other.size() > 0) {
            reserve(other.size());
            std::move(other.memory.get(), std::next(other.memory.get(), other.size()), memory.get());
            count = other.count;
            other.count = 0;
            other.allocatedSize = 0;
        }
    }

    Vector(std::initializer_list<T> list) {
        reserve(list.size());
        for (auto& value: list) push(value);
    }

    T& operator=(const Vector<T>& other) {
        clear();
        reserve(other.size());
        for (const auto& value: other) push(value);
    }

    T& operator=(Vector<T>&& other) {
        clear();
        if (other.size > 0) {
            reserve(other.size());
            std::move(other.memory.get(), std::next(other.memory.get(), other.size()), memory.get());
            count = other.count;
            other.count = 0;
            other.allocatedSize = 0;
        }
    }

    T& operator[](size_t index) { 
        if (index >= count) throw IllegalIndexException(index); 
        return memory[index]; 
    }

    const T& operator[](size_t index) const { 
        if (index >= count) throw IllegalIndexException(index); 
        return memory[index]; 
    }

    bool operator==(const Vector<T>& other) const {
        if (size() != other.size()) return false;
        for(size_t i = 0; i < size(); i++) {
            if ((*this)[i] != other[i]) { return false; }
        }
        return true;
    }

    bool operator!=(const Vector<T>& other) const {
        return !((*this) == other);
    }

    typedef T* iterator; 
    typedef const T* const_iterator;

    constexpr iterator begin() noexcept { 
        return iterator(memory.get()); 
    }

    constexpr const_iterator cbegin() noexcept { 
        return const_iterator(memory.get()); 
    }

    constexpr iterator begin() const noexcept { 
        return iterator(memory.get()); 
    }

    constexpr const_iterator cbegin() const noexcept { 
        return const_iterator(memory.get()); 
    }

    constexpr iterator end() noexcept { 
        return iterator(memory.get() + size()); 
    }

    constexpr const_iterator cend() noexcept { 
        return const_iterator(memory.get() + size()); 
    }

    constexpr iterator end() const noexcept { 
        return iterator(memory.get() + size()); 
    }

    constexpr const_iterator cend() const noexcept { 
        return const_iterator(memory.get() + size()); 
    }    

    bool empty() const noexcept { 
        return count == 0; 
    }

    size_t size() const noexcept { 
        return count; 
    }

    size_t capacity() const noexcept { 
        return allocatedSize; 
    }

    void reserve(size_t newSize) {
        if (newSize <= capacity()) return; 
        T* newMemory = new T[newSize];
        if (size() > 0) memcpy((void*)(newMemory), (void*)(memory.get()), sizeof(T) * size());
        memory.reset(newMemory);
        allocatedSize = newSize;
    } 

    void resize(size_t newSize, const T& value = {}) {
        if (newSize == size()) {
            return;
        } else if (newSize < size()) {
            for(size_t i = 0; i < size() - newSize; i++) pop();
        } else {
            for(size_t i = 0; i < newSize - size(); i++) push(value);
        }
    }

    void push(const T& element) {
        if (count + 1 > capacity()) reserve((allocatedSize == 0 ? 1 : allocatedSize * 2));
        memory.get()[count] = element;
        count++;
    }

    void push(T&& element) {
        if (count + 1 > capacity()) reserve((allocatedSize == 0 ? 1 : allocatedSize * 2));
        memory.get()[count] = std::move(element);
        count++;
    }

    void insert(size_t at, const T& value) {
        if (at >= size()) throw IllegalIndexException(at);
        push(last());
        for(size_t i = size() - 1; i > at; i--) ((*this)[i]) = std::move((*this)[i - 1]);
        ((*this)[at]) = value;
    }

    void erase(size_t at) {
        T& element = (*this)[at];
        for(size_t i = at + 1; i < count; i++) (*this)[i - 1] = std::move((*this)[i]);
        count--;
    }

    void pop() {
        erase(size() - 1);
    }  

    void clear() noexcept {
        for (size_t i = 0; i < count; i++) pop();
    }

    void deallocate() noexcept {
        clear();
        memory.reset(nullptr);
        allocatedSize = 0;
    }

    const T& first() const {
        return (*this)[0];
    }

    const T& last() const {
        return (*this)[size() - 1];
    }

    void fill(const T& value) noexcept { 
        for(size_t i = 0; i < size(); i++) memory[i] = value;
    }

    void swap(size_t a, size_t b) {
        T tmp = std::move(memory[a]);
        memory[a] = std::move(memory[b]);
        memory[b] = std::move(tmp);
    }
};

#endif