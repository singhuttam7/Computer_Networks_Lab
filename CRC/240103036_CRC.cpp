# include<iostream>
# include<cstring>
# include<string>
using namespace std;

//Function to perform XOR
string XOR(string a, string b){
string result = "";
//First bit is ignored beacause 1 XOR 1 = 0
for(int i = 1; i < b.length(); i++){
if(a[i] == b[i]){
result = result + '0';

}else{
result = result + '1';
}
}
return result;
}

//Function to perform CRC division
string modulo2Division(string dividend, string divisor){
int pick = divisor.length();
//Take first n bits, where n = divisor length
string temp = dividend.substr(0, pick);

while(pick < dividend.length()){
//If leftmost bit is 1, XOR with divisor
if(temp[0] == '1'){
temp = XOR(divisor, temp);
}else{
//XOR with zeros
temp = XOR(string(divisor.length(), '0'), temp);
}
//Bring down the next bit
temp += dividend[pick];
pick++;
}

//Last XOR operation
if(temp[0] == '1'){
temp = XOR(divisor, temp);
}else{
temp = XOR(string(divisor.length(), '0'), temp);
}
return temp;
}

int main(){
string data, divisor;

cout<<"Enter the data bits: ";
cin>>data;

cout<<"Enter the divisor bits: ";
cin>>divisor;
//Step1: Append (divisor length - 1) zeros
string dividend = data + string(divisor.length() - 1, '0');

cout<<"\nDividend: " <<dividend<<endl;

//Step2: Perform modulo-2 division
string remainder = modulo2Division(dividend, divisor);

//Step 3: Append remainder to original data
string codeword = data + remainder;

cout<<"CRC Remainder: "<<remainder<<endl;
cout<<"Transmitted Codeword: "<<codeword<<endl;



/***
char input[100];
std::string input2;

std::cout<<"Enter the input: "<<std::endl;
std::cin>>input;
std::cout<<input<<std::endl;
std::cout<<"Character length: "<<strlen(input)<<std::endl;

std::cin.ignore(); //Remove leftover new line
std::cout<<"Enter the string: "<<std::endl;
std::getline(std::cin, input2);
std::cout<<input2;
std::cout<<"String length: "<<input2.length()<<std::endl;
std::cout<<"String length: "<<input2.size()<<std::endl;


**/
return 0;
}
