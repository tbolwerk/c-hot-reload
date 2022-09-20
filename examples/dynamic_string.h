/*
This library copies the src dynamic_string in order to prevent modifactions during execution of the function. 
*/

typedef struct
{
	unsigned int capacity;
	unsigned int length;
	char *s;
} dynamic_string;

void create_dynamic_string(dynamic_string *ds, char *src);

void free_dynamic_string(dynamic_string *ds);

void reverse(dynamic_string src, dynamic_string *dst);

void concat(char *src, dynamic_string *dst);

void take(dynamic_string src, dynamic_string *dst, unsigned int n);

void drop(dynamic_string src, dynamic_string *dst, unsigned int n);

void filter(dynamic_string src, dynamic_string *dst, int (*ptr) (char x));

void map(dynamic_string src, dynamic_string *dst, char (*ptr) (char x));

void sort(dynamic_string src, dynamic_string *dst);

void print_dynamic_string(dynamic_string *ds);

char* toString(dynamic_string src);

#ifdef DYNAMIC_STRING_IMPL
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

void free_dynamic_string(dynamic_string *ds)
{
	ds->s = NULL;
	free(ds->s);
	ds->length = 0;
	ds->capacity = 0;
	ds = NULL;
	free(ds);
}

void create_dynamic_string(dynamic_string *ds,  char *src)
{
	ds->length += strlen(src);
	ds->capacity = ds->length * 2;
	if(ds->s == NULL)
	{
		ds->s = malloc(ds->capacity);
		strcpy(ds->s, src);
		return;
	}
	ds->s = realloc(ds->s, ds->capacity * sizeof(char));
	ds->s = strcat(ds->s, src); 
}

void concat(char *src, dynamic_string *dst)
{
	unsigned int src_size = (strlen(src) / sizeof(char));
	if(dst->capacity - dst->length < src_size){
	 	 create_dynamic_string(dst, src);
		 return;
	}
	
	strcat(dst->s, src);
	dst->length += src_size;
}

void copy_dynamic_string(dynamic_string src, dynamic_string *dst)
{
	dst->length = src.length;
	dst->capacity = src.capacity;
	dst->s = src.s;
}

void reverse(dynamic_string src, dynamic_string *dst)
{
	char buffer[src.length];
	int j = src.length;
	for(int i = 0; i < src.length; i ++)
	{
		j = j - 1;
		buffer[i] = src.s[j];
	}
	dst->s = buffer;
	dst->s[src.length] = '\0';
}

void take(dynamic_string src, dynamic_string *dst, unsigned int n)
{
	assert(src.length > n);
	copy_dynamic_string(src, dst);
	dst->s[n] = '\0';
	dst->length = n;
}

void print_dynamic_string(dynamic_string *ds)
{
	printf("ds: {capacity: %d, length: %d, s: %s}\n", ds->capacity, ds->length, ds->s);
}

void filter(dynamic_string src, dynamic_string *dst, int (*ptr) (char x))
{
	copy_dynamic_string(src,dst);
	int new_length = 0;
	char buffer[src.length];
	for(int i =  0; i < dst->length; i ++)
	{
		int predicate = (*ptr)(src.s[i]);
		if(predicate != 0){
			buffer[new_length] = src.s[i];
			new_length ++;
		}
	}
	
	dst->s = buffer;
	dst->s[new_length] = '\0';
	dst->length = new_length;
}

void drop(dynamic_string src, dynamic_string *dst, unsigned int n)
{
	copy_dynamic_string(src, dst);
	dst->s = &src.s[n];
	dst->length -= n;
}

void map(dynamic_string src, dynamic_string *dst, char (*ptr) (char x))
{
	copy_dynamic_string(src, dst);
	for(int i = 0; i < dst->length; i ++)
	{
		char c = (*ptr)(src.s[i]);
		dst->s[i] = c;
	}
	dst->s[dst->length] = '\0';
}

void sort(dynamic_string src, dynamic_string *dst)
{
	copy_dynamic_string(src, dst);

	for(int i = 0; i < src.length; i ++)
	{
		for(int j = 0; j < src.length; j ++)
		{
			if(dst->s[i] < dst->s[j])
			{
				char tmp = dst->s[i];
				dst->s[i] = dst->s[j];
				dst->s[j] = tmp;
			}
		}
	}

	dst->s[dst->length] = '\0';	
}


char* toString(dynamic_string src)
{
	assert(src.s != NULL);
	return src.s;
}
#endif
