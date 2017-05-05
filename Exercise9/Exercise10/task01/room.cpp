

Room::Room (){}

Room::~Room(){ process_thread.join(); }

void Room::initialize_threads(){
  process_thread = thread(&Room::process_loop, this );
  input_thread = thread(&Room::input_loop, this );
  input_thread.join();
}

void Room::process_loop() {
  // deque<Message> processed_queue;
  while (!exit_flag) {

    /**
     * I Think something here is not as intended by the task.
     * Especially concerning the delay whch then leads to a different output in
     * the Counter + ECHO task.
     */
    Message line;
    queue_lock.lock();
    if(received_messages.size() != 0){
      line = received_messages.front();
      received_messages.pop_front();
    }
    queue_lock.unlock();
    if(line.content.size()!=0)process_line(line);
    sleep_for(milliseconds(100));
  }
}

void Room::input_loop(){
  string input;
  Message entered_Message;
  while(!exit_flag){
    getline(cin, input);
    if(input.size() == 0) continue;
    if(input == "exit"){
      entered_Message.type_id = MessageTypes::EXIT;
      entered_Message.content = input;
      enter_message(entered_Message);
      sleep_for(seconds(6));
      set_exitflag();
      break;
    }else if(input.find("bot:") == 0){
      entered_Message.type_id = MessageTypes::BOT_COMMAND;
      entered_Message.content = input;
      // sleep_for(milliseconds(100));
      // create_Bot(input.substr(4));
    } else{
      entered_Message.type_id = MessageTypes::USER_INPUT;
      entered_Message.content = input;
    }
    enter_message(entered_Message);
  }
}

/**
 * The Bots are created here which is basically not in the Mainthread. To do exactly
 * this the commented lines in input_loop had to be used. But I realized this restriction
 * to late and just sticked to my design.
 */
void Room::process_line(Message line){
  accepted_messages.push_back(line);
  switch (line.type_id) {
    case MessageTypes::EXIT:
      break;
    case MessageTypes::USER_INPUT:
      break;
    case MessageTypes::BOT_COMMAND:
      create_Bot(line.content.substr(4));
      break;
    default:
      std::cout << line.botname << ": " << line.content << "\n";
  }
}

void Room::create_Bot(string parameters){
  int seperator_position = parameters.find(",");
  string parameter_1 = parameters.substr(0, seperator_position);
  string parameter_2 = parameters.substr(seperator_position + 1);
  if(parameter_1 == ECHO){
    Bot_Echo* echo_Bot = new Bot_Echo(this, parameter_2);
    echo_Bot->initialize_threads();
  } else if(parameter_1 == COUNTER) {
    Bot_Counter* counter_Bot = new Bot_Counter(this, parameter_2);
    counter_Bot->initialize_threads();
  } else if(parameter_1 == DELAY) {
    Bot_Delay* delay_Bot = new Bot_Delay(this, parameter_2);
    delay_Bot->initialize_threads();
  } else if(parameter_1 == PRIME) {
    Bot_Prime* prime_Bot = new Bot_Prime(this, parameter_2);
    prime_Bot->initialize_threads();
  } else if(parameter_1 == QUIZ) {
    Bot_Quiz* quiz_Bot = new Bot_Quiz(this, parameter_2);
    quiz_Bot->initialize_threads();
  }
}

int Room::get_messagecount() const{
  return accepted_messages.size();
}

Message Room::get_message( int n ) const {
  return accepted_messages[n];
}

int Room::enter_message(Message message){
  queue_lock.lock();

  received_messages.push_back(message);
  int count = received_messages.size();

  queue_lock.unlock();
  return count;
}


void Room::set_exitflag(){
  exit_flag = true;
}

bool Room::get_exitflag(){
  return exit_flag;
};
