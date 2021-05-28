#include <iostream>
#include "Vector.h"
int main(){
    
    Vector<int> stud;
    cout << "push_back testavimas" << endl;
    stud.push_back(10);
    stud.push_back(5);
    stud.push_back(1);
     for(int i=0; i<stud.size(); i++ ){
         cout <<stud[i] << endl;
     }
   
     cout << stud.capacity() << endl;
     cout << stud.size() << endl;
    cout << "resize testavimas" << endl;

     stud.resize(10);
     cout << stud.capacity() << endl;
     cout << stud.size() << endl;
     cout << "reserve testavimas" << endl;
     stud.reserve(25);
    cout << stud.capacity() << endl;
     cout << stud.size() << endl;
cout <<"shrink to fit testavimas" << endl;

     stud.shrink_to_fit();
     cout << stud.capacity() << endl;
     cout << stud.size() << endl;
     cout <<"clear testavimas" << endl;
    stud.clear();
    cout << stud.capacity() << endl;
     cout << stud.size() << endl;
     
    
     
}