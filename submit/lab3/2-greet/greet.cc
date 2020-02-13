#include <iostream>
#include <cstdlib>
#include <cstring>

#define GREET "hello"

void
greetMsg(const char *name)
{
  const std::size_t len = strlen(GREET) + 1 + strlen(name);
  char *msg = new char[len + 1];
  strcpy(msg, GREET); strcat(msg, " "); strcat(msg, name);
  //return msg;
  std::cout << msg << std::endl;
  delete [] msg;
}

int 
main(int argc, const char *argv[])
{
  if (argc == 1) {
    std::cerr << "usage: " << argv[0] << " NAME..." << std::endl;
    std::exit(1);
  }
  else {
    for (int i = 1; i < argc; i++) {
      greetMsg(argv[i]);
    }
  }
}
