#include"hash.h"

#include<assert.h>


typedef struct hash_node
{
	void *key;
	void *value;
	struct hash_node *prev;
	struct hash_node *next;
}hash_node_t;


struct hash
{
	unsigned int buckets;
	hashfunc_t hash_func;
	hash_node_t **nodes;
};

hash_node_t ** hash_get_bucket(hash_t *hash,void *key);

hash_node_t * hash_get_node_by_key(hash_t *hash,void *key,unsigned int key_size);



hash_node_t ** hash_get_bucket(hash_t *hash,void *key)
{
	unsigned int bucket=hash->hash_func(hash->buckets,key);
	if(bucket>=hash->buckets)
	{
		fprintf(stderr,"bad buckets lookup\n");
		exit(EXIT_FAILURE);
	}
	return &(hash->nodes[bucket]);
}

hash_node_t * hash_get_node_by_key(hash_t *hash,void *key,unsigned int key_size)
{
	hash_node_t ** bucket = hash_get_bucket(hash,key);
	hash_node_t * node=*bucket;
	if(node==NULL)
	{
		return NULL;
	}
	while(node!=NULL && memcmp(node->key,key,key_size)!=0)
	{
		node=node->next;
	}
	
	return node;
}

hash_t* hash_alloc(unsigned int buckets, hashfunc_t hash_func)
{
	hash_t *h=(hash_t *)malloc(sizeof(hash_t));
	//assert(h!=NULL);
	h->buckets=buckets;
	h->hash_func=hash_func;
	
	int size=buckets*sizeof(hash_node_t *);
	h->nodes=(hash_node_t **)malloc(size);
	memset(h->nodes,0,size);
	return h;
}

void* hash_lookup_entry(hash_t *hash, void* key, unsigned int key_size)
{
	hash_node_t *node = hash_get_node_by_key(hash, key ,key_size);
	if(node == NULL)
	{
		return NULL;
	}
	return node->value;
	
}

void hash_add_entry(hash_t *hash, void *key, unsigned int key_size,
	void *value, unsigned int value_size)
{
	//如果已经存在
	if(hash_get_node_by_key(hash,key,key_size))
	{
		fprintf(stderr,"duplicate hash key\n");
		return;
	}
	
	hash_node_t *temp=(hash_node_t *)malloc(sizeof(hash_node_t));
	temp->next=NULL;
	temp->prev=NULL;
	temp->key=malloc(key_size);
	temp->value=malloc(value_size);
	
	memcpy(temp->key,key,key_size);
	
	memcpy(temp->value,value,value_size);
	
	hash_node_t ** bucket=hash_get_bucket(hash,key);
	if(*bucket==NULL)
	{
		*bucket=temp;
	}
	else 
	{
		//头插法
		temp->next=*bucket;
		(*bucket)->prev=temp;
		(*bucket)=temp;
	}
}

void hash_free_entry(hash_t *hash, void *key, unsigned int key_size)
{
	hash_node_t * node = hash_get_node_by_key(hash,key,key_size);
	if(node==NULL)
	{
		return;
	}
	else
	{
		free(node->key);
		free(node->value);
		if(node->prev)
			node->prev->next=node->next;
		else
		{
			hash_node_t ** p = hash_get_bucket(hash,key);
			(*p)->next=node->next;
		}
		if(node->next)
			node->next->prev=node->prev;
		free(node);
	}
}










