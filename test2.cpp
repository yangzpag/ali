#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
int ans =  0x7fffffff;
int mask = 0x00000007;

int getnum(int i,int status){
	return (status >> (i * 3)) & mask;
}

int getnstatus(int i,int num,int status){
	return status & ~(mask << (i * 3)) | num << (i*3);
}

void dfs(int status,int deep){
	if(ans <= deep) return;
	if(status ==  0){
		ans = min(ans,deep);
		return;
	}

	//连对
	for(int i=0;i<8;i++){
		int num1,num2,num3;
		num1 = getnum(i,status);
		num2 = getnum(i+1,status);
		num3 = getnum(i+2,status);
		if(num1 >= 2 && num2 >= 2 && num3 >= 2){
			int s1 = getnstatus(i,num1-2,status);
			int s2 = getnstatus(i+1,num2-2,s1);
			int s3 = getnstatus(i+2,num3-2,s2);
			dfs(s3,deep + 1);
		}
	} 
	//顺子
	for(int i=0;i<6;i++){
		int num1,num2,num3,num4,num5;
		num1 = getnum(i,status);
		num2 = getnum(i+1,status);
		num3 = getnum(i+2,status);
		num4 = getnum(i+3,status);
		num5 = getnum(i+4,status);
		if(num1 >= 1 && num2 >= 1 && num3 >= 1 && num4 >= 1 && num5 >= 1){
			int s1 = getnstatus(i,num1-1,status);
			int s2 = getnstatus(i+1,num2-1,s1);
			int s3 = getnstatus(i+2,num3-1,s2);
			int s4 = getnstatus(i+3,num4-1,s3);
			int s5 = getnstatus(i+4,num5-1,s4);
			dfs(s5,deep + 1);
		}
	} 
	//对子
	for(int i=0;i<10;i++){
		int num = getnum(i,status);
		if(num >= 2){
			dfs(getnstatus(i,num-2,status),deep+1);
		}
	} 
	//单张 
	for(int i=0;i<10;i++){
		int num = getnum(i,status);
		if(num >= 1){
			dfs(getnstatus(i,num-1,status),deep+1);
		}
	} 
}
int main(){
	
	int status = 0;
	for(int i=0;i<10;i++){
		int a;
		cin >> a;
		status |= a << (i*3);
	}
	dfs(status,0);
	cout << ans << endl;
    return 0;
}
