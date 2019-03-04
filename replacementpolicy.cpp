#include"prog3.h"
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
    myvector.push_back(7);
    myvector.push_back(8);
    myvector.push_back(9);
    myvector.push_back(10);


    OPTReplacement(10, myvector);
    LRUReplacement(10, myvector);
    FIFOReplacement(10, myvector);
    RandReplacement(10, myvector);
    ClockReplacemet(10, myvector);

    return 0;
}

int OPTReplacement(int memory_size, std::vector<int> workflow){
    /*Local Variables*/
    int hitcounter = 0;
    int table_index;
    int page_table [memory_size] = {-1};
    int victim_page;
    int victim_page_distance;
    /*Iterate through workflow pages*/
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){
        table_index = findindex(memory_size, page_table, (*it));
        if(table_index == memory_size){
            /*Page (*it) not in memory*/
            table_index = findIndex(memory_size, page_table, -1);
            if(table_index != memory_size){
                /*Free spaces in page table, push to queue*/
                page_table[table_index] = (*it);
            } else {
                /*No free spaces in page table*/
                victim_page = page_table[0];
                victim_page_distance = 0;
                for(int j = 0; j < memory_size; j++){
                    for(std::vector<int>::iterator iter = (it + 1); iter != workflow.end(); iter++){if((*iter) == page_table[j]){break;}}
                    if(std::distance(it,iter) > victim_page_distance){
                        victim_page_distance = std:distance(it, iter);
                        victim_page = j
                    }
                }
                page_table[j] = (*it);
            }
        } else {
            /*Page (*it) in memory*/
            hitcounter++;
        }
    }
    return hitcounter;
}
int LRUReplacement(int memory_size, std::vector<int> workflow){

    int hitcounter = 0;
    int lru_table [memory_size] = {-1};
    int page_table [memory_size] = {-1};


    //iterate through the workflow
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){
        table_index = findindex(memory_size, page_table, (*it));
        if(table_index == memory_size){
            /*Page (*it) not in memory*/
            table_index = findIndex(memory_size, page_table, -1);
            if(table_index != memory_size){
                /*Free spaces in page table*/
                page_table[table_index] = (*it);
                for(int i = 0; i < memory_size; i++){
                    if(i == table_index){
                        lru_table[i] = 0;
                    } else if(lru_table[i] != -1){
                        lru_table[i] = lru_table[i] + 1;
                    }
                }
            } else {
                /*No free spaces in page table*/
                for(int i = 0; i < memory_size; i++){
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
            for(int i = 0; i < memory_size; i++){
                if(lru_table[i] < lru_table[table_index]){
                    lru_table[i] = lru_table[i] + 1;
                }
            }
            lru_table[table_index] = 0;
            hitcounter++;
        }
    }
    //TODO: least Recently used replacement

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
    int page_table [memory_size] = {-1};
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
    return hitcounter;
}
int RandReplacement(int memory_size, std::vector<int> workflow){
    /*Local Variables*/
    int hitcounter = 0;
    int page_table [memory_size] = {-1};
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
    return hitcounter;
}
int ClockReplacemet(int memory_size, std::vector<int> workflow){

    //clock replacement

    int hitcounter = 0;
    int page_table [memory_size] = {-1};
    int valid_table [memory_size] = {0};
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
    return hitcounter;
}

int findIndex(int memory_size, int * table, int value){
    int index;
    for(index = 0; index < memory_size; index++){
        if(table[index] == value){return index;}
    }
    return memory_size;
}
