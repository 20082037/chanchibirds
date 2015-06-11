#include <iostream>
#include <stdio.h> 	
#include <cstdlib>
#include <math.h>
using namespace std;

float stof(string s){
	float result;
	int pos = s.find(".");
	int size = s.size();
	if(pos != string::npos){
		int intPart = atoi(s.substr(0,pos+1).c_str());
		float floatPart = atoi(s.substr(pos+1,size-pos-1).c_str()) / pow(10,size-pos-1);
		result = intPart + floatPart;		
	}else{
		result = atoi(s.c_str());
	}
	return result;
}

int main(){
	float n = stof("3123.42212");
	printf("Numero %f\n",n);
//	cout<<stof("3123.42212")<<endl;
	return 0;
}

