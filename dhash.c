/// This program is distribuited under the licence GPL-3.0
/// I have not so much requirement, just alert me if you find
/// some bugs: spanu_andrea(at)yahoo.it
/// ah I am a man, I am italian do not send me nudes please, unless you are a girl of course.

#include "dhash.h"
#include <stdio.h>
#include <string.h>
#include <wchar.h>
typedef struct _dfl
{
	char *file;
	int line;
} dFL;

typedef struct _mstack
{
	size_t *val;
	size_t sz;
	size_t n;
	size_t io_val;
} dmStack;

dmStack *new_dmStack();
void destroy_dmStack(dmStack *stk);
size_t dmStack_push(dmStack *stk);
int dmStack_pop(dmStack *stk);

typedef struct _dmhlist
{
	struct _dmhlist *next;
	void *key;
	dFL value;
} dmHList;
typedef struct _dmhashtable dmHashtable;

typedef enum dmhsh_res_value
{
	DMHSH_RUN_OUT_OF_MEM = 0,
	DMHSH_OK,
	DMHSH_ERR_EXISTS,
	DMHSH_ERR_NOT_EXISTS

} DMHSH_RES_VALUE;
typedef size_t (*dmhash_f)(void *);
typedef struct _dmhashtable
{
	dmHList **tbl;
	size_t tblsz;
	dmHList *lst;
	size_t lstsz;
	size_t lstn;
	dmStack *free_slots;
	void *i_key;
	dFL i_val;
	void *o_key;
	dFL *o_val;
	dmhash_f hsh_f;
	DMHSH_RES_VALUE err_n;

} dmHashtable;
dmHashtable *dhtbl;

dmHashtable *new_dmHashtable();
void destroy_dmHashtable(dmHashtable *tbl);

DMHSH_RES_VALUE dmhash_insert(dmHashtable *htbl);
DMHSH_RES_VALUE dmhash_get(dmHashtable *htbl);
DMHSH_RES_VALUE dmhash_pop(dmHashtable *htbl);

dmStack *new_dmStack()
{
	dmStack *res = malloc(sizeof(dmStack));
	res->sz = 10;
	res->val = malloc(sizeof(size_t) * res->sz);
	res->n = 0;
	return res;
}

void destroy_dmStack(dmStack *stk)
{
	free(stk->val);
	free(stk);
}
size_t dmStack_push(dmStack *stk)
{
	if (stk->n >= stk->sz)
	{
		stk->sz <<= 1;
		stk->val = realloc(stk->val, stk->sz * sizeof(size_t));
	}
	stk->val[stk->n] = stk->io_val;
	return ++stk->n;
}
int dmStack_pop(dmStack *stk)
{
	if (stk->n == 0)
		return 0;
	stk->io_val = stk->val[--stk->n];
	return 1;
}
size_t dhash_f(void *p)
{
	unsigned long long res = ((unsigned long long)p >> 4);
	return res;
}
dmHashtable *new_dmHashtable()
{
	dmHashtable *res = malloc(sizeof(dmHashtable));
	res->lstsz = 16;
	res->tblsz = 4;
	res->lstn = 0;
	res->tbl = calloc(res->tblsz, sizeof(dmHList *));
	res->lst = calloc(res->lstsz, sizeof(dmHList));
	res->free_slots = new_dmStack();
	res->hsh_f = dhash_f;
	return res;
}
void destroy_dmHashtable(dmHashtable *tbl)
{
	free(tbl->tbl);
	free(tbl->lst);
	free(tbl);
}

static DMHSH_RES_VALUE dmhash_realloc(dmHashtable *htbl)
{
	dmHList **tbl_tmp, *list_buf_tmp;
	size_t new_tbl_sz, new_lst_sz = htbl->lstsz << 3, i, c_hsh;
	new_tbl_sz = new_lst_sz >> 2;

	list_buf_tmp = realloc(htbl->lst, sizeof(dmHList) * new_lst_sz);

	if (!list_buf_tmp)
		return htbl->err_n = DMHSH_RUN_OUT_OF_MEM;

	memset(list_buf_tmp + htbl->lstn, 0, (new_lst_sz - htbl->lstn) * sizeof(dmHList));
	htbl->lst = list_buf_tmp;
	tbl_tmp = calloc(new_tbl_sz, sizeof(dmHList *));
	if (!tbl_tmp)
		return htbl->err_n = DMHSH_RUN_OUT_OF_MEM;

	htbl->tblsz = new_tbl_sz;
	for (i = 0; i < htbl->lstsz; i++)
	{

		c_hsh = (*htbl->hsh_f)(htbl->lst[i].key) % htbl->tblsz;
		htbl->lst[i].next = tbl_tmp[c_hsh];
		tbl_tmp[c_hsh] = htbl->lst + i;
	}
	htbl->lstsz = new_lst_sz;
	free(htbl->tbl);
	htbl->tbl = tbl_tmp;
	return htbl->err_n = DMHSH_OK;
}

