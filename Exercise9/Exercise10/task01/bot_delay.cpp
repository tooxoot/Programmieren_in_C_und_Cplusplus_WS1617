Bot_Delay::Bot_Delay (Room* room, string name) : Bot(room, name){};
Bot_Delay::~Bot_Delay (){};

void Bot_Delay::process_line(Message line){
  thread counter_thread;
  if (line.type_id >= -1 && line.type_id != bot_id && line.content.find("delayed ") == 0) {
    temp_thread = new thread(&Bot_Delay::start_delay_thread, this, line.content.substr(8) );
  }
};
void Bot_Delay::start_delay_thread(string delayed_content){
  sleep_for(seconds(2));
  Message output;
  output.type_id = bot_id;
  output.botname = assigned_name;
  output.content = delayed_content;
  assigned_Room->enter_message(output);
};
