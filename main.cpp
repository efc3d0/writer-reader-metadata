#include <iostream>
#include <taglib/taglib.h>
#include <taglib/fileref.h>
#include <taglib/tag.h>
using std::cout;
using std::endl;

int main(int argc, char *argv[])
{
  TagLib::FileRef file(argv[1]);

  if(!file.isNull() && file.tag())
    {
      TagLib::Tag * tag = file.tag();
      tag->setYear(10);
      cout << "Title: " << tag->title() << endl;
      cout << "Artist: " << tag->artist() << endl;
      cout << "Album:" << tag->album() << endl;
      cout << "Year: " << tag->year() << endl;
      cout << "Comment: " << tag->comment() << endl;
      cout << "Track: " << tag->track() << endl;
      cout << "Genre: " << tag->genre() << endl;
    }
  return 0;
}
