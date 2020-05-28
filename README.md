# Find and Replace
Glibc uses a method for scanning several bytes at a time for the null-terminator in its implementation or strlen.
This library generalizes this approach to allow finding/replacing any character in a string:

```c
char const* findchr(char const* begin, char const* end, char needle);
void replacechr(char* begin, char* end, char before, char after);
```
