// Decalration of class StopWatch.
// Member functions are defined in stopwatch.cpp.
// Prevent multiple inclunions.
#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <ctime>

/**
 * Defines a macro that measures the time for the repeated execution of given
 * instructions. Provides an outputline with description and measurement.
 *
 * @param  description       The description which is integrated into the outputline.
 * @param  repetitions       Gives the number of execution repetitions.
 * @param  instructions2test The instructions which are executed.
 */
#define MEASURETIME( description, repetitions, instructions2test)\
  { StopWatch stopwatch ;\
  stopwatch.start();\
  for (int i = 0; i < repetitions; i++) {\
    instructions2test\
  }\
  double t = stopwatch.stop();\
  std::cout << "My computer requires " << t << " seconds to execute "\
  << description << " " << repetitions << " times" << std::endl;};


/**
* A stopwatch class capable of measuring the time between starting and stopping.
*/
class StopWatch {
private:
  clock_t starttime;    /**< The system time measured when start() is called.*/
  bool running; /**< True if the watch is running.*/
public:
  /** Ordinary emty constructor */
  StopWatch ();

  /**
  * Starts the stopwatch.
  * Does nothing but printing a warning message if the watch is already running.
  */
  void start(void);

  /**
  * Stops the watch.
  * Returns -1.0 and prints a warning message if the watch is not running.
  *
  * @return Returns the measured time between calling start() and stop() as a
  *         double value.
  */
  double stop(void);

};
#endif

#include "stopwatch.cpp"
