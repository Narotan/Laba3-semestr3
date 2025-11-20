# Лабораторная работа №3 - Объектно-ориентированное программирование

## Описание

Данная работа посвящена изучению основных принципов объектно-ориентированного программирования и юнит-тестирования. Проект включает реализацию абстрактных структур данных на **C++** и **Go** с полным покрытием тестами, бенчмарками и сериализацией.

## Структура проекта

```
Laba3/
├── C++/                      # C++ реализация
│   ├── include/              # Заголовочные файлы
│   ├── src/                  # Исходные файлы
│   ├── tests/                # Юнит-тесты (Google Test)
│   ├── main.cpp              # Демонстрационная программа
│   ├── Makefile              # Сборка проекта
│   └── README.md             # Документация C++
│
├── go/                       # Go реализация
│   ├── structs/              # Пакеты структур данных
│   │   ├── array/
│   │   ├── linkedlist/
│   │   ├── doublelinkedlist/
│   │   ├── queue/
│   │   ├── stack/
│   │   ├── hashtable/
│   │   └── bst/
│   ├── cmd/                  # Главная программа
│   ├── go.mod                # Go модуль
│   └── README.md             # Документация Go
│
└── README.md                 # Этот файл
```

## Реализованные структуры данных

### 1. Array (Массив)
- Динамический массив с автоматическим изменением размера
- Операции: append, insert, get, set, remove
- Сложность доступа: O(1)
- Сложность вставки/удаления: O(n)

### 2. LinkedList (Односвязный список)
- Линейный список с односторонними связями
- Операции: pushFront, pushBack, insert, remove
- Сложность вставки в начало: O(1)
- Сложность доступа по индексу: O(n)

### 3. DoubleLinkedList (Двусвязный список)
- Список с двусторонними связями
- Оптимизированный доступ с обоих концов
- Операции: pushFront, pushBack, popFront, popBack
- Сложность вставки/удаления с концов: O(1)

### 4. Queue (Очередь)
- FIFO (First In, First Out)
- Операции: enqueue, dequeue, peek
- Сложность всех операций: O(1)

### 5. Stack (Стек)
- LIFO (Last In, First Out)
- Операции: push, pop, peek
- Сложность всех операций: O(1)

### 6. HashTable (Хеш-таблица)
- Разрешение коллизий методом цепочек
- Динамическое изменение размера (rehashing)
- Операции: insert, get, remove, contains
- Средняя сложность операций: O(1)

### 7. BinarySearchTree (Бинарное дерево поиска)
- Упорядоченное бинарное дерево
- Операции: insert, search, remove
- Средняя сложность операций: O(log n)

## Ключевые особенности

### Принципы ООП

#### C++:
- ✅ Инкапсуляция (private/public секции)
- ✅ Конструкторы копирования
- ✅ Операторы присваивания
- ✅ Деструкторы для управления памятью
- ✅ Константные методы
- ✅ Списки инициализации

#### Go:
- ✅ Инкапсуляция через экспорт/не-экспорт
- ✅ Интерфейсы (json.Marshaler, json.Unmarshaler)
- ✅ Методы с receiver'ами
- ✅ Обработка ошибок через возвращаемые значения

### Тестирование

### C++ (Google Test):
- Один комплексный тест на каждую структуру данных
- Покрытие всех основных операций в одном тесте
- HTML отчеты через lcov (опционально)
- Тесты граничных случаев
- Тесты исключений

Команды:
```bash
cd Laba3/C++
make test        # Запуск тестов
make coverage    # Генерация отчета о покрытии (опционально)
```

#### Go (testing):
- Покрытие кода >85%
- HTML отчеты через go tool cover
- Benchmark тесты с измерением памяти
- Табличные тесты

Команды:
```bash
cd Laba3/go
go test ./... -v                              # Запуск тестов
go test ./... -cover                          # Покрытие
go test ./... -coverprofile=coverage.out      # Генерация отчета
go tool cover -html=coverage.out              # Просмотр отчета
go test ./... -bench=. -benchmem              # Бенчмарки
```

### Сериализация

#### C++:
- **Формат**: Бинарный
- **Методы**: serialize(), deserialize()
- **Использование**: std::ofstream, std::ifstream

Пример:
```cpp
Array arr;
arr.append("test");

std::ofstream out("data.bin", std::ios::binary);
arr.serialize(out);
out.close();

Array arr2;
std::ifstream in("data.bin", std::ios::binary);
arr2.deserialize(in);
in.close();
```

#### Go:
- **Формат**: JSON (текстовый)
- **Интерфейсы**: json.Marshaler, json.Unmarshaler
- **Использование**: encoding/json

Пример:
```go
arr := array.New()
arr.Append("test")

data, _ := json.Marshal(arr)
os.WriteFile("data.json", data, 0644)

arr2 := array.New()
fileData, _ := os.ReadFile("data.json")
json.Unmarshal(fileData, arr2)
```

## Быстрый старт

### C++

```bash
cd Laba3/C++

# Сборка и запуск
make all
make run

# Тестирование
make test

# Покрытие кода
make coverage

# Очистка
make clean
```

### Go

```bash
cd Laba3/go

# Запуск программы
go run cmd/main.go

# Тестирование
go test ./... -v

# Покрытие
go test ./... -cover

# Бенчмарки
go test ./... -bench=.
```

## Линтеры

### C++:
```bash
clang-tidy src/*.cpp -- -Iinclude
cppcheck --enable=all src/
```

### Go:
```bash
gofmt -w .
go vet ./...
golangci-lint run
```

## UML диаграммы

UML диаграммы классов доступны в документации. Основные элементы:

- **Array**: Динамический массив с capacity управлением
- **LinkedList/DoubleLinkedList**: Node-based структуры
- **Stack/Queue**: Node-based с указателями на top/front/back
- **HashTable**: Bucket array с chaining
- **BST**: Tree структура с рекурсивными методами

## Производительность

### Сложность операций

| Структура | Вставка | Удаление | Поиск | Доступ |
|-----------|---------|----------|-------|--------|
| Array | O(n) | O(n) | O(n) | O(1) |
| LinkedList | O(1)* | O(n) | O(n) | O(n) |
| DoubleLinkedList | O(1)* | O(1)* | O(n) | O(n) |
| Stack | O(1) | O(1) | - | O(1)** |
| Queue | O(1) | O(1) | - | O(1)** |
| HashTable | O(1)*** | O(1)*** | O(1)*** | O(1)*** |
| BST | O(log n)*** | O(log n)*** | O(log n)*** | - |

\* В начало/конец  
\** Только top/front  
\*** Средний случай

## Требования к работе

- [x] Многофайловый проект
- [x] Разделение на private/public (C++) / экспорт (Go)
- [x] Google Test для C++ (один тест на структуру)
- [x] Стандартный testing для Go
- [x] Сериализация (C++ - бинарная, Go - текстовая/JSON)
- [x] Документация и README
- [x] Примеры использования
- [x] Использование линтеров (опционально)
- [x] Benchmark тесты (опционально для C++, реализованы для Go)
- [x] HTML отчеты о покрытии (опционально)

## Авторы

Данный проект выполнен в рамках курса "Объектно-ориентированное программирование", семестр 3.

## Лицензия

Учебный проект. Все права защищены.
