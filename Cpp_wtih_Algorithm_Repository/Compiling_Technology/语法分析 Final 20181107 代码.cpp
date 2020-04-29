//copyright@pzw 20181107

#include <iostream>
#include <string>
#include <set>

#pragma warning(disable:4996)

using namespace std;

/*

	Ö¼ØæÇßäß

	Expr->Expr+Term|Term|Expr-Term
	Term->Term*Factor|Factor|Term/Factor
	Factor->(Expr)|i
----------------------------------------------
	Expr->TermExpr'
	Expr'->+TermExpr'|-TermExpr'|e
	Term->FactorTerm'
	Term'->*FactorTerm'|/FactorTerm'|e
	Factor->(Expr)|i

*/

void advance();
void Init();
void error();
void Term1();
void Expr1();
void Factor();
void Term();
void Expr();

set <char> digit_set;
set <char> char_set;
set <string> symbol_set;

void Init() {
	for (int i='0';i<='9';i++) {
		digit_set.insert(i);
	}
	for (int i='a';i<='z';i++) {
		char_set.insert(i);
	}
	char_set.insert('_');
}

string Grammar[6][3]={
	"Expr->TermExpr'","","",
	"Expr'->+TermExpr'","Expr'->-TermExpr'","Expr'->e",
	"Term->FactorTerm'","","",
	"Term'->*FactorTerm'","Term'->/FactorTerm'","Term'->e",
	"Factor->(Expr)","Factor->i","",
	"i->Constant","i->Symbol",""
};
char sym;
int flag=0;
char s[1000];
FILE *fp=fopen("source3.txt","r");
FILE *fpr=fopen("detail.txt","w");
FILE *fperror=fopen("error.txt","w");

void printdetail(int x,int y) {
	for (int i=1;i<=30;i++) {
		fprintf(fpr,"-");
	}
	fprintf(fpr,"\n");
	fprintf(fpr,"ËðÆîÎû?ÆíÈ¢¡¨%s\n",Grammar[x][y].c_str());
	fprintf(fpr,"ÄØÅ¡ÎµÎûÈë¡¨");
	for (int i=0;i<flag;i++) {
		fprintf(fpr,"%c",s[i]);
	}
	fprintf(fpr,"\n?Ð©ÇóÜÊ:%c\n",s[flag]);
	fprintf(fpr,"Þ·É§Èë¡¨");
	for (int i=flag;i<strlen(s);i++) {
		fprintf(fpr,"%c",s[i]);
	}
	fprintf(fpr,"\n");
	for (int i=1;i<=30;i++) {
		fprintf(fpr,"-");
	}
	fprintf(fpr,"\n");
}

void advance() {
	flag++;
	string token="";
	if (flag>=strlen(s))
		return;
	if (digit_set.find(s[flag-1])!=digit_set.end()) {
		token.append(string(1,s[flag-1]));
		while (flag<strlen(s)&&digit_set.find(s[flag])!=digit_set.end()) {
			token.append(string(1,s[flag]));
			flag++;
		}
		flag--;
		printdetail(5,0);
	}
	else if (char_set.find(s[flag-1])!=char_set.end()) {
		token.append(string(1,s[flag-1]));
		while (flag<strlen(s)&&char_set.find(s[flag])!=char_set.end()) {
			token.append(string(1,s[flag]));
			flag++;
		}
		flag--;
		printdetail(5,1);
	}
	flag++;
	sym=s[flag];
}

void error() {
	for (int i=1;i<=30;i++) {
		fprintf(fpr,"-");
	}
	fprintf(fpr,"\n");
	fprintf(fpr,"Unaccepted:Match Fail on %dth Letter.",flag);
	fprintf(fperror,"Unaccepted:Match Fail on %dth Letter.",flag);
	exit(0);
	return;
}

void Term1() {
	if (sym=='*'||sym=='/') {
		printdetail(3,(sym-42)/4);
		flag++;
		sym=s[flag];
		Factor();
		Term1();
	}
	else {
		printdetail(3,2);
	}
}

void Expr1() {
	if (sym=='+'||sym=='-') {
		printdetail(1,(sym-43)/2);
		flag++;
		sym=s[flag];
		Term();
		Expr1();
	}
	else {
		printdetail(1,2);
	}
}

void Factor() {
	if (s[flag]=='(') {
		flag++;
		printdetail(4,0);
		Expr();
		if (s[flag]==')') {
			flag++;
			sym=s[flag];
		}
		else error();
	}
	else if ((digit_set.find(s[flag])!=digit_set.end()||char_set.find(s[flag])!=char_set.end())){
		printdetail(4,1);
		advance();
	}
	else error();
}

void Term() {
	printdetail(2,0);
	Factor();
	Term1();
}

void Expr() {
	printdetail(0,0);
	Term();
	Expr1();
}

int main(){
	Init();
	//fscanf(fp,"%s",s);
	fgets(s,1000,fp);
	for (int i=0;i<strlen(s);i++) {
		if (s[i]==' ') {
			for (int j=i;j<=strlen(s)-1;j++) {
				s[j]=s[j+1];
			}
		}
	}
	//InitSymbol();
	sym=s[0];
	Expr();
	if (flag<strlen(s))
		error();
}
