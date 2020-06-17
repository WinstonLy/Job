#ifndef _PERSON_H_
#define _PERSON_H_

#include <string>
#include <iostream>

using namespace std;

class Person
{
	friend ostream &operator<<(ostream &out, Person &person);

public:
	string m_strName;
	string m_strPhone;

	Person &operator=(Person &person);
	bool operator==(Person &person); 
};


#endif