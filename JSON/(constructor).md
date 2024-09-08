# [lib](../README.md)::[JSON](./README.md)::(constructors)
|||
|-|-|
| 1 | `JSON();` |
| 2 | `JSON(const int val);` |
| 3 | `JSON(const std::string val);` |
| 4 | `JSON(const char *val);` |
| 5 | `JSON(const bool val);` |
| 6 | `JSON(const Object val);` |
| 7 | `JSON(const Array val);` |

construct the JSON object with type of data.
## Parameters
- 1 Nothing => assigns element to null
- 2-7 val => assigns JSON element to val
## Complexity
- 1-5 O(1)
- 6-7 O(N)
