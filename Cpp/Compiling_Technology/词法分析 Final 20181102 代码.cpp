#include<iostream>
#include<stdio.h>
#include<set>
#include<map>
#include<vector>
#pragma warning(disable:4996)

using namespace std;

struct node_string {
	string value;
	int index;
};

vector <node_string> constant_string;

struct node_integer {
	int value;
	int index;
};

vector <node_integer> constant_integer;

int constant_size=0;

set <char> char_set,digit_set;
map <string,int> reserved_table_set;
map <string,int> sym_map;

#define T_SYMBOL 1
#define T_CONSTANT 2
#define T_INT 3
#define T_IF 4
#define T_ELSE 5
#define T_WHILE 6
#define T_FOR 7
#define T_READ 8
#define T_WRITE 9
#define T_ADD 10
#define T_SUB 11
#define T_MUL 12
#define T_DIV 13
#define T_L 14
#define T_LE 15
#define T_G 16
#define T_GE 17
#define T_NE 18
#define T_E 19
#define T_ASSIGN 20
#define T_LPAR 21
#define T_RPAR 22
#define T_COM 23
#define T_SEM 24
#define T_ERROR 666
#define NEXTLINE 2333
#define T_END 0
#define T_MOD 342
#define T_LOGIC_AND 30
#define T_LOGIC_OR 31
#define T_BIT_AND 32
#define T_BIT_OR 33
#define T_ADD_ONE 110
#define T_SUB_ONE 111
#define T_LOGIC_NOT 2332
#define T_Escape_character 2322
#define T_SPACE 3444

enum Token;

int line=1;

void create_reserved_table() {
	reserved_table_set["int"]=3;
	reserved_table_set["if"]=4;
	reserved_table_set["else"]=5;
	reserved_table_set["printf"]=9;
	reserved_table_set["scanf"]=8;
	reserved_table_set["for"]=7;
	reserved_table_set["while"]=6;
	reserved_table_set["include"]=101;
	reserved_table_set["return"]=102;
}

void InitScanner() {
	create_reserved_table();
	for (char i='a';i<='z';i++) {
		char_set.insert(i);
	}
	for (char i='A';i<='Z';i++) {
		char_set.insert(i);
	}
	char_set.insert('_');
	//char_set.insert('.');
	for (char i='0';i<='9';i++) {
		digit_set.insert(i);
	}
}

int sym_size=0,ERROR_EXIST=0;
void new_sym(string token) {
	sym_size++;
	sym_map[token]=sym_size;
}

