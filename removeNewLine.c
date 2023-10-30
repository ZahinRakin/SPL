void removeNewLine(char* str, int size){
  if(size > 0 && str[size - 1] == '\n'){
    str[size-1] = '\0';
  }
}
