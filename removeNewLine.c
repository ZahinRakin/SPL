void removeNewLine(char* str, int size){
  if(size > 0 && str[size - 1] == '\n'){
    str[size-1] = '\0';
  }
}
//whenever i get a line using fgets. There remains a new line character at the end of string. It dusturbs so to remove that this method beomes handy.