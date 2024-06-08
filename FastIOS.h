//The following is a BSD license template. To generate your own license, change the values of OWNER, ORGANIZATION and YEAR from their original values as given here, and substitute your own.
//
//Note: The advertising clause in the license appearing on BSD Unix files was officially rescinded by the Director of the Office of Technology Licensing of the University of California on July 22 1999. He states that clause 3 is "hereby deleted in its entirety."
//
//Note the new BSD license is thus equivalent to the MIT License, except for the no-endorsement final clause.
//
//	<OWNER> = A6n6d6y6
//
//	<ORGANIZATION> = None
//
//	<YEAR> = 2024
//
//	In the original BSD license, both occurrences of the phrase "COPYRIGHT HOLDERS AND CONTRIBUTORS" in the disclaimer read "REGENTS AND CONTRIBUTORS".
//
//	Here is the license template:
//
//	Copyright (c) 2024, A6n6d6y6
//
//	All rights reserved.
//
//	Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//
//	Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
//
//	Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
//
//	Neither the name of the <ORGANIZATION> nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
//	THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

/**
 * @File: FastIOS.h
 * @Language: C++
 * @Author: A6n6d6y6
 **/

#ifndef __FASTIOS_H__
#define __FASTIOS_H__
#include<iostream>
#include<cstdio>
#ifndef IOS_BUFSIZE
	#define IOS_BUFSIZE (1<<20)
#endif
namespace FastIOS{
	bool blank(char ch){
		return ch==' '||ch=='\n'||ch=='\r'||ch=='\t';
	}
	class instream{
	protected:
		bool iseof=false;
		virtual char getchar(){
			return EOF;
		}
	public:
		operator bool(){
			return!iseof;
		}
		template<class T>void read(T&x){
			double tmp=1;
			bool sign=0;
			x=0;
			char ch=getchar();
			if(ch==EOF||iseof){
				iseof=true;
				return;
			}
			for(;!isdigit(ch);ch=getchar())if(ch=='-')sign=1;
			for(;isdigit(ch);ch=getchar())x=x*10+(ch-'0');
			if(ch=='.')for(ch=getchar();isdigit(ch);ch=getchar())tmp/=10.0,x+=tmp*(ch-'0');
			if(sign)x=-x;
		}
		void read(char*s){
			char ch=getchar();
			if(ch==EOF||iseof){
				iseof=true;
				return;
			}
			for(;blank(ch);ch=getchar());
			for(;!blank(ch);ch=getchar())*s++=ch;
			*s=0;
		}
		void read(std::string &s){
			char ch=getchar();
			if(ch==EOF||iseof){
				iseof=true;
				return;
			}
			for(;blank(ch);ch=getchar());s="";
			for(;!blank(ch);ch=getchar())s.push_back(ch);
		}
		void read(char&c){
			c=getchar();
			if(c==EOF||iseof){
				iseof=true;
				return;
			}
			for(c=getchar();blank(c);c=getchar());
		}
		template<class T>friend instream&operator>>(instream&ins,T&in){
			ins.read(in);
			return ins;
		}
	};
	class fastinstream:public instream{
	protected:
		std::streambuf*cinbuf=std::cin.rdbuf();
		char inbuf[IOS_BUFSIZE],*p1,*p2;
		char getchar(){
			if(p1==p2&&(p2=(p1=inbuf)+cinbuf->sgetn(inbuf,IOS_BUFSIZE),p1==p2))return EOF;
			return*p1++;
		} public:
		void flush(){
			fflush(stdin);
		}
		fastinstream():p1(inbuf),p2(inbuf){}
	}qinf;
	class stdinstream:public instream{
	protected:
		char inbuf[IOS_BUFSIZE],*p1,*p2;
		char getchar(){
			if(p1==p2)p2=(p1=inbuf)+fread(inbuf,1,IOS_BUFSIZE,stdin);
			return p1==p2?EOF:*p1++;
		}
	public:
		void flush(){
			fflush(stdin);
		} stdinstream():p1(inbuf),p2(inbuf){}
	}qinn;
	class errinstream:public instream{
	protected:
		char getchar(){
			return std::getchar();
		}
	}qins;
	struct ENDL{}Endl;
	struct ENDS{}Ends;
	struct FLUSH{}Flush;
	class outstream{
	protected:
		virtual void putchar(const char&c){}
	public:
		virtual void flush(){} template<class T>void write(T x){
			if(x<0)x=-x,putchar('-');
			__uint128_t Z=x;
			long double R=x-Z;
			static int sta[35],top=0;
			do{
				sta[top++]=Z%10,Z/=10;
			} while(Z);
			while(top)putchar(sta[--top]+'0');
			if(R==0)return;
			putchar('.');
			R+=5e-11;
			for(int i=1;i<=10;i++){
				R*=10;
				putchar(int(R)+'0');
				R-=int(R);
			}
		}
		void write(char*s){
			for(int i=0;s[i];i++)putchar(s[i]);
		}
		void write(const char*s){
			for(int i=0;s[i];i++)putchar(s[i]);
		}
		void write(std::string s){
			for(int i=0;i<(int)s.size();i++)putchar(s[i]);
		}
		void write(char c){
			putchar(c);
		}
		void write(ENDL a){
			putchar('\n');
			flush();
		}
		void write(ENDS a){
			putchar(' ');
			flush();
		}
		void write(FLUSH a){
			flush();
		}
		template<class T>friend outstream&operator<<(outstream&outs,T out){
			outs.write(out);
			return outs;
		}
	};
	class fastoutstream:public outstream{
	protected:
		std::streambuf*coutbuf=std::cout.rdbuf();
		void putchar(const char&c){
			coutbuf->sputc(c);
		}
	public:
		void flush(){
			fflush(stdin);
		}
	}qoutf;
	class stdoutstream:public outstream{
	protected:
		char outbuf[IOS_BUFSIZE],*op;
		void putchar(const char&c){
			if(op-outbuf==IOS_BUFSIZE)flush();
			*op++=c;
		}
	public:
		void flush(){
			fwrite(outbuf,1,op-outbuf,stdout);
			op=outbuf;
		}
		stdoutstream():op(outbuf){}~stdoutstream(){
			flush();
		}
	}qoutn;
	class erroutstream:public outstream{
	protected:
		void putchar(const char&c){
			std::putchar(c);
		}
	public:
		void flush(){
			fflush(stdout);
		}
		~erroutstream(){
			fflush(stdout);
		}
	}qouts;
#if defined(LOCAL)
	auto &qin=qins;
	auto &qout=qouts;
#elif defined(NORMAL)
	auto &qin=qinn;
	auto &qout=qoutn;
#else
	auto &qin=qinf;
	auto &qout=qoutf;
#endif
};
#endif
