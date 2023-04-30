#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
struct person
{
    const char* name;
	int a[13];
};
  
int save(char * filename, struct person *p);
int load(char * filename);
int move(struct person *p);
  
int main(void)
{
    //char * filename = "prog.bin";
    struct person p1 = {"p1",{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
	struct person p2 = {"p2",{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
    struct person p3 = {"p3",{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};
	srand(time(NULL));
	for( int i = 0; i<1000; i++){// самый легкий выход из ситуации
		if(p3.a[10] < 100){
			move(&p1);
		}
		else{
			printf("p3 - WINNER \n");
			return 0;
		}
		if(p1.a[10] < 100){
			move(&p2);
		}
		else{
			printf("p1 - WINNER \n");
			return 0;
		}
		if(p2.a[10] < 100){
			move(&p3);
		}
		else{
			printf("p2 - WINNER \n");
			return 0;
		}
	}
    return 0;
}

// запись структуры в файл
int save(char * filename, struct person * p)
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
   printf("\n");
    return 0;
}
int move(struct person *p)
{	int b[3];
	char * filename = "prog.bin";
	for (int j = 0; j < 3; j++){
		int r = rand()%9 + 1;
		b[j] = r;
		//printf("%d ", r);
		//printf("\n");
		p->a[r-1] = p->a[r-1] + 1;
		//printf("%d ", b[j]);
	}
	if (b[0] == b[1] || b[0] == b[2] || b[1] == b[2]){
		for (int j = 0; j < 3; j++){
			p->a[b[0]-1] = 0;
			p->a[b[1]-1] = 0;
			p->a[b[2]-1] = 0;
		}
		p->a[11] = p->a[11] + 1;
	}
	else {
		p->a[10] = p->a[10] + b[0] + b[1] + b[2];
		for (int j = 0; j < 10; j++){
			p->a[b[0]-1] = 0;
			p->a[b[1]-1] = 0;
			p->a[b[2]-1] = 0;
		}
	}
	if (p->a[11] == 3){
		p->a[10] = p->a[10] + 50;
		p->a[11] = 0;
	}
	//p->a[10] -  ячейка для суммы
	//p->a[11] - ячейка для карт лося
	//p->a[12] - статус хода 
	save(filename, p);
    load(filename);
	return 0;
}
