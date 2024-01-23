# mparser
Parser Engine for Gold Parser

mparser is a parser engine for  <a href="http://www.goldparser.org/">Gold Parser</a> , wrote in ANSI C. So should work with every OS.  Designed to be light-weight and fast.<br>
The reason to write a new engine was that I need an engine that works with UTF-8, with a complete error handling and that can read the .egt files.<br>
Since that .egt files are written in UNICODE, with small effort was possible to support both coding.<br>
To switch from a code to the other just change the 12th row of the file mparser.h, the macro MP_CODING set  it to MP_UTF8 or to MP_UNICODE.<br>
## Usage mparser
  The engine is composed only from the files mparser.h and mparser.c. You just need these two files, and remove the line #include "dhash.h" . <br>
You have to create a parser with one of the follows:<br>
```
  mParser * new_mParserF(const char* file_name, MP_ERRS * err_n  );
  mParser * new_mParserA(const char* src, size_t len, MP_ERRS * err_n);
  mParser * new_mParser();
```
All three return a pointer to a mParser object if succeed and NULL if they fail. For the first two you have to check the variable err_n that is an enum, meanwhile if the third one fails it means it is RUN OUT OF MEMORY.<br>
<b>The third one is not defined, to define it you have to run main.c and then launch \a </b><br>
After you have created the mParser object, just call mpExec(...) declared as follows:<br>
```
#if MP_CODING==MP_UTF8
  MP_ERRS mpExec(mParser * mp, const char * exp);
  MP_ERRS mpExecF(mParser * mp, const  char * file_name);
#elif MP_CODING==MP_UNICODE
    MP_ERRS mpExec(mParser * mp, const wchar_t * exp);
#endif
```
The second argument changes with the coding. I did not implement the xxxF version with UNICODE  since there are too many variables, big-endian, small-endian, with BOM or without.<br>
If some error occurs the error message is available in the member mp->err_msg, meanwhile the  error number is available as return value and also in the member mp->err_n. The error message is not to free.<br>
The output tree is the member mp->out_tree in the mParser object. To get a hint look for the function print_tree(...) in the main.c file.<br>
## Usage main.c
The file main.c it gives you a small but very useful set of commands:<br>

![Schermata del 2024-01-23 15-03-34](https://github.com/jurhas/mparser/assets/11569832/20e3263c-209c-41f7-a772-37d6f0a1a0bf)

First of all It allows you to test the grammar from shell, that is very fast. Since that the new line can be part of the syntax  you have to digit twice enter to accept the input. After few attempts it becomes natural.<br>
With the option \a it translates the .egt file to a C array so you do not need to carry around the file anymore, and it defines the function <br><br>
```
mParser * new_mParser()
```
without arguments<br> 
With the option \s creates a skeleton program, customizable, where you can define return value, arguments and code inside.<br>
With the option \l you can load again the file.<br>
The other are less important, you can see them launching \h .<br>

## usage dhash  
The files dhash.c and dhash.h are a debug tool useful to check if you handle correctly the memory and avoid memory leakage. To use them in other applications just #include "dhash.h" in your root .h file and in the same file define the macros: <br><br>
```
#ifdef DHASH_H_INCLUDED
#define malloc(a) dmalloc(a,__FILE__, __LINE__)
#define calloc(a,b) dcalloc(a,b,__FILE__, __LINE__)
#define realloc(a,b) drealloc(a,b,__FILE__, __LINE__)
#define free(a) dfree(a)
#define strdup(a) dstrdup(a,__FILE__, __LINE__)
#define wcsdup(a) dwcsdup(a,__FILE__, __LINE__)
#endif
```
After this, the first row in the main() function must be:<br>
```
dstart();
```
and the last row:<br>
```
dend();
```
And it checks if you freed correctly all the memory.<br>
To avoid putting hand after you remove the dhash library, maybe you can enclose these instructions inside the #ifdef DHASH_H_INCLUDED as the macros above.
## Further libraries
In mparser.c there are other three libraries, an hashtable, a 8 byte string, and 16 byte string. 4 libraries I forgot the stack.<br>
The one a bit more sophisticated is the hashtable, also designed to be fast and cover a very huge amount of situations. To create it:<br>
```
mHashtable * new_mHashtable(size_t start_size, mhash_f hsh_f,mcmp_f cmp_f); 
```
where mhash_f and mcmp_f are mandatory functions typedef'ed as:<br>
```
typedef size_t (*mhash_f)(mValue*);
typedef int (*mcmp_f)(mValue *a, mValue *b);
```
be careful that the arguments are the union mValue. The first computes the hash and the second compare them as usual. With the hashtable, I just need to know if they are equal or less, but once I wrote it I cover each combination.<br>
After you create the hashtable set the flags as required in the member h->flags :<br>
```
typedef enum mhsh_flags
{
    MHSH_STRDUP_KEY= (1<<0),
    MHSH_STRDUP_VALUE= (1<<1),
    MSHS_WCSDUP_KEY =(1<<2),
    MSHS_WCSDUP_VALUE = (1 << 3),
    MHSH_DESTROY_KEY_ON_POP= (1<<4),
    MHSH_DESTROY_VALUE_ON_POP=(1<<5),
    MHSH_FREE_STR_KEY_ON_POP=(1<<6),
    MHSH_FREE_STR_VALUE_ON_POP=(1<<7),
    MSHS_FREE_STR_KEY_ON_DESTROY=(1<<8),
    MSHS_FREE_STR_VALUE_ON_DESTROY=(1<<9)
}MHSH_FLAGS;
```
And you are done with the creation. There is only an exception if you choose the flags MHSH_DESTROY_KEY_ON_POP,MHSH_DESTROY_VALUE_ON_POP you have to set the member h->fk_f and h->fv_f. These members contain the functions to destroy key and/or value. When you destroy the hashtable you have to give again these functions in the function destroy_...() . If required, of course, or just set them to NULL.<br>  
To avoid the traditional C functions for each combination of types of key and value,  you have to set key and value with the members: h->i_key and  h->i_val then launch one of the follow:<br>
```
MHSH_RES_VALUE mhash_insert(mHashtable * htbl);
MHSH_RES_VALUE mhash_get(mHashtable * htbl);
MHSH_RES_VALUE mhash_pop(mHashtable * htbl);
```
as you can see, they have as only argument the hashtable.  To get the output, you have to look in the members h->o_key and h->o_val. Be careful that these members refer to the location in the memory, they are not a copy.  The insert function sets the output members too. If the new insert does not exist, set the output with the new position and  returns MHSH_OK otherwise set the output with the existing one and returns MHSH_ERR_EXISTS. So with insert and get you cannot modify the o_key or nobody will find it anymore.<br>
If you need a hint, there is the function test_hash_tbl() in the main.c file.<br>
With the combination of the union, flags and errors it is possible to cover practically each requirement, better also than C++ with just three functions. And of course stunning performance since you have not to call contains(), the memory allocation is also very fast because I allocate buffer and not single elements, I  avoid useless strdup and with combination of factos you can optimize it for your needs.<br>
