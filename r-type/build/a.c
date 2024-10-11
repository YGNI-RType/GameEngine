#include <stdio.h>
#include <stdbool.h>

int is_alphanum(char c)
{
    if ((c >= 'a' && c <= 'z') || (c >= 'a' && c <= 'z') || (c >= '1' && c <= '9'))
        return true;
    return false;
}

int count_words(const char *str)
{
    int index = 0;
    int how_many_words = 0;

    while (str[index] != '\0') {
        while(is_alphanum(str[index]) == false) {
            if (str[index] == '\0')
                return how_many_words;
            index++;
        }
        how_many_words++;
        while(is_alphanum(str[index]) == true) {
            if (str[index] == '\0')
                return how_many_words;
            index++;
        }
    }
    return how_many_words;
}

int main(int ac, char const **av)
{
    printf("%d\n", count_words(av[1]));
}