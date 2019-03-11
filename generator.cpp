#include<iostream>
#include<vector>


const int seed = 15;

        /* Generates random page accesses */
void generateRandom(int num_pages, int num_mem_accesses, std::vector<int> &numbers){
  srand(seed);
  for(int i = 0; i < num_mem_accesses; i++){
    numbers.push_back(rand() % (num_pages +1));
  }
  return;
}

        /* Generates page accesses, 80% of which access 20% of pages */
void generate8020(int num_pages, int num_mem_accesses, std::vector<int> &numbers){
  srand(seed);
  for(int i = 0; i < num_mem_accesses; i++){
    if(rand()%100 < 80){
        numbers.push_back(rand() % (num_pages/5));
    }
    else{
        numbers.push_back(rand() % (4*num_pages/5) + num_pages/5);
    }
  }
  return;
}

        /* Generates page accesses linearly */
void generateLooping(int num_pages, int num_mem_accesses, std::vector<int> &numbers){
  srand(seed);
  int cntr = 0;
  for(int i = 0; i < num_mem_accesses; i++){
    numbers.push_back(cntr);
    cntr++;
    cntr = cntr % num_pages;
  }
  return;
}

/*
 * int main(int argc, char* argv[]){
 *  std::vector<int> vec;
 *  //generateRandom(100, 10000, vec);
 *  //generate8020(100, 10000, vec);
 *  //generateLooping(100, 10000, vec);
 *  int cntr = 0;
 *  for(auto i = vec.begin(); i != vec.end(); ++i){
 *      std::cout << cntr << ":\t" <<  *i << std::endl;
 *      cntr++;
 *  }
 *
 * }
 */
