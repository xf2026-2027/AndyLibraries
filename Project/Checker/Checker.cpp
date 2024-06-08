#include<bits/stdc++.h>
#include<windows.h>
using namespace std;
const int MAXC=64;//max codes num
const int MAXT=10;//max tests num
const string GCCPATH="g++";//compiler path 
const string PARAMAT="-O2 -std=c++14 -pipe -Wl,--stack=268435456";//paramat lists
string codes[MAXC],maker,judger;
auto system(string s){return system(s.c_str());}
auto puts(string s){return puts(s.c_str());}
int main(int n,char **argv){
	if(n>=MAXC){puts("There are too much codes to judge.");return 1;}
	n-=3;
	for(int i=1;i<=n;i++)codes[i]=argv[i];
	maker=argv[n+1];judger=argv[n+2];
	puts("Initing...");
	system("rmdir /s /q .\\answers\\ .\\tests\\");
	system("mkdir .\\answers\\ .\\tests\\");
	for(int i=1;i<=n;i++)
		system(("mkdir .\\answers\\"+codes[i]));
	puts("\nCompiling...");
	for(int i=1;i<=n;i++){
		if(system((GCCPATH+" \""+codes[i]+".cpp\" -o \""+codes[i]+".exe\" "+PARAMAT))){
			puts("Compile error on "+codes[i]+".cpp!");
			return 2;
		}
		puts("Compile success on "+codes[i]+".cpp.");
	}
	puts("\nMaking data...");
	for(int t=1;t<=MAXT;t++){
		string in="test"+to_string(t)+".in";
		system(("\""+maker+"\".exe > tests\\"+in));
	}
	puts("\nJudging...");
	for(int t=1;t<=MAXT;t++){
		string in="test"+to_string(t);
		string ncmp="";
		for(int i=1;i<=n;i++){
			system((codes[i]+".exe < tests\\"+in+".in > answers\\"+codes[i]+"\\"+in+".out"));
			ncmp+=" answers\\"+codes[i]+"\\"+in+".out";
		}
		if(system(judger+".exe "+ncmp))puts("Don\'t Pass the "+in+"!");
		else puts("Pass the "+in+".");
	}
	return 0;
}
