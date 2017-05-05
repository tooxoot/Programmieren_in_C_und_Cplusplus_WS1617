#include <iostream>
#include <ctime>

/**
* A stopwatch class capable of measuring the time between starting and stopping.
*/
class StopWatch {
private:
  clock_t starttime;    /**< The system time measured when start() is called.*/
  bool running = false; /**< True if the watch is running.*/
public:
  /** Ordinary emty constructor */
  StopWatch (){}

  /**
  * Starts the stopwatch.
  * Does nothing but printing a warning message if the watch is already running.
  */
  void start(void) {
    if (running) {
      std::cout << "StopWatch already running" << std::endl;
      return;
    }
    running = true;
    starttime = clock();
    std::cout << "Started at " << starttime << std::endl;
  }

  /**
  * Stops the watch.
  * Returns -1.0 and prints a warning message if the watch is not running.
  *
  * @return Returns the measured time between calling start() and stop() as a
  *         double value.
  */
  double stop(void){
    if (!running) {
      std::cout << "StopWatch not started yet!" << std::endl;
      return -1.0;
    }
    running = false;
    return clock() - starttime;
  }
};
