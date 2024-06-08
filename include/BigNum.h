//The following is a BSD license template. To generate your own license, change the values of OWNER, ORGANIZATION and YEAR from their original values as given here, and substitute your own.
//
//Note: The advertising clause in the license appearing on BSD Unix files was officially rescinded by the Director of the Office of Technology Licensing of the University of California on July 22 1999. He states that clause 3 is "hereby deleted in its entirety."
//
//Note the new BSD license is thus equivalent to the MIT License, except for the no-endorsement final clause.
//  
//    <OWNER> = A6n6d6y6
//  
//    <ORGANIZATION> = None
//  
//    <YEAR> = 2024
//  
//    In the original BSD license, both occurrences of the phrase "COPYRIGHT HOLDERS AND CONTRIBUTORS" in the disclaimer read "REGENTS AND CONTRIBUTORS".
//  
//    Here is the license template:
//  
//    Copyright (c) 2024, A6n6d6y6
//  
//    All rights reserved.
//  
//    Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//  
//    Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//  
//    Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//  
//    Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//  
//    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/**
 * @File: FastIOS.h
 * @Language: C/C++
 * @Author: A6n6d6y6
 **/

#ifndef __BIGNUM_H__
#define __BIGNUM_H__
#include<iostream>
#include<algorithm>
#include<cmath>
#include<string>
#include<cstdio>
#include<vector>
#include<complex>
#include<cstring>
namespace BigNum{
	#ifndef BIGNUM_MAXL
		#define BIGNUM_MAXL 10010
	#endif
	struct BigNum{
		int len;
		unsigned short num[BIGNUM_MAXL];
		bool sign=0;
		
		struct FastFourierTransform{
			std::complex<double>aa[BIGNUM_MAXL],bb[BIGNUM_MAXL];
			int rev[BIGNUM_MAXL];
			void getrev(int n){
				for(int i=0,j=0;i<n;i++){
					rev[i]=j;
					for(int k=n>>1;(j^=k)<k;k>>=1);
				}
			}
			void fft(std::complex<double>a[],int n,int dft){
				for(int i=0;i<n;i++)if(i<rev[i])swap(a[i],a[rev[i]]);
				for(int st=1;st<n;st<<=1){
					std::complex<double>dwfg=exp(std::complex<double>(0,dft*3.1415926535/st));
					for(int i=0;i<n;i+=(st<<1)){
						std::complex<double>nfg=1;
						for(int j=i;j<i+st;j++){
							std::complex<double> x=a[j],y=a[j+st]*nfg;
							nfg*=dwfg;
							a[j]=x+y; a[j+st]=x-y;
						}
					}
				}
				if(dft==-1) for(int i=0;i<n;i++) a[i]/=n;
			}
		};
		
		BigNum(int x){
			memset(num,0,sizeof(num));
			if(x<0)sign=1,x=abs(x);
			for(len=1;x;len++)
				num[len]=x%10,x/=10;
			len--;
		}
		BigNum(long long x){
			memset(num,0,sizeof(num));
			if(x<0)sign=1,x=abs(x);
			for(len=1;x;len++)
				num[len]=x%10,x/=10;
			len--;
		}
		BigNum(std::string s){
			memset(num,0,sizeof(num));
			if(s[0]=='-')sign=1,s=s.substr(1,s.size()-1);
			else if(s[0]=='+')s=s.substr(1,s.size()-1);
			for(len=1;len<=(int)s.size();len++)
				num[s.size()-len+1]=s[len-1]-'0';
			len--;
			if(s[0]=='0')sign=0;
		}
		BigNum(){
			BigNum(0); 
		}
		
		unsigned short &operator[](int i){
			return num[i];
		}
		friend bool operator<(BigNum a,BigNum b){
			if(a.sign==1&&b.sign==0)return 1;
			if(a.sign==0&&b.sign==1)return 0;
			if(a.sign==0){
				if(a.len>b.len)return 0;
				else if(a.len<b.len)return 1;
				else for(int i=a.len;i>=1;i--){
					if(a[i]>b[i])return 0;
					if(a[i]<b[i])return 1;
				}
			}else{
				if(a.len>b.len)return 1;
				else if(a.len<b.len)return 0;
				else for(int i=a.len;i>=1;i--){
					if(a[i]>b[i])return 0;
					if(a[i]<b[i])return 0;
				}
			}
			return 0;
		}
		friend bool operator>(BigNum a,BigNum b){
			if(a.sign==1&&b.sign==0)return 0;
			if(a.sign==0&&b.sign==1)return 1;
			if(a.sign==0){
				if(a.len>b.len)return 1;
				else if(a.len<b.len)return 0;
				else for(int i=a.len;i>=1;i--){
					if(a[i]>b[i])return 1;
					if(a[i]<b[i])return 0;
				}
			}else{
				if(a.len>b.len)return 0;
				else if(a.len<b.len)return 1;
				else for(int i=a.len;i>=1;i--){
					if(a[i]>b[i])return 0;
					if(a[i]<b[i])return 1;
				}
			}
			return 0;
		}
		friend bool operator==(BigNum a,BigNum b){
			if(a.sign^b.sign)return 0;
			if(a.len>b.len)return 0;
			else if(a.len<b.len)return 0;
			else for(int i=a.len;i>=1;i--)if(a[i]!=b[i])return 0;
			return 1;
		}
		friend bool operator>=(BigNum a,BigNum b){
			return (a>b||a==b);
		}
		friend bool operator<=(BigNum a,BigNum b){
			return (a<b||a==b);
		}
		friend bool operator!=(BigNum a,BigNum b){
			return !(a==b);
		}
		
