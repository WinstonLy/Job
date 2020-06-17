#include <stdio.h>
#include <stdlib.h>

#define N 100
int main()
{
	FILE *fp;
	char str[N + 1] = {0};
	char strTemp[100] = "fadsfadf";
	if((fp = fopen("./text.txt", "rt")) == NULL)
	{
		puts("Fail to open file");
		exit(0);
	}

	while(fgets(str, N, fp) != NULL)
	{
		printf("%s", str);
	}

	fputs(strTemp, fp);

	fclose(fp);
	
	if((fp = fopen("./text.txt", "rt")) == NULL)
	{
		puts("Fail to open file");
		exit(0);
	}

	while(fgets(str, N, fp) != NULL)
	{
		printf("%s", str);
	}

	fclose(fp);
	return 0;
}