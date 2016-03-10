#include <stdio.h>
#include <string.h>

int main(void)
{
	char *ch = (char *)malloc(0);
	printf("sizeof %d\n", strlen(ch));
	memcpy(ch, "abcefghijklmn", strlen("abcdejekfj"));
	printf("%s\n", ch);
	return 0;
}
