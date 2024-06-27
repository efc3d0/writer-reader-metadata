/*#include "handler.cpp"
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
}*/

#include "handler.cpp"
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

static void glfw_error_callback(int error, const char *description) {
  fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int argc, char *argv[]) {
  glfwSetErrorCallback(glfw_error_callback);
  if (!glfwInit())
    return 1;
  app *application = new app;
  application->Init(argv[1]);
}