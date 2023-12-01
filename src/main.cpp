#include <iostream>

#include <computer.h>
#include <memory.h>

using namespace std;

int main(int argc, char **argv) {
  Memory *memory = new Memory;

  if (argc != 2) {
    cout << "\x1b[31m[error]\x1b[37m you must input 1 file name\n";
    return 0;
  }

  if (memory->load_program(argv[1])) {
    cout << "\x1b[31m[error]\x1b[37m failed to load program\n";
    return 0;
  }
  cout << "\x1b[32m[info]\x1b[37m program loaded\n";

  Computer computer(memory);
  cout << "\x1b[32m[info]\x1b[37m start computer\n";
  computer.run();
  cout << "\x1b[32m[info]\x1b[37m terminated\n";

  return 0;
}