		void flatten(int l){
			len=l;
			for(int i=1;i<=len;i++){
				if(num[i]>=10)num[i+1]+=num[i]/10,num[i]%=10;
				while(num[i]<0)num[i+1]--,num[i]+=10;
			}
			for(;!num[len];)len--;
			if(len==0)sign=0;
		}
		friend BigNum abs(BigNum a){
			a.sign=0;
			return a;
		}
		
		friend std::istream&operator>>(std::istream&is,BigNum&c){
			std::string s;
			is>>s;
			c=BigNum(s);
			return is;
		}
		friend std::ostream&operator<<(std::ostream &os,const BigNum &t){
			if(t.sign==1)os<<'-';
			for(int i=std::max(t.len,1);i>=1;i--)
				os<<(int)(t.num[i]);
			return os;
		}
		
		#ifdef __FASTIOS_H__
			friend FastIOS::instream&operator>>(FastIOS::instream &is,BigNum &c){
				std::string s;
				is>>s;
				c=BigNum(s);
				return is;
			}
			friend FastIOS::outstream&operator<<(FastIOS::outstream &os,const BigNum &t){
				if(t.sign==1)os<<'-';
				for(int i=std::max(t.len,1);i>=1;i--)
					os<<(int)(t.num[i]);
				return os;
			}
		#endif
		
		friend BigNum operator-(BigNum a){
			a.sign=!a.sign;
			return a;
		}
		friend BigNum operator<<(BigNum a,int dest){
			BigNum b(0);
			b.sign=a.sign;
			for(int i=1;i<=a.len;i++)
				b[i+dest]=a[i];
			b.len=a.len+dest;
			return b;
		}
		friend BigNum operator>>(BigNum a,int dest){
			BigNum b(0);
			b.sign=a.sign;
			for(int i=2;i<=a.len;i++)
				if(i-dest>0)b[i-dest]=a[i];
			b.len=a.len-dest;
			return b;
		}
		
		friend BigNum operator+(BigNum a,BigNum b){
			BigNum c(0);
			if(a.sign==0&&b.sign==0){
				c.sign=0;
				int len=std::max(a.len,b.len);
				for(int i=1;i<=len;i++)
					c[i]+=a[i]+b[i];
				c.flatten(len+1);
			}
			else if(a.sign==1&&b.sign==1){
				c.sign=1;
				int len=std::max(a.len,b.len);
				for(int i=1;i<=len;i++)
					c[i]+=a[i]+b[i];
				c.flatten(len+1);
			}
			else{
				if(abs(a)>abs(b)){
					c.sign=a.sign;
					int len=std::max(a.len,b.len);
					for(int i=1;i<=len;i++)
						c[i]+=a[i]-b[i];
					c.flatten(len+1);
				}else{
					c.sign=b.sign;
					int len=std::max(a.len,b.len);
					for(int i=1;i<=len;i++)
						c[i]+=b[i]-a[i];
					c.flatten(len+1);
				}
			}
			if(c.len==-1)c.sign=0;
			return c;
		}
		friend BigNum operator-(BigNum a,BigNum b){
			return a+(-b);
		}
		friend BigNum operator*(BigNum a,BigNum b){
			FastFourierTransform FFT;
			BigNum c(0);
			int l1=a.len,l2=b.len;
			for(int i=1;i<=l1;i++)FFT.aa[i-1]=a[i];
			for(int i=1;i<=l2;i++)FFT.bb[i-1]=b[i];
			int s=2;
			for(;s<l1+l2-1;s<<=1);
			FFT.getrev(s);
			FFT.fft(FFT.aa,s,1);
			FFT.fft(FFT.bb,s,1);
			for(int i=0;i<s;i++)FFT.aa[i]*=FFT.bb[i];
			FFT.fft(FFT.aa,s,-1);
			for(int i=0;i<s;i++){
				c[i+1]+=(int)(FFT.aa[i].real()+0.5);
				c[i+2]+=c[i+1]/10;
				c[i+1]%=10;
			}
			c.sign=a.sign^b.sign;
			c.flatten(l1+l2);
			return c;
		}
		friend BigNum operator/(BigNum a,BigNum b) {
			std::vector<BigNum>sta,s;
			bool f=a.sign^b.sign;
			a=abs(a);b=abs(b);
			BigNum r=b,c=BigNum(1);
			while(r<=a){
				sta.push_back(r);
				s.push_back(c);
				r=r+r;c=c+c;
			}
			r=a;c=BigNum(0);
			int len=sta.size()-1;
			while(len>=BigNum(0)) {
				BigNum t=sta[len];
				if (t<=r)r=r-t,c=c+s[len];
				len--;
			}
			c.sign=f;
			c.flatten(a.len-b.len+1);
			return c;
		}
		friend BigNum operator%(BigNum a,BigNum b){
			BigNum d(0);
			bool f=a.sign;
			d=a-a/b*b;
			d.sign=a.sign;
			d.flatten(d.len);
			return d;
		}
		
		friend BigNum operator+=(BigNum &a,BigNum b){a=a+b;return a;}
		friend BigNum operator-=(BigNum &a,BigNum b){a=a-b;return a;}
		friend BigNum operator*=(BigNum &a,BigNum b){a=a*b;return a;}
		friend BigNum operator/=(BigNum &a,BigNum b){a=a/b;return a;}
		friend BigNum operator%=(BigNum &a,BigNum b){a=a%b;return a;}
		
		friend int to_int(BigNum a){
			int ans=0;
			for(int i=a.len;i>=1;i--)ans=ans*10+a[i];
			return ans;
		}
		friend long long to_long_long(BigNum a){
			long long ans=0;
			for(int i=a.len;i>=1;i--)ans=ans*10+a[i];
			return ans;
		}
	};
}
#endif
