#include"hash.h"
#include<string.h>

typedef struct stu
{
	char sno[5];
	char name[32];
	int age;
}stu_t;

typedef struct stu2
{
	int sno;
	char name[32];
	int age;
}stu2_t;


unsigned int hash_str(unsigned int buckets, void *key)
{
	char *sno=(char *)key;
	unsigned int index = 0;
	while(*sno)
	{
		index = *sno + 4*index;
		sno++;
	}
	return index % buckets;
}


unsigned int hash_int(unsigned int buckets, void *key)
{
	int  *sno=(int *)key;
	
	return (*sno) % buckets;
}

int main()
{
/*
	stu_t stu_arr[]=
	{
		{"1234","AAAA",20},
		{"4568","BBBB",20},
		{"6729","CCCC",20},
		
	};
*/	

	stu2_t stu2_arr[]=
	{
		{1234,"AAAA",20},
		{4568,"BBBB",20},
		{6729,"CCCC",20},
		
	};
	hash_t *hash=hash_alloc(256,hash_int);
	int size=sizeof(stu2_arr)/sizeof(stu2_arr[0]);
	int i;
	for(i=0;i<size;++i)
	{
		hash_add_entry(hash, &(stu2_arr[i].sno),sizeof(stu2_arr[i].sno),&stu2_arr[i],sizeof(stu2_arr[i]));
	}
	
	int sno=4568;
	stu2_t *stu =(stu2_t *)hash_lookup_entry(hash,&sno,sizeof(sno));	
	if(stu)
	{
		printf("%d %s %d\n",stu->sno,stu->name,stu->age);
	}
	else
	{
		printf("not found\n");
	}
	
	sno=4568;
	hash_free_entry(hash,&sno,sizeof(sno));
	stu =(stu2_t *)hash_lookup_entry(hash,&sno,sizeof(sno));	
	if(stu)
	{
		printf("%d %s %d\n",stu->sno,stu->name,stu->age);
	}
	else
	{
		printf("not found\n");
	}
	
	return 0;
}

















