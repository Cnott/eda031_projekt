#include "diskdatabase.h"

using namespace std;

DiskDatabase::DiskDatabase() {
  latestNewsgroupID = 0;
  latestArticleID = 0;

  infoDatabase();
}

void DiskDatabase::infoDatabase() {
  unsigned char isFile = 0x8;
  // Check if db exists - otherwise create the required directory
  DIR* dbRootDir;
  struct dirent* ng_dirent;
  if (!(dbRootDir = opendir(dbRoot))) {
    cout << "No database exists at " << dbRoot << ".\n Creating a new one.\n";
    mkdir(dbRoot, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    latestNewsgroupID = 0;
    return;
  }

  // List all newsgroups
  // cout << "Newsgroups in database: " << endl;
  // while((ng_dirent = readdir(dbRootDir))) {
  //   string ngName = ng_dirent->d_name;
  //   if (!(ngName == "." | ngName == ".."))
  //     cout << ng_dirent->d_name << " ";
  // }
  // cout << endl;

  // List all articles in each newsgroup
  cout << "\nDATABASE\n--------\n";
  DIR* ngDir;
  struct dirent* art_dirent;
  rewinddir(dbRootDir);
  while(ng_dirent = readdir(dbRootDir)) {
    string ngName = ng_dirent->d_name;
    if (!(ngName == "." | ngName == "..")) {
      cout << ngName << " ";
      string ngRoot = dbRoot;
      ngRoot += "/" + ngName;
      ngDir = opendir(ngRoot.c_str());
      cout << endl;
      while (art_dirent = readdir(ngDir)) {
          char* artId = art_dirent->d_name;
          if (art_dirent->d_type != 0x4) {
            cout << artId << " ";
        }
      }
    }
    cout << endl;
  }
  cout << endl;


}