int ScanOneToken(FILE *fp,FILE *pr) {
	string token;
	char ch=fgetc(fp);
	while (ch==' '||ch=='\t') {
		fprintf(pr,"line %.2d: Space\n",line);
		ch=fgetc(fp);
	}
	if (char_set.find(ch)!=char_set.end()) {
		token="";
		token.append(string(1,ch));
		while (true) {
			ch=fgetc(fp);
			if (char_set.find(ch)==char_set.end()) {
				ungetc(ch,fp);
				break;
			}
			token.append(string(1,ch));
		}
		if (reserved_table_set.find(token)!=reserved_table_set.end()) {
			fprintf(pr,"line %.2d: Reserved Word Code=%d\n",line,reserved_table_set[token]);
			return 999;
		}
		if (sym_map.find(token)==sym_map.end()) {
			new_sym(token);
		}
		fprintf(pr,"line %.2d: Symbol Code=%d\n",line,sym_map[token]);
		return 1;
	}
	else if (digit_set.find(ch)!=digit_set.end()) {
		int constant=ch-'0';
		while (true) {
			ch=fgetc(fp);
			if (digit_set.find(ch)==digit_set.end()) {
				if (char_set.find(ch)!=char_set.end()) {
					while (char_set.find(ch)!=char_set.end())
						ch=fgetc(fp);
					ungetc(ch,fp);
					return T_ERROR;
				}
				else {
					ungetc(ch,fp);
					constant_size++;
					constant_integer.push_back(node_integer{constant,constant_size});
					fprintf(pr,"line %.2d: Constant IntegerOrFloat Value=%d\n",line,constant);
					return 2;
				}
			}
			else {
				constant=constant*10+ch-'0';
			}
		}
	}
	else {
		switch (ch) {
		case '+':			
			ch=getc(fp);
			if (ch=='+')
				return T_ADD_ONE;
			else {
				ungetc(ch,fp);
				return T_ADD;
			}
		case '-':			
			ch=getc(fp);
			if (ch=='=')
				return T_SUB_ONE;
			else {
				ungetc(ch,fp);
				return T_SUB;
			}
		case '*':return T_MUL;
		case '/':return T_DIV;
		case '%':return 342;
		case '<':
			ch=getc(fp);
			if (ch=='=')
				return 15;
			else {
				ungetc(ch,fp);
				return 14;
			}
		case '>':
			ch=getc(fp);
			if (ch=='=')
				return 17;
			else {
				ungetc(ch,fp);
				return 16;
			}
		case '=':
			ch=getc(fp);
			if (ch=='=')
				return 19;
			else {
				ungetc(ch,fp);
				return 20;
			}
		case '!':
			ch=getc(fp);
			if (ch=='=')
				return 18;
			else {
				ungetc(ch,fp);
				return T_LOGIC_NOT;
			}
		case '(':return 21;
		case ')':return 22;
		case ',':return 23;
		case ';':return 24;
		case '#':return 1010;
		case '\n':line++;
			fprintf(pr,"line %.2d: NewLine Num=%.2d\n",line-1,line);
			fprintf(pr,"\n");return 2333;
		case EOF:return T_END;
		case '\"':
			fprintf(pr,"line %.2d: Double Quotation Marks\n",line);
			return 1;
		case '\'':			
			fprintf(pr,"line %.2d: Single Quotation Marks\n",line);
			return 1;
		case '.':
			fprintf(pr,"line %.2d: Dot\n",line);
			return 1;
		case '{':
			fprintf(pr,"line %.2d: Open Brace\n",line);
			return 1;
		case '}':
			fprintf(pr,"line %.2d: Close Brace\n",line);
			return 1;
		case '&':
			ch=fgetc(fp);
			if (ch=='&') {
				return T_LOGIC_AND;
			}
			ungetc(ch,fp);
			return T_BIT_AND;
		case '|':
			ch=fgetc(fp);
			if (ch=='|') {
				return T_LOGIC_OR;
			}
			ungetc(ch,fp);
			return T_BIT_OR;
		case '\\':
			return T_Escape_character;
		default:return T_ERROR;
		}
	}
}

void Output(FILE *pr) {
	fprintf(pr,"Symbol_Table_Set");
	fprintf(pr,"\n  Code=	      Value=");
	for (map<string,int>::iterator it=sym_map.begin();it!=sym_map.end();it++) {
		fprintf(pr,"\n%5d                  %s",it->second,(it->first).c_str());
	}
	fprintf(pr,"\n\n\n\nReserved_Table_Set");
	fprintf(pr,"\n  Code=	      Value=");
	for (map<string,int>::iterator it=reserved_table_set.begin();it!=reserved_table_set.end();it++) {
		fprintf(pr,"\n%5d                  %s",it->second,(it->first).c_str());
	}
	fprintf(pr,"\n\n\n\nConstant_Integer_Table_Set");
	fprintf(pr,"\n  Code=	      Value=");
	for (vector<node_integer>::iterator it=constant_integer.begin();it!=constant_integer.end();it++) {
		fprintf(pr,"\n%5d                  %d",it->index,(it->value));
	}
	fprintf(pr,"\n\n\n\nConstant_StringOrChar*OrChar_Table_Set");
	fprintf(pr,"\n  Code=	      Value=");
	for (vector<node_string>::iterator it=constant_string.begin();it!=constant_string.end();it++) {
		fprintf(pr,"\n%5d                  %s",it->index,(it->value).c_str());
	}
}

