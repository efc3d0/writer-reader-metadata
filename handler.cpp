#include<iostream>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
using std::cout;
using std::endl;

class fileHandler
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

/* 
  From library
    TagLib::List<TagLib::FileRef> fileList; // list of files

    while(argc > 0 && isFile(argv[argc - 1])) { if count of arguments > 0 and [argv[argc-1]] isFile
      for example program start is -> file.mp3

    TagLib::FileRef f(argv[argc - 1]); // our file -> argv[argc-1]
*/
