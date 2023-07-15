#pragma once

#include "ListAbstract.h"

class List: public AbstractList {
private:

    struct Element {
        void* data;
        size_t dataSize;
        Element* nextElement;
    };

public:

    Element* firstElement;
    int num = 0;

    class ListIterator: public Container::Iterator {
    public:

        Element* currentElement;

        explicit ListIterator(Element* currentElement) : currentElement(currentElement) {}

        void* getElement(size_t &size) override {
            if (currentElement == nullptr) {
                size = 0;
                return nullptr;
            }
            size = currentElement->dataSize;
            return currentElement->data;
        }

        bool hasNext() override {
            if (currentElement == nullptr || currentElement->nextElement == nullptr)
                return false;
            return true;
        }

        void goToNext() override {
            if (currentElement != nullptr && currentElement->nextElement != nullptr) {
                currentElement = currentElement->nextElement;
            }
        }

        bool equals(Iterator* right) override {
            auto* newRight = dynamic_cast<ListIterator*>(right);
            return currentElement == newRight->currentElement;
        }
    };

    explicit List(MemoryManager &mem) : AbstractList(mem), firstElement(nullptr) {}

    ~List() override {
        List::clear();
    }

    int push_front(void* elem, size_t elemSize) override {
        auto* frontElement = new Element;
        frontElement->data = static_cast<void*>(new char[elemSize]);
        if (frontElement->data == nullptr) {
            delete frontElement;
            return 1;
        }

        memcpy(frontElement->data, elem, elemSize);
        frontElement->dataSize = elemSize;
        frontElement->nextElement = firstElement;

        firstElement = frontElement;

        num++;

        return 0;
    }

    void pop_front() override {
        if (firstElement == nullptr)
            return;

        auto* secondElement = firstElement->nextElement;
        delete[]static_cast<char*>(firstElement->data);
        delete firstElement;

        firstElement = secondElement;

        num--;
    }

    void* front(size_t &size) override {
        if (firstElement == nullptr) {
            size = 0;
            return nullptr;
        }
        size = firstElement->dataSize;

        return firstElement->data;
    }

    int insert(Iterator* iter, void* elem, size_t elemSize) override {
        auto* newIter = dynamic_cast<ListIterator*>(iter);
        auto* findIter = dynamic_cast<ListIterator*>(newIterator());

        if (newIter->equals(findIter))
            return push_front(elem, elemSize);

        while (findIter->currentElement->nextElement != newIter->currentElement) {
            if (findIter->hasNext())
                findIter->goToNext();
        }

        auto* newElement = new Element();
        newElement->data = static_cast<void*>(new char[elemSize]);
        if (newElement->data == nullptr) {
            delete newElement;
            return 1;
        }

        memcpy(newElement->data, elem, elemSize);
        newElement->dataSize = elemSize;
        newElement->nextElement = findIter->currentElement->nextElement;

        findIter->currentElement->nextElement = newElement;
        delete findIter;

        num++;

        return 0;
    }

    int size() override {
        return num;
    }

    size_t max_bytes() override {
        return _memory.maxBytes();
    }

    Iterator* find(void* elem, size_t size) override {
        auto* iter = dynamic_cast<ListIterator*>(newIterator());
        if (iter == nullptr)
            return nullptr;

        while (iter->currentElement != nullptr) {
            if (size != iter->currentElement->dataSize) {
                if (iter->hasNext())
                    iter->goToNext();
                else
                    return nullptr;
                continue;
            }
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

    Iterator* newIterator() override {
        return new ListIterator(firstElement);
    }

    void remove(Iterator* iter) override {
        auto* newIter = dynamic_cast<ListIterator*>(iter);
        if (newIter->currentElement == nullptr)
            return;
        auto* findIter = dynamic_cast<ListIterator*>(newIterator());

        if (newIter->equals(findIter)) {
            pop_front();
            newIter->currentElement = firstElement;
            return;
        }

        while (findIter->currentElement->nextElement != newIter->currentElement) {
            if (findIter->hasNext())
                findIter->goToNext();
        }

        findIter->currentElement->nextElement = newIter->currentElement->nextElement;
        delete[]static_cast<char*>(newIter->currentElement->data);
        delete newIter->currentElement;

        newIter->currentElement = findIter->currentElement->nextElement;
        delete findIter;

        num--;
    }

    void clear() override {
        auto* element = firstElement;

        while (element != nullptr) {
            delete[]static_cast<char*>(element->data);
            auto* nextElement = element->nextElement;
            delete element;

            element = nextElement;
        }

        firstElement = nullptr;
        num = 0;
    }

    bool empty() override {
        if (firstElement == nullptr)
            return true;
        return false;
    }
};
