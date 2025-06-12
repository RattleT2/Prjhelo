#include <iostream>
#include <string>
using namespace std;

int main(){
    string listnama[] = {"Mario Pratama putra wahyudi","Kelas TI axioo"," Alumni smk binabanua"};
    int nama = sizeof(listnama)/sizeof(listnama[0]);

    for (int i = 0; i < nama; i++){
        cout << listnama[i] << endl;
    }

    return 0;
}