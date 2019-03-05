#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <vector>
#include <queue>
#include <algorithm>
#include "replacementpolicy.h"

int main(){

    std::vector<int> myvector;

    myvector.push_back(1);
    myvector.push_back(2);
    myvector.push_back(3);
    myvector.push_back(4);
    myvector.push_back(5);
    myvector.push_back(6);
    myvector.push_back(1);
    myvector.push_back(2);
    myvector.push_back(3);
    myvector.push_back(4);


    // printf("OPT HITCOUNT:   %d\n", OPTReplacement(5, myvector));
    // printf("LRU HITCOUNT:   %d\n", LRUReplacement(5, myvector));
    // printf("FIFO HITCOUNT:  %d\n", FIFOReplacement(5, myvector));
    // printf("RAND HITCOUNT:  %d\n", RandReplacement(5, myvector));
    // printf("CLOCK HITCOUNT: %d\n", ClockReplacemet(5, myvector));

    std::vector<std::vector<int>> data = repeatReplacement(5, 15, 5, myvector);

    for(std::vector<std::vector<int>>::iterator iter_0 = data.begin(); iter_0 != data.end(); iter_0++){
        for(std::vector<int>::iterator iter_1 = (*iter_0).begin(); iter_1 != (*iter_0).end(); iter_1++){
            printf("VECTOR VECTOR DATA: %d\n", (*iter_1));
        }
    }

    return 0;
}

std::vector<std::vector<int>> repeatReplacement(int memory_size_start, int memory_size_end, int memory_size_step, std::vector<int> workflow){

    std::vector<std::vector<int>> return_vector;
    int index;

    for(index = memory_size_start; index < (memory_size_end + 1); index += memory_size_step){
        std::vector<int> data;
        data.push_back(OPTReplacement(index, workflow));
        data.push_back(LRUReplacement(index, workflow));
        data.push_back(FIFOReplacement(index, workflow));
        data.push_back(RandReplacement(index, workflow));
        data.push_back(ClockReplacemet(index, workflow));
        // printf("\nINDEX IS: %d\n\n", index);
        return_vector.push_back(data);
    }

    return return_vector;
}

