#ifndef TREE_HPP
#define TREE_HPP

#include <cstdlib>
#include "types/Array.hpp"
#include "types/Optional.hpp"

template <typename T, size_t S>
struct Tree {
    T value;
    Array<Optional<Tree<T, S>>, S> children;
    bool isLeaf() { return children.length == 0; } 
};

#endif