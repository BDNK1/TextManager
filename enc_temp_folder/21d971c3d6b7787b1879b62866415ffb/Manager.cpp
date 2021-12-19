#include "Header.h"
#include "TextTable.h"

vector<Archive*> Archives;
vector<Document*> Docs;
vector<Author*> Authors;
string projectPath;
double avgDocs() {
    double count = 0;
    double sum = 0;
    for (int i = 0; i < Archives.size(); i++) {
        sum += (double)Archives[i]->getDocsCount();
        count++;
    }
    return sum / count;
};
void menu() {
    int choose=-1;
    while (choose != 0) {
        cout <<endl<< "1) Show all archives" << endl << "2) Show all docs"<<endl<<"3) Find docs by author"<<endl<<"4) Find docs by date" << endl << "5) Create new archive" << endl << "6) Create new document" << endl << "7) Average number of documents in archives" << endl << "0) Exit" << endl;
        cin >> choose;


        switch (choose) {

        case 1:{
            int choose2 = -1;
            while (choose != 4) {
                showArchives();
                cout << endl << "1) Unpack archive" << endl << "2) View files inside archive" << endl << "3) Delete Archive" << endl << "4) Go back" << endl;
                cin >> choose2;
                switch (choose2) {
                     case 1:{
                        int numberFile;
                        cout<<endl << "enter number of archive: ";
                        cin >> numberFile;
                        Archives[--numberFile]->InCompress();
                        break;
                    }
                     case 2: {
                         int numberFile;
                         cout<<endl << "enter number of archive: ";
                         cin >> numberFile;
                         Archives[--numberFile]->showArchiveInfo();
                         break;
                     }
                     case 3: {
                         Archive::delArchive();
                         break;
                     }
                     case 4:
                         return;
                }
            }
            break;
        }

        case 2:{
            int choose3 = -1;
            while (choose3 != 4) {
                showDocs();
                cout << endl << "1) Open document" << endl << "2) Show keywords of document" << endl << "3) Delete file" << endl<<"4) Go back"<<endl;
                cin >> choose3;
                switch (choose3) {
                case 1: {
                    int numberDoc;
                    cout<<endl << "Enter number of file: ";
                    cin >> numberDoc;
                    Docs[--numberDoc]->openDoc();
                    Docs[numberDoc]->workWithDoc();
                    break;
                    }
                case 2: {
                    int numberDoc;
                    cout<<endl << "Enter number of file: ";
                    cin >> numberDoc;
                    vector<string> keys = Docs[--numberDoc]->getKeywords();
                    cout << endl;
                    for (int i = 0; i < keys.size(); i++) {

                        cout << keys[i] + " ";
                    };
                    
                    cout << endl;
                    break;
                    }
                case 3: {
                    Document::delDoc();
                    break;
                    }
                }
            }
            break;
        }
        case 3:{
            
            int choose3 = -1;
            while (choose3 != 4) {
                showAuthors();
                int choose;
                cout << endl << "enter number of Author";
                cin >> choose;
                choose--;
                showDocs(findByAuthor(Authors[choose]));
                cout << endl << "1) Open document" << endl << "2) Show keywords of document" << endl << "3) Delete file" << endl << "4) Go back" << endl;
                cin >> choose3;
                switch (choose3) {
                case 1: {
                    int numberDoc;
                    cout << endl << "Enter number of file: ";
                    cin >> numberDoc;
                    Docs[--numberDoc]->openDoc();
                    Docs[numberDoc]->workWithDoc();
                    break;
                }
                case 2: {
                    int numberDoc;
                    cout << endl << "Enter number of file: ";
                    cin >> numberDoc;
                    vector<string> keys = Docs[--numberDoc]->getKeywords();
                    cout << endl;
                    for (int i = 0; i < keys.size(); i++) {

                        cout << keys[i] + " ";
                    };

                    cout << endl;
                    break;
                }
                case 3: {
                    Document::delDoc();
                    break;
                }
                }
            }
            break; }
        case 4: {

            int choose3 = -1;
            while (choose3 != 4) {

                int d, m, y;
                cout << "year of birth ";
                cin >> y;
                cout << "month of birth: ";
                cin >> m;
                cout << "date of birth: ";
                cin >> d;
                Date* date = new Date(d, m, y);
                showDocs(findByDate(date));
                cout << endl << "1) Open document" << endl << "2) Show keywords of document" << endl << "3) Delete file" << endl << "4) Go back" << endl;
                cin >> choose3;
                switch (choose3) {
                case 1: {
                    int numberDoc;
                    cout << endl << "Enter number of file: ";
                    cin >> numberDoc;
                    Docs[--numberDoc]->openDoc();
                    Docs[numberDoc]->workWithDoc();
                    break;
                }
                case 2: {
                    int numberDoc;
                    cout << endl << "Enter number of file: ";
                    cin >> numberDoc;
                    vector<string> keys = Docs[--numberDoc]->getKeywords();
                    cout << endl;
                    for (int i = 0; i < keys.size(); i++) {

                        cout << keys[i] + " ";
                    };

                    cout << endl;
                    break;
                }
                case 3: {
                    Document::delDoc();
                    break;
                }
                }
            }
            break;
        }
        case 5:
            
            Archive::makeArchive();
            break;
        case 6:
            Document::makeDoc();
            break;
        case 7:
            cout<<avgDocs();
            break;
        case 0:
            cout << endl << "Bye!";
            exit(0);
        }
    }
}
void SplitString(string s, vector<string>& v) {

    string temp = "";
    for (int i = 0; i < s.length(); ++i) {

        if (s[i] == ' ') {
            v.push_back(temp);
            temp = "";
        }
        else {
            temp.push_back(s[i]);
        }

    }
    v.push_back(temp);

}

