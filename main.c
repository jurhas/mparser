#line 2 "main.c"
///This program is distribuited under the licence GPL-3.0
///I have not so much requirement, just alert me if you find
///some bugs: spanu_andrea(at)yahoo.it 
///ah I am a man, I am italian do not send me nudes please, unless you are a girl of course.

#include <ctype.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "mparser.h"

#ifdef _WIN32
#include "windows.h"
#endif // _WIN32
#define MP_LAST_FILE "lastgrm.tb"
#undef mUs_concat
#undef mUs_concatc
#undef mUs_concatcm
#undef mUs_concats
#undef mUs_concat_U16c
#undef mUs_realloc
#undef mUs_reset
#undef ustrcmp
#undef ustrncmp
#undef ustrdup
#undef ustrlen
#undef ustrstr
#undef new_mUString
#undef destroy_mUString
#undef MP_WCSFORMATER
void get_str(m8String *s, char *prompt);
int get_randchr(int srnd, char *buf, int len)
{
	char a[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u',
				'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
				'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

	if (srnd == 0)
		srand((unsigned int)time(NULL));
	while (--len)
		*buf++ = a[rand() % sizeof(a)];
	*buf = '\0';
	return 1;
}
char *get_op_name(int code)
{
	static char *op_name[] = {
		"NULL",	  /*0 NUL (null)*/
		"SOH",	   /*1 SOH (start of header)*/
		"STK",	   /*2 STX (start of text)*/
		"ETX",	   /*3 ETX (end of text)*/
		"EOT",	   /*4 EOT (end of transmission)*/
		"ENQ",	   /*5 ENQ (enquiry)*/
		"ACK",	   /*6 ACK (acknowledge)*/
		"BEL",	   /*7 BEL (bell)*/
		"BS",		/*8 BS (backspace)*/
		"HT",		/*9 HT (horizontal tab)*/
		"LF",		/*10 LF (line feed - new line)*/
		"VT",		/*11 VT (vertical tab)*/
		"FF",		/*12 FF (form feed - new page)*/
		"CR",		/*13 CR (carriage return)*/
		"SO",		/*14 SO (shift out)*/
		"SI",		/*15 SI (shift in)*/
		"DLE",	   /*16 DLE (data link escape)*/
		"DC1",	   /*17 DC1 (device control 1)*/
		"DC2",	   /*18 DC2 (device control 2)*/
		"DC3",	   /*19 DC3 (device control 3)*/
		"DC4",	   /*20 DC4 (device control 4)*/
		"NAK",	   /*21 NAK (negative acknowledge)*/
		"SYN",	   /*22 SYN (synchronous idle)*/
		"ETB",	   /*23 ETB (end of transmission block)*/
		"CAN",	   /*24 CAN (cancel)*/
		"EM",		/*25 EM (end of medium)*/
		"SUB",	   /*26 SUB (substitute)*/
		"ESC",	   /*27 ESC (escape)*/
		"FS",		/*28 FS (file separator)*/
		"GS",		/*29 GS (group separator)*/
		"RS",		/*30 RS (record separator)*/
		"US",		/*31 US (unit separator)*/
		"SPACE",	 /*32 (space)*/
		"ExMark",	/*33 !*/
		"DblQuot",   /*34 "*/
		"NumSgn",	/*35 #*/
		"Dol",	   /*36 $*/
		"Perc",	  /*37 %*/
		"Amper",	 /*38 &*/
		"SngQuot",   /*39 '*/
		"OBrk",	  /*40 (*/
		"CBrk",	  /*41 )*/
		"Times",	 /*42 **/
		"Plus",	  /*43 +*/
		"Comma",	 /*44 ,*/
		"Minus",	 /*45 -*/
		"Dot",	   /*46 .*/
		"Slash",	 /*47 /*/
		"Zero",	  /*48 0*/
		"One",	   /*49 1*/
		"Two",	   /*50 2*/
		"Three",	 /*51 3*/
		"Four",	  /*52 4*/
		"Five",	  /*53 5*/
		"Six",	   /*54 6*/
		"Seven",	 /*55 7*/
		"Eight",	 /*56 8*/
		"Nine",	  /*57 9*/
		"Colon",	 /*58 :*/
		"Semcln",	/*59 ;*/
		"Lt",		/*60 <*/
		"Eq",		/*61 =*/
		"Gt",		/*62 >*/
		"QstMrk",	/*63 ?*/
		"At",		/*64 @*/
		"A",		 /*65 A*/
		"B",		 /*66 B*/
		"C",		 /*67 C*/
		"D",		 /*68 D*/
		"E",		 /*69 E*/
		"F",		 /*70 F*/
		"G",		 /*71 G*/
		"H",		 /*72 H*/
		"I",		 /*73 I*/
		"J",		 /*74 J*/
		"K",		 /*75 K*/
		"L",		 /*76 L*/
		"M",		 /*77 M*/
		"N",		 /*78 N*/
		"O",		 /*79 O*/
		"P",		 /*80 P*/
		"Q",		 /*81 Q*/
		"R",		 /*82 R*/
		"S",		 /*83 S*/
		"T",		 /*84 T*/
		"U",		 /*85 U*/
		"V",		 /*86 V*/
		"W",		 /*87 W*/
		"X",		 /*88 X*/
		"Y",		 /*89 */
		"Z",		 /*90 Z*/
		"OSBrk",	 /*91 [*/
		"BackSlash", /*92 \ */
		"CSBrk",	 /*93 ]*/
		"Caret",	 /*94 ^*/
		"UndScr",	/*95 _*/
		"BckTck",	/*96 `*/
		"a",		 /*97 a*/
		"b",		 /*98 b*/
		"c",		 /*99 c*/
		"d",		 /*100 d*/
		"e",		 /*101 e*/
		"f",		 /*102 f*/
		"g",		 /*103 g*/
		"h",		 /*104 h*/
		"i",		 /*105 i*/
		"j",		 /*106 j*/
		"k",		 /*107 k*/
		"l",		 /*108 l*/
		"m",		 /*109 m*/
		"n",		 /*110 n*/
		"o",		 /*111 o*/
		"p",		 /*112 p*/
		"q",		 /*113 q*/
		"r",		 /*114 r*/
		"s",		 /*115 s*/
		"t",		 /*116 t*/
		"u",		 /*117 u*/
		"v",		 /*118 v*/
		"w",		 /*119 w*/
		"x",		 /*120 x*/
		"y",		 /*121 y*/
		"z",		 /*122 z*/
		"OCBrk",	 /*123 {*/
		"VertBar",   /*124 |*/
		"CCBrk",	 /*125 }*/
		"Tilde",	 /*126 ~*/
		"DEL",	   /*127 DEL (delete)*/
	};
	if (code < 0 || code >= sizeof(op_name) / sizeof(op_name[0]))
		return NULL;
	return op_name[code];
}

void get_simple_input(m8String *s, char *prompt, int twice_enter)
{
	int c, is_valid = 1, twice;
	m8s_reset(s);
	printf("%s", prompt);
	twice = 0;
	while (1)
	{
		c = getchar();
		if (c > 127)
			is_valid = 0;
		else if (c == '\n' && twice_enter && twice)
			break;
		else if (c == '\n' && twice_enter)
		{
			printf("%s", prompt);
			twice = 1;
		}
		else if (c == '\n')
			break;
		else
			twice = 0;
		m8s_concatc(s, c);
	}
	if (!is_valid)
	{
		printf("Charachter Not Valid\n");
		get_simple_input(s, prompt, twice_enter);
		return;
	};
}
void format_valid_c_identifier(m8String *s)
{
	char *cur = (char *)s->s;
	size_t len = 0;
	if (!(isalpha((int)(unsigned char)*cur) || *cur == '_'))
		*cur = '_';

	/// the follow 29 comes from this article
	/// https://stackoverflow.com/questions/2352209/max-identifier-length
	/// it leaves the space for 99 further same-name functions
	/// feel free to modify it if you use it in internal code bla bla bla
	///  this number does not compare in nowhere else

	while (*cur && len < 29)
	{
		if (!isalnum((int)(unsigned char)*cur))
			*cur = '_';
		cur++;
		len++;
	}
	*cur = '\0';

	s->n = (size_t)(cur - s->s);
}
FILE *get_file_w(m8String *s)
{
	FILE *f;
	do
	{
		get_simple_input(s, "Get File Name Inclusive extension(q = quit)>", 0);
		if (strcmp(s->s, "q") == 0)
			return NULL;
		f = fopen(s->s, "r");
		if (f)
		{
			m8String *s_tmp = new_m8String();
			fclose(f);
			get_simple_input(s_tmp,
							 "File already existing do you want overwrite it? (y/any "
							 "other key to denie)>",
							 0);
			if (strcmp(s_tmp->s, "y") != 0)
			{

				f = NULL;
				destroy_m8String(s_tmp);
				continue;
			}
			destroy_m8String(s_tmp);
		}

		f = fopen(s->s, "wb");
		if (!f)
			printf("Cannot Open the file\n");

	} while (f == NULL);
	return f;
}
void create_skeleton(mParser *mp, m8String *s)
{
	char *ret_val, *arg_list, *code_inside;
	m8String *decl, *jt, *def, *rl_name, *f_name;
	mHashtable *h;
	mRule *rl;
	mSymbol *sy;
	FILE *f;
	int i, j;
	clock_t t1, t2;
	printf("The Program is going to create the skeleton as follow:\n");
	printf("<ret_val>  FunctionName <arg_list>\n");
	printf("{\n");
	printf("<code_inside>\n");
	printf("}\n");

	get_simple_input(s, "Get <ret_val>:", 0);
	ret_val = strdup(s->s);
	get_simple_input(s, "Get <arg_list>(brackets inclusive):", 0);
	arg_list = strdup(s->s);
	printf("Get <code_inside>(can be multi-line, remember the semicolon and the "
		   "tabs, twice Enter to accept)\n");
	get_simple_input(s, ">", 1);
	code_inside = strdup(s->s);
	printf("The function prototype is going to be as follow:\n");
	printf("%s FunctionName %s\n", ret_val, arg_list);
	printf("{\n");
	printf("%s", code_inside);
	printf("}\n");
	get_simple_input(s, "Is Ok? (any key to continue/n q=quite)", 0);
	switch (*s->s)
	{

	case 'q':
		free(ret_val);
		free(arg_list);
		free(code_inside);
		return;
	case 'n':
	case 'N':
		free(ret_val);
		free(arg_list);
		free(code_inside);
		create_skeleton(mp, s);
		return;
	default:
		break;
	}
	t1 = clock();

	decl = new_m8String();
	jt = new_m8String();
	def = new_m8String();
	rl_name = new_m8String();
	f_name = new_m8String();
	h = new_mHashtable(100, mhash_f_s, mcmp_s);
	h->flags = MHSH_STRDUP_KEY | MSHS_FREE_STR_KEY_ON_DESTROY;

	m8s_concats(decl, "typedef ");
	m8s_concats(decl, ret_val);
	m8s_concats(decl, " (* mp_f)");
	m8s_concats(decl, arg_list);
	m8s_concats(decl, ";\n\n");

	m8s_concats(jt, "mp_f RuleJumpTable [] ={\n");

	for (i = 0; i < mp->grm->nrule; i++)
	{
		rl = mp->grm->rule + i;

		m8s_reset(rl_name);
		m8s_reset(f_name);

		m8s_concatcm(f_name, 'R');

		mUs_concatCurCodingS(f_name, mp->grm->sym[rl->NonTerminal].Name);

		m8s_concatcm(f_name, '_');

		m8s_concats(rl_name, "//");
		m8s_concati(rl_name, i);
		m8s_concats(rl_name, ") <");

		mUs_concatCurCodingS(rl_name, mp->grm->sym[rl->NonTerminal].Name);

		m8s_concats(rl_name, ">::=");

		for (j = 0; j < rl->nsymbol; j++)
		{
			const muchar *lcur;
			const char *tmp;
			sy = mp->grm->sym + rl->symbol[j];

			if (sy->Type == mSyNonterminal)
				m8s_concatcm(rl_name, '<');
			mUs_concatCurCodingS(rl_name, sy->Name);
			if (sy->Type == mSyNonterminal)
				m8s_concatcm(rl_name, '>');

			if (isalnum(*sy->Name))
			{
				mUs_concatCurCodingS(f_name, sy->Name);
			}
			else
			{
				lcur = sy->Name;
				while (*lcur)
				{
					tmp = get_op_name(*lcur);
					if (tmp)
						m8s_concats(f_name, tmp);
					else
						m8s_concats(f_name, "Unk");
					lcur++;
				}
			}
		}
		m8s_concatcm(rl_name, '\n');
		format_valid_c_identifier(f_name);
		h->i_key.s = f_name->s;
		if (mhash_insert(h) == MHSH_ERR_EXISTS)
		{
			int k = 2;
			m8s_reset(s);
			m8s_concat8s(s, f_name);
			do
			{
				m8s_reset(f_name);
				m8s_concat8s(f_name, s);
				m8s_concati(f_name, k++);
				h->i_key.s = f_name->s;
			} while (mhash_insert(h) == MHSH_ERR_EXISTS);
		}
		m8s_concat8s(decl, rl_name);
		m8s_concats(decl, ret_val);
		m8s_concatcm(decl, ' ');
		m8s_concat8s(decl, f_name);
		if (*arg_list != '(')
			m8s_concatcm(decl, ' ');
		m8s_concats(decl, arg_list);
		m8s_concats(decl, ";\n\n");

		m8s_concat8s(jt, rl_name);
		m8s_concat8s(jt, f_name);
		m8s_concats(jt, ",\n\n");

		m8s_concat8s(def, rl_name);
		m8s_concats(def, ret_val);
		m8s_concatcm(def, ' ');
		m8s_concat8s(def, f_name);
		if (*arg_list != '(')
			m8s_concatcm(def, ' ');

		m8s_concats(def, arg_list);
		m8s_concats(def, "\n{\n");
		m8s_concats(def, code_inside);
		m8s_concats(def, "\n}\n\n");
	}
	m8s_concats(jt, "};\n");
	t2 = clock();
	printf("Create Skeleton sz=%d kB t=%f\n", (int)(decl->n + jt->n + def->n), F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
	f = get_file_w(s);
	if (!f)
		goto QUIT;
	fputs("#include \"mparser.h\"\n\n", f);
	fputs(decl->s, f);
	fputs(jt->s, f);
	fputs(def->s, f);
	fclose(f);
QUIT:
	destroy_mHashtable(h, NULL, NULL);
	destroy_m8String(jt);
	destroy_m8String(decl);
	destroy_m8String(def);
	destroy_m8String(rl_name);
	destroy_m8String(f_name);
	;

	free(ret_val);
	free(arg_list);
	free(code_inside);
	system(s->s);
}

//the follow block is happily copied from SQLite 
typedef enum
{
	PBCRED = 4,
	PBCGREEN = 2,
	PBCBLUE = 1
} PRINTBOLDCOLOR;
#ifdef _WIN32
void printBold(const char *zText, int color)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO defaultScreenInfo;
	GetConsoleScreenBufferInfo(out, &defaultScreenInfo);
	SetConsoleTextAttribute(out, color | FOREGROUND_INTENSITY);
	printf("%s", zText);
	SetConsoleTextAttribute(out, defaultScreenInfo.wAttributes);
}
#else
#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KYEL "\x1B[33m"
#define KBLU "\x1B[34m"
#define KMAG "\x1B[35m"
#define KCYN "\x1B[36m"
#define KWHT "\x1B[37m"

void printBold(const char *zText, int color)
{
	if (color == PBCRED)
		printf(KRED "%s" KNRM, zText);
	else if (color == PBCGREEN)
		printf(KGRN "%s" KNRM, zText);
	else if (color == PBCBLUE)
		printf(KCYN "%s" KNRM, zText);
}
#endif

int load_fl(m8String *s)
{
	FILE *f = fopen(s->s + 3, "rb");
	size_t sz;
	if (!f)
	{
		printBold("Cannot open the file", PBCRED);
		printf("\n");
		return 0;
	}
	fseek(f, 0, SEEK_END);
	sz = ftell(f);
	fseek(f, 0, SEEK_SET);
	m8s_realloc(s, sz);
	fread(s->s, sizeof(char), sz, f);
	s->n = sz;
	s->s[s->n] = '\0';
	fclose(f);
	return 1;
}
void test_mp(mParser *mp, m8String *s)
{
	int n;
	MP_ERRS err_n;
	clock_t t1, t2;
	printf("Get Exp or \\i <namefile>\n");
	get_str(s, "Get Exp");
	printf("Get N\n");
	scanf("%d", &n);
	if (strncmp(s->s, "\\i ", 3) == 0)
	{
		if (!load_fl(s))
			return;
	}

#if MP_CODING == MP_UNICODE
	mU16String *u16s = new_mU16String();
	m8s_to_mU16s(s, u16s);
	printf("UNICODE:");
	t1 = clock();
	/***************/
	while (n--)
		if ((err_n = mpExec(mp, u16s->s)) != MP_OK)
		{
			printf("%ls", mp->err_msg);
			return;
		}
	/***************/
	t2 = clock();

	destroy_mU16String(u16s);
#elif MP_CODING == MP_UTF8
	printf("UTF-8:");
	t1 = clock();
	/***************/
	while (n--)
		if ((err_n = mpExec(mp, s->s)) != MP_OK)
		{
			printf("%s", mp->err_msg);
			return;
		}

	/***************/
	t2 = clock();
#endif
	printf("Time:%f sec\n", F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
}

int test_hash_tbl()
{
	int op = 'i';
	char key[100] = {0}, value[100] = {0};
	mHashtable *htbl = new_mHashtable(0, mhash_f_s, mcmp_s);
	htbl->flags = MHSH_STRDUP_KEY | MHSH_STRDUP_VALUE;

	printf("\\i insert\n");
	printf("\\g get\n");
	printf("\\p pop\n");
	printf("\\b benchmark\n");
	printf("\\q quit\n");
	while (1)
	{
		printf("Op %s\n", op == 'i' ? "insert" : op == 'g' ? "get" : "pop");
		printf("Insert Key:");
		(void)scanf("%98s", key);

		if (strcmp(key, "\\q") == 0)
		{
			break;
		}
		if (strcmp(key, "\\i") == 0)
		{
			op = 'i';
			continue;
		}
		else if (strcmp(key, "\\g") == 0)
		{
			op = 'g';
			continue;
		}

		else if (strcmp(key, "\\p") == 0)
		{
			op = 'p';
			continue;
		}
		else if (strcmp(key, "\\b") == 0)
		{
			int sz, i;
			char **buf, wrd[15];
			clock_t t1, t2;
			mHashtable *ht, *conf;
			ht = new_mHashtable(10, mhash_f_s, mcmp_s);
			ht->flags = MHSH_STRDUP_KEY | MHSH_FREE_STR_KEY_ON_POP;
			conf = new_mHashtable(10, mhash_f_ull, mcmp_ull);
			printf("Get Items count:");

			(void)scanf("%d", &sz);

			buf = calloc(sz, sizeof(char *));
			t1 = clock();
			for (i = 0; i < sz; i++)
			{
				get_randchr(i, wrd, sizeof(wrd) - 1);
				buf[i] = strdup(wrd);
			}
			t2 = clock();
			printf("Key array prep:%f\n", (float)(t2 - t1) / CLOCKS_PER_SEC);
			t1 = clock();
			for (i = 0; i < sz; i++)
			{
				ht->i_key.s = buf[i];
				ht->i_val.ull = i;
				if (mhash_insert(ht) == MHSH_RUN_OUT_OF_MEM)
				{
					printf("ROOM\n");
					goto ERR1;
				}
				else if (ht->err_n == MHSH_ERR_EXISTS)
				{
					printf("Key Already Exists %s\n", buf[i]);
				}
			}
			t2 = clock();
			printf("Insert %d items:%f\n", sz, F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
			t1 = clock();
			for (i = 0; i < sz; i++)
			{
				ht->i_key.s = buf[i];
				if (mhash_get(ht) == MHSH_ERR_NOT_EXISTS)
				{
					printf("Key %s Not Exists\n", buf[i]);
					// system("pause");
				}
			}
			t2 = clock();
			printf("Get %d items:%f sec\n", sz, F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
			t1 = clock();
			for (i = 0; i < ht->tblsz; i++)
			{
				mull count = 0;
				mHList *tmp;
				for (tmp = ht->tbl[i]; tmp; tmp = tmp->next)
					count++;
				conf->i_key.ull = count;
				conf->i_val.ull = 0;
				if (mhash_insert(conf) == MHSH_RUN_OUT_OF_MEM)
				{
					printf("ROOM\n");
					goto ERR1;
				}
				conf->o_val->ull++;
			}
			t2 = clock();
			printf("Conflict study:%f sec\n", F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
			for (i = 0; i < conf->lstn; i++)
			{
				printf("%d rows have %d collisions\n", (int)conf->lst[i].value.ull, (int)conf->lst[i].key.ull);
			}

			t1 = clock();
			for (i = 0; i < sz; i += 2)
			{
				ht->i_key.s = buf[i];
				if (mhash_pop(ht) == MHSH_RUN_OUT_OF_MEM)
				{
					printf("ROOM\n");
					goto ERR1;
				}
				else if (ht->err_n == MHSH_ERR_NOT_EXISTS)
				{
					printf("Key %s Not Exists\n", buf[i]);
					// system("pause");
				}
			}
			for (i = 1; i < sz; i += 2)
			{
				ht->i_key.s = buf[i];
				if (mhash_pop(ht) == MHSH_RUN_OUT_OF_MEM)
				{
					printf("ROOM\n");
					goto ERR1;
				}
				else if (ht->err_n == MHSH_ERR_NOT_EXISTS)
				{
					printf("Key %s Not Exists\n", buf[i]);
				}
			}
			t2 = clock();
			printf("Pop %d items:%f sec\n", sz, F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
		ERR1:
			for (i = 0; i < sz; i++)
				free(buf[i]);
			free(buf);
			destroy_mHashtable(ht, NULL, NULL);
			destroy_mHashtable(conf, NULL, NULL);
		}
		else
		{
			htbl->i_key.s = key;

			if (op == 'i')
			{
				printf("Get Value:");
				(void)scanf("%98s", value);

				htbl->i_val.s = value;
				mhash_insert(htbl);
			}
			else if (op == 'g')
				mhash_get(htbl);
			else if (op == 'p')
				mhash_pop(htbl);

			switch (htbl->err_n)
			{
			case MHSH_RUN_OUT_OF_MEM:
				printf("ROOM\n");
				break;
			case MHSH_ERR_EXISTS:
				printf("Exists %s %s\n", htbl->i_key.s, htbl->i_val.s);
				break;
			case MHSH_ERR_NOT_EXISTS:
				printf("Not Exists %s %s\n", htbl->i_key.s, htbl->i_val.s);
				break;
			case MHSH_OK:
				if(htbl->o_key && htbl->o_val)
					printf("Ok %s %s\n", htbl->o_key->s, htbl->o_val->s);
				else
					printf("Err: Output members not setted\n");
				break;
			}
			if (op == 'p' && htbl->err_n == MHSH_OK)
			{
				free(htbl->o_key->s);
				free(htbl->o_val->s);
			}
		}
	}
	return 1;
}
void print_err(MP_ERRS err_n)
{
	switch (err_n)
	{
	case MP_RUN_OUT_OF_MEMORY:
		printBold("ERR:ROOM\n", PBCRED);
		break;
	case MP_OK:
		printBold("ERR:Ok\n", PBCRED);
		break;
	case MP_CANNOT_OPEN_FILE:
		printBold("ERR:Cannot open file\n", PBCRED);
		break;
	case MP_ERR_READING_FILE:
		printBold("ERR:Error occurs reading the file\n", PBCRED);
		break;
	case MP_NOT_VALID_GRAMMAR:
		printBold("ERR:Grammar not valid\n", PBCRED);
		break;
	case MP_NOT_VALID_UTF8_SEQ:
		printBold("ERR:Not valid UTF8 seq", PBCRED);
		break;
	case MP_NOT_VALID_CHAR:
		printBold("ERR:Not valid char", PBCRED);
		break;
	case MP_NOT_VALID_END:
		printBold("ERR:Unexpected End", PBCRED);
		break;
	case MP_UNKNOWN_ERR:
		printBold("ERR:Unknowm Error ", PBCRED);
		break;
	default:
		printBold("Opss\n", PBCRED);
		break;
	}
}
void print_tree(mTree *t, m8String *indent, int last)
{
	size_t i;
	m8String *nl = new_m8String();

	printf("%s", indent->s);
	printf("+- ");
	if (t->symbol.Type == mSyTerminal)
	{
		printBold(t->token.lexeme ? t->token.lexeme : MP_EMPTY_STR, PBCGREEN);
	}
	else if (t->symbol.Type == mSyNonterminal && indent->n)
		printf("<%" MP_STRINGPAT ">:: = ", t->symbol.Name ? t->symbol.Name : MP_EMPTY_STR);
	else if (t->symbol.Type == mSyNonterminal && indent->n == 0)
	{
		printBold("<", PBCBLUE);
		printBold(t->symbol.Name, PBCBLUE);
		printBold(">::= ", PBCBLUE);
	}
	else
	{
		printBold("ERROR", PBCRED);
		printf("\n");
		goto ERR;
	}

	for (i = 0; i < t->nchs; i++)
		if (t->chs[i]->symbol.Type == mSyTerminal)
		{
			printf("%" MP_STRINGPAT " ", t->chs[i]->symbol.Name ? t->chs[i]->symbol.Name : MP_EMPTY_STR);
		}
		else if (t->chs[i]->symbol.Type == mSyNonterminal)
		{
			printf("<%" MP_STRINGPAT "> ", t->chs[i]->symbol.Name ? t->chs[i]->symbol.Name : MP_EMPTY_STR);
		}

	printf("\n");
	m8s_concat(nl, indent->s, indent->n);
	if (last)
		m8s_concats(nl, "  ");
	else
		m8s_concats(nl, "| ");

	for (i = 0; i < t->nchs; i++)
		print_tree(t->chs[i], nl, (int)i == t->nchs - 1);
ERR:
	destroy_m8String(nl);
}

void print_treeF(mTree *t, m8String *indent, int last, FILE *f)
{
	size_t i;
	m8String *nl = new_m8String();

	fputs(indent->s, f);
	fputs("+- ", f);

	if (t->symbol.Type == mSyTerminal)
		fprintf(f, "%" MP_STRINGPAT, t->token.lexeme ? t->token.lexeme : MP_EMPTY_STR);

	else if (t->symbol.Type == mSyNonterminal)
		fprintf(f, "<%" MP_STRINGPAT ">:: = ", t->symbol.Name ? t->symbol.Name : MP_EMPTY_STR);
	else
	{
		printBold("ERROR", PBCRED);
		printf("\n");
		goto ERR;
	}

	if (t->nchs)
	{
		for (i = 0; i < t->nchs; i++)
			if (t->chs[i]->symbol.Type == mSyTerminal)
			{
				fprintf(f, "%" MP_STRINGPAT " ", t->chs[i]->symbol.Name ? t->chs[i]->symbol.Name : MP_EMPTY_STR);
			}
			else if (t->chs[i]->symbol.Type == mSyNonterminal)
			{
				fprintf(f, "<%" MP_STRINGPAT "> ", t->chs[i]->symbol.Name ? t->chs[i]->symbol.Name : MP_EMPTY_STR);
			}
	}
	fputs("\n", f);

	m8s_concat(nl, indent->s, indent->n);
	if (last)
		m8s_concats(nl, "  ");
	else
		m8s_concats(nl, "| ");

	for (i = 0; i < t->nchs; i++)
		print_treeF(t->chs[i], nl, (int)i == t->nchs - 1, f);
ERR:
	destroy_m8String(nl);
}

void get_str(m8String *s, char *prompt)
{
	char c;
	int nl_twice = 1;
	m8s_reset(s);
	printf("%s>", prompt);

	while ((c = (char)getchar()))
	{
		if (c == '\n' && nl_twice)
			break;
		else if (c == '\n')
		{
			printf("%s>", prompt);
			nl_twice = 1;
		}
		else
			nl_twice = 0;
		m8s_concatcm(s, c);
	}

	while (s->n > 0 && isspace((int)(unsigned char)s->s[s->n - 1]))
		s->s[--s->n] = '\0';

	if (s->n == 0)
	{
		get_str(s, prompt);
		return;
	}
}
void print_help()
{
	printf("Digit twice Enter to accept input\n");
	printf("\\q to quit\n");
	printf("\\a translate the .egt file to a C array, therefore defines the "
		   "function new_mParser() without arguments\n");
	printf("\\i <namefile> to execute a file\n");
	printf("\\l to load the tables again\n");
	printf("\\l <namefile>to load another tables \n");
	printf("\\n to navigate node by node\n");
	printf("\\o displays the last tree again\n");
	printf("\\o <namefile> saves the last tree in a file\n");
	printf("\\s create a skeleton program\n");
	printf("\\t benchmark the program\n");
	printf("\\h help\n");
}
int get_choose(m8String *s, char *prompt, int max)
{
	int c;
	int res = 0;
	char *cur;
	m8s_reset(s);
	printf("%s", prompt);
	printf(">");
	while ((c = getchar()) != '\n')
		m8s_concatcm(s, c);
	cur = s->s;
	if (*s->s == '.')
		return -1;
	while (isdigit((int)(unsigned char)*cur))
	{
		res += res * 10 + *cur - '0';
		cur++;
	}
	while (isspace((int)(unsigned char)*cur))
		cur++;
	if (*cur || res >= max)
	{
		printf("Not valid choose\n");
		printf("Number of the node the enter in the level\n");
		printf(". to exit a level\n");
		return get_choose(s, prompt, max);
	}
	return res;
}
void _navigate(mTree *t, m8String *s, char *prompt)
{
	size_t i;
	int choose;
	if (t->symbol.Type == mSyTerminal)
		printf("%" MP_STRINGPAT "\n", t->token.lexeme ? t->token.lexeme : MP_EMPTY_STR);
	else if (t->symbol.Type == mSyNonterminal)
		printf("<%" MP_STRINGPAT ">::=\n", t->symbol.Name ? t->symbol.Name : MP_EMPTY_STR);
	if (t->nchs)
	{
		for (i = 0; i < t->nchs; i++)
			if (t->chs[i]->symbol.Type == mSyTerminal)
			{
				printf("  +-%d) %" MP_STRINGPAT "\n", (int)i,
					   t->chs[i]->token.lexeme ? t->chs[i]->token.lexeme : MP_EMPTY_STR);
			}
			else if (t->chs[i]->symbol.Type == mSyNonterminal)
			{
				printf("  +-%d) <%" MP_STRINGPAT ">\n", (int)i,
					   t->chs[i]->symbol.Name ? t->chs[i]->symbol.Name : MP_EMPTY_STR);
			}
	}
	choose = get_choose(s, prompt, (int)t->nchs);
	if (choose < 0)
		return;
	_navigate(t->chs[choose], s, prompt);
	_navigate(t, s, prompt);
}
void navigate(mTree *t, m8String *s, char *prompt)
{
	if (!t)
		return;
	printf("Digit node number  to enter in the node\n");
	printf(". to exit from the current node\n");
	_navigate(t, s, prompt);
}
void create_c_array(char *fname)
{
	m8String *s, *out_fl_name;
	FILE *f, *out_fl;
	int c, i = 0;
	clock_t t1, t2;
	f = fopen(fname, "rb");
	if (!f)
	{
		printf("Cannot open file\n");
		return;
	}
	t1 = clock();
	s = new_m8String();
	out_fl_name = new_m8String();
	m8s_concats(s, "mParser * new_mParser()\n");
	m8s_concats(s, "{\n");
	m8s_concats(s, "\tMP_ERRS err_n;\n");
	m8s_concats(s, "\tunsigned char grm_arr[]={\n\t\t");
	while ((c = fgetc(f)) != EOF)
	{
		m8s_concati(s, c);
		m8s_concatcm(s, ',');
		if (++i % 20 == 0)
		{
			m8s_concats(s, "\n\t\t");
			i = 0;
		}
	}
	m8s_concats(s, "};\n");
	m8s_concats(s, "\t\treturn new_mParserA((char*)grm_arr,sizeof(grm_arr),&err_n);\n");
	m8s_concats(s, "}");
	t2 = clock();
	printf("Array Construction size:%d time:%f secs\n", (int)s->n, F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
	out_fl = get_file_w(out_fl_name);
	if (out_fl)
	{
		fputs(s->s, out_fl);
		fclose(out_fl);
	}
	fclose(f);
	destroy_m8String(s);
	system(out_fl_name->s);
	destroy_m8String(out_fl_name);
}
void save_last_file(char *fname)
{
	FILE *f = fopen(MP_LAST_FILE, "wb");
	if (!f)
		return;
	fputs(fname, f);
	fclose(f);
}
void mainloop(mParser **smp, m8String *s, char **fn)
{
	mParser *mp = *smp;
	MP_ERRS err_n;
	clock_t t1, t2;
	while (1)
	{
		get_str(s, "Get Exp");

		if (strcmp(s->s, "\\q") == 0)
			break;
		if (strcmp(s->s, "\\l") == 0)
		{
			t1 = clock();
			mParser *new_mp = new_mParserF(*fn, &err_n);
			t2 = clock();

			if (new_mp)
			{
				destroy_mParser(mp);
				*smp = mp = new_mp;
				printf("Load Tables %f secs\n", F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
			}
			else
			{
				print_err(err_n);
				printf("The program keeps the old tables\n");
			}
			continue;
		}
		if (strncmp(s->s, "\\l ", 3) == 0)
		{
			t1 = clock();
			mParser *new_m = new_mParserF(s->s + 3, &err_n);
			t2 = clock();
			if (!new_m)
			{
				print_err(err_n);
				printf("The program keeps the old tables\n");
				continue;
			}
			destroy_mParser(mp);
			*smp = mp = new_m;
			free(*fn);
			*fn = strdup(s->s + 3);
			save_last_file(*fn);
			printf("Load Tables %f secs\n", F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
			continue;
		}
		if (strcmp(s->s, "\\h") == 0)
		{
			print_help();
			continue;
		}
		if (strcmp(s->s, "\\n") == 0)
		{
			navigate(mp->out_tree, s, "Get Node");
			continue;
		}
		if (strcmp(s->s, "\\s") == 0)
		{
			create_skeleton(mp, s);
			continue;
		}
		if (strcmp(s->s, "\\a") == 0)
		{
			create_c_array(*fn);
			continue;
		}
		if (strcmp(s->s, "\\o") == 0)
		{
			if (mp->out_tree)
			{
				m8s_reset(s);
				print_tree(mp->out_tree, s, 1);
			}
			else
				printf("No output tree available\n");

			continue;
		}
		if (strncmp(s->s, "\\o ", 3) == 0)
		{
			if (!mp->out_tree)
			{
				printf("No output tree available\n");
				continue;
			}

			FILE *fout = fopen(s->s + 3, "r");
			m8String *s_tmp = new_m8String();
			if (fout)
			{

				get_simple_input(s_tmp,
								 "File already existing do you want overwrite it? "
								 "(y/any other key to denie)>",
								 0);
				if (strcmp(s_tmp->s, "y") != 0)
				{
					fclose(fout);
					destroy_m8String(s_tmp);
					continue;
				}
				fclose(fout);
			}
			fout = fopen(s->s + 3, "wb");
			if (!fout)
			{
				printf("Cannot open the file\n");
				destroy_m8String(s_tmp);
				continue;
			}
			m8s_reset(s_tmp);
			print_treeF(mp->out_tree, s_tmp, 1, fout);
			fclose(fout);
			destroy_m8String(s_tmp);
			system(s->s + 3);
			continue;
		}
		if (strncmp(s->s, "\\i ", 3) == 0)
			if (!load_fl(s))
				continue;
		if (strcmp(s->s, "\\t") == 0)
		{
			test_mp(mp, s);
			continue;
		}
#if MP_CODING == MP_UNICODE
		mU16String *u16s = new_mU16String();
		m8s_to_mU16s(s, u16s);

		t1 = clock();
		/***************/
		err_n = mpExec(mp, u16s->s);
		/***************/
		t2 = clock();
		destroy_mU16String(u16s);
#elif MP_CODING == MP_UTF8
		t1 = clock();
		/***************/
		err_n = mpExec(mp, s->s);
		/***************/
		t2 = clock();
#endif
		if (err_n != MP_OK && mp->err_msg)
		{
			m8s_reset(s);
			mUs_concatCurCodingS(s, mp->err_msg);
			printBold(s->s, PBCRED);
			printf("\n");
		}
		else if (err_n != MP_OK)
			print_err(err_n);
		else if (mp->out_tree)
		{
			m8s_reset(s);
			print_tree(mp->out_tree, s, 1);
			printf("Stat: %d nodes time:%f sec\n",
				   (int)((mp->tree_data.mem_chunks->n - 1) * mp->tree_data.sz + mp->tree_data.n),
				   F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
		}
	}
}

int main()
{
#ifdef DHASH_H_INCLUDED
	dstart();
#endif
#ifdef _WIN32
	SetConsoleCP(CP_UTF8);
	SetConsoleOutputCP(CP_UTF8);
#endif
	mParser *mp = NULL;
	clock_t t1, t2;
	FILE *f;
	MP_ERRS err_n;
	int c, new_fname = 0;
	char *fname;
	m8String *s = new_m8String();

	printf("Digit twice Enter to accept input\n");
	printf("\\h To help\n");
	f = fopen(MP_LAST_FILE, "r");
	if (f)
	{
		while ((c = fgetc(f)) != EOF)
			m8s_concatcm(s, (char)c);
		fclose(f);
	}
	if (s->n)
		fname = strdup(s->s);
	else
		fname = NULL;
	do
	{
		err_n = MP_OK;
		printf("Get .egt file q=quite");
		if (fname)
			printf("[%s]", fname);
		get_simple_input(s, ">", 0);
		if (strcmp(s->s, "q") == 0)
			break;
		if (s->n)
		{

			t1 = clock();
			mp = new_mParserF(s->s, &err_n);
			t2 = clock();
			new_fname = 1;
		}
		else if (fname)
		{
			t1 = clock();
			mp = new_mParserF(fname, &err_n);
			t2 = clock();
			new_fname = 0;
		}
		if (err_n != MP_OK)
			print_err(err_n);
		if (mp)
			printf("Load File: %f secs\n", F_PAT_TYPE(t2 - t1) / CLOCKS_PER_SEC);
		else
			printf("Without a valid .egt file, the program cannot continue\n");

	} while (mp == NULL);
	if (new_fname && mp)
	{
		if (fname)
			free(fname);
		fname = strdup(s->s);
		save_last_file(fname);
	}
	if (mp)
		mainloop(&mp, s, &fname);

	if (fname)
		free(fname);
	destroy_m8String(s);
	if (mp)
		destroy_mParser(mp);
#ifdef DHASH_H_INCLUDED
	dend();
#endif

	return 0;
}
