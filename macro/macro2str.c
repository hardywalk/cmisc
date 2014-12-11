#include <stdio.h>

#define MACRO_STR(x)	#x
#define MACRO_DICT(x)	{x, (char *)#x}

typedef enum {
	RED,
	GREEN,
	BLUE,
} COLOR;

char *color_name[] = {
	(char *)MACRO_STR(RED),
	(char *)MACRO_STR(GREEN),
	(char *)MACRO_STR(BLUE),
	NULL,
};

typedef struct {
	int key;
	char *value;
} dict_t;

dict_t color_dict[] = {
	MACRO_DICT(BLUE),
	MACRO_DICT(GREEN),
	MACRO_DICT(RED),
	{-1, NULL},
};


int main(void)
{
	int i = 0;

	printf("-----------------------\n");
	while (color_name[i] != NULL) {
		printf("%s\n", color_name[i]);
		i++;
	}
	printf("-----------------------\n");
	i = 0;
	while (color_dict[i].key != -1) {
		printf("DICT:%d->%s\n", color_dict[i].key, color_dict[i].value);
		i++;
	}
	printf("-----------------------\n");

	return 0;
}
