#include "diskdatabase.h"

using namespace std;

const bool DEBUG = true;

DiskDatabase::DiskDatabase() : tmpArticle(0, "", "", ""){
  latestNewsgroupID = 0;
  latestArticleID   = 0;

  initDatabase();

  if (DEBUG) print();

  // check if in db
  // if (newsgroupInDB("comp.lang.c++")) cout << "found comp.lang.c++" << endl;
  //
  // // try adding to db
  // if (addNewsgroup("test.ng.1")) {
  //   if (newsgroupInDB("test.ng.1")) cout << "created test.ng.1" << endl;
  // } else {
  //   cout << "test.ng.1 was already in the database" << endl;
  // }

  // try adding article
  // if (addArticle(latestNewsgroupID, "Article 1", "Author Name",
  //                "This is the text of the article")) cout <<
  //   "Added Article " << latestArticleID << " to ng "  << latestNewsgroupID << endl;
  //
  // if(removeArticle(6, 7))
  //   cout << "removed article" << endl;
  //else
  //  cout << "failed to remove article" << endl;

  Article tmp = getArticle(6, 10);
  cout << endl << tmp.getTitle() << endl << tmp.getAuthor() << endl << tmp.getText() << endl;

  removeNewsgroup(6);

  vector<Newsgroup> ngDB = listNewsgroups();
  for (Newsgroup ng : ngDB) {
    cout << ng.getId() << " - " << ng.getName() << endl;
  }

  saveDBInfo();
}

void DiskDatabase::saveDBInfo() {
  string   path = dbRoot;
  ofstream ofs(path + ".dbinfo", ofstream::out);

  ofs << to_string(latestNewsgroupID) << endl << to_string(latestArticleID);
  ofs.close();
}

bool DiskDatabase::addNewsgroup(string name) {
  if (newsgroupInDB(name)) return false;

  string path = dbRoot;
  path.append("/" + to_string(++latestNewsgroupID));
  mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  saveNewsgroupInfo(path.append("/"), name);

  return true;
}

bool DiskDatabase::addArticle(unsigned int ngId,
                              std::string  title,
                              std::string  author,
                              std::string  text) {
  DIR   *ngDir;
  string path = dbRoot + to_string(ngId);

  if (!(ngDir = opendir(path.c_str()))) return false;

  ofstream ofs(path + "/" + to_string(++latestArticleID), ofstream::out);
  ofs << title << endl << author  << endl << text;
  ofs.close();

  return true;
}

vector<Newsgroup> DiskDatabase::listNewsgroups() {
  cout << "got into listNewsgroups.. " << endl;
  dirent *ng_dirent;

  vector<Newsgroup> ngDB;

  rewinddir(dbRootDir);
  while (ng_dirent = readdir(dbRootDir)) {
    string ngIdStr = ng_dirent->d_name;

    if (!(ngIdStr == "." | ngIdStr == "..") && (ng_dirent->d_type == isDir)) {
      unsigned int ngId = stoul(ngIdStr);
      Newsgroup ng(ngId, getNewsgroupName(ngId));
      ngDB.push_back(ng);
    }
  }

  return ngDB;
}

bool DiskDatabase::removeArticle(unsigned int ngId, unsigned int aId) {
    // does the ng exist?
    if (!newsgroupInDB(ngId)) return false;

    // try to remove article from ng
    string path = dbRoot;
    path.append(to_string(ngId) + "/" + to_string(aId));

    return remove(path.c_str()) == 0;
}

bool DiskDatabase::newsgroupInDB(unsigned int ngId) {
  string path = dbRoot;
  path.append(to_string(ngId));
  return opendir(path.c_str());
}

bool DiskDatabase::removeNewsgroup(unsigned int ngId) {
  // probe dir
  // dirent *ng_dirent;
  // rewinddir(dbRootDir);

  if (!newsgroupInDB(ngId)) return false;

  dirent* art_dirent;
  DIR* ngDir;
  string ngRoot = dbRoot;
  ngRoot.append(to_string(ngId));
  ngDir   = opendir(ngRoot.c_str());

  // iterate through articles and remove them
  while (art_dirent = readdir(ngDir)) {
    string artId = art_dirent->d_name;
    if (artId == ".dbinfo") {
      string path = ngRoot;
      path.append("/.dbinfo");
      remove(path.c_str());
    } else if (artId != "." && artId != ".."){
      removeArticle(ngId, stoul(artId));
    }
  }

  return rmdir(ngRoot.c_str()) != 0;
}

void DiskDatabase::saveNewsgroupInfo(string path, string name) {
  ofstream ofs(path + ".dbinfo", ofstream::out);

  ofs << name;
  ofs.close();
}

bool DiskDatabase::newsgroupInDB(string name) {
  // probe dir
  dirent *ng_dirent;

  rewinddir(dbRootDir);

  while (ng_dirent = readdir(dbRootDir)) { // for all files/dirs in root
    string ngIdStr = ng_dirent->d_name;    // get name of file = ngId
    unsigned int ngId;

    // probe all directories, excluding root and parent dir
    if (((ngIdStr != ".") &&
         (ngIdStr != ".."))  && (ng_dirent->d_type == isDir)) {
      ngId = stoul(ngIdStr);

      if (getNewsgroupName(ngId) == name) { // get name of current ng
        return true;
      }
    }
  }
  return false;
}

void DiskDatabase::initDatabase() {
  // Check if db exists - otherwise create the required directory
  dirent *ng_dirent;

  if (!(dbRootDir = opendir(dbRoot))) {
    cout << "No database exists at " << dbRoot << ".\n Creating a new one.\n";
    mkdir(dbRoot, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    latestNewsgroupID = 0;
    return;
  }

  string   path = dbRoot;
  ifstream ifs(path + ".dbinfo", ifstream::in);
  ifs >> latestNewsgroupID >> latestArticleID;
  ifs.close();
}

void DiskDatabase::print() {
  DIR *ngDir;
  dirent *ng_dirent;
  dirent *art_dirent;

  rewinddir(dbRootDir);
  cout << endl << "Database Contents:" << endl;

  while (ng_dirent = readdir(dbRootDir)) {
    string ngId = ng_dirent->d_name;

    if (!(ngId == "." | ngId == "..") && (ng_dirent->d_type == isDir)) {
      cout << getNewsgroupName(stoul(ngId)) << " ";
      string ngRoot = dbRoot;
      ngRoot += "/" + ngId;
      ngDir   = opendir(ngRoot.c_str());
      cout << endl;

      while (art_dirent = readdir(ngDir)) {
        string artId = art_dirent->d_name;

        if (art_dirent->d_type != isDir && artId != ".dbinfo") {
          cout << artId << " ";
        }
      }
      cout << endl;
    }
  }
}

string DiskDatabase::getNewsgroupName(unsigned int ngId) {
  string path = dbRoot;

  path.append("/" + to_string(ngId) + "/.dbinfo");
  ifstream ifs(path, ifstream::in);

  string ngName;
  getline(ifs, ngName);
  ifs.close();

  return ngName;
}

const Article& DiskDatabase::getArticle(unsigned int ngID, unsigned int artID) {
  string title, author;
  string text = "";
  string path = dbRoot;
  path.append(to_string(ngID) + "/" + to_string(artID));

  ifstream ifs(path, ifstream::in);
  getline(ifs, title);
  getline(ifs, author);
  string line = "";
  while (getline(ifs, line)) {
    text.append(line);
    line = "";
  }

tmpArticle = Article(artID, title, author, text);
return tmpArticle;
}
