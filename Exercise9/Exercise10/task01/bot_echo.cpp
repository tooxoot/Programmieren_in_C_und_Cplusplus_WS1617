Bot_Echo::Bot_Echo(Room* room, string name) : Bot(room, name) {}
Bot_Echo::~Bot_Echo(){}

void Bot_Echo::process_line(Message line) {
  if (line.type_id >= -1 && line.type_id != bot_id && line.content.find("?") == -1) {
    Message output;
    output.type_id = bot_id;
    output.botname = assigned_name;
    output.content = line.content + "?";
    assigned_Room->enter_message(output);
  }
};
