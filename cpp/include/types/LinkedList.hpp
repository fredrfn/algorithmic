#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <cstdlib>
#include "types/Exceptions.hpp"
#include <array>

template <typename T>
struct LinkedListNode {
    T value;
    LinkedListNode<T>* next = nullptr;
    LinkedListNode(T value, LinkedListNode<T>* next = nullptr) : value(value), next(next) {}
};

template <typename T>
class LinkedList {
    LinkedListNode<T>* head;

    LinkedListNode<T>* getNode(size_t at) const noexcept {
        LinkedListNode<T>* current = head;        
        for (size_t i = 0; i < at; i++) {
            if (current == nullptr) return nullptr;
            current = current->next;
        }
        return current;
    }

    void clear(LinkedListNode<T>* node) {
        if (node == nullptr) return;
        if (node->next != nullptr) clear(node->next);
        delete node;
    } 
public:
    class Iterator {
        friend class LinkedList;
    private:
        LinkedListNode<T>* current;
        public:
        Iterator(LinkedListNode<T> *current = nullptr) : current(current) {}
        bool operator==(Iterator& other) noexcept { return current == other.current; } 
        bool operator!=(Iterator& other) noexcept { return current != other.current; } 
        T& operator*() const { return current->value; }
        Iterator operator++() {
            Iterator tmp = Iterator(current);
            if(current != nullptr) {
                current = current->next;
            }
            return tmp;
        }
    };

    typedef Iterator iterator;
    iterator begin() const { return iterator(head);  }
    iterator end() const { return iterator(nullptr); }

    LinkedList() : head(nullptr) {}

    LinkedList(LinkedList<T>& other) { 
        head = nullptr; 
        for(auto& value: other) push(value); 
    }
    
    LinkedList(const LinkedList<T>& other) { 
        head = nullptr; 
        for(auto& value: other) push(value); 
    }
    
    LinkedList(LinkedList<T>&& other) { 
        head = other.head; 
        other.head = nullptr; 
    }
    
    ~LinkedList() { 
        clear(); 
    }

    LinkedList& operator=(LinkedList<T>& other) noexcept { 
        clear(); 
        for(auto& value: other) push(value); 
        return *this;
    }
    
    LinkedList& operator=(const LinkedList<T>& other) noexcept { 
        clear(); 
        for(auto& value: other) push(value); 
        return *this;
    }
    
    LinkedList& operator=(LinkedList<T>&& other) noexcept {
        head = other->head; 
        other->head = nullptr; 
        return *this;
    }

    T& operator[](size_t at) { 
        LinkedListNode<T>* node = getNode(at);
        if (node == nullptr) throw IllegalIndexException(at);
        return node->value;
    }

    const T& operator[](size_t at) const {
        LinkedListNode<T>* node = getNode(at);
        if (node == nullptr) throw IllegalIndexException(at);
        return node->value;
    }

    bool operator==(LinkedList<T>& other) const noexcept {
        size_t length = size();
        if (length != other.size()) return false;
        for(size_t i = 0; i < length; i++) {
            if ((*this)[i] != other[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator==(const LinkedList<T>& other) const noexcept {
        size_t length = size();
        if (length != other.size()) return false;
        for(size_t i = 0; i < length; i++) {
            if ((*this)[i] != other[i]) {
                return false;
            }
        }
        return true;
    }

    bool operator!=(LinkedList<T>& other) const noexcept {
        return !((*this) == other);
    }

    bool operator!=(const LinkedList<T>& other) const noexcept {
        return !((*this) == other);
    }

    bool empty() const noexcept { 
        return size() == 0; 
    }

    size_t size() const noexcept {
        if (head == nullptr) return 0;

        LinkedListNode<T>* current = head;
        size_t count = 1;
        while (current->next != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }

    void push(const T& value) noexcept {
        LinkedListNode<T>* added = new LinkedListNode<T>(value, nullptr);
        if(empty()) {
            head = added;
        } else {
            LinkedListNode<T>* tail = head;
            while(tail->next != nullptr) tail = tail->next;
            tail->next = added;
        }
    }

    void pop() noexcept {
        if (empty()) return;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
        } else {
            LinkedListNode<T>* previous = head;
            while(previous != nullptr && previous->next != nullptr && previous->next->next != nullptr) previous = previous->next;
            delete previous->next;
            previous->next = nullptr;
        }  
    }

    void insertBefore(size_t at, const T& value) {
        if (at == 0) {
            head = new LinkedListNode<T>(value, head == nullptr ? nullptr : head->next);
        } else {
            insertAfter(at - 1, value);
        }
    }

    void insertAfter(size_t at, const T& value) {
        LinkedListNode<T>* node = getNode(at);
        if (node == nullptr) throw IllegalIndexException(at);
        node->next = new LinkedListNode<T>(value, node->next);
    }

    void erase(size_t at) {
        LinkedListNode<T>* node = getNode(at);
        if (empty() || node == nullptr) throw IllegalIndexException(at);
        if (at == 0) {
            head = node->next;
            delete node;
        } else {
            LinkedListNode<T>* previous = head;
            while(previous->next != node) previous = previous->next;
            previous->next = node->next;
            delete node;
        }       
    } 

    void clear() {
        clear(head);
        head = nullptr;
    } 
};

#endif