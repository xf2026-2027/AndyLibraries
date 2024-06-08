#include<bits/stdc++.h>
using namespace std;
bool is_double(string s){
	try{double x=stod(s);}
	catch(const exception&){return false;}
	return true;
}
string round(double n,int p){
    stringstream s;
    s<<fixed<<setprecision(p)<<n;
    return s.str();
}
unsigned int gethash(char *path){
	freopen(path,"r",stdin);
	string data="";double tmp;
	cin>>tmp;do{
		data+=round(tmp,6);
	}while(cin>>tmp);
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
