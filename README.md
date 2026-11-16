# Library Management System
C++17 application using classes, structures, vectors and file handling.

Features: add books, register members, search by title/author (case-insensitive), issue and return books, prevent duplicate IDs and invalid issue/return operations. Records persist in `books.txt` and `members.txt`.

Compile:
```bash
g++ -std=c++17 -Wall -Wextra main.cpp -o library
./library
```
On Windows run `.\library.exe` after compiling with `-o library.exe`. Data files are plain text; use fictional sample data only.
