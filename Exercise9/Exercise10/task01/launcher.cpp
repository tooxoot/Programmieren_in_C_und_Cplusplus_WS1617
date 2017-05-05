// It would probably be better to have these in the hpp files
#include <iostream>
#include <stdlib.h>
#include <cstdio>
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <thread>
#include <typeinfo>
#include <unistd.h>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <mutex>
#include <deque>
using namespace std;
using namespace std::chrono;
using namespace std::this_thread;

#include "room.hpp"

int main(int argc, char const *argv[]) {
  Room* r = new Room();
  Message m1; m1.type_id = -2; m1.content = "bot:counter,@1";
  Message m2; m2.type_id = -1; m2.content = "startcounter";
  Message m3; m3.type_id = -2; m3.content = "bot:echo,@2";
  r->enter_message(m1);
  r->enter_message(m2);
  r->enter_message(m3);
  //For Debugin reasons
  // Bot_Echo* b1 = new Bot_Echo(r,"@1");
  // Bot_Echo* b2 = new Bot_Echo(r,"@2");
  // Bot_Echo* b3 = new Bot_Echo(r,"@3");
  // Bot_Delay* b4 = new Bot_Delay(r,"@4");
  // Bot_Counter* b5 = new Bot_Counter(r,"@5");
  // Bot_Quiz* b6 = new Bot_Quiz(r,"@6");
  // b1->initialize_threads();
  // b2->initialize_threads();
  // b3->initialize_threads();
  // b4->initialize_threads();
  // b5->initialize_threads();
  // b6->initialize_threads();
  r->initialize_threads();

  return 0;
}