int main()
{
	char argv[20];
	scanf("%s",argv);
	char prt[20]="lex.txt";
	InitScanner();
	FILE *p=fopen(argv,"r");
	FILE *pr=fopen(prt,"w");
	FILE *prsymtable=fopen("symtable.txt","w");
	FILE *prerror=fopen("error.txt","w");
	fprintf(pr,"彭子为-201722110202\n\n");
	int now=0;
	while (now=ScanOneToken(p,pr)) {
		if (now==1010) {
			fprintf(pr,"line %.2d: Preprocessor\n",line);
		}
		else if (now==1||now==2||now==999||now==2333) {
			//已经处理或不需要处理的情况
			continue;
		} else{
			switch (now) {
			case T_LPAR:
				fprintf(pr,"line %.2d: Open Parenthesis\n",line);
				break;
			case T_RPAR:
				fprintf(pr,"line %.2d: Close Parenthesis\n",line);
				break;
			case T_ADD:
				fprintf(pr,"line %.2d: Operator +\n",line);
				break;
			case T_ADD_ONE:
				fprintf(pr,"line %.2d: Operator Self_Add ++\n",line);
				break;
			case T_SUB:
				fprintf(pr,"line %.2d: Operator -\n",line);
				break;
			case T_SUB_ONE:
				fprintf(pr,"line %.2d: Operator Self_Sub --\n",line);
				break;
			case T_MUL:
				fprintf(pr,"line %.2d: Operator *\n",line);
				break;
			case T_DIV:
				fprintf(pr,"line %.2d: Operator /\n",line);
				break;
			case T_L:
				fprintf(pr,"line %.2d: Operator <\n",line);
				break;
			case T_LE:
				fprintf(pr,"line %.2d: Operator <=\n",line);
				break;
			case T_MOD:
				fprintf(pr,"line %.2d: Operator MOD\n",line);
				break;
			case T_G:
				fprintf(pr,"line %.2d: Operator >\n",line);
				break;
			case T_GE:
				fprintf(pr,"line %.2d: Operator >=\n",line);
				break;
			case T_NE:
				fprintf(pr,"line %.2d: Operator !=\n",line);
				break;
			case T_E:
				fprintf(pr,"line %.2d: Operator ==\n",line);
				break;
			case T_ASSIGN:
				fprintf(pr,"line %.2d: Operator =\n",line);
				break;
			case T_COM:
				fprintf(pr,"line %.2d: Operator Comma\n",line);
				break;
			case T_SEM:
				fprintf(pr,"line %.2d: Operator Semicolon\n",line);
				break;
			case T_ERROR:
				fprintf(pr,"line %.2d: Invalid Statement\n",line);
				fprintf(prerror,"line %.2d: Invalid Statement\n",line);
				ERROR_EXIST=1;
				break;
			case T_LOGIC_AND:
				fprintf(pr,"line %.2d: Operator && LOGIC_AND\n",line);
				break;
			case T_LOGIC_OR:
				fprintf(pr,"line %.2d: Operator && LOGIC_OR\n",line);
				break;
			case T_BIT_OR:
				fprintf(pr,"line %.2d: Operator & BIT_OR\n",line);
				break;
			case T_BIT_AND:
				fprintf(pr,"line %.2d: Operator & BIT_AND\n",line);
				break;
			case T_LOGIC_NOT:
				fprintf(pr,"line %.2d: Operator & LOGIC_NOT\n",line);
				break;
			case T_Escape_character:
				fprintf(pr,"line %.2d: Escape Character \\\n",line);
				break;
			default:fprintf(pr,"line %.2d: %d\n",line,now);break;
			}
		}
	}
	Output(prsymtable);
	if (!ERROR_EXIST)
		fprintf(prerror,"No Errors!!!\n");
	return 0;
}

