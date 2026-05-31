#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

string filecource;
string fileca;
const string line = "---------------------------------------------------------------------------------------------------";
const string dline = "==================================================================================================";

struct course{
    int caNumber = 0;
    string courseName;
    string courseGrade= "IN PROGRESS";
    double remaingMarks = 100;
    double marksOnCa = 0;

};

struct ca{
    string grade;
    int caNumber;
    double caPercent;
    double value;
};

struct courseCa{
    int courseIndex;
    int caIndex;
};
void clearScrean();
string calcGrade(const double& mark);
double percent();

template <typename T>
T getValidInput(const string& question){
    T value;
    do{
        cout << question<<": ";
        if(!(cin>>value)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"invalid entry"<<endl;
            value = -1; 
        }
        cin.ignore();
    }while(value < 0);
    return value;
}

double calcValue(double& value, double& remaining, double& onCa, double& cavalue){
    double value2;
    double value3;
    
    bool running = true;
    while(running){
        cavalue = getValidInput<double>("what percent does the contineous assessment add to the final results");
        value3 = (value/100) * cavalue;
        if(value3 > 100 || value3 < 0){
            cout<<"sorry value cant bypass the 100 mark\n press any key to reenter contribution value and q to leave: ";
            string choice;
            getline(cin, choice);
            if(choice == "q" || choice == "Q"){
                return -1.00;
            }
        }
        else{
            onCa = value3 + onCa;
            if(onCa > 100) {
                cout << "your marks on ca are ecceedng 100\n press any key to reenter value and q to exit: ";
                string choice;
                getline(cin, choice);
                if(choice == "q" || choice == "Q"){
                    return -1.00;
                }
            }
            else{
                remaining = remaining - cavalue;
                running = false;
            }
        }


    
    }
    return value3;
}
void addCourse(vector<course>& c, vector<ca>& cas){
    course course;
    cout<<"add the name of the course: ";
    string enteredName;
    getline(cin, enteredName);
    
    course.courseName=enteredName;
  
    cout << "press any key to enter ca or q to quit";
    string choice;
    getline(cin,choice);

    if(choice == "q" || choice == "Q"){
        c.push_back(course);
        return;
    }

    int count = 1;
    while(choice != "q" || choice != "Q"){
        cout << dline<<endl;
        cout << "ADDING "<< " "<< course.courseName << " "<< "CONTINEOUS ASSESSMENT RESULTS"<<endl;
        cout << line<<endl;
        ca ca;
        while(true) {
            ca.caNumber = count;
            ca.caPercent = percent();
            double validation = calcValue(ca.caPercent, course.remaingMarks, course.marksOnCa,ca.value);
            if(validation == -1.00){
               
                break;
            }
            else{
                ca.grade = calcGrade(ca.caPercent);
                cas.push_back(ca);
                course.caNumber++;
                count++;
                break;
            }
        }
        cout << "press any key enter onother ca and q to quit: ";
        string choise;
        getline(cin, choise);
        clearScrean();

        if(choise == "q" || choise == "Q") {
            c.push_back(course);
            return;
        }
    }
    return;
}

int findCourse(vector<course>& c){
    int index;
    for(int i = 0; i < c.size(); i++){
        cout<<i + 1<<" "<<c[i].courseName<<endl;
    }

    while (true){
        index = getValidInput<int>("ENTER NUMBER");
        if(index < 1 || index > c.size()){
            cout << "invalid input press q to quit or any key to reenter: ";
            string choice;
            getline(cin, choice);
            clearScrean();
            if(choice == "q" || choice == "Q") {
                index =0;
                break;
            }
        }
        else{
            break;
        }
    }
    index--;
    clearScrean();
    return index;
}

void viewAllCourses(vector<course>& c, vector<ca>& cas){
    int count = 0;
    int counter;
    for(int i = 0; i < c.size();i++) {
        cout << dline<<endl;
        cout << c[i].courseName<<endl;
        cout << line<<endl;
        cout<<c[i].courseGrade<<endl;
        cout << "marks remaining: "<<c[i].remaingMarks<<endl;
        cout<<"marks on ca: "<< c[i].marksOnCa<<endl;
        cout<<line<<endl;
        cout<< c[i].courseName<<" "<<"has"<<c[i].caNumber<<" "<<"contineous assessments"<<endl;
        cout<<line<<endl;
        counter = count;
        for(int j = counter; j < (c[i].caNumber + counter); j++) {
            cout<< c[i].courseName<< ": "<<cas[count].caNumber<<endl;
            cout<< "grade"<<cas[count].grade<<endl;
            cout<<"percent: "<<cas[count].caPercent<<endl;
            cout<<line<<endl;
            count++;
        }
    }
    system("pause");
    clearScrean();
}

