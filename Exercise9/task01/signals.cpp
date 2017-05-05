#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>

// I assume we don't have to comment the given class and enum.
enum SignalType {WLAN, BLUETOOTH};

/**
 * @brief The Signal class represents a captured signal
 */
class Signal {
private:
    SignalType type;
    std::string deviceId;
    int strength;
    unsigned channel;

public:
    Signal(): type(WLAN){}

    SignalType getType() const {return type;}
    void setType(SignalType _type){this->type = _type;}
    std::string getDeviceId() const {return deviceId;}
    void setDeviceId(std::string _deviceId){this->deviceId = _deviceId;}
    int getStrength() const {return strength;}
    void setStrength(int _strength){this->strength = _strength;}
    unsigned getChannel() const{return channel;}
    void setChannel(unsigned _channel){this->channel = _channel;}

    friend std::ostream& operator<<(std::ostream& output, const Signal& signal);
    friend std::istream& operator>>(std::istream& input, Signal& signal);
};

/**
 * Reads all signals found in the file specified by the given filepath.
 *
 * @param filepath C-String that specifies the Path to the file.
 * @return A vector consisting of all the signals which were read.
 */
std::vector<Signal> readSignals(const char* filepath){
    std::cout << "Reading signals from " << filepath << std::endl;
    // Preparing input streams
    std::ifstream input_f(filepath);
    std::istream& input = input_f;

    std::vector<Signal> read_signals;

    // Read from input Stream until the end of the file is reached
    while(input_f.peek() != std::ifstream::traits_type::eof()){
      Signal temp_sig;
      input >> temp_sig;
      read_signals.push_back(temp_sig);
    }

    //Closing the input stream
    input_f.close();
    return read_signals;
}

/**
 * Returns all Signals with given type from the given Signal-vector.
 *
 * @param type The SignalType which the vector is searched for.
 * @param signalReadings The searched Signal-vector.
 * @return A vector consisting of all found Signals with given type.
 */
std::vector<Signal> filterSignals(SignalType type, std::vector<Signal>& signalReadings){
    std::vector<Signal> filtered_signals;

    for (int i = 0; i < signalReadings.size(); i++)
      if(signalReadings[i].getType() == type) filtered_signals.push_back(signalReadings[i]);

    return filtered_signals;
}

/**
 * Writes all the Signals from given Signal-vector to a file specified by outputFilename.
 * @param outputFilename    The path to the output file.
 * @param aggregatedSignals All Signals from this vector will be printed to the file.
 */
void writeSignals(const char* outputFilename, const std::vector<Signal> aggregatedSignals){
    std::cout << "Writing signals to " << outputFilename << std::endl;
    // Preparing the output streams
    std::ofstream output_f(outputFilename);
    std::ostream& output = output_f;

    // Writing all signals to the file
    for (int i = 0; i < aggregatedSignals.size(); i++)
      output << aggregatedSignals[i] << std::endl;

    // Closing the output stream
    output_f.close();
}

/**
 * Input operator to fill a Signal from a given istream.
 * @param input  The istream that is used to fill the Signal. Note that one whole
 *               Line is read from the stream!
 * @param signal The Signal that is filled with the information read from the stream.
 * @return The input stream
 */
std::istream& operator>>(std::istream& input, Signal& signal){
  // Prepare input
  std::string input_line;

  // I'm not quite sure if this is an elegant way to implement this operator.
  // But I assumed that for this task all Signals are seperated by '\n'.
  std::getline(input, input_line);

  // Initialize temp varaibles
  char        type_to_parse[10] = "default";
  char        deviceId_temp[12] = "default";
  int         strength_temp = 0;
  unsigned    channel_temp = 0;

  sscanf(input_line.c_str(), "%[^, ], %[^, ], %d, %u", type_to_parse, deviceId_temp, &strength_temp, &channel_temp);

  // Write to signal
  switch (type_to_parse[0]) {
    case 'W': signal.setType(WLAN); break;
    case 'B': signal.setType(BLUETOOTH); break;
    default:
      signal.setType(WLAN); break;
      std::cout << "Unexpected type! Defaulted to WLAN!" << std::endl;
      break;
  }
  signal.setDeviceId(deviceId_temp);
  signal.setStrength(strength_temp);
  signal.setChannel(channel_temp);

  return input;
}

/**
 * Writes the Signal's data to the given ostream.
 *
 * @param output The ostream to which the data is written.
 * @param signal The Signal from which the data is read.
 * @return The given ostream
 */
std::ostream& operator<<(std::ostream& output, const Signal& signal){
  // Parse signal::type to string
  std::string type_temp = "WLAN";
  if(signal.getType() == BLUETOOTH) type_temp = "BLUETOOTH";

  // Write to output
  output  << type_temp << ", "
          << signal.getDeviceId() << ", "
          << signal.getStrength() << ", "
          << signal.getChannel();
  return output;
}

int main(void){
    const char * filename = "signals.txt";
    std::vector<Signal> rawSignals = readSignals(filename);
    std::vector<Signal> filteredSignals = filterSignals(WLAN, rawSignals);

    std::cout << rawSignals.size() << " signals were read, of which "
              << filteredSignals.size() << " were WLAN signals!"
              << std::endl;

    writeSignals("filtered_signals.txt", filteredSignals);
    return 0;
}
