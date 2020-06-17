
int main(void)
{
	// int sum = 0, i = 0;
	// char input[5];
	// while (1) {
	// 	sum = 0;
	// 	scanf("%s", input);
	// 	for (i = 0; input[i] != '\0'; i++)
	// 		sum = sum*10 + input[i] - '0';
	// 	printf("input=%d\n", sum);
	// }
	// 
	// 
	enum week{ Mon = 1, Tues, Wed, Thurs, Fri, Sat, Sun } day;
    scanf("%d", &day);
    switch(day){
        case Mon: puts("Monday"); break;
        case Tues: puts("Tuesday"); break;
        case Wed: puts("Wednesday"); break;
        case Thurs: puts("Thursday"); break;
        case Fri: puts("Friday"); break;
        case Sat: puts("Saturday"); break;
        case Sun: puts("Sunday"); break;
        default: puts("Error!");
    }

	return 0;
}
