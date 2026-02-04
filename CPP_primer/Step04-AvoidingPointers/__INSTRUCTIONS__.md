# Avoiding Raw Pointers

Manual memory management is error-prone. Fortunately, safer alternatives exist.

## STL: Standard Template Library

Templates reduce boilerplate and improve safety. Common examples:
- `std::string`: Replaces `char*`/`char[]`
- `std::cout`: Output stream
- `std::swap`: Generic swap function

**Namespaces**: `std::` prevents naming conflicts. Avoid `using namespace std;` (namespace pollution).

## STL Containers

Choose based on your data and operations:

| Container       | Properties                       | Best For                            |
|-----------------|----------------------------------|-------------------------------------|
| `vector`        | Contiguous, indexed, grows       | General-purpose; fast random access |
| `deque`         | Indexed, grows both ends         | Front/back insertion                |
| `set`           | Ordered, O(log n) insert/find    | Sorted data                         |
| `map`           | Key-value pairs, O(log n) lookup | Dictionaries; cache                 |
| `slist`         | Singly-linked list               | Fast forward iteration, insertion   |
| `list`          | Doubly-linked list               | Fast iteration, insertion           |
| `unordered_set` | Hash-based, O(1) average         | Fast membership testing             |
| `unordered_map` | Hash-based KV, O(1) average      | Fast key lookup                     |

All manage memory automatically.

## Task 1: Run and Observe

Examine, compile, and run the code.

Compare to the previous exercise: What's different?

