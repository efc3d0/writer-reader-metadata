#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl2.h"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <taglib/fileref.h>
#include <taglib/tag.h>
#include <taglib/taglib.h>
#include <taglib/tpropertymap.h>
using std::cout;
using std::endl;

/*class fileHandler
{
public:
    virtual void read_file() = 0;
    virtual void write_file() = 0;
} ;

class fileReader : public fileHandler
{
private:
  TagLib::FileRef f;
public:
  [[ nodiscard ]] fileReader(char const * path)
  {
      TagLib::FileRef temp(path);
      this->f = temp;
  }
  ~fileReader() {}

  virtual void read_file()
  {
    if(!f.isNull() && f.tag())
    {
      cout << "\n\n\--------Main--------\n\n";
      TagLib::Tag * tag = this->f.tag();
      cout << "Title: " << tag->title() << endl;;
      cout << "Artist: " << tag->artist() << endl;;
      cout << "Album: " << tag->album() << endl;;
      cout << "Year: " << tag->year() << endl;
      cout << "Comment: " << tag->comment() << endl;
      cout << "Track: " << tag->track() << endl;
      cout << "Genre: " << tag->genre() << endl;

      TagLib::AudioProperties *properties = f.audioProperties();

      int seconds = properties->lengthInSeconds() & 60;
      int minutes = (properties->lengthInSeconds() - seconds) / 60;

      cout << "\n\n---- AUDIO ----\n\n";
      cout << "bitrate  - " << properties->bitrate() << endl;
      cout << "sample rate  - " << properties->sampleRate() << endl;
      cout << "channels   - " << properties->channels() << endl;
      cout << "length      - " << minutes << ":" << seconds << endl;
      return;
    }
  }
  virtual void write_file() {}
} ;

class fileWriter: public fileHandler
{
private:
  TagLib::FileRef f;
public:
  [[ nodiscard ]] fileWriter(char const * file)
  {
    TagLib::FileRef temp(file);
    this->f = temp;
  }
  ~fileWriter() {}
  virtual void read_file() {}
  virtual void write_file()
  {
    TagLib::Tag * tag = this->f.tag();
    char * choose = new char;
    char temp;
    X:
    for( ; ; )
    {
      cout << "1 -> setTitle\n" << endl;
      cout << "2 -> setArtist\n" << endl;
      cout << "3 -> setAlbum\n" << endl;
      cout << "4 -> setYear\n" << endl;
      cout << "5 -> setComment\n" << endl;
      cout << "6 -> setTrack\n" << endl;
      cout << "7 -> setGenre\n" << endl;
      do
      {
        std::cin >> temp;
        switch (temp) // we can use *"" for char
        {
          case '1':
            cout << "setTitle to: " << endl;
            std::cin>>choose;
            tag->setTitle(choose);
            goto X;
            break;
          case '2':
            cout << "setArtist to: " << endl;
            std::cin>>choose;
            tag->setArtist(choose);
            goto X;
            break;
          case '3':
            cout << "setAlbum to: " << endl;
            std::cin>>choose;
            tag->setAlbum(choose);
            goto X;
            break;
          case '4':
            short temp_i;
            cout << "setYear to \n" << endl;
            std::cin>>temp_i;
            tag->setYear(temp_i);
            goto X;
            break;
          case '5':
            cout << "setComment to: " << endl;
            std::cin>>choose;
            tag->setComment(choose);
            goto X;
            break;
          case '6':
            cout << "setTrack to: " << endl;
            std::cin>>temp_i;
            tag->setTrack(temp_i);
            goto X;
            break;
          case '7':
            cout << "setGenre to: " << endl;
            std::cin>>choose;
            tag->setGenre(choose);
            goto X;
            break;
          default:
            break;
        }
      } while (temp != 'q');
      delete choose;
      f.save();
      break;
    }
  }
} ;
*/
class app {
public:
  void Init(char const *st) {
    GLFWwindow *window =
        glfwCreateWindow(1280, 720, "wreader! writer-reader", nullptr, nullptr);
    if (window == nullptr)
      return;
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |=
        ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls

    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL2_Init();
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
    TagLib::FileRef f(st);
    TagLib::Tag *tag = f.tag();
    TagLib::AudioProperties *prop = f.audioProperties();
    int seconds = prop->lengthInSeconds() & 60;
    int minutes = (prop->lengthInSeconds() - seconds) / 60;
    /*const char * title = tag->title().toCString(true);
    const char * artist = tag->artist().toCString(true);
    const char * album = tag->album().toCString(true);
    const char * comment = tag->comment().toCString(true); * bad code with
    const_cast<>() bad code*/
    short *year = new short;
    short *track = new short;
    char title[128] = "";
    char artist[128] = "";
    char album[128] = "";
    char comment[128] = "";
    char genre[128] = "";
    bool set_window = false;
    bool addition_information_window = false;
    strcpy(title, tag->title().toCString(true));
    strcpy(artist, tag->artist().toCString(true));
    strcpy(album, tag->album().toCString(true));
    strcpy(comment, tag->comment().toCString(true));
    strcpy(genre, tag->genre().toCString(true));
    *year = tag->year();
    *track = tag->track();
    // Main loop
    while (!glfwWindowShouldClose(window)) {
      // Poll and handle events (inputs, window resize, etc.)
      // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to
      // tell if dear imgui wants to use your inputs.
      // - When io.WantCaptureMouse is true, do not dispatch mouse input data to
      // your main application, or clear/overwrite your copy of the mouse data.
      // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input
      // data to your main application, or clear/overwrite your copy of the
      // keyboard data. Generally you may always pass all inputs to dear imgui,
      // and hide them from your application based on those two flags.
      glfwPollEvents();

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL2_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
      {
        ImGui::Begin("reader");
        ImGui::SetCursorPos(ImVec2(5.5, 50.5));
        ImGui::Text("Title: %s", tag->title().toCString(true));
        ImGui::SetCursorPos(ImVec2(6, 80.5));
        ImGui::Text("Artist: %s", tag->artist().toCString(true));
        ImGui::SetCursorPos(ImVec2(7.5, 110.5));
        ImGui::Text("Album: %s", tag->album().toCString(true));
        ImGui::SetCursorPos(ImVec2(7.5, 140.5));
        ImGui::Text("Year: %d", tag->year());
        ImGui::SetCursorPos(ImVec2(5, 170.5));
        ImGui::Text("Comment: %s", tag->comment().toCString(true));
        ImGui::SetCursorPos(ImVec2(6, 200.5));
        ImGui::Text("Track: %d", tag->track());
        ImGui::SetCursorPos(ImVec2(6, 230.5));
        ImGui::Text("Genre: %s", tag->genre().toCString(true));
        ImGui::SetCursorPos(ImVec2(6, 260.5));
        if (ImGui::Button("Edit "))
          set_window = true;
        if (ImGui::Button("Additional information "))
          addition_information_window = true;
        ImGui::End();

        if (set_window) {
          ImGui::Begin("writer", &set_window);
          if (ImGui::InputText("Change Title to: ", const_cast<char *>(title),
                               sizeof(title)))
            tag->setTitle(title);
          if (ImGui::InputText("Change Artist to: ", const_cast<char *>(artist),
                               sizeof(artist)))
            ;
          tag->setArtist(artist);
          if (ImGui::InputText("Change Album to: ", const_cast<char *>(album),
                               sizeof(album)))
            ;
          tag->setAlbum(album);
          /*if(ImGui::InputInt("Change Year to: ", reinterpret_cast< int *
            >(year), sizeof(year))); tag->setYear(*year);*/
          ImGui::SliderInt("Change Year to: ", reinterpret_cast<int *>(year), 1,
                           4000);
          tag->setYear(*year);
          if (ImGui::InputText("Change Comment to: ",
                               const_cast<char *>(comment), sizeof(comment)))
            ;
          tag->setComment(comment);
          // if(ImGui::InputInt("Change Track to: ", reinterpret_cast< int *
          // >(track), sizeof(track))); tag->setTrack(*track);
          ImGui::SliderInt("Change Track to: ", reinterpret_cast<int *>(track),
                           0, 4000);
          tag->setTrack(*track);
          if (ImGui::InputText("Change Genre to: ", genre, sizeof(genre)))
            ;
          tag->setGenre(genre);
          if (ImGui::Button("Save file changes"))
            f.save();
          ImGui::End();
          if (addition_information_window) {
            ImGui::Begin("Additional information");
            ImGui::Text("Bitrate  -  %d", prop->bitrate());
            ImGui::Text("Sample Rate  - %d", prop->sampleRate());
            ImGui::Text("Channels   - %d", prop->channels());
            ImGui::Text("Length   - %d : %d", minutes, seconds);
            ImGui::End();
          }
        }
      }

      // Rendering
      ImGui::Render();
      int display_w, display_h;
      glfwGetFramebufferSize(window, &display_w, &display_h);
      glViewport(0, 0, display_w, display_h);
      glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w,
                   clear_color.z * clear_color.w, clear_color.w);
      glClear(GL_COLOR_BUFFER_BIT);

      ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

      glfwMakeContextCurrent(window);
      glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    delete year;
    delete track;
    glfwDestroyWindow(window);
    glfwTerminate();
  }
};

/*
  From library
    TagLib::List<TagLib::FileRef> fileList; // list of files

    while(argc > 0 && isFile(argv[argc - 1])) { if count of arguments > 0 and
  [argv[argc-1]] isFile for example program start is -> file.mp3

    TagLib::FileRef f(argv[argc - 1]); // our file -> argv[argc-1]
*/
