//Implement checksum error control mechanism
//Data: 11000111 01011001 11001101



#include<iostream>
#include<bits/stdc++.h>

//function to find the ones complement
std::string onesComp(std::string data){
for(int i = 0; i < data.length(); i++){
if(data[i] == '0'){
data[i] = '1';
}else{
data[i] = '0';
}

}
return data;
}

//Function to return the checksum value given in the string when divided by k block size
std::string checkSum(std::string data, int block_size){
//check data size is divisible by block size 
//if not add 0 (padding)
int n = data.length();
if(n % block_size != 0){
int pad_size = block_size - (n % block_size);
for (int i = 0; i < pad_size; i++){
data = '0' + data;
}
}

//Binary addition of all blocks with carry
std::string result = "";

//first block of data stored in result variable
for(int i = 0; i < block_size; i++){
result = result + data[i];
}

//Loop to calculate the blockwise addition data
for(int i = block_size; i < n; i = i + block_size){
std::string next_block = "";
//Loop to calculate the next block data
for(int j = i; j < i + block_size; j++){
next_block = next_block + data[j];
}

//Stores the binary addition of two blocks
std::string additions = "";
int sum = 0;
int carry = 0;

//Loop to calculate the binary addition of two current blocks of k size

for(int k = block_size - 1; k >= 0; k--){
sum += (next_block[k] - '0') + (result[k] - '0');
carry = sum/2;
if(sum == 0){
additions = '0' + additions;
sum = carry;
}else if(sum == 1){
additions = '1' + additions;
sum = carry;
}else if(sum == 2){
additions = '0' + additions;
sum = carry;
}else{
additions = '1' + additions;
sum = carry;
}
 }
 
 //After binary add of two blocks with carry
 //If carry is one then apply binary addition
 std::string final = "";
 
 if(carry == 1){
 for(int l = additions.length() -1; l >= 0; l--){
 if(carry == 0){
 final = additions[l] + final;
 }else if(((additions[l] - '0') + carry)% 2 == 0){
 final = '0' + final;
 carry  = 1;
 }else{
 final = '1'+ final;
 carry = 0;
 }
 }
 result = final;
 }
 else{
 result = additions;
 }
}
//Returns ones complement of the result value which represents the required checksum value
return onesComp(result);
}

//Functions to check if the received message is same as sender's message
bool checker(std::string sent_message, std::string recv_message, int block_size){
//Checksum value of the senders message
std::string sender_checksum = checkSum(sent_message, block_size);
//message received by the receiver side , checksum vaue
std::string receiver_checksum = checkSum(recv_message + sender_checksum, block_size);

//if receiver checksum value is 0
if(count(receiver_checksum.begin(), receiver_checksum.end(), '0') == block_size){
return true;
}else{
return false;
}
}
int main(){
std::cout<<"We are performing the Checksum error detection"<<std::endl;
std::string sent_message = "111111101111110111111";
std::string recv_message = "111111101111110111111";
int block_size = 8;

if(checker(sent_message, recv_message, block_size)
){
std::cout<<"No error"<<std::endl;
}else{
std::cout<<"Error"<<std::endl;
}

return 0;
}
