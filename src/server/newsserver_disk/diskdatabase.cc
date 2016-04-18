#include "diskdatabase.h"

using namespace std;

const bool DEBUG = false;

DiskDatabase::DiskDatabase() : tmpArticle(0, "", "", "") {
  latestNewsgroupID = 0;

  initDatabase();
  if (DEBUG) print();
  saveDBInfo();
}

/*  Reads the latest article id from a file in the appropriate
    newsgroup.
*/
unsigned int DiskDatabase::latestArticleId( unsigned int ngId ) {
  ifstream ifs(path(ngId) + "/.dbinfo", ifstream::in);    // path to newsgroup

  unsigned int aId;
  string tmp;
  getline(ifs, tmp);          // first line is ngName
  ifs >> tmp;
  aId = stoul(tmp);           // this is the lates article id
  ifs.close();

  return aId;
}

/*  Returns the path to the newsgroup with the id ngId */
string DiskDatabase::path(unsigned int ngId) {
  return dbRoot + to_string(ngId);
}

/*  Returns the path to the article with the id aId, in the newsgroup
    with ngId.
*/
string DiskDatabase::path(unsigned int ngId, unsigned int aId) {
  return path(ngId) + "/" + to_string(aId);
}

/*  Save relevant info for the database. Atm, this is just the latest ngId */
void DiskDatabase::saveDBInfo() {
  ofstream ofs(dbRoot + ".dbinfo", ofstream::out);

  ofs << to_string(latestNewsgroupID) << endl;
  ofs.close();
}

/*  Adds a newsgroup with the name 'name' to the database, if it does not
    already exist.
*/
bool DiskDatabase::addNewsgroup(string name) {
  if (newsgroupInDB(name)) return false;

  string path = dbRoot;
  path.append("/" + to_string(++latestNewsgroupID));
  mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
  saveNGInfo(name, latestNewsgroupID, 0);

  saveDBInfo();
  return true;
}

/*  Adds an article to the database if the newsgroup with id ngId already
    exists. Article parameters are 'title', 'author' and 'text'.
*/
bool DiskDatabase::addArticle(unsigned int ngId,
                              std::string  title,
                              std::string  author,
                              std::string  text) {
  DIR   *ngDir;

  if (!(ngDir = opendir(path(ngId).c_str()))) return false;

  unsigned int aId = latestArticleId(ngId);
  aId++;
  ofstream ofs(path(ngId, aId), ofstream::out);
  ofs << title << endl << author  << endl << text;
  ofs.close();

  saveNGInfo(getNewsgroupName(ngId), ngId, aId);
  saveDBInfo();
  return true;
}

vector<Newsgroup> DiskDatabase::listNewsgroups() {
  dirent *ng_dirent;

  vector<Newsgroup> ngDB;
  list<unsigned int> ngOrder;


  rewinddir(dbRootDir);
  while (ng_dirent = readdir(dbRootDir)) {
    string ngIdStr = ng_dirent->d_name;

    if (!(ngIdStr == "." | ngIdStr == "..") && (ng_dirent->d_type == isDir)) {
      unsigned int ngId = stoul(ngIdStr);
      ngOrder.push_back(ngId);
    }
  }

  ngOrder.sort();

  for (unsigned int i : ngOrder) {
    Newsgroup ng(i, getNewsgroupName(i));
    ngDB.push_back(ng);
  }

  return ngDB;
}

bool DiskDatabase::removeArticle(unsigned int ngId, unsigned int aId) {
    // does the ng exist?
    if (!newsgroupInDB(ngId)) return false;

    return remove(path(ngId, aId).c_str()) == 0;
}

bool DiskDatabase::newsgroupInDB(unsigned int ngId) {
  string ngName = getNewsgroupName(ngId);
  return newsgroupInDB(ngName);
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

  rmdir(ngRoot.c_str());
  closedir(ngDir);

  return true;
}

void DiskDatabase::saveNGInfo(std::string name, unsigned int ngId,
                                                unsigned int aId  ) {
  ofstream ofs(path(ngId) + "/.dbinfo", ofstream::out);

  ofs << name << endl << aId;
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

  if (!(dbRootDir = opendir(dbRoot.c_str()))) {
    cout << "No database exists at " << dbRoot << ".\n Creating a new one.\n";
    mkdir(dbRoot.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    latestNewsgroupID = 0;
    dbRootDir = opendir(dbRoot.c_str());
    return;
  }

  string   path = dbRoot;
  ifstream ifs(path + ".dbinfo", ifstream::in);
  ifs >> latestNewsgroupID;// >> latestArticleId();
  ifs.close();
}

void DiskDatabase::print() {
  vector<Newsgroup> ngDB= listNewsgroups();
  for (auto ng : ngDB) {
    cout << ng.getName() << endl;
    vector<Article> artDB = listArticles(ng.getId());
    for (auto a : artDB) {
      cout << a.getTitle() << " ";
    }
  }
}

string DiskDatabase::getNewsgroupName(unsigned int ngId) {
  string ngPath = path(ngId);
  ngPath.append("/.dbinfo");
  ifstream ifs(ngPath, ifstream::in);

  string ngName;
  getline(ifs, ngName);
  ifs.close();

  return ngName;
}

vector<Article> DiskDatabase::listArticles(unsigned int ngId) {
  DIR* ngDir;
  dirent* art_dirent;
  ngDir = opendir(path(ngId).c_str());


  list<unsigned int> artOrder;
  while (art_dirent = readdir(ngDir)) {
    string artId = art_dirent->d_name;
    if (artId != "." && artId != ".." && artId != ".dbinfo") {
      artOrder.push_back(stoul(artId));
    }
  }

  closedir(ngDir);

  artOrder.sort();

  vector<Article> articles;
  for (unsigned int i : artOrder) {
    Article art = getArticle(ngId, i);
    articles.push_back(art);
  }

  return articles;
}

const Article& DiskDatabase::getArticle(unsigned int ngId, unsigned int aId) {
  string title, author;
  string text = "";

  ifstream ifs(path(ngId, aId), ifstream::in);
  getline(ifs, title);
  getline(ifs, author);
  stringstream buffer;
  buffer << ifs.rdbuf();
  text = buffer.str();

  tmpArticle = Article(aId, title, author, text);

  return tmpArticle;
}

bool DiskDatabase::articleInDB(unsigned int ngId, unsigned int aId) {
  DIR* ngDir;
  dirent* a_dirent;
  ngDir = opendir(path(ngId).c_str());

  while (a_dirent = readdir(ngDir)) {
    string aIdStr = a_dirent->d_name;
    if (aIdStr != "." && aIdStr != ".."
                      && aIdStr != ".dbinfo"
                      && stoul(aIdStr) == aId) {
        closedir(ngDir);
        return true;
    }
  }
  closedir(ngDir);
  return false;
}
