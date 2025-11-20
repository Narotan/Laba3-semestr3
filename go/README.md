# Go Data Structures - Lab 3

## Описание

Реализация основных абстрактных структур данных на Go с использованием принципов ООП.

## Структуры данных

1. **Array** - Динамический массив
2. **LinkedList** - Односвязный список
3. **DoubleLinkedList** - Двусвязный список
4. **Queue** - Очередь (FIFO)
5. **Stack** - Стек (LIFO)
6. **HashTable** - Хеш-таблица с разрешением коллизий методом цепочек
7. **BinarySearchTree** - Бинарное дерево поиска

## Особенности реализации

- ✅ Модульная структура проекта
- ✅ Инкапсуляция через экспортируемые/неэкспортируемые поля
- ✅ JSON сериализация/десериализация
- ✅ Обработка ошибок через возвращаемые значения
- ✅ Юнит-тесты с покрытием >85%
- ✅ Benchmark тесты
- ✅ Использование Go интерфейсов

## Сборка и запуск

### Требования

- Go 1.21 или выше

### Установка зависимостей

```bash
go mod tidy
```

### Запуск основной программы

```bash
go run cmd/main.go
```

### Запуск тестов

```bash
# Все тесты
go test ./... -v

# Тесты с покрытием
go test ./... -cover

# Детальный отчет о покрытии
go test ./... -coverprofile=coverage.out
gо tool cover -html=coverage.out -o coverage.html

# Просмотр отчета
open coverage.html  # macOS
```

### Запуск бенчмарков

```bash
# Все бенчмарки
go test ./... -bench=. -benchmem

# Бенчмарки для конкретной структуры
go test ./structs/array -bench=. -benchmem
```

## Структура проекта

```
go/
├── structs/
│   ├── array/
│   │   ├── array.go
│   │   └── array_test.go
│   ├── linkedlist/
│   │   ├── linkedlist.go
│   │   └── linkedlist_test.go
│   ├── doublelinkedlist/
│   │   ├── doublelinkedlist.go
│   │   └── doublelinkedlist_test.go
│   ├── queue/
│   │   ├── queue.go
│   │   └── queue_test.go
│   ├── stack/
│   │   ├── stack.go
│   │   └── stack_test.go
│   ├── hashtable/
│   │   ├── hashtable.go
│   │   └── hashtable_test.go
│   └── bst/
│       ├── bst.go
│       └── bst_test.go
├── cmd/
│   └── main.go
├── go.mod
└── README.md
```

## Примеры использования

### Array

```go
import "laba3/structs/array"

arr := array.New()
arr.Append("Hello")
arr.Append("World")
val, _ := arr.Get(0)  // "Hello"

// JSON Serialization
data, _ := json.Marshal(arr)
```

### Stack

```go
import "laba3/structs/stack"

s := stack.New()
s.Push("first")
s.Push("second")
val, _ := s.Pop()  // "second"
```

### HashTable

```go
import "laba3/structs/hashtable"

ht := hashtable.New()
ht.Insert("name", "John")
ht.Insert("age", "25")
val, _ := ht.Get("name")  // "John"
```

### Binary Search Tree

```go
import "laba3/structs/bst"

bst := bst.New()
bst.Insert("dog")
bst.Insert("cat")
bst.Insert("elephant")

if bst.Search("cat") {
    fmt.Println("Found!")
}

// Get sorted values
values := bst.InOrder()
```

## Тестирование

Проект использует стандартный пакет `testing` из Go.

Каждая структура данных покрыта следующими типами тестов:

- Тесты базовых операций (вставка, удаление, поиск)
- Тесты граничных случаев (пустая структура)
- Тесты ошибок
- Тесты сериализации/десериализации (JSON)
- Benchmark тесты производительности

## Сериализация

Все структуры поддерживают JSON сериализацию через интерфейсы `json.Marshaler` и `json.Unmarshaler`:

```go
// Запись в JSON
data, err := json.Marshal(structure)

// Запись в файл
os.WriteFile("data.json", data, 0644)

// Чтение из файла
fileData, _ := os.ReadFile("data.json")
json.Unmarshal(fileData, &structure)
```

## Линтеры

Рекомендуется использовать:

```bash
# gofmt - форматирование кода
gofmt -w .

# go vet - статический анализ
go vet ./...

# golangci-lint - комплексный линтер
golangci-lint run
```

## Benchmark результаты

Для получения производительности различных операций:

```bash
go test ./structs/array -bench=BenchmarkArray -benchmem
```

Пример вывода:
```
BenchmarkArrayAppend-8     1000000    1234 ns/op    256 B/op    2 allocs/op
BenchmarkArrayGet-8       10000000     123 ns/op      0 B/op    0 allocs/op
```

## Генерация coverage отчета

```bash
# Установка зависимостей (если нужно)
go install golang.org/x/tools/cmd/cover@latest

# Генерация отчета
go test ./... -coverprofile=coverage.out
go tool cover -html=coverage.out -o coverage.html
```

Отчет будет доступен в `coverage.html`