void viewIndividualCourse(vector<course>& c, vector<ca>& cas){
    int number = findCourse(c);
    int count = 0;
    int counter;
    for (int i =0; i < number; i++){
        count = count + c[i].caNumber;
    }

    
    cout << dline<<endl;
    cout << c[number].courseName<<endl;
    cout << line<<endl;
    cout<<c[number].courseGrade<<endl;
    cout << "marks remaining: "<<c[number].remaingMarks<<endl;
    cout<<"marks on ca: "<< c[number].marksOnCa<<endl;
    cout<<line<<endl;
    cout<< c[number].courseName<<" "<<"has"<<c[number].caNumber<<" "<<"contineous assessments"<<endl;
    cout<<line<<endl;
    counter = count;
    for(int j = counter; j < (c[number].caNumber + counter); j++) {
        cout<< "grade"<<cas[count].grade<<endl;
        cout<<"percent: "<<cas[count].caPercent<<endl;
        cout<<line<<endl;
        count++;
    }
    
    system("pause");
}

void loadFile(vector<course>& c, vector<ca>& cas){
    ifstream courseFile;
    ifstream caFile;

    
    bool running = true;

    
    while(running){
        cout << "enter the file you are using for your course: ";
        getline(cin, filecource);
        courseFile.open(filecource);
        if(!courseFile.is_open()){
            cout << "file "<< fileca<<" "<<"has failed to open\nPRESS Q TO QUIT AND ANY KEY TO REENTER FILE: ";
            string choice;
            getline(cin, choice);
            clearScrean();
        
            if(choice == "q"||choice=="Q"){
                return;
            }
        }
        else{
            running = false;
        }
    }
    running = true;

    while(running){
        cout << "enter the file you are using for your ca: ";
        getline(cin, fileca);
        caFile.open(fileca);
        if(!caFile.is_open()){
            cout << "file "<< fileca<<" "<<"has failed to open\nPRESS Q TO QUIT AND ANY KEY TO REENTER FILE: ";
            string choice;
            getline(cin, choice);
            clearScrean();
            if(choice == "q"||choice=="Q"){
                return;
            }
        }
        else{
            running = false;
        }
    }
    string stringcount;
        
    while(getline(courseFile, stringcount)){
        course course;
        int count;
        count = stoi(stringcount);
        course.caNumber = count;
        getline(courseFile, course.courseName);
        getline(courseFile, course.courseGrade);
        string stringRemainingMarks;
        getline(courseFile, stringRemainingMarks);
        course.remaingMarks = stod(stringRemainingMarks);
        string stringMarksOnCa;
        getline(courseFile, stringMarksOnCa);
        course.marksOnCa = stod(stringMarksOnCa);
        c.push_back(course);
    }

    ca ca;
    while(getline(caFile, ca.grade)){
        string stringcount;
        int count;
        getline(caFile, stringcount);
        count = stoi(stringcount);
        ca.caNumber = count;
        string stringRemainingMarks;
        getline(caFile, stringRemainingMarks);
        ca.caPercent = stod(stringRemainingMarks);
        cas.push_back(ca);
    }

}

void writeFile(vector<course>& c, vector<ca>& cas){
    ofstream courseFile;
    bool running = true;
    while(running){
        cout<<"enter the file you are using to save course data: ";
        getline(cin,filecource);
        courseFile.open(filecource);
        if(!courseFile.is_open()){
            cout <<"file"<<" "<<filecource<<" "<< " has faield to open press q to close app or any key to reenter filenam: ";
            string choice;
            getline(cin, choice);
            if(choice == "q" || choice == "Q"){
                return;
            }
        }
        else {
            running = false;
        }

    }

    ofstream caFile;
    running = true;
    while(running){
        cout<<"enter the file you are using to save data: ";
        getline(cin,fileca);
        caFile.open(fileca);
        if(!caFile.is_open()){
            cout <<"file"<<" "<<fileca<<" "<< " has faield to open press q to close app or any key to reenter filenam: ";
            string choice;
            getline(cin, choice);
            if(choice == "q" || choice == "Q"){
                return;
            }
        }
        else {
            running = false;
        }

    }
    int keepcount = 0;
    for (int i = 0; i < c.size(); i++){
        int count = c[i].caNumber;
        courseFile << count<<endl;
        courseFile << c[i].courseName <<endl;
        courseFile << c[i].courseGrade<<endl;
        courseFile << c[i].remaingMarks<<endl;
        courseFile << c[i].marksOnCa<<endl;
    }
        for(int j = 0;j < cas.size(); j++){
            caFile << cas[j].grade<<endl;
            caFile << cas[j].caNumber<<endl;
            caFile << cas[j].caPercent<<endl;
        }


}



