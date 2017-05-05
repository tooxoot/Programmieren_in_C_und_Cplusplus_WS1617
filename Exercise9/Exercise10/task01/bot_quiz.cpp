Bot_Quiz::Bot_Quiz (Room* room, string name) : Bot(room, name){};
Bot_Quiz::~Bot_Quiz (){};

void Bot_Quiz::process_line(Message line){
  if (line.type_id >= -1 && line.type_id != bot_id)
    if(line.content.find("startquiz ") == 0 && !is_quizing) {
      initialize_quiz(line.content.substr(10));
    }else if(is_quizing && line.content == answers[0]){
      answers.pop_front();

      Message correct;
      correct.type_id = bot_id;
      correct.botname = assigned_name;
      correct.content = "Correct!";
      assigned_Room->enter_message(correct);

      if(answers.size() == 0) {
        is_quizing = false;
        return;
      }
      next_question();
    }

};

void Bot_Quiz::initialize_quiz(string filename){
  deque<string> lines;
  bool odd = false;
  std::ifstream input_f(filename);
  std::istream& input = input_f;
  if(input_f.fail()) return;
  while(input_f.peek() != std::ifstream::traits_type::eof()){
    string temp_line;
    // input >> temp_line;
    getline(input, temp_line);

    if(temp_line.size() != 0){
      lines.push_back(temp_line);
      odd = !odd;
    }
  }
  if(odd) lines.pop_back();
  input_f.close();
  while(lines.size() != 0){
    questions.push_back(lines[0]);
    lines.pop_front();
    answers.push_back(lines[0]);
    lines.pop_front();
  }

  is_quizing = true;
  next_question();
}

void Bot_Quiz::next_question(){
  Message output;
  output.type_id = bot_id;
  output.botname = assigned_name;
  output.content = questions[0];
  assigned_Room->enter_message(output);
  questions.pop_front();
}
