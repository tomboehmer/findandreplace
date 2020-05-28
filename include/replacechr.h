#ifndef REPLACECHR_H
#define REPLACECHR_H

#ifdef __cplusplus
extern "C" {
#endif

void replacechr(char* begin, char* end, char before, char after);
void replacechr_fancy(char* begin, char* end, char before, char after);
void replacechr_naive(char* begin, char* end, char before, char after);

#ifdef __cplusplus
}
#endif

#endif /* REPLACECHR_H */
