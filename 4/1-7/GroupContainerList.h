#pragma once

#include "List.h"

class GroupContainerList: public List {
public:

    explicit GroupContainerList(MemoryManager &mem): List(mem) {}

    Iterator* find(void* elem, size_t size) override {
        auto* iter = dynamic_cast<ListIterator*>(newIterator());
        if (iter == nullptr)
            return nullptr;

        while (iter->currentElement != nullptr) {
            if (memcmp(elem, iter->currentElement->data, size) == 0)
                break;
            else if (iter->hasNext())
                iter->goToNext();
            else
                return nullptr;
        }
        if (iter->currentElement == nullptr) {
            delete iter;
            return nullptr;
        }
        return iter;
    }
};
