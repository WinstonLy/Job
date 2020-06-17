#include <iostream>
#include <string>

using namespace std;

void getNext(string p, int next[])
{
	int pLen = p.size();
	int k = 0;
	int j = -1;
	next[0] = -1;

	while(k < pLen - 1)
	{
		if(j == -1 || p[k] == p[j])
		{
			++k;
			++j;
			next[k] = j;
		}
		else
		{
			j = next[j];
		}
	}
}

int KMP(string s, string p, int next[])
{
	getNext(p, next);

	int sLen = s.size();
	int pLen = p.size();

	int i = 0;
	int j = 0;

	while(i < sLen && j < pLen)
	{
		if(s[i] == p[j] || j == -1)
		{
			++i;
			++j;
		}
		else
		{
			j = next[j];
		}
	}
	if(j == pLen)
		return i - j;

	return -1;
}


int main()
{
	string s = "BBCABCDABABCDABCDABDE";
	string p = "ABCDABD";
	int next[7] = {0};
	cout << KMP(s, p, next) << endl;
	for(int i = 0; i < p.size(); ++i)
		cout << next[i] << endl;
	return 0;
}