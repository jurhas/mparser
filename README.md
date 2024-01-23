# mparser
Parser Engine for Gold Parser

mparser is a parser engine for  <a href="http://www.goldparser.org/">Gold Parser</a> , wrote in ANSI C. So should work with every SO.  Designed to be lightweight and fast.<br>
The reason to write a new engine was that I need an engine that works with UTF-8, has a complete error handling and can read the .egt files.<br>
Since that .egt files is wrote in UNICODE, with small effort was possible support both coding.<br>
To switch from a code to the other just change the 12th row of the file mparser.h, to MP_UTF8 or to MP_UNICODE.<br>
<h3>Usage mparser</h3>
  The engine is composed only from the files mparser.h and mparser.c. You just need this two files, and remove the line #include "dhash.h" . <br>
  You have to create a parser with one of the follows:<br>
mParser * new_mParserF(const char* file_name, MP_ERRS * err_n  );<br>
mParser * new_mParserA(const char* src, size_t len, MP_ERRS * err_n);<br>
mParser * new_mParser();<br>
All three return a pointer to a mParser object if suceed and NULL if they fail. For the first two you have to check the variable err_n that is an enum.  Meanwhile if the third one fails it means it is RUN OUT OF MEMORY.<br>
<b>The third one is not defined, to define it you have to run main.c and than launch \a </b>
After you have created the mParser object, just launch :<br>
#if MP_CODING==MP_UTF8<br>
MP_ERRS mpExec(mParser * mp, const char * exp);<br>
MP_ERRS mpExecF(mParser * mp, const  char * file_name);<br>
#elif MP_CODING==MP_UNICODE<br>
    MP_ERRS mpExec(mParser * mp, const wchar_t * exp);<br>
#endif<br>
Choose one according with your coding. I did not implement the xxxxF version with UNICODE  since there are too many variables, big-endian, small-endian, with BOM or without.<br>
To read the output tree just read the variable mp->out_tree in the mParser object. To get a hint look for the function print_tree(...) in the main.c file.<br>  
<h3>Usage main.c</h3>
The file main.c it gives you a small but very usefuul set of commands:<br>
![Schermata del 2024-01-23 15-03-34](https://github.com/jurhas/mparser/assets/11569832/20e3263c-209c-41f7-a772-37d6f0a1a0bf)

First of all It allows you to test the grammar from shell, that is very quick. Since the new line can be part of the sintax to accept the input you have to digit twice enter.<br>
With the option \a it translates the .egt file to a C array so you do not need to carry around the file anymore,and it defines the function <br>
mParser * new_mParser() without argunments<br> 
With the .option \s create a skeleton program, customizable, where you can define return value. arguments and code insdide.<br>
With the option \l you can load again the file.<br>
The other are less important, you can see them launching \h .<br>

<h3>dhash usage </h3>
The files dhash.c and dhash.h are a debug tool usefull to check if you handle correctly the memory and avoid memory leakage. To use them just in other applications just #include "dhash.h" in your root .h file and in the same file to define the macros: <br>

#ifdef DHASH_H_INCLUDED
#define malloc(a) dmalloc(a,__FILE__, __LINE__)
#define calloc(a,b) dcalloc(a,b,__FILE__, __LINE__)
#define realloc(a,b) drealloc(a,b,__FILE__, __LINE__)
#define free(a) dfree(a)
#define strdup(a) dstrdup(a,__FILE__, __LINE__)
#define wcsdup(a) dwcsdup(a,__FILE__, __LINE__)
#endif


After this , the first row in the main() function must be:<br>
dstart();<br>
and the last row:<br>
dend();<br>
And it checks if you freed correctly all the memory.<br>









