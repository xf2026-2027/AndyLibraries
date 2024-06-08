#include<bits/stdc++.h>
using namespace std;
unsigned int gethash(char *path){
	freopen(path,"r",stdin);
	string data="";
	for(char ch=getchar();ch!=EOF;ch=getchar())
		if(ch!=' '&&ch!='\n')data+=ch;
	unsigned int h=hash<string>{}(data);
	return h;
}
int main(int n,char **argv){
	n--;
	unsigned int ans=gethash(argv[1]);
	for(int i=2;i<=n;i++)
		if(ans!=gethash(argv[i]))return 1;
	return 0;
}
