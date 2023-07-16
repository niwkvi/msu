#include <iostream>

#include "Mem.h"
#include "Table.h"
#include "TableTest.h"

int main() {
    int memSize = 10'000'000;
    int num = 1'000'000;

    Mem mem(memSize);
    Table table(mem);

    TableTest::insertByKeyTest(table, num);
    TableTest::findByKeyTest(table, num);
    TableTest::removeByKeyTest(table, num);
    TableTest::removeTest(table, num);
    TableTest::clearTest(table, num);
    TableTest::iteratorTest(table, num);
    TableTest::sizeTest(table, num);
    TableTest::timeTest(table, num);

    cout << "Test is over :)" << endl;

    return 0;
}
