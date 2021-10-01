#include <cstdio>
#include <cstring>

char read_from(const char *str,size_t pos)
{
	if(pos > strlen(str))
		return '\0';
	return str[pos];
}

bool write_to(char *str, char ch, size_t pos)
{
	if(pos > strlen(str))
		return false;
	str[pos] = ch;
	return true;
}

int main()
{
	char lower[] = "abc?e";
	char upper[] = "ABC?E";
	char* upper_ptr = upper;
	write_to(lower, 'd', 3);
	write_to(upper_ptr, 'D', 3);
	char letter_d = read_from(lower, 3);
	char letter_D = read_from(upper_ptr, 3);
	printf("lower: %s\nupper: %s\n", lower, upper);
	printf("letter_d: %c\nletter_D: %c\n", letter_d, letter_D);
	return 0;
}