DMHSH_RES_VALUE dmhash_insert(dmHashtable *htbl)
{
	size_t n_list, c_hsh;
	DMHSH_RES_VALUE res;
	dmHList *cur;
	htbl->o_key = NULL;
	htbl->o_val = NULL;
	c_hsh = (*htbl->hsh_f)(htbl->i_key) % htbl->tblsz;
	for (cur = htbl->tbl[c_hsh]; cur; cur = cur->next)
		if (cur->key == htbl->i_key)
		{
			htbl->o_key = &cur->key;
			htbl->o_val = &cur->value;
			res = htbl->err_n = DMHSH_ERR_EXISTS;
			return res;
		}
	if (dmStack_pop(htbl->free_slots))
	{
		n_list = htbl->free_slots->io_val;
	}
	else
	{
		if (htbl->lstn >= htbl->lstsz)
		{
			res = dmhash_realloc(htbl);
			if (res == DMHSH_RUN_OUT_OF_MEM)
				return res;
			c_hsh = (*htbl->hsh_f)(htbl->i_key) % htbl->tblsz;
		}
		n_list = htbl->lstn++;
	}

	cur = htbl->lst + n_list;
	cur->next = htbl->tbl[c_hsh];
	htbl->tbl[c_hsh] = cur;

	cur->key = htbl->i_key;
	cur->value = htbl->i_val;

	htbl->o_key = &cur->key;
	htbl->o_val = &cur->value;
	res = htbl->err_n = DMHSH_OK;

	return res;
}
DMHSH_RES_VALUE dmhash_get(dmHashtable *htbl)
{
	size_t c_hsh;
	dmHList *cur;
	htbl->o_key = NULL;
	htbl->o_val = NULL;
	c_hsh = (*htbl->hsh_f)(htbl->i_key) % htbl->tblsz;

	for (cur = htbl->tbl[c_hsh]; cur; cur = cur->next)
		if (htbl->i_key == cur->key)
		{

			htbl->o_key = &cur->key;
			htbl->o_val = &cur->value;
			return htbl->err_n = DMHSH_OK;
		}
	return htbl->err_n = DMHSH_ERR_NOT_EXISTS;
}
DMHSH_RES_VALUE dmhash_pop(dmHashtable *htbl)
{
	size_t c_hsh;
	dmHList *cur, *prev_cur;
	static dmHList clone;
	htbl->err_n = DMHSH_OK;
	htbl->o_key = NULL;
	htbl->o_val = NULL;

	c_hsh = (*htbl->hsh_f)(htbl->i_key) % htbl->tblsz;
	for (prev_cur = NULL, cur = htbl->tbl[c_hsh]; cur; prev_cur = cur, cur = cur->next)
		if (htbl->i_key == cur->key)
			break;

	if (!cur)
		return htbl->err_n = DMHSH_ERR_NOT_EXISTS;

	if (prev_cur == NULL)
		htbl->tbl[c_hsh] = cur->next;
	else
		prev_cur->next = cur->next;

	htbl->free_slots->io_val = cur - htbl->lst;

	if (!dmStack_push(htbl->free_slots))
		htbl->err_n = DMHSH_RUN_OUT_OF_MEM;

	clone = *cur;
	htbl->o_key = &clone.key;
	htbl->o_val = &clone.value;
	memset(cur, 0, sizeof(dmHList));
	return htbl->err_n;
}
void dstart()
{
	if (dhtbl)
		return;
	dhtbl = new_dmHashtable();
}
void dend()
{
	size_t i;
	dmHList *cur;
	if (!dhtbl)
		return;
	for (i = 0; i < dhtbl->tblsz; i++)
		for (cur = dhtbl->tbl[i]; cur; cur = cur->next)
			printf("%p  file:%s  line:%d\n", cur->key, cur->value.file, (int)cur->value.line);
	destroy_dmHashtable(dhtbl);
	dhtbl = NULL;
}

void *dmalloc(size_t sz, char *file, int line)
{
	void *res = malloc(sz);
	dhtbl->i_key = res;
	dhtbl->i_val.file = file;
	dhtbl->i_val.line = line;
	if (dmhash_insert(dhtbl) == DMHSH_ERR_EXISTS)
		printf("%p exists malloc\n", res);
	return res;
}
void *dcalloc(size_t n, size_t sz, char *file, int line)
{
	void *res = calloc(n, sz);
	dhtbl->i_key = res;
	dhtbl->i_val.file = file;
	dhtbl->i_val.line = line;
	if (dmhash_insert(dhtbl) == DMHSH_ERR_EXISTS)
		printf("%p exists calloc\n", res);
	return res;
}
void *drealloc(void *p, size_t sz, char *file, int line)
{
	dhtbl->i_key = p;
	if (dmhash_pop(dhtbl) == DMHSH_ERR_NOT_EXISTS)
		printf("%p not exists realloc\n", p);
	void *res = realloc(p, sz);
	dhtbl->i_key = res;
	dhtbl->i_val.file = file;
	dhtbl->i_val.line = line;
	if (dmhash_insert(dhtbl) == DMHSH_ERR_EXISTS)
		printf("%p exists realloc\n", res);
	return res;
}
char *dstrdup(const char *s, char *file, int line)
{
	void *res = strdup(s);
	dhtbl->i_key = res;
	dhtbl->i_val.file = file;
	dhtbl->i_val.line = line;
	if (dmhash_insert(dhtbl) == DMHSH_ERR_EXISTS)
		printf("%p exists strdup\n", res);
	return res;
}

wchar_t *dwcsdup(const wchar_t *s, char *file, int line)
{
	void *res = wcsdup(s);
	dhtbl->i_key = res;
	dhtbl->i_val.file = file;
	dhtbl->i_val.line = line;
	if (dmhash_insert(dhtbl) == DMHSH_ERR_EXISTS)
		printf("%p exists strdup\n", res);
	return res;
}
void dfree(void *p)
{
	dhtbl->i_key = p;
	if (dmhash_pop(dhtbl) == DMHSH_ERR_NOT_EXISTS)
		printf("%p not exists free\n", p);
	free(p);
}
void dcomment(void *p, char *cmt)
{
	dhtbl->i_key = p;
	if (dmhash_get(dhtbl) == DMHSH_ERR_NOT_EXISTS)
	{
		printf("%p not exists comment\n", p);
		return;
	}
	dhtbl->o_val->file = cmt;
}