void deleteCourse(vector<course>& c, vector<ca>& cas){
    int index = findCourse(c);
    cout << "press q to delete the "<<" "<<c[index].courseName<<"and any key to esc ";
    string choice;
    getline(cin, choice);
    int number = 0;
    if(choice == "Q" || choice == "q") {
        string course = c[index].courseName;
        for(int i =0; i < index; i++){
            number = number = c[i].caNumber;
        }

        for(int i = number; i < (number + c[index].caNumber); i++){
            cas.erase(begin(cas) + i);
        }
        c.erase(begin(c) + index);
        cout << course << " "<<"has been deleted successfuly"<<endl;
    }


}
courseCa viewCA(vector<course>& c, vector<ca>& cas, int& index){
    int counter = 0;
    courseCa returnIndex;
    for(int i = 0; i < index; i++ ){
        counter = counter = c[i].caNumber;
    }
    int count = counter;
    for(counter; counter < (count + c[index].caNumber); counter++ ) {
        cout << c[index].courseName<<": "<<cas[counter].caNumber<<endl;
        cout<< "grade "<<cas[counter].grade<<endl;
        cout<<"percent: "<<cas[counter].caPercent<<endl;
        cout<<line<<endl;
    }
    returnIndex.courseIndex = index;
    bool running = true;
    while (running){
        returnIndex.caIndex = getValidInput<int>("enter number conteneous assessment number");
        if(returnIndex.caIndex > 0 && returnIndex.caIndex <= c[index].caNumber){
            returnIndex.caIndex = (returnIndex.caIndex + count) - 1;
            return returnIndex;
            
        }
        else{
            cout<<"invalid input"<<endl;
        }
    }
    return returnIndex;
    clearScrean();
}
void deleteCa(vector<course>& c, vector<ca>& cas, courseCa& index){
    c[index.courseIndex].caNumber--;
    c[index.courseIndex].remaingMarks =  c[index.courseIndex].remaingMarks + cas[index.caIndex].value;
    c[index.courseIndex].marksOnCa =  c[index.courseIndex].marksOnCa - ((cas[index.caIndex].caPercent/100)*cas[index.caIndex].value);
    cas.erase(begin(cas) + index.caIndex);
    int count = 1;
    int counter = 0;
    for(int i = 0; i < index.courseIndex; i++ ){
        counter = counter + c[i].caNumber;
    }
    int noncounter = counter;
    for(counter; counter < (c[index.courseIndex].caNumber + noncounter) ;counter++){
        cas[counter].caNumber = count;
        count++;
    }
}
void addCa(vector<course>& c, vector<ca>& cas, int& index ){
        course course;
        cout << dline<<endl;
        cout << "ADDING "<< " "<< c[index].courseName << " "<< "CONTINEOUS ASSESSMENT RESULTS"<<endl;
        int count = 0;
        for(int i = 0; i < index; i++){
            count = count + c[i].caNumber;
        }
        count = (count + c[index].caNumber) ;
        cout << line<<endl;
        ca ca;
        ca.caNumber = c[index].caNumber + 1;
        ca.caPercent = percent();
        double validation = calcValue(ca.caPercent,c[index].remaingMarks,c[index].marksOnCa,ca.value);
        if(validation == -1.00){
            cout << "operarion failure"<<endl;
            return;
        }
        ca.grade = calcGrade(ca.caPercent);
        cas.insert(cas.begin(), count, ca);
        
        c[index].caNumber++;
}

void changeName(vector<course>& c, vector<ca>& cas , const int& index){
    string newName;
    cout<<"enter name: ";
    getline(cin, newName);

    c[index].courseName = newName;

}

