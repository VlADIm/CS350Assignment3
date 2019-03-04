#ifndef H_REPLACEMENTPOLICY_H
#define H_REPLACEMENTPOLICY_H

#define USAGE_STRING "\n\nNone yet\n\n"
#define TRUE 1
#define FALSE 0

int findIndex(int memory_size, int * table, int value);
int OPTReplacement(int memory_size, std::vector<int> workflow);
int LRUReplacement(int memory_size, std::vector<int> workflow);
int FIFOReplacement(int memory_size, std::vector<int> workflow);
int RandReplacement(int memory_size, std::vector<int> workflow);
int ClockReplacemet(int memory_size, std::vector<int> workflow);

#endif
