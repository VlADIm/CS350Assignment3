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

int main(){
    return 0;
}

int OPTReplacement(int memory_size, std::vector workflow){

    int hitcounter = 0;

    int page_table [memory_size] = {-1};


    //use find from algorithms to find next used
    //knowing which is the furthest access in the future

    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){

    }


    return hitcounter;
}
int LRUReplacement(int memory_size, std::vector<int> workflow){

    int hitcounter = 0;

    int page_table [memory_size] = {-1};


    //iterate through the workflow
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){

    }
    //TODO: least Recently used replacement

    return hitcounter;
}
/**
*
*
*
**/
int FIFOReplacement(int memory_size, std::vector workflow){

    //first in first out replacement
    //this is just a queue
    int hitcounter = 0;
    int page_table [memory_size] = {-1};

    std::queue<int> page_queue;

    //iterate through the workflow
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){

        while((i < memory_size) && (page_table[i] != (*it)) && (page_table[i] != -1)){
            i++;
        }

        if(i == memory_size){
            //pop from queue and replace page

        } else if(page_table[i] == -1){
            //push to queue and input (*it)
            page_table[i] = (*it);
            page_queue.push((*it));
        }  else if(page_table[i] == (*it)){
            hitcounter++;
        }

    }

    return hitcounter;
}
int RandReplacement(int memory_size, std::vector workflow){
    /*Local Variables*/
    int hitcounter = 0;
    int page_table [memory_size] = {-1};
    int rand_num;
    int table_index;
    /*Iterate through workflow pages*/
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){

        /*Search page_table for (*it)*/
        table_index = std::find(page_table, page_table + memory_size, (*it));
        if(table_index != (page_table + memory_size)){
            /*Page (*it) not in memory*/
            table_index = std::find(page_table, page_table + memory_size, -1);
            if(table_index != (page_table + memory_size)){
                /*No free spaces in page table*/
                srand(time(NULL));
                rand_num = rand() % memory_size;

                /*NEED TO CHECK FOR 3 CASES:
                *CASE 1:
                *CASE 2:
                */
                if(page_table[rand_num] != (*it)){

                }

            } else {
                *table_index = (*it);
            }


        } else {
            /*Page (*it) in memory*/
            hitcounter++;
        }
        /*Seed and generate randome number in [0, memory_size)*/

    }
    /*Return hitcounter variable*/
    return hitcounter;
}
int ClockReplacemet(int memory_size, std::vector workflow){

    //clock replacement

    int hitcounter = 0;


    int page_table [memory_size] = {-1};


    //iterate through the workflow
    for(std::vector<int>::iterator it = workflow.begin(); it != workflow.end(); it++){

    }


    return hitcounter;
}
