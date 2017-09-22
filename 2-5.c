#include <stdio.h>
#include <math.h> 
#include <string.h> 
#define  HEX  16 
#define  BIN  2 
	/*
   *题目:
   *已知整数3510593的十六进制表示为0x00359141,浮点数3510593.0的十六进制数为0x4A564504
   *1. 写出这两个十六进制数的二进制形式
   *2. 移动这两个串的相对位置,使得他们相匹配的位数最多.有多少位匹配呢?
   *3. 串中什么部分不相匹配
   
   
	//十六进制转十进制 
	int hextodec(char *hex){
		int step = 0; 
		long int decimalRes = 0; 
		int val = 0; 
		int i = 0; 
		int len = strlen(hex); 
	
		for(i = len- 2;hex[i];i--){
			if(hex[i]>=65&&hex[i]<=70) {
				val = hex[i]-'0' - 7;
				
			}else{
				val = hex[i] - '0';
			} 
			
			decimalRes += val * pow(HEX,step);
		
			step++; 
		} 
	
		printf("\nthe result of hextodec is : %d\n",decimalRes); 
		return decimalRes; 
	}
  
  
	//十进制转二进制 
	void dectobin(long int dec,char binary[35]){
		int start = 0;
		int begin = 0;
		int remainder = 0; 
		char temp[35]; 
		int ii,j; 
		while(dec){
			remainder = dec %  BIN;
			temp[start++] =  remainder; 
			dec /= BIN; 
		} 
		for( ii = start-1;ii>=0;ii--){
			binary[begin++]=temp[ii]+'0';
		} 
	 	for( j = 0;j<begin;j++){
	 		printf("%c ",binary[j]); 
		 }
		 printf("\n"); 
		 return ; 
	}
  
  
	//最常公共子串 version 1
	void LCS(char *one,char *another){
		int oneSize = strlen(one);
		int anotherSize = strlen(another);
		int oneStart = -1;
		int anotherStart = -1;
		int i,j;
		int m,n;
		int maxLength = 0,length = 0;
		int comparsions  =  0;
		for(i = 0;i<oneSize;i++){
			for(j = 0;j<anotherSize;j++ ){
				m = i;
				n = j;
				length = 0;
				
				while(m<oneSize&&n<anotherSize){
					comparsions++;
					if(one[m]!=another[n]) break;
					m++;
					n++;
					length++;
				}
				if(length > maxLength){
					maxLength = length;
					oneStart = i;
					anotherStart = j;
				}
			}
		}
		printf("the max length of LCS is %d\n",maxLength); 
		printf("the count of comparsions is %d\n",comparsions);
	} 
  
  
	//优化时间 
	void DRLCS(char *one,char *another){
		int oneSize = strlen(one);
		int anotherSize = strlen(another);
		int oneStart = -1;
		int anotherStart = -1;
		//为了减少时间,开辟了更多的空间 
		int drbox[40][40] = {0};
		int longest = 0;
		int comparsions = 0;
		int i,j;
		//边界值
		for(j = 0;j<anotherSize;j++){
			comparsions++;
			drbox[0][j] = (one[0]==another[j]?1:0);
		} 
		for(i = 1;i<oneSize;i++){
			comparsions++;
			drbox[i][0] = (another[0] == one[i]?1:0);
			for(j = 1;j<anotherSize;j++){
				comparsions++;
				if(one[i] == another[j]){
					drbox[i][j] = drbox[i-1][j-1] + 1;
					if(drbox[i][j] > longest){
						longest = drbox[i][j];
						oneStart = i;
						anotherStart = j;
					}
				}else{
					drbox[i][j] = 0;
				}
			}
		}
	
		printf("the max length of LCS is %d\n",longest); 
		printf("the count of comparsions is %d\n",comparsions);
	}
  
  
	//同时优化空间 
	void SLCS(char *one,char *another){
		//第二个for我直接复制了第一个for的内容,改了定义变量的初始值,这表示代码冗余太大 
		int oneSize = strlen(one);
		int anotherSize = strlen(another);
		int oneStart = -1;
		int anotherStart = -1;
		int longest = 0;
		int comparsions = 0;
		int i,j;
		//在减少时间的同时,也节省空间 
		for(i = 0;i<oneSize;i++){
			int m = i;
			int n = 0;
			int length = 0;
			while(m<oneSize&&n<anotherSize){
				comparsions++; 
				if(one[m] == another[n]){
					
					length++;
				}
				if(length>longest){
					longest = length;
					oneStart = m - length + 1;
					anotherStart = n - length + 1;
				}
				m++;
				n++;
			}
		}
		//移动第二个字符串
		for(j = 0;j<oneSize;j++){
			int m = 0;
			int n = j;
			int length = 0;
			while(m<oneSize&&n<anotherSize){
				comparsions++; 
				if(one[m] == another[n]){
					
					length++;
				}
				if(length>longest){
					longest = length;
					oneStart = m - length + 1;
					anotherStart = n - length + 1;
				}
				m++;
				n++;
			}
		}
		printf("the max length of LCS is %d\n",longest); 
		printf("the count of comparsions is %d\n",comparsions); 
	}
	
  //单次执行对比
	void single(int *longest,int f,char *one,char *another){
		int oneSize = strlen(one);
		int anotherSize = strlen(another);
		int oneStart = -1;
		int anotherStart = -1;
		int i; 
		int m,n; 
		int size = 0;
		size = (f == 0? oneSize:anotherSize); 
	
		//先以第一个字符串为移动标准 
		for(i = 0;i<size;i++){
			 if(f == 0){
			 	m = i; 
			 }else{
			 	n = i; 
			 }
			 if(f == 0){
			 	n = 0; 
			 }else{
			 	m = 0; 
			 }
			 
			int length = 0;
			while(m<oneSize&&n<anotherSize){
				
				 
				if(one[m] == another[n]){
					
					length++;
				}
				if(length>*longest){
					*longest = length;
					oneStart = m - length + 1;
					anotherStart = n - length + 1;
				}
				m++;
				n++;
			}
	
		}
	} 
	
	//减少冗余
	void RSLCS(char *one,char *another){
		int length = 0; 
		
		int *longest =  &length;

		single(longest,0,one,another);
		
		single(longest,1,one,another); 
		
		printf("the max length of LCS is %d\n",length); 
		
	}
int main(){
	
	char str[8] = "00359141"; 
	char str1[8]= "4A264504"; 
	long int dec = 10;
	char binary[35]; 
	char binary01[35];
	dec = hextodec(str); 
	dectobin(dec,binary);
	dec = hextodec(str1); 
	dectobin(dec,binary01);
	LCS(binary,binary01);
	DRLCS(binary,binary01);
	SLCS(binary,binary01);
	RSLCS(binary,binary01); 
	return 0; 
}