void modifyca(vector<course>& c,vector<ca>& cas,int& courseIndex, int& caIndex){
    cout<<"percent: "<<" "<<cas[caIndex].caPercent<<endl;
    while(true){
        cas[caIndex].caPercent = getValidInput<double>("enter new percent");
        
        double validation = calcValue(cas[caIndex].caPercent, c[courseIndex].remaingMarks, c[courseIndex].marksOnCa,cas[caIndex].value);
        if(validation == -1.00){               
                break;
            }
        else{
            cas[caIndex].grade = calcGrade(cas[caIndex].caPercent);
            break;
        }
    }

}

void modifycourse(vector<course>& c , vector<ca>& cas, int& index){
    int choice;
    courseCa courseca;
    while(true){
        choice = getValidInput<int>("1: change course name\n 2: adit contineos assessment result");
        if (choice < 1 || choice > 2) {
            cout << "invalid input"<<endl;
            cin.get();
            clearScrean();
        }
        else{
            break;
        }
    }

    if(choice == 1){
        changeName(c, cas,index );
    }
    else{
        courseca = viewCA(c, cas, index);
        modifyca(c,cas,courseca.courseIndex, courseca.caIndex);
    }

}
void modifyCourse(vector<course>& c, vector<ca>& cas){
    int index;
    courseCa returnindex;
    bool running = true;
    int choice;
    while(running){
        choice = getValidInput<int>("1: delete the course\n 2: modify course and course results\n3: delete contineoues assessments\n 4: add ca to acourse");
        if(choice < 5 && choice > 0){
            running = false;
        }
        else{
            cout << "invalid unput"<<endl;
        }
    }

    running = true;
    while(running){

        
        switch(choice){
            case 1: deleteCourse(c, cas);
                    running = false;
                    break;
            case 2: index = findCourse(c);
                    modifycourse(c, cas, index);
                    running = false;
                    break;
            case 3: index = findCourse(c);
                    returnindex = viewCA(c, cas, index);
                    deleteCa(c, cas, returnindex);
                    running = false;
                    break;
            case 4: index = findCourse(c);
                    addCa(c, cas, index);
                    running = false;
                    break;
            defaut: running = false;
                    break;
        }

    }
}
void clearScrean(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


double percent(){
    int choice;
    double percent;
    double totalMarks;
    double score;
    do{
        choice = getValidInput<int>("1: enter percent directly\n 2: enter marks\n ENTER NUMBER");
        if (choice>2 || choice<1){
            cout<<"invalidentry"<<endl;
        }
    }while(choice>2 || choice <1);

    if (choice == 1){
        percent = getValidInput<double>("enter your percent");
    }
    else if(choice == 2){
        totalMarks = getValidInput<double>("enetr your total marks");
        score = getValidInput<double>("enter yourscore on the test");
        percent = (score/totalMarks)*(100);
    }
    return percent;

}

string calcGrade( const double& mark){
    string grade;
    if(mark >=86){
        grade = "A+";
    }
    else if(mark <86 && mark>=76){
        grade = "A";
    }
    else if(mark<76 && mark>=68){
        grade = "B+";
    }
    else if(mark<68 && mark>=62){
        grade = "B";
    }
    else if(mark < 62 && mark>=56){
        grade = "C+";
    }
    else if(mark<56 && mark >=50){
        grade = "C";
    }
    else if (mark <50 && mark >=40){
        grade = "D";
    }
    else{
        grade = "F";
    }
    return grade;
}


int main(){

    

    int index;
    vector<course> courses;
    vector<ca> cas;

    loadFile(courses, cas);
    clearScrean();

    bool running = true;
    while(running){
        int choice = getValidInput<int>("1; VIEW ALL RELSULTS\n2: VIEW COURSE RESULTS\n3: ADD COURSE\n 4:DELETE COURSE\n 5: modify course results\n 6:EXIT AND SAVE TO FILE\nENTER NUMBER");
        switch (choice){
            case 1: viewAllCourses(courses, cas);
                    break;
            case 2: viewIndividualCourse(courses, cas);
                    clearScrean();
                    break;
            case 3: addCourse(courses, cas);
                    clearScrean;
                    break;
            case 4: deleteCourse(courses, cas);
                    clearScrean();
                    break;
            case 5: modifyCourse(courses, cas);
                    break;
            default:cout<<"invalid input press any key to reenter value or press q to exit program: ";
                    string choice;
                    getline(cin, choice);
                    if (choice == "q"||choice == "Q"){
                        running = false;
                    }
                    break;
        }
    }

    writeFile(courses, cas);
    system("pause");
}
