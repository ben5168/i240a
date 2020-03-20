#ifndef DLINK_SEQ_HH_
#define DLINK_SEQ_HH_

#include "seq.hh"

#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

template <typename E> class DLinkSeqConstIter;

template <typename E>
class DLinkSeq : public Seq<E> {
    friend class DLinkSeqConstIter<E>;

    struct Node {
        Node* prev;
        Node* next;
        Node(Node* prev = nullptr, Node* next = nullptr): prev(prev), next(next) {
            if (prev) prev->next = this;
            if (next) next->prev = this;
        }
        virtual ~Node() {
            if (prev) prev->next = next;        
            if (next) next->prev = prev;        
        }
    };

    struct DataNode : public Node{
        E val;
        DataNode(E e, Node* prev = nullptr, Node* next = nullptr): Node(prev, next), val(e) {};
    };

    Node sentinel{&sentinel, &sentinel};
    int len = 0;

    void insertAfter(Node* node, E item){
        new DataNode(item, node, node->next);
        len++;
    }

    E remove(DataNode* node){
        assert(node && "shift on empty DLink seq");
        E val = node->val;
        delete node;
        len--;
        return val;
    }

public:
    DLinkSeq() = default;

    static SeqPtr<E> make() {
        return std::make_unique<DLinkSeq<E>>();
    }

    ~DLinkSeq() override {
        clear();
    }
 
    void clear() override {
        while (sentinel.prev != &sentinel) {
            delete sentinel.prev;
        }
        len = 0;
    }

    void unshift(const E& item) override {
        insertAfter(&sentinel, item);
    }

    void push(const E& item) override {
        insertAfter(sentinel.prev, item);
    }

    E shift() {
        return remove(dynamic_cast<DataNode*>(sentinel.next));
    }

    E pop(){
        return remove(dynamic_cast<DataNode*>(sentinel.prev));
    }

    int size() const override { return len; }

    ConstIterPtr<E> cbegin() const override {
        return std::make_unique<DLinkSeqConstIter<E>>(sentinel.next);
    }

    ConstIterPtr<E> cend() const override {
        return std::make_unique<DLinkSeqConstIter<E>>(const_cast<Node*>(&sentinel));
    }
};

template <typename E>
class DLinkSeqConstIter : public ConstIter<E> {
    using Node = typename DLinkSeq<E>::Node;
    using DataNode = typename DLinkSeq<E>::DataNode;
    Node* current;

public:
    DLinkSeqConstIter(Node* current): current(current) {}
    
    DLinkSeqConstIter& operator++() {
        current = current->next;
        return *this;
    }

    //pre-decrement
    DLinkSeqConstIter& operator--() {
        current = current->prev;
        return *this;
    }

    //return true iff this ptr is not NULL 
    operator bool() override {
        return dynamic_cast<DataNode*>(current);
    }

    //return element this is pointing to
    const E& operator*() override {
        return dynamic_cast<DataNode*>(current)->val;
    }
    
    const E* operator->() override {
        return &(dynamic_cast<DataNode*>(current)->val);
    }
};

#endif





