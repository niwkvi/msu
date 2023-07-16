#pragma once

#include "Container.h"
#include "GroupContainerList.h"

class GroupContainer: public Container {
public:
    static const size_t SIZE = 10'000'000;
    GroupContainerList** table;
    int num = 0;

    class GroupIterator: public Container::Iterator {
    public:
        GroupContainer* container;
        int index;
        GroupContainerList::Iterator* listIterator;

        GroupIterator(GroupContainer* container, int index, GroupContainerList::Iterator* listIterator) :
            container(container),
            index(index),
            listIterator(listIterator) {}

        ~GroupIterator() {
            container = nullptr;
            listIterator = nullptr;
        }

        // Table and Set have different implementations
        void* getElement(size_t &size) override;

        bool hasNext() override {
            if (listIterator == nullptr) return false;
            if (listIterator->hasNext()) return true;
            for (int i = index + 1; i < SIZE; i++) {
                if (container->table[i] != nullptr && !container->table[i]->empty()) return true;
            }
            return false;
        }

        void goToNext() override {
            if (listIterator == nullptr) return;

            if (listIterator->hasNext()) {
                listIterator->goToNext();
                return;
            }

            for (int i = index + 1; i < SIZE; i++) {
                if (container->table[i] != nullptr && !container->table[i]->empty()) {
                    index = i;
                    delete dynamic_cast<GroupContainerList*>(listIterator);
                    listIterator = dynamic_cast<GroupContainerList::Iterator*>(container->table[i]->newIterator());
                    return;
                }
            }
        }

        bool equals(Iterator* right) override {
            if (listIterator == nullptr || right == nullptr) return false;
            return listIterator->equals((dynamic_cast<GroupIterator*>(right))->listIterator);
        }
    };

    explicit GroupContainer(MemoryManager &mem): Container(mem) {
        table = new (mem.allocMem(SIZE * sizeof(GroupContainerList*))) GroupContainerList*[SIZE];
        for (int i = 0; i < SIZE; i++) table[i] = nullptr;
    }

    ~GroupContainer() {
        GroupContainer::clear();
    }

    // Set (elem, elemSize, elem, elemSize, elemSize)
    // Table (key, keySize, keySize+key+elemSize+elem, sizeof(keySize+key+elemSize+elem), sizeof(keySize+key))
    int groupInsert(void* key, size_t keySize, void* data, size_t dataSize, size_t keySizeAndKeySize) {
        size_t index = groupHashFunction(key, keySize);

        if (table[index] == nullptr)
            table[index] = new (_memory.allocMem(sizeof(GroupContainerList))) GroupContainerList(_memory);

        GroupContainerList* list = table[index];
        Container::Iterator* iterator = nullptr;

        if (!list->empty()) iterator = list->find(data, keySizeAndKeySize);

        if (iterator == nullptr) {
            list->push_front(data, dataSize);
            num++;
            return 0;
        }

        delete dynamic_cast<GroupIterator*>(iterator);

        return 1;
    }

    // Set (elem, elemSize, elem, elemSize)
    // Table (key, keySize, keySize+key, sizeof(keySize+key))
    GroupIterator* groupFind(void* key, size_t keySize, void* keySizeAndKey, size_t keySizeAndKeySize) {
        size_t index = groupHashFunction(key, keySize);

        GroupContainerList* list = table[index];

        if (list == nullptr || list->empty()) return nullptr;

        Container::Iterator *iterator = nullptr;

        iterator = list->find(keySizeAndKey, keySizeAndKeySize);

        if (iterator == nullptr) return nullptr;

        return new GroupIterator(this, (int)index, dynamic_cast<GroupContainerList::Iterator*>(iterator));
    }

    static size_t groupHashFunction(void* key, size_t keySize) {
        char* keyChar = static_cast<char*>(key);
        size_t hash = 5381;
        for (int i = 0; i < keySize; i++) hash = 33 * hash + keyChar[i];
        return hash % SIZE;
    }

    int size() override {
        return num;
    }

    size_t max_bytes() override {
        return _memory.maxBytes();
    }

    void remove(Iterator* iter) override {
        if (iter == nullptr) return;

        auto* iterator = dynamic_cast<GroupIterator*>(iter);
        GroupContainerList* list = table[iterator->index];

        if (list == nullptr || list->empty()) return;

        list->remove(iterator->listIterator);
        num--;

        size_t size = 0;

        if (iterator->getElement(size) == nullptr) {
            if (list->empty()) {
                _memory.freeMem(table[iterator->index]);
                table[iterator->index] = nullptr;
            }
            
            if (iterator->hasNext()) iterator->goToNext();
            else {
                delete dynamic_cast<GroupContainerList*>(iterator->listIterator);
                iterator->listIterator = nullptr;
                iterator->index = SIZE;
            }
        }
    }

    void clear() override {
        for (int i = 0; i < SIZE; i++) {
            if (table[i] != nullptr) {
                table[i]->clear();
                table[i] = nullptr;
            }
        }
        num = 0;
    }

    bool empty() override {
        return size() == 0;
    }

};
