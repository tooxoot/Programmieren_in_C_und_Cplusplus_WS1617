int Bot::bot_count = 0;

Bot::Bot(Room* room, string name){
  assigned_Room = room;
  assigned_name = name;
  messages_read = assigned_Room->get_messagecount();
  bot_id = bot_count;
  bot_count++;
}

Bot::~Bot(){ process_thread.join(); }

void Bot::initialize_threads(){
  process_thread = thread(&Bot::process_loop, this );
}

void Bot::process_loop(){
  while (!(assigned_Room->get_exitflag())) {
    if(messages_read < assigned_Room->get_messagecount()){
      for (int i = messages_read; i < assigned_Room->get_messagecount(); i++) {
        (*this).process_line(assigned_Room->get_message(i));
        messages_read++;
      }
    }
  }
}
