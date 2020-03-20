#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
const int INF = 0x7fffffff;
int ans =  INF;
int mask = 0x00000007;

unordered_map<int,int> m;
int getnum(int i,int status){
	return (status >> (i * 3)) & mask;
}

int getnstatus(int i,int num,int status){
	return status & ~(mask << (i * 3)) | num << (i*3);
}

int dfs(int status){
	if(status ==  0){
		return 0;
	}
	if(m.count(status)) return m[status];
	m[status] = INF;
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
			dfs(s3);
			m[status] = min (m[status],m[s3] + 1);
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
			dfs(s5);
			m[status] = min (m[status],m[s5] + 1);
		}
	} 
	//对子
	for(int i=0;i<10;i++){
		int num = getnum(i,status);
		if(num >= 2){
			int s1 = getnstatus(i,num-2,status);
			dfs(s1);
			m[status] = min (m[status],m[s1] + 1);
		}
	} 
	//单张 
	for(int i=0;i<10;i++){
		int num = getnum(i,status);
		if(num >= 1){
			int s1 = getnstatus(i,num-1,status);
			dfs(s1);
			m[status] = min (m[status],m[s1] + 1);
		}
	} 
	return m[status];
}
int main(){
	
	int status = 0;
	for(int i=0;i<10;i++){
		int a;
		cin >> a;
		status |= a << (i*3);
	}
	
	cout << dfs(status) << endl;
    return 0;
}
