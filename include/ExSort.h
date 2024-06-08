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
 * @File: ExSort.h
 * @Language: C/C++
 * @Author: A6n6d6y6
 **/

#ifndef __EXSORT_H__
#define __EXSORT_H__
#include<unordered_map>
#include<algorithm>
#include<vector>
namespace ExSort{
#define SORT_ZASK 255		//((1<<8)-1)
#define SORT_DIGT 31		//((1<<5)-1)
#define SORT_RUN 32			//For TimSort
#define SORT_SHRINK (1.25);	//For CombSort
	template<typename T>void SelectSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg,k;
		for(int i=0,k=0;i<n-1;i++,k=i){
			for(int j=i+1;j<n;j++)
				if(a[j]<a[k])k=j;
			std::swap(a[i],a[k]);
		}
	}
	template<typename T>void BubbleSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		bool flag=0;do{
			flag=0;for(int i=0;i<n-1;i++)if(a[i+1]<a[i])
				std::swap(a[i],a[i+1]),flag=1;
		}while(flag);
	}
	template<typename T>void InsertSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		if(n<=1)return;
		for(int i=0;i<n;i++){
			int j=a[i],k=std::upper_bound(a,a+i,j)-a;
			memmove(a+k+1,a+k,(i-k)*sizeof(int));
			a[k]=j;
		}
	}
	template<typename T>void BucketSort(T *bg,T *ed){
		T *a=bg,w=a[0];int n=ed-bg,len,p;
		std::vector<T>*b=new std::vector<T>[n];
		for(int i=0;i<n;i++)w=(w<a[i]?a[i]:w);
		len=w/n+1,p=0;
		for(int i=0;i<n;i++)b[a[i]/len].push_back(a[i]);
		for(int i=0;i<n;i++){
			InsertSort(&*b[i].begin(),&*b[i].end());
			for(T j:b[i])a[p++]=j;
		}
	}
	template<typename T>void CountSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		static std::unordered_map<T,int>c;
		T maxx=a[0],minn=a[0];int tot=0;
		for(int i=0;i<n;i++){
			maxx=(maxx<a[i]?a[i]:maxx);
			minn=(minn<a[i]?minn:a[i]);
			c[a[i]]++;
		}
		for(T i=minn;i<=maxx;i++)
			if(c.count(i))for(int j=1;j<=c[i];j++)
				a[tot++]=i;
		c.clear();
	}
	template<typename T>void RadixSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		T *b=new T[n],*cnt=new T[SORT_ZASK+1];
		for(int i=0;i<=SORT_DIGT;i+=8){
			for(int j=0;j<=SORT_ZASK;j++)cnt[j]=0;
			for(int j=0;j<n;j++)++cnt[a[j]>>i&SORT_ZASK];
			for(int sum=0,j=0;j<=SORT_ZASK;j++)
				sum+=cnt[j],cnt[j]=sum-cnt[j];
			for(int j=0;j<n;j++)b[cnt[a[j]>>i&SORT_ZASK]++]=a[j];
			std::swap(a,b);
		}
		delete[] cnt,b;
	}
	template<typename T>void QuickSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		if(n<=1)return;
		int i=0,j=0,k=n;
		for(int p=a[rand()%n];i<k;){
			if(a[i]<p){std::swap(a[i++],a[j++]);continue;}
			if(p<a[i]){std::swap(a[i],a[--k]);continue;}
			i++;
		}
		QuickSort(a,a+j);
		QuickSort(a+k,a+n);
	}
	template<typename T>void MergeSort(T *a,int l,int r){
		if(r-l<=1)return;int mid=l+r>>1;
		MergeSort(a,l,mid);MergeSort(a,mid,r);
		T *tmp=new T[r-l+1];
		std::merge(a+l,a+mid,a+mid,a+r,tmp); 
		for(int i=0;i<r-l;i++)a[i+l]=tmp[i];
		delete[] tmp;
	}
	template<typename T>void MergeSort(T *bg,T *ed){MergeSort(bg,0,ed-bg);}
	template<typename T>void HeapSort(T *bg,T *ed){std::make_heap(bg,ed),std::sort_heap(bg,ed);}
	void ShellSort(int *bg,int *ed){
		int *a=bg,n=ed-bg;
		int h=1;while(h<n/3)h=3*h+1;
		for(;h>=1;h=h/3)
			for(int i=h;i<n;i++)
				for(int j=i;j>=h&&a[j]<a[j-h];j-=h)
					std::swap(a[j],a[j-h]);
	}
	template<typename T>int winner(int x,int y,T tmp[],int n){
		int u=x>=n?x:tmp[x],v=y>=n?y:tmp[y];
		if(tmp[u]<tmp[v])return u;
		else return v;
	}
	template<typename T>void ContestSort(T *bg,T *ed){
		int n=ed-bg;T *a=bg,*tmp=new int[n*2],value;
		for(int i=0;i<n;i++)tmp[n+i]=a[i];
		for(int i=2*n-1;i>1;i-=2)
			tmp[i/2]=winner(i,i-1,tmp,n);
		value=tmp[tmp[1]];
		tmp[tmp[1]]=INT_MAX;
		for(int i=0,j,k,son;i<n;i++){
			a[i]=value;
			for(j=tmp[1];j>1;j=son){
				son=j/2;
				if(!(j%2)&&j<=2*n)k=j+1;
				else k=j-1;
				tmp[son]=winner(j,k,tmp,n);
			}
			value=tmp[tmp[1]];
			tmp[tmp[1]]=INT_MAX;
		}
		delete[] tmp;
	}  
	template<typename T>void TimSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		for(int i=0;i<n;i+=SORT_RUN)
			InsertSort(a+i,a+std::min(i+SORT_RUN,n));
		for (int size=SORT_RUN;size<n;size=2*size){
			for (int l=0,mid=0,r=0;l<n;l+=2*size){
				mid=l+size-1,r=std::min(l+2*size,n)-1;
				if(mid<r)std::merge(a+l,a+mid,a+mid+1,a+r,a);  
			}
		}
	}
	template<typename T>void CocktailSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		bool flag=0;do{
			for(int i=0;i<n-1;i++)
				if(a[i+1]<a[i])std::swap(a[i],a[i+1]),flag=1;
			flag=0;
			for(int i=n-1;i>=1;i--)
				if(a[i]<a[i-1])std::swap(a[i],a[i-1]),flag=1;
		}while(flag);
	}
	template<typename T>void GnomeSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		for(int i=0;i<n;){
			if(i==0||a[i-1]<a[i]){i++;continue;}
			std::swap(a[i],a[i-1]);i--;
		}
	}
	template<typename T>void CombSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		int i,d=n,gap=0;
		while(!gap){
			for(gap=1,i=0;i+d<n;i++)
				if(a[i]>a[i+d])
					std::swap(a[i],a[i+d]),gap=0;
			if(d>1){d/=SORT_SHRINK;gap=0;}
		}
	}
	template<typename T>void StoogeSort(T a[],int l,int r){
		if(a[l]>a[r])std::swap(a[l],a[r]);
		if(l+1>=r)return;
		int split=(r-l+1)/3;
		StoogeSort(a,l,r-split);
		StoogeSort(a,l+split,r);
		StoogeSort(a,l,r-split);
	}
	template<typename T>void StoogeSort(T *bg,T *ed){StoogeSort(bg,0,ed-bg-1);}
	template<typename T>void BogoSort(T *bg,T *ed){
		T *a=bg;int n=ed-bg;
		while(true){
			bool f=1;
			for(int i=0;i<n;i++)
				if(a[i]<a[i-1]){f=0;break;}
			if(f)break;
			std::random_shuffle(a,a+n);
		}
	}
}
#endif
