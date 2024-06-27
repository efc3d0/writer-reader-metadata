#include "handler.cpp"
int main(int argc, char * argv[])
{
  fileHandler * filehandle;
  fileReader * reader = new fileReader(argv[1]);
  fileWriter * writer = new fileWriter(argv[1]);

  filehandle = reinterpret_cast< fileReader * >(reader);
  filehandle->read_file();
  filehandle = reinterpret_cast< fileWriter * >(writer);
  filehandle->write_file();
  filehandle = reinterpret_cast< fileReader * >(reader);
  filehandle->read_file();

  delete reader;
  delete writer;
  return 0;
}
