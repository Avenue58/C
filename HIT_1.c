#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
  
struct person
{
    const char* name;
	int a[13];
};
  
int save(char * filename, struct person *p);
int load(char * filename);
  
int main(void)
{
    char * filename = "prog.bin";
    struct person tom = {"p1",{14, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1 }};
  
    save(filename, &tom);
    load(filename);
      
    return 0;
}
  
// запись структуры в файл
int save(char * filename, struct person *p)
{
    FILE * fp ;//= NULL;
    //printf ("%s\n", filename);
	char *c = NULL;
    int size = sizeof(struct person); // количество записываемых байтов
	
    fp = fopen(filename, "wb"); 
	if (fp == NULL) printf ("ERROR __FILE__ __LINE__");
    // устанавливаем указатель на начало структуры
    c = (char *)p;
    // посимвольно записываем в файл структуру
    for (int i = 0; i < size; i++)
    {
		putc(*c++, fp);
    }
    fclose(fp);
    return 0;
}
  
// загрузка из файла структуры
int load(char * filename)
{
    FILE * fp;
    char *c;
    int i; // для считывания одного символа
    // количество считываемых байтов
    int size = sizeof(struct person);
    // выделяем память для считываемой структуры
    struct person * ptr = calloc(size, 1);
    fp = fopen(filename, "rb");     // открываем файл для бинарного чтения
    if (fp == NULL)
    {
        printf("Error occured while opening file \n");
        return 1;
    }
  
    // устанавливаем указатель на начало блока выделенной памяти
    c = (char *)ptr;
    // считываем посимвольно из файла
    while ((i = getc(fp))!=EOF)
    {
        *c = i;
        c++;
    }
  
   // fclose(fp);
    // вывод на консоль загруженной структуры
    printf ("%s: ", ptr->name);
	for (int i = 0; i < 13;i++){
	printf("%d ",*(ptr->a + i));
	}
   // free(ptr);
    return 0;
}
