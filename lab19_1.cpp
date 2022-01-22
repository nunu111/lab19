#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string file, vector<string> &name,vector<int> &scores,vector<char> &grades){
    name.clear();
    scores.clear();
    grades.clear();
    ifstream run(file);
    string allname;
    char a[100];
    int b,c,d;
    char check[] ="%[^:]: %d %d %d";
    for(int i=0;getline(run,allname);i++){
        sscanf(allname.c_str(),check,a,&b,&c,&d);
        name.push_back(a);
        scores.push_back(b+c+d);
        grades.push_back(score2grade(scores[i]));
    }
    run.close();
    
}

void getCommand(string &command,string &keyword){
    cout << "Please input your command: ";
    cin >> command;
    cin.ignore();
    if(toUpperStr(command) == "GRADE" || toUpperStr(command) == "NAME") getline(cin,keyword);
}

void searchName(vector<string>name ,vector<int> scores,vector<char> grade,string keyword){
    cout << "---------------------------------\n";
    for(unsigned int i=0,j=0;i<name.size();i++){
        string a= toUpperStr(name[i]);
        if(a == keyword){
            cout << name[i] << "'s score = " << scores[i] << endl;
            cout << name[i] << "'s grade = " << grade[i] << endl;
            j++;
        }
        else if (j == 0 && i==name.size()-1) {
            cout << "Cannot found." << endl;
            
        }
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string>name ,vector<int> scores,vector<char> grade,string keyword){
    cout << "---------------------------------\n";
    for(unsigned int i=0,j=0;i<name.size();i++){
        if( keyword[0] == grade[i] && keyword[1] == '\0'){
            cout << name[i] << " (" << scores[i] << ")" << endl;
            j++;
        }
        else if (j == 0 && i==name.size()-1) {
            cout << "Cannot found." << endl;
            
        }
    }
    cout << "---------------------------------\n";
}


int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}