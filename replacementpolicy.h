#ifndef H_REPLACEMENTPOLICY_H
#define H_REPLACEMENTPOLICY_H

#define USAGE_STRING "\n\nNone yet\n\n"
#define TRUE 1
#define FALSE 0
std::vector<std::vector<int>> repeatReplacement(int memory_size_start, int memory_size_end, int memory_size_step, std::vector<int> workflow);
void initTable(int memory_size, int * table);
int findIndex(int memory_size, int * table, int value);
int OPTReplacement(int memory_size, std::vector<int> workflow);
int LRUReplacement(int memory_size, std::vector<int> workflow);
int FIFOReplacement(int memory_size, std::vector<int> workflow);
int RandReplacement(int memory_size, std::vector<int> workflow);
int ClockReplacemet(int memory_size, std::vector<int> workflow);
#endif
