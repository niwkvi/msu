#pragma once

#include "TableAbstract.h"
#include "MemoryManager.h"
#include "GroupContainer.h"

class Table : public AbstractTable {
public:

    class TableIterator: public GroupContainer::GroupIterator {
    public:
        TableIterator(Table* table, int index, List::Iterator* iterator);
    };

    explicit Table(MemoryManager &mem);
    ~Table() override = default;

    int insertByKey(void* key, size_t keySize, void* elem, size_t elemSize) override;
    void removeByKey(void* key, size_t keySize) override;
    Container::Iterator* findByKey(void* key, size_t keySize) override;
    void* at(void* key, size_t keySize, size_t &valueSize) override;
    size_t hash_function(void* key, size_t keySize) override;

    Container::Iterator* find(void* elem, size_t size) override;
    Container::Iterator* newIterator() override;
};
