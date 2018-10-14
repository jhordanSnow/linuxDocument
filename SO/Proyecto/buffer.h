typedef int buffer_item;
#define BUFFER_SIZE 5


int validateEntry(char entry[]){
  int i = 0;
  if (entry[0] == '-') return 0;
  for (; entry[i] != 0; i++){
    if (entry[i] > '9' || entry[i] < '0') return 0;
  }
  return 1;
}
