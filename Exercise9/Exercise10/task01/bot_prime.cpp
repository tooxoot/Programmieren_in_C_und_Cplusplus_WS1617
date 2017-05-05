Bot_Prime::Bot_Prime (Room* room, string name) : Bot(room, name){};
Bot_Prime::~Bot_Prime (){};

void Bot_Prime::process_line(Message line){
  thread counter_thread;
  if (line.type_id >= -1 && line.type_id != bot_id && line.content.find("isprime ") == 0) {
    temp_thread = new thread(&Bot_Prime::start_prime_thread, this, line.content.substr(8) );
  }
};

void Bot_Prime::start_prime_thread(string prime_args){
  prime_args += " ";
  int seperator_position = -1;
  while((seperator_position = prime_args.find(" ")) != -1){
    string candidate = prime_args.substr(0, seperator_position);
    prime_args = prime_args.substr(seperator_position + 1);
    try{
      temp_thread = new thread(&Bot_Prime::is_prime, this, stoi(candidate) );
    } catch(...){
      //
    }
  }
};

bool Bot_Prime::is_prime(int candidate){
  Message output;
  output.type_id = bot_id;
  output.botname = assigned_name;
  output.content = to_string(candidate) + " is " ;
  bool prime = true;
  for (int i = 2; i < candidate; i++)
    if(candidate % i == 0){ prime = false; break; }
  if(!prime) output.content += "not ";
  output.content += "a prime";
  assigned_Room->enter_message(output);
}
