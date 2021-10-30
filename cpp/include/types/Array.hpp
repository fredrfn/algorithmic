#ifndef ARRAY_HPP
#define ARRAY_HPP

#include "types/Exceptions.hpp"

#include <cstdlib>

template <typename T, size_t S>
class Array {
    T items[S];
public:
    Array(T value = {}) noexcept {
        fill(value);
    }

    Array(Array<T, S>& other) noexcept { 
        for(size_t i = 0; i < size(); i++) {
            items[i] = other[i];
        }
    }

    Array(const Array<T, S>& other) noexcept { 
        for(size_t i = 0; i < size(); i++) {
            items[i] = other[i];
        }
    }

    Array<T, S>& operator=(Array<T, S>& other) {
        for(size_t i = 0; i < size(); i++) {
            items[i] = other[i];
        }
        return *this;
    }

    Array<T, S>& operator=(const Array<T, S>& other) {
        for(size_t i = 0; i < size(); i++) {
            items[i] = other[i];
        }
        return *this;
    }

    const T& operator[](size_t i) const { 
        if (i >= size()) {
            throw IllegalIndexException(i);
        }
        return items[i]; 
    }

    T& operator[](size_t i) { 
        if (i >= size()) {
            throw IllegalIndexException(i);
        }
        return items[i];
    }

    bool operator==(Array& other) const noexcept {
        for(size_t i = 0; i < size(); i++) {
            if(items[i] != other.items[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(Array& other) const noexcept {
        return !((*this) == other);
    }

    bool operator==(const Array& other) const noexcept {
        for(size_t i = 0; i < size(); i++) {
            if(items[i] != other.items[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Array& other) const noexcept {
        return !((*this) == other);
    }

    inline constexpr size_t size() const noexcept { 
        return S; 
    }

    void fill(T value) noexcept { 
        for(size_t i = 0; i < size(); i++)
            items[i] = value;
    }

    void swap(size_t a, size_t b) {
        if (a >= size() || b >= size()) {
            throw IllegalIndexException(a > b ? a : b);
        }
        T tmp = std::move(items[a]);
        items[a] = std::move(items[b]);
        items[b] = std::move(tmp);
    }

    T& first() noexcept {
        return items[0];
    }

    T& last() noexcept {
        return items[size() - 1];
    }

    const T& first() const noexcept {
        return items[0];
    }

    const T& last() const noexcept {
        return items[size() - 1];
    }

    typedef T* iterator; 
    typedef const T* const_iterator;

    constexpr iterator begin() noexcept { 
        return iterator(items); 
    }

    constexpr const_iterator cbegin() noexcept { 
        return const_iterator(items); 
    }

    constexpr iterator begin() const noexcept { 
        return iterator(items); 
    }

    constexpr const_iterator cbegin() const noexcept { 
        return const_iterator(items); 
    }

    constexpr iterator end() noexcept { 
        return iterator(items + size()); 
    }

    constexpr const_iterator cend() noexcept { 
        return const_iterator(items + size()); 
    }

    constexpr iterator end() const noexcept { 
        return iterator(items + size()); 
    }

    constexpr const_iterator cend() const noexcept { 
        return const_iterator(items + size()); 
    }    
};

#endif