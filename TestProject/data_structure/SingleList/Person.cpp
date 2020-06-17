#include "Person.h"


ostream &operator<<(ostream &out, Person &person)
{
	cout << person.m_strName << "----------" << person.m_strPhone << endl;

	return out;
}

Person &Person::operator=(Person &person)
{
	this->m_strName = person.m_strName;
	this->m_strPhone = person.m_strPhone;

	return *this;
}

bool Person::operator==(Person &person)
{
	if(this->m_strName == person.m_strName && this->m_strPhone == person.m_strPhone)
	{
		return true;
	}

	return false;
}