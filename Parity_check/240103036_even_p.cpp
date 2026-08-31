//Parity_check (Error Detection)
//=============================From Sender Side========================

#include <iostream>
#include <cstring>

int count = 0;
int main(){
char input[100];
char output[200];
int j = 0;
std::cout<<"Enter the bits: "<<std::endl;
std::cin>>input;
std::cout<<"Original Data Packet: "<<input<<std::endl;
int len = strlen(input);

for(int i = 0; i < len; i++){
output[j] = input[i];
j++;
if(input[i] == '1'){
count ++;
}
}
std::cout<<"Value of count: "<<count<<std::endl;
if(count % 2 == 0){
output[j] = '0';
}else{
output[j] = '1';
}
j++;
output[j] = '\0';
std::cout<<"Parity bit included:"<<std::endl;
std::cout<<output<<std::endl;

//============Simulate Transmission error===================
if(output[2] == '0'){
output[2] = '1';
}else{
output[2] = '0';
}
std::cout<<"Transmission Error: "<<output<<std::endl;
count = 0;
//====================From Receiver Side=================
char decode_out[200];
len = strlen(output);
int k = 0;
for(int i = 0; i < len; i++){
decode_out[k] = output[i];
k++;
if(output[i] == '1'){
count ++;
}
}
std::cout<<"Value of count(output): "<<count<<std::endl;


if(count % 2 == 0){
std::cout<<"Accept the packet by Receiver."<<std::endl;
}else{
std::cout<<"Reject the packet"<<std::endl;
}
decode_out[k] = '\0';
std::cout<<"Received Packet: "<<decode_out<<std::endl;
std::cout<<"Packet after decoding."<<std::endl;
for(int i = 0; i < len - 1; i++){
std::cout<<decode_out[i];

}
std::cout<<"\n";
return 0;
}

