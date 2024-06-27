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

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main(int argc, char * argv[])
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;
    app * application = new app;
    application->Init(argv[1]);
    return 0;
}