bool Date::leap(int y)const {
    return ((y % 4 == 0 && y % 100 != 0) || y % 400);
}

int Date::maxday()const {
    int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (leapyear)days[1] = 29;
    return days[month - 1];
}

Date& Date::operator+=(int d) {
    if (day + d > maxday()) {
        d -= maxday() - day;
        if (++month > 12) {
            month = 1;
            year++;
        }
        while (d / maxday()) {
            if (++month > 12) {
                month = 1;
                year++;
            }
            d -= maxday();
        }
        day = d;
    }
    else day += d;
    return *this;
}

Date& Date::operator-=(int d) {
    if (day - d < 1) {
        d -= day;
        if (--month == 0) {
            month = 12;
            year--;
        }
        while (d / maxday()) {
            d -= maxday();
            if (--month == 0) {
                month = 12;
                year--;
            }
        }
        day = maxday() - d;
    }
    else day -= d;
    return *this;
}

int Date::getDay()
{
    return day;
}

int Date::getMonth()
{
    return month;
}

int Date::getYear()
{
    return year;
}

std::string Date::operator-(Date& dt)const {
    int d, m, y;
    if (year >= dt.year) {
        y = year - dt.year;
        if (month > dt.month) {
            m = month - dt.month;
            d = day + dt.maxday() - dt.day;
            if (d > dt.maxday())d -= dt.maxday();
            else --m;
            --y;
        }
        else {
            m = 12 - month + dt.month;
            d = dt.day + maxday() - day;
            if (d > maxday())d -= maxday();
            else --m;
        }
    }
    else {
        y = dt.year - year;
        if (month > dt.month) {
            m = 12 - month + dt.month;
            d = day + dt.maxday() - dt.day;
            if (d > dt.maxday())d -= dt.maxday();
            else --m;
            --y;
        }
        else {
            m = dt.month - month;
            d = maxday() - day + dt.day;
            if (d > maxday())d -= maxday();
            else --m;
        }
    }
    std::string s;
    std::stringstream ss;
    ss << d << " days " << m << " month " << y << " years";
    getline(ss, s);
    return s;
}

