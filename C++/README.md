# C++ Data Structures - Lab 3

## Описание

Реализация основных абстрактных структур данных на C++ с использованием принципов ООП.

## Структуры данных

1. **Array** - Динамический массив
2. **LinkedList** - Односвязный список
3. **DoubleLinkedList** - Двусвязный список
4. **Queue** - Очередь (FIFO)
5. **Stack** - Стек (LIFO)
6. **HashTable** - Хеш-таблица с разрешением коллизий методом цепочек
7. **BinarySearchTree** - Бинарное дерево поиска

## Особенности реализации

- ✅ Многофайловая структура проекта
- ✅ Разделение на private/public секции
- ✅ Конструкторы копирования и операторы присваивания
- ✅ Деструкторы для корректного управления памятью
- ✅ Бинарная сериализация/десериализация
- ✅ Обработка исключений
- ✅ Google Test - один комплексный тест на структуру
- ✅ Makefile для сборки и тестирования

## Сборка и запуск

### Требования

- g++ с поддержкой C++17
- Google Test
- lcov (для генерации отчетов о покрытии)

### Установка зависимостей (macOS)

```bash
brew install googletest lcov
```

### Сборка основной программы

```bash
make all
make run
```

### Запуск тестов

```bash
make test
```

### Генерация отчета о покрытии кода

```bash
make coverage
```

Отчет будет доступен в `coverage/html/index.html`

### Очистка

```bash
make clean
```

## Структура проекта

```
C++/
├── include/          # Заголовочные файлы
│   ├── Array.h
│   ├── LinkedList.h
│   ├── DoubleLinkedList.h
│   ├── Queue.h
│   ├── Stack.h
│   ├── HashTable.h
│   └── BinarySearchTree.h
├── src/              # Реализация
│   ├── Array.cpp
│   ├── LinkedList.cpp
│   ├── DoubleLinkedList.cpp
│   ├── Queue.cpp
│   ├── Stack.cpp
│   ├── HashTable.cpp
│   └── BinarySearchTree.cpp
├── tests/            # Юнит-тесты
│   ├── test_array.cpp
│   ├── test_linkedlist.cpp
│   ├── test_doublelinkedlist.cpp
│   ├── test_queue.cpp
│   ├── test_stack.cpp
│   ├── test_hashtable.cpp
│   └── test_bst.cpp
├── main.cpp          # Демонстрационная программа
├── Makefile          # Makefile для сборки
└── README.md         # Этот файл
```

## Примеры использования

### Array

```cpp
#include "include/Array.h"

Array arr;
arr.append("Hello");
arr.append("World");
std::cout << arr.get(0) << std::endl;  // "Hello"

// Сериализация
std::ofstream out("data.bin", std::ios::binary);
arr.serialize(out);
out.close();
```

### Stack

```cpp
#include "include/Stack.h"

Stack stack;
stack.push("first");
stack.push("second");
std::cout << stack.pop() << std::endl;  // "second"
```

### HashTable

```cpp
#include "include/HashTable.h"

HashTable ht;
ht.insert("name", "John");
ht.insert("age", "25");
std::cout << ht.get("name") << std::endl;  // "John"
```

### Binary Search Tree

```cpp
#include "include/BinarySearchTree.h"

BinarySearchTree bst;
bst.insert("dog");
bst.insert("cat");
bst.insert("elephant");

if (bst.search("cat")) {
    std::cout << "Found!" << std::endl;
}
```

## Тестирование

Проект использует Google Test framework. Все тесты находятся в директории `tests/`.

**Реализовано по одному комплексному тесту для каждой структуры данных:**
- `test_array.cpp` - Comprehensive тест для Array
- `test_linkedlist.cpp` - Comprehensive тест для LinkedList
- `test_doublelinkedlist.cpp` - Comprehensive тест для DoubleLinkedList
- `test_queue.cpp` - Comprehensive тест для Queue
- `test_stack.cpp` - Comprehensive тест для Stack
- `test_hashtable.cpp` - Comprehensive тест для HashTable
- `test_bst.cpp` - Comprehensive тест для BinarySearchTree

Каждый тест покрывает:
- Базовые операции (вставка, удаление, поиск)
- Граничные случаи (пустая структура, переполнение)
- Исключения
- Копирование и присваивание
- Сериализацию/десериализацию

## Сериализация

Все структуры поддерживают бинарную сериализацию и десериализацию:

```cpp
// Запись
std::ofstream out("data.bin", std::ios::binary);
structure.serialize(out);
out.close();

// Чтение
std::ifstream in("data.bin", std::ios::binary);
structure.deserialize(in);
in.close();
```

## Линтеры (опционально)

Для улучшения качества кода рекомендуется использовать:
- `clang-tidy`
- `cppcheck`

```bash
clang-tidy src/*.cpp -- -Iinclude
cppcheck --enable=all --inconclusive src/
```
