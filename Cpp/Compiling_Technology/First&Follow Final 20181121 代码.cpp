#include<iostream>
#include<string>
#include<vector>
#include<set>

using namespace std;

const int maxn=201;
int n=0;
struct Production_Representation {
	string value;
	char left;
	string right;
}s[maxn];

set<char> terminal,not_terminal;
set<char> first[200],follow[200];

inline bool isterminal(char x){
	if (x >= 'A'&& x <= 'Z')	return false;
	return true;
}

inline void Init() {
	terminal.clear();
	not_terminal.clear();
}

void read() {
ReInput:
	printf("Please Enter n(Interger between 1 and %d):",maxn-1);
	try { 
		cin>>n;
		if (n<1||n>=maxn)
			throw(n);
	}
	catch(int){
		cout<<"Error:Illegal Input n"<<endl;
		Init();
		goto ReInput;
	}
	printf("Please Enter n Production Representations (A->abc in which ~ means empty):\n");
	for (int i=1;i<=n;i++) {
		cin>>s[i].value;
		if (s[i].value.find("->")==-1) {
			Init();
			goto ReInput;
		}
		else {
			s[i].left=s[i].value[0];
			s[i].right=s[i].value.substr(s[i].value.find("->")+2,s[i].value.length()-s[i].value.find("->")-2);
			//即(0,1)和(3,l-3)此写法可在文法符号不为单字符使用
		}
		not_terminal.insert(s[i].left);
		for (int j=0;j<s[i].right.length();j++) {
			if (isterminal(s[i].right[j])) {
				terminal.insert(s[i].right[j]);
				first[s[i].right[j]].insert(s[i].right[j]);
			}
			else {
				not_terminal.insert(s[i].right[j]);
			}
		}
	}
	cout<<n<<" Production Representations:"<<endl;
	for (int i=1;i<=n;i++) {
		printf("%3d%30c%30s\n",i,s[i].left,s[i].right.c_str());
	}
}

void compute_first() {
	printf("\nCompting First:\n");
	bool flag=true;
	while (flag) {
		flag=false;
		for (int i=1;i<=n;i++) {
			printf("This is the %dth product\n",i);
			for (int j=0;j<s[i].right.length();j++) {
				printf("Current character is %c\n",s[i].right[j]);
				if (isterminal(s[i].right[j])) {
					if (first[s[i].left].find(s[i].right[j])==first[s[i].left].end()) {
						flag=true;
						first[s[i].left].insert(s[i].right[j]);
						printf("Add %c into FIRST(%c)\n",s[i].right[j],s[i].left);
					}
					break;
				}
				else {
					for (set<char>::iterator it=first[s[i].right[j]].begin();it!=first[s[i].right[j]].end();it++) {
						if (*it!='~'&&first[s[i].left].find(*it)==first[s[i].left].end()) {
							flag=true;
							first[s[i].left].insert(*it);
							printf("Add %c into FIRST(%c)\n",*it,s[i].left);
						}
					}
					if (first[s[i].right[j]].find('~')==first[s[i].right[j]].end()) {
						break;
					}
				}
				if (j==s[i].right.length()-1) {
					if (first[s[i].left].find('~')==first[s[i].left].end()) {
						first[s[i].left].insert('~');
						printf("Add %c into FIRST(%c)\n",'~',s[i].left);
						flag=true;
					}
				}
			}
		}
	}
}

void compute_follow() {
	printf("\nCompting Follow:\n");
	//Rule 1
	follow[s[1].left].insert('#');
	bool flag=true,r=false;
	while (flag) {
		flag=false;
		for (int i=1;i<=n;i++) {
			printf("This is the %dth product\n",i);
			//Rule 3
			if (!isterminal(s[i].right[s[i].right.length()-1])) {
				for (set<char>::iterator it=follow[s[i].left].begin();it!=follow[s[i].left].end();it++) {
					if (follow[s[i].right[s[i].right.length()-1]].find(*it)==follow[s[i].right[s[i].right.length()-1]].end()) {
						flag=true;
						follow[s[i].right[s[i].right.length()-1]].insert(*it);
						printf("Add %c into Follow(%c)\n",*it,s[i].right[s[i].right.length()-1]);
					}
				}
			}
			//Rule 2
			for (int j=0;j<s[i].right.length()-1;j++) {
				if (!isterminal(s[i].right[j])) {
					int initj=j;
				repeatloop:
					r=false;
					for (set<char>::iterator it=first[s[i].right[j+1]].begin();it!=first[s[i].right[j+1]].end();it++) {
						if (*it!='~'&&follow[s[i].right[initj]].find(*it)==follow[s[i].right[initj]].end()) {
							flag=true;
							follow[s[i].right[initj]].insert(*it);
							printf("Add %c into Follow(%c)\n",*it,s[i].right[initj]);
						}else if (*it=='~')
							r=true;
					}
					if (r&&j<s[i].right.length()-1) {
						j+=1;
						goto repeatloop;
					}
					else
						j=initj;
				}
			}
			for (int j=s[i].right.length()-1;j>0;j--) {
				if (isterminal(s[i].right[j])||isterminal(s[i].right[j-1]))
					break;
				if (first[s[i].right[j]].find('~')!=first[s[i].right[j]].end()) {
					for (set<char>::iterator it=follow[s[i].left].begin();it!=follow[s[i].left].end();it++) {
						if (follow[s[i].right[j-1]].find(*it)==follow[s[i].right[j-1]].end()) {
							flag=true;
							follow[s[i].right[j-1]].insert(*it);
							printf("Add %c into Follow(%c)\n",*it,s[i].right[j-1]);
						}
					}
				}
				else
					break;
			}
		}
	}
}

#define t *p
void print_first() {
	puts("\n");
	for (set<char>::iterator p=not_terminal.begin();p!=not_terminal.end();p++) {
		printf("%s(%c):	","FIRST",t);
		for (set<char>::iterator it=first[t].begin();it!=first[t].end();it++) {
			printf("%c	",*it);
		}
		printf("\n");
	}
}

void print_follow() {
	puts("\n");
	for (set<char>::iterator p=not_terminal.begin();p!=not_terminal.end();p++) {
		printf("%s(%c):	","Follow",t);
		for (set<char>::iterator it=follow[t].begin();it!=follow[t].end();it++) {
			printf("%c	",*it);
		}
		printf("\n");
	}
}

int main() {
	read();
	compute_first();
	print_first();
	compute_follow();
	print_follow();
	return 0;
}