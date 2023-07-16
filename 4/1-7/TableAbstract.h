#pragma once

#include "GroupContainer.h"

// Абстрактный класс: ассоциативная таблица
class AbstractTable: public GroupContainer {
public:
    // конструктор
    explicit AbstractTable(MemoryManager &mem): GroupContainer(mem) {}

    // деструктор
    virtual ~AbstractTable() = default;

    // Добавление элемента в контейнер, с соответствующим ключом.
    // В случае успешного добавления функция возвращает значение 0, в случае неудачи 1.
    virtual int insertByKey(void *key, size_t keySize, void *elem, size_t elemSize) = 0;

    // Удаление элемента с соответствующим ключом из контейнера.
    virtual void removeByKey(void *key, size_t keySize) = 0;

    // Функция возвращает указатель на итератор, указывающий на найденный в контейнере элемент с соответствующим ключом.
    // Если элемент не найден, возвращается нулевой указатель.
    virtual Iterator* findByKey(void *key, size_t keySize) = 0;

    // доступ к элементу с ключом key
    virtual void* at(void *key, size_t keySize, size_t &valueSize) = 0;

    // хэш функция
    virtual size_t hash_function(void *key, size_t keySize) = 0;
};
