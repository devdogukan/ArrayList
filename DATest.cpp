#include <iostream>
#include "DynamicArray.h"

using namespace std;

int main(){

	Array<string> name;
	Array<double> height;
	Array<char> character;
	Array<bool> TF;
	Array<int> age;

	age.add(20);
	
	cout<<name.isEmpty()<<endl;  // true of 1
	cout<<age.isEmpty()<<endl;   // false of 0

	age.clear();

	age.add(5);
	age.add(4);
	age.add(100);
	age.add(85);
	age.print();

	cout<<endl;

	try{
		cout<<age.get(-4)<<endl;  // negative index
		cout<<age.get(0)<<endl;
		cout<<age[3]<<endl;
		cout<<age[-1]<<endl;   // neagtive index
	}
	catch(const char* e){
		cout<<e<<endl;
	}

	cout<<"Array size: "<<age.size()<<endl;
	cout<<"Array length: "<<age.length()<<endl;
	
	age.insert(0,age.begin(),age.end()); // being tested
	age.print();

	cout<<endl;

	age.remove(0);
	age.print();

	cout<<endl;

	age.remove(age.size() - 1);
	age.print();

	cout<<endl;

	age.remove();
	age.print();
	
	return 0;
}
