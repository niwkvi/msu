#include "Table.h"

Table::TableIterator::TableIterator(Table* table, int index, GroupContainerList::Iterator* listIterator) :
                                    GroupContainer::GroupIterator(table, index, listIterator) {}

void* GroupContainer::GroupIterator::getElement(size_t &size) {
    if (listIterator == nullptr) {
        size = 0;
        return nullptr;
    }

    size_t sz = sizeof(size_t);
    size_t keySize = 0;
    size_t elemSize = 0;
    size_t temp = 0;

    if (listIterator->getElement(temp) == nullptr) return nullptr;

    char* data = static_cast<char*>(listIterator->getElement(temp));

    memcpy(&keySize, data, sz);
    memcpy(&elemSize, data + sz + keySize, sz);

    size = elemSize;

    return data + sz + keySize + sz;
}

Table::Table(MemoryManager &mem) : AbstractTable(mem) {}

int Table::insertByKey(void* key, size_t keySize, void* elem, size_t elemSize) {
    size_t size = sizeof(size_t);

    size_t keySizeAndKeySize = size + keySize;
    size_t dataSize = keySizeAndKeySize + size + elemSize;

    char* keySizeAndKey = (char*)_memory.allocMem(keySizeAndKeySize);
    char* data = (char*)_memory.allocMem(dataSize);

    memcpy(keySizeAndKey, &keySize, size);
    memcpy(keySizeAndKey + size, key, keySize);

    memcpy(data, &keySize, size);
    memcpy(data + size, key, keySize);
    memcpy(data + size + keySize, &elemSize, size);
    memcpy(data + size + keySize + size, elem, elemSize);

    return groupInsert(key, keySize, data, dataSize, keySizeAndKeySize);
}

void Table::removeByKey(void* key, size_t keySize) {
    auto* iterator = findByKey(key, keySize);
    remove(iterator);
    delete dynamic_cast<GroupIterator*>(iterator);
}

Container::Iterator* Table::findByKey(void* key, size_t keySize) {
    size_t size = sizeof(size_t);
    size_t keySizeAndKeySize = size + keySize;

    char* keySizeAndKey = (char*)_memory.allocMem(keySizeAndKeySize);

    memcpy(keySizeAndKey, &keySize, size);
    memcpy(keySizeAndKey + size, key, keySize);

    return groupFind(key, keySize, keySizeAndKey, keySizeAndKeySize);
}

void* Table::at(void* key, size_t keySize, size_t &valueSize) {
    auto* iterator = dynamic_cast<GroupIterator*>(findByKey(key, keySize));
    if (iterator == nullptr) return nullptr;
    return iterator->getElement(valueSize);
}

size_t Table::hash_function(void* key, size_t keySize) {
    return groupHashFunction(key, keySize);
}

Container::Iterator* Table::find(void* elem, size_t size) {
    size_t elemSize = 0;

    Container::Iterator* iterator = newIterator();
    if (iterator == nullptr) return nullptr;

    do {
        void* elemFound = iterator->getElement(elemSize);
        if (elemSize == size) {
            if (memcmp(elemFound, elem, size) == 0) return iterator;
        }
        if (iterator->hasNext()) iterator->goToNext();
        else break;
    } while (true);

    delete dynamic_cast<GroupIterator*>(iterator);

    return nullptr;
}

Container::Iterator* Table::newIterator() {
    for (int i = 0; i < SIZE; i++) {
        if (table[i] != nullptr && !table[i]->empty())
            return new TableIterator(this, i, dynamic_cast<GroupContainerList::Iterator*>(table[i]->newIterator()));
    }
    return new TableIterator(this, SIZE,nullptr);
}
