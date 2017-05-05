// Include definition of class StopWatch in stopwatch.hpp.


/*
* This is the source file to header file stopwatch.hpp containing the StopWatch
* class.Please look at the header for Method descriptions.
*/

StopWatch::StopWatch (){
  this->running = false;
}

void StopWatch::start(void) {
  if (running) {
    std::cout << "StopWatch already running" << std::endl;
    return;
  }
  running = true;
  starttime = clock();
}

double StopWatch::stop(void){
  if (!running) {
    std::cout << "StopWatch not started yet!" << std::endl;
    return -1.0;
  }
  running = false;
  return (clock() - starttime) / (double) CLOCKS_PER_SEC;
}