bool Date::equals (Date& oth) {
    return day == oth.day && month == oth.month && year == oth.year;
}

void Date::show()
{
    std::string m[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
    cout << this->day << " " << m[this->month - 1] << " " << this->year;

}

string Date::toString()
{
    std::string m[] = { "January","February","March","April","May","June","July","August","September","October","November","December" };
    string date = to_string(this->day) + " " + m[this->month - 1] + " " + to_string(this->year)+"\0";
    return date;
}

bool Date::operator <= (const Date& d) const {
    if (this != &d) {
        if (year < d.year)
            return true;
        if (year > d.year)
            return false;
        if (month < d.month)
            return true;
        if (month > d.month)
            return false;
        if (day < d.day)
            return true;
        if (day > d.day)
            return false;
    }
    return true;
}



void initArchives()
{
    for (const auto& entry : fs::directory_iterator(projectPath)) {
        if (entry.path().extension().string() == ".zipper") {
            string path = (entry.path()).string();
            string filename = (entry.path().filename()).string();
            size_t lastindex = filename.find_last_of(".");
            filename = filename.substr(0, lastindex);
            int size = entry.file_size();
            Archive* arc = new Archive(filename, path,size);
        }
    }
}

void initDocs()
{
    for (const auto& entry : fs::directory_iterator(projectPath)) {
        if (entry.path().extension().string() == ".txt") {
            string path = (entry.path().string());
            string filename = (entry.path().filename()).string();
            size_t lastindex = filename.find_last_of(".");
            filename = filename.substr(0, lastindex);
            int size = entry.file_size();
            ifstream fin;
            fin.open(path);
            string surname, name;
            string keyword;
            vector<string> keywordsV;
            int d, m, y;
            fin >> name;
            fin >> surname;
            fin >> d;
            fin >> m;
            fin >> y;
            while (keyword != "|") {
                fin >> keyword;
                keywordsV.push_back(keyword);
            }
            Date* date = new Date(d,m,y);
            Author* author = Author::addAuthor(surname,name,date);
            Document* doc = new Document(filename, size,author,keywordsV);
        }
    }
}

void showAuthors()
{
    TextTable t2('-', '|', '+');
    t2.add("No ");
    t2.add(" Name ");
    t2.add(" Surname ");
    t2.add(" Year of birth ");
    t2.endOfRow();

    for (int i = 0; i < Authors.size(); i++) {
        t2.add(to_string(i + 1));
        t2.add(Authors[i]->getName());
        t2.add( Authors[i]->getSurname());
        t2.add(to_string(Authors[i]->getDateOfBirth()->getYear()));
        t2.endOfRow();
    }
    t2.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t2;
}

void showDocs()
{
    TextTable t('-', '|', '+');
    t.add("No ");
    t.add(" Name ");
    t.add(" Author ");
    t.add(" Date of creation ");
    t.add(" Size ");

    t.endOfRow();
    for (int i = 0; i < Docs.size(); i++) {
        t.add(to_string(i + 1));
        t.add(Docs[i]->getName());
        t.add(Docs[i]->getAuthor()->getName() +" "+ Docs[i]->getAuthor()->getSurname());
        t.add(Docs[i]->getDate()->toString());
        t.add(to_string(Docs[i]->getSize()));
        t.endOfRow();
    }
    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;

}
void showDocs(vector<int> arr)
{
    TextTable t('-', '|', '+');
    t.add("No ");
    t.add(" Name ");
    t.add(" Author ");
    t.add(" Date of creation ");
    t.add(" Size ");

    t.endOfRow();
    for (int i = 0; i < arr.size(); i++) {
        t.add(to_string(arr[i]+1));
        t.add(Docs[arr[i]]->getName());
        t.add(Docs[arr[i]]->getAuthor()->getName() + " " + Docs[arr[i]]->getAuthor()->getSurname());
        t.add(Docs[arr[i]]->getDate()->toString());
        t.add(to_string(Docs[arr[i]]->getSize()));
        t.endOfRow();
    }
    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;
}

void showArchives()
{
    TextTable t('-', '|', '+');
    t.add("No ");
    t.add(" Name ");
    t.add(" Date of creation ");
    t.add(" Size ");
    t.endOfRow();
    for (int i = 0; i < Archives.size(); i++) {
        t.add(to_string(i + 1));
        t.add(Archives[i]->getName());
        t.add(Archives[i]->getDate()->toString());
        t.add(to_string(Archives[i]->getSize()));
        t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;
}




vector<int> findByAuthor(Author* author)
{
    vector<int> arr;
    for (int i = 0; i < Docs.size(); i++) {
        if (Docs[i]->getAuthor()->equals(*author)) {
            arr.push_back(i);
        }
    }
    return arr;
}

vector<int> findByDate(Date* date)
{
    vector<int> arr;
    for (int i = 0; i < Docs.size(); i++) {
        if (Docs[i]->getDate()->equals(*date)) {
            arr.push_back(i);
        }
    }
    return arr;
}



void Archive::makeArchive()
{
    string name;
    int  choose =-1;
    vector<Document* > vec;
    vector<string> files;
    cout << "input name of archive: ";
    cin >> name;

    showDocs();

    while (choose != 0) {
        cout << "enter number of file that need to be included to archive, 0 to stop: ";
        cin >> choose;
        if (choose != 0) {
            choose--;
            files.push_back(Docs[choose]->getFullPath());
            Docs.erase(std::remove(Docs.begin(), Docs.end(), Docs[choose]), Docs.end());
            showDocs();
            choose++;
        }
    }
    Archive* arc = new Archive(files, name);
    arc->InCompress();
    arc->showArchiveInfo();
}


void Document::makeDoc()
{
    string name,res,text;
    vector<string> keywords;
    vector<string> allText;
    cout << "input name of document (without witespaces) : ";
    cin >> name;
    cout << "input text (print 's' to stop): ";
    cin.ignore();
    while (text != "s") {
        text = "";
        getline(cin, text);
        if (text != "s") { allText.push_back(text); }
    }
    
    Author* author = Author::addAuthor();
    cout <<"input keywords";
    cin.ignore();
    getline(cin, res);
    SplitString(res, keywords);

    ofstream o((projectPath+"\\" + name+".txt").c_str());
    o << author->getName() << endl << author->getSurname() << endl << author->getDateOfBirth()->getDay()<<" "<< author->getDateOfBirth()->getMonth()<<" "<< author->getDateOfBirth()->getYear() << endl ;
    for (int i = 0; i < keywords.size(); i++) {
        o << keywords[i]<<" ";
    }
    o << " |";
    o << endl;
    for (int i = 0; i < allText.size(); i++) {

        o << allText[i] << endl;
    }
    int x =fs::file_size(projectPath + "\\" + name + ".txt");

    Document* th = new Document(name, x,author,keywords);
    author->addDoc(th);
    
}

void Archive::delArchive()
{
    showArchives();
    int choose;
    cout << "input number of archive to delete: ";
    cin >> choose;
    choose--;
    string name = Archives[choose]->getName();
    remove(Archives[choose]->getFullPath().c_str());
    Archives.erase(Archives.begin() + choose);
    cout << "Archive " << name << "was deleted"<<endl;
}

void Document::delDoc()
{
    int choose;
    cout << "input number of file to delete: ";
    cin >> choose;
    choose--;
    remove(Docs[choose]->getFullPath().c_str());
    Docs.erase(Docs.begin() + choose);
}

void Document::workWithDoc()
{
    int choose = -1;
    while (choose != 3) {

        cout << "1) Add text" << endl << "2) Go back" << endl;
        cin >> choose;
        switch (choose) {
            case 1:
                addText();
                break;
            case 3:
                return;
        }
    }
}

void Document::addText()
{
    ofstream o((projectPath + "\\" + name + ".txt").c_str(), std::ios_base::app);
    string text;
    vector<string> allText;
    cout << "input text you want to add to end of file";
    cout << "input text (print 's' to stop): ";
    cin.ignore();
    while (text != "s") {
        text = "";
        getline(cin, text);
        if (text != "s") { allText.push_back(text); }
    }

    
    for (int i = 0; i < allText.size(); i++) {

        o << allText[i] << endl;
    }

}



void Archive::unpackArchive()
{
    showArchives();

        int  choose = 0;
        cout << "enter number of archive that need to be unpacked";
        cin >> choose;
        if (choose != 0) {
            choose--;
            Archive* x = Archives[choose];
            x->OutCompress(Archives[choose]->getFullPath());
        }
       
}

void initPath()
{
    cout << "enter path to working directory: ";
    cin >> projectPath;
    if (projectPath.at(0) == '\"') {
        projectPath = projectPath.substr(1, projectPath.size() - 2);
    }
    struct stat info;
    try
    {
        if (stat(projectPath.c_str(), &info) != 0)
            printf("cannot access %s\n", projectPath.c_str());
        else if (info.st_mode & S_IFDIR)  // S_ISDIR() doesn't exist on my windows 
            printf("%s is a working directory\n", projectPath.c_str());
        else
            printf("%s is no directory\n", projectPath.c_str());
        const auto& entry = fs::directory_iterator(projectPath);

    }
    catch (const std::exception&)
    {
        cout << "invalid input\n";
        initPath();
    }
}

Document::Document(string name, int size,Author* author, vector<string> keywords) : File(name,".txt",size){
    Docs.push_back(this);
    this->author = author;
    this->keywords = keywords;
    this->getKeywords();
}

File::File(string name, string format,int size)
{
    this->path = projectPath;
    this->name = name;
    this->format = format;
    this->size = size;
    string fullpath = this->getFullPath();
    char timeStr[100] = "";
    struct stat buf;
    time_t ltime;
    char datebuf[9]{};
    char timebuf[9]{};
    if (fs::exists(this->getFullPath())) {
        if (!stat(fullpath.c_str(), &buf))
        {
            strftime(timeStr, 100, "%d-%m-%Y", localtime(&buf.st_mtime));
            string d, m, y;
            d.push_back(timeStr[0]);
            d.push_back(timeStr[1]);
            m.push_back(timeStr[3]);
            m.push_back(timeStr[4]);
            y.push_back(timeStr[6]);
            y.push_back(timeStr[7]);
            y.push_back(timeStr[8]);
            y.push_back(timeStr[9]);
            int date = stoi(d);
            int month = stoi(m);
            int year = stoi(y);
            Date* dateOfCreation = new Date(date, month, year);

            this->dateOfCreation = dateOfCreation;
        };
    }
    else {
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        int curYear = now->tm_year + 1900;
        int curMonth = now->tm_mon + 1;
        int curDate = now->tm_mday;
        Date* dateOfCreation = new Date(curDate, curMonth, curYear);
        this->dateOfCreation = dateOfCreation;
    }
    
}

int digs(double w)
{
    int yield = 0;
    while (w > 10) { yield++; w /= 10; }
    return yield + 1;
}

Archive::Archive(string name, string real_bin_file,int size):File(name, ".zipper", size)
{
    this->real_bin_file = real_bin_file;
    Archives.push_back(this);
}

Archive::Archive(vector<string>& vec, string name) :File(name,".zipper",0)
{
    this->name = name;
    if (vec.size() > 0) files.assign(vec.begin(), vec.end());
    path = projectPath + "\\";
    real_bin_file = path + name + ".zipper";
    Archives.push_back(this);
}

void Archive::getInfo()
{
    char byte[1];
    basic_string<char> s_info = "";
    remove((this->path+"\\" + "info.txt").c_str());
    FILE* info = fopen((this->path+"\\" + "info.txt").c_str(), "a+");
    int bytes_size = 0;
    for (vector<string>::iterator itr = this->files.begin(); itr != this->files.end(); ++itr)
    {
        FILE* f = fopen((*itr).c_str(), "rb");
        if (!f) break;

        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        string name = Archive::get_file_name(*itr);
        char* m_size = new char[digs(size)];
        _itoa(size, m_size, 10);
        fclose(f);

        bytes_size += digs(size);
        bytes_size += strlen(name.c_str());

        s_info.append(m_size);
        s_info.append("||");
        s_info.append(name);
        s_info.append("||");

        //delete[] m_size;

    }
    bytes_size = s_info.size() + 2;
    char* b_buff = new char[digs(bytes_size)];
    _itoa(bytes_size, b_buff, 10);
    if (digs(bytes_size) < 5) fputs(string(5 - digs(bytes_size), '0').c_str(), info);
    fputs(b_buff, info);
    fputs("||", info);
    fputs(s_info.c_str(), info);

    fclose(info);
}

void Archive::InCompress()
{
    char byte[1];

    getInfo();
    FILE* f, * main = fopen((this->real_bin_file).c_str(), "wb");
    FILE* info = fopen((this->path+"\\" + "info.txt").c_str(), "rb");
    while (!feof(info))
    {
        if (fread(byte, 1, 1, info) == 1) fwrite(byte, 1, 1, main);
    }

    fclose(info);
    remove((this->path + "\\" + "info.txt").c_str());

    for (vector<string>::iterator itr = this->files.begin(); itr != this->files.end(); ++itr)
    {
        f = fopen((*itr).c_str(), "rb");
        if (!f) { cout << *itr << " not fined" << endl; break; }
        while (!feof(f))
        {
            if (fread(byte, 1, 1, f) == 1) fwrite(byte, 1, 1, main);
        }
        cout << *itr << " packed to '" << this->real_bin_file << "'." << endl;
        fclose(f);
        remove((*itr).c_str());
    }
    fclose(main);
}

string File::getName()
{
    return this->name;
}

Date* File::getDate()
{
    return dateOfCreation;
}


void Document::openDoc()
{
    cout<<endl<<"    " << name<<endl;
    ifstream fin;
    fin.open(path+"\\"+name + format);
    string buf;
    string text;
    while (buf != "|") {
        fin >> buf;
    }
    while (!fin.eof()) {
        text = "";
        getline(fin, text);
        cout << text<<endl;
    }
}


Author* Document::getAuthor()
{
    return this->author;
}


vector<string> Document::getKeywords()
{
    return keywords;


}

string File::getFullPath()
{
    return this->path+"\\"+this->name+this->format;
}

int File::getSize()
{
    return size;
}

void Archive::showArchiveInfo()
{
    string binary = this->getFullPath();
    FILE* bin = fopen(binary.c_str(), "rb");
    char info_block_size[5];
    fread(info_block_size, 1, 5, bin);
    int _sz = atoi(info_block_size);

    char* info_block = new char[_sz];
    fread(info_block, 1, _sz, bin);

    vector<string> tokens;
    char* tok = strtok(info_block, "||");
    int toks = 0;
    while (tok)
    {
        if (strlen(tok) == 0) break;
        tokens.push_back(tok);
        tok = strtok(NULL, "||");
        toks++;
    }
    if (toks % 2 == 1) toks--;
    int files = toks / 2;

    TextTable t('-', '|', '+');
    t.add("Name of file");
    t.add("Size of file");
    t.endOfRow();
    for (int i = 0; i < tokens.size()-1; i+=2) {
        
            t.add(tokens[i+1]);
            t.add(tokens[i]);
            t.endOfRow();
    }
    t.setAlignment(2, TextTable::Alignment::RIGHT);
    cout << t;
}
int Archive::getDocsCount()
{
    string binary = this->getFullPath();
    FILE* bin = fopen(binary.c_str(), "rb");
    char info_block_size[5];
    fread(info_block_size, 1, 5, bin);
    int _sz = atoi(info_block_size);

    char* info_block = new char[_sz];
    fread(info_block, 1, _sz, bin);

    vector<string> tokens;
    char* tok = strtok(info_block, "||");
    int toks = 0;
    while (tok)
    {
        if (strlen(tok) == 0) break;
        tokens.push_back(tok);
        tok = strtok(NULL, "||");
        toks++;
    }
    if (toks % 2 == 1) toks--;
    int files = toks / 2;

    return files;
}

void Archive::OutCompress(string binary)
{
    FILE* bin = fopen(binary.c_str(), "rb");
    char info_block_size[5];
    fread(info_block_size, 1, 5, bin);
    int _sz = atoi(info_block_size);

    char* info_block = new char[_sz];
    fread(info_block, 1, _sz, bin);

    vector<string> tokens;
    char* tok = strtok(info_block, "||");
    int toks = 0;
    while (tok)
    {
        if (strlen(tok) == 0) break;
        tokens.push_back(tok);
        tok = strtok(NULL, "||");
        toks++;
    }
    if (toks % 2 == 1) toks--;
    int files = toks / 2;

    char byte[1];

    for (int i = 0; i < files; i++)
    {
        const char* size = tokens[i * 2].c_str();
        const char* name = tokens[i * 2 + 1].c_str();
        char full_path[255];
        strcpy(full_path, this->path.c_str());
        strcat(full_path, "\\");
        strcat(full_path, name);
        int _sz = atoi(size);
        cout << "--  '" << name << "' unpacked to '" << this->path << "' ." << endl;
        FILE* curr = fopen(full_path, "wb");
        for (int r = 1; r <= _sz; r++)
        {
            if (fread(byte, 1, 1, bin) == 1) fwrite(byte, 1, 1, curr);
        }
        fclose(curr);

        //delete[] size;
        //delete[] name;
    }
    fclose(bin);
    remove(binary.c_str());
}

Person::Person(string surname, string name, Date* dateOfBirth)
{
    this->surname = surname;
    this->name = name;
    this->dateOfBirth = dateOfBirth;
}
Author::Author(string surname, string name, Date* dateOfBirth):Person(surname,name,dateOfBirth)
{

}

Author* Author::addAuthor()
{
    string name, surname;
    Date* date;
    cout << "input Surname: ";
    cin >> surname;
    cout << "input name: ";
    cin >> name;
    int d, m, y;
    cout << "year of birth ";
    cin >> y;
    cout << "month of birth: ";
    cin >> m;
    cout << "date of birth: ";
    cin >> d;
    date = new Date(d, m, y);
    for (int i = 0; i < Authors.size(); i++) {
        if (Authors[i]->getSurname() == surname && Authors[i]->getName() == name && Authors[i]->getDateOfBirth()->equals(*date)) {
            return Authors[i];
        }
    }
    Author* author = new Author(surname, name, date);
    Authors.push_back(author);
    return author;
}
Author* Author::addAuthor(string surname, string name, Date* date)
{   
    
    for (int i = 0; i < Authors.size(); i++) {
        if (Authors[i]->getSurname() == surname && Authors[i]->getName() == name && Authors[i]->getDateOfBirth() == date) {
            return Authors[i];
        }
    }
    Author* author = new Author(surname, name, date);
    Authors.push_back(author);
    return author;
}

string Author::getName()
{
    return name;
}

string Author::getSurname()
{
    return surname;
}

bool Author::equals (Author& oth) 
{
    if (oth.getSurname() == surname && oth.getName() == name && oth.getDateOfBirth() == dateOfBirth) {
        return true;
    }
    else {
        return false;
    }
}

void Author::addDoc(Document* doc)
{

}


Date* Author::getDateOfBirth()
{
    
    return dateOfBirth;
}
