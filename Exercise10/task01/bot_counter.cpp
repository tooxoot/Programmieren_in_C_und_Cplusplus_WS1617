Bot_Counter::Bot_Counter (Room* room, string name) : Bot(room, name){};
Bot_Counter::~Bot_Counter (){};

void Bot_Counter::process_line(Message line){
  thread counter_thread;
  if (line.type_id >= -1 && line.type_id != bot_id && line.content == "startcounter") {
    temp_thread = new thread(&Bot_Counter::start_counter_thread, this );
  }
};
void Bot_Counter::start_counter_thread( ){
  Message output;
  output.type_id = bot_id;
  output.botname = assigned_name;
  for (int i = 0; i < 3; i++) {
    output.content = to_string(i+1);
    assigned_Room->enter_message(output);
    sleep_for(seconds(1));
  }
};