int OPTReplacement(int memory_size, std::vector<int> workflow){
    /*Local Variables*/
    int hitcounter = 0;
    int table_index;
    int * page_table = new int[memory_size];
    initTable(memory_size, page_table);
    // int victim_page;
    int victim_page_distance;
    int j;
    std::vector<int>::iterator iter;
    /*Iterate through workflow pages*/
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){
        table_index = findIndex(memory_size, page_table, (*it));
        if(table_index == memory_size){
            /*Page (*it) not in memory*/
            table_index = findIndex(memory_size, page_table, -1);
            if(table_index != memory_size){
                /*Free spaces in page table, push to queue*/
                page_table[table_index] = (*it);
            } else {
                /*No free spaces in page table*/
                // victim_page = page_table[0];
                victim_page_distance = 0;
                for(j = 0; j < memory_size; j++){
                    for(iter = (it + 1); iter != workflow.end(); iter++){if((*iter) == page_table[j]){break;}}
                    if(std::distance(it,iter) > victim_page_distance){
                        victim_page_distance = std::distance(it, iter);
                        // victim_page = j;
                    }
                }
                page_table[j] = (*it);
            }
        } else {
            /*Page (*it) in memory*/
            hitcounter++;
        }
    }
    delete[] page_table;
    return hitcounter;
}
int LRUReplacement(int memory_size, std::vector<int> workflow){

    int hitcounter = 0;
    int * lru_table  = new int[memory_size];
    int * page_table = new int[memory_size];
    initTable(memory_size, page_table);
    initTable(memory_size, lru_table);
    int table_index;
    int i;

    //iterate through the workflow
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){
        table_index = findIndex(memory_size, page_table, (*it));
        if(table_index == memory_size){
            /*Page (*it) not in memory*/
            table_index = findIndex(memory_size, page_table, -1);
            if(table_index != memory_size){
                /*Free spaces in page table*/
                page_table[table_index] = (*it);
                for(i = 0; i < memory_size; i++){
                    if(i == table_index){
                        lru_table[i] = 0;
                    } else if(lru_table[i] != -1){
                        lru_table[i] = lru_table[i] + 1;
                    }
                }
            } else {
                /*No free spaces in page table*/
                for(i = 0; i < memory_size; i++){
                    if(lru_table[i] == (memory_size - 1)){
                        lru_table[i] = 0;
                        page_table[i] = (*it);
                    } else {
                        lru_table[i] = lru_table[i] + 1;
                    }
                }
            }
        } else {
            /*Page (*it) in memory*/
            for(i = 0; i < memory_size; i++){
                if(lru_table[i] < lru_table[table_index]){
                    lru_table[i] = lru_table[i] + 1;
                }
            }
            lru_table[table_index] = 0;
            hitcounter++;
        }
    }
    //TODO: least Recently used replacement
    delete[] page_table;
    delete[] lru_table;
    return hitcounter;
}
/**
*
*
*
**/
int FIFOReplacement(int memory_size, std::vector<int> workflow){
    /*Local Variables*/
    int hitcounter = 0;
    int table_index;
    int * page_table = new int[memory_size];
    initTable(memory_size, page_table);
    std::queue<int> page_queue;
    /*Iterate through workflow pages*/
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){
        table_index = findIndex(memory_size, page_table, (*it));
        if(table_index == memory_size){
            /*Page (*it) not in memory*/
            table_index = findIndex(memory_size, page_table, -1);
            if(table_index != memory_size){
                /*Free spaces in page table, push to queue*/
                page_table[table_index] = (*it);
                page_queue.push((*it));
            } else {
                /*No free spaces in page table*/
                /*Pop and push from queue*/
                page_table[page_queue.front()] = (*it);
                page_queue.pop();
                page_queue.push((*it));
            }
        } else {
            /*Page (*it) in memory*/
            hitcounter++;
        }
    }
    delete[] page_table;
    return hitcounter;
}
int RandReplacement(int memory_size, std::vector<int> workflow){
    /*Local Variables*/
    int hitcounter = 0;
    int * page_table = new int[memory_size];
    initTable(memory_size, page_table);
    int table_index;
    /*Seed random number generator*/
    srand(time(NULL));
    /*Iterate through workflow pages*/
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){
        /*Search page_table for (*it)*/
        table_index = findIndex(memory_size, page_table, (*it));
        if(table_index == memory_size){
            /*Page (*it) not in memory*/
            table_index = findIndex(memory_size, page_table, -1);
            if(table_index != memory_size){
                /*Free spaces in page table*/
                page_table[table_index] = (*it);
            } else {
                /*No free spaces in page table*/
                /*generate randome number in [0, memory_size)*/
                page_table[(rand() % memory_size)] = (*it);
            }
        } else {
            /*Page (*it) in memory*/
            hitcounter++;
        }
    }
    /*Return hitcounter variable*/
    delete[] page_table;
    return hitcounter;
}
int ClockReplacemet(int memory_size, std::vector<int> workflow){

    //clock replacement

    int hitcounter = 0;
    int * page_table = new int[memory_size];
    initTable(memory_size, page_table);
    int * valid_table = new int[memory_size]();
    int table_index;
    int clock_hand = 0;

    //iterate through the workflow
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){
        table_index = findIndex(memory_size, page_table, (*it));
        if(table_index == memory_size){
            /*Page (*it) not in memory*/
            while(valid_table[clock_hand] != 0){
                valid_table[clock_hand] = 0;
                clock_hand = ((clock_hand + 1) % memory_size);
            }
            page_table[clock_hand] = (*it);
            clock_hand = ((clock_hand + 1) % memory_size);
        } else {
            /*Page (*it) in memory*/
            hitcounter++;
            valid_table[table_index] = 1;
        }
    }

    delete[] page_table;
    delete[] valid_table;
    return hitcounter;
}

int findIndex(int memory_size, int * table, int value){
    int index;
    for(index = 0; index < memory_size; index++){
        if(table[index] == value){return index;}
    }
    return memory_size;
}

void initTable(int memory_size, int * table){
    int index;
    for(index = 0; index < memory_size; index++){
        table[index] = -1;
    }
}
