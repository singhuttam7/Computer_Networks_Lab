/*
==========================================================
                    BIT STUFFING
==========================================================

Definition:
Bit Stuffing is a technique used in bit-oriented communication
to prevent the Flag pattern from appearing inside the data.

Flag:
- A Flag is a special bit pattern used to indicate the
  beginning and end of a data frame.
- Standard Flag = 01111110

Rule:
1. Scan the data bit by bit.
2. Whenever five consecutive 1s are found,
   insert a 0 immediately after them.
3. No bit is inserted after consecutive 0s.
4. At the receiver, the inserted 0 is removed
   (Bit Destuffing) to obtain the original data.

Purpose:
- Prevents the Flag pattern from appearing in the data.
- Helps the receiver correctly identify the start
  and end of each frame.
- Ensures reliable data transmission.

Example:
Original Data : 11111011111
Stuffed Data  : 1111100111110

Flag Example:
Frame Sent:
01111110 1111100111110 01111110

Here,
- First 01111110  -> Start Flag
- Last 01111110   -> End Flag

==========================================================
*/
/*
BIT STUFFING
*/

#include <iostream>
#include <cstring>
int main(){
char input[100];
char stuffed[200];
char unstuffed[200];
int count = 0;
int j = 0;
std::cout<<"Enter the bits:"<<std::endl;
std::cin>>input;
std::cout<<"Original Bits: "<<input<<std::endl;
int len = strlen(input);
//by traversing
for(int i = 0; i< len; i++){
stuffed[j] = input[i];
j++;
if(input[i] == '1'){
count ++;
if(count == 5){
stuffed[j] = '0';
j++;
count = 0;
}

}else{
count = 0;
}
}
stuffed[j] = '\0';
std::cout<<"Stuffed bit: "<<stuffed<<std::endl;
/*================
BIT UNSTUFFING
*/
count = 0;
j = 0;
len = strlen(stuffed);
for(int i = 0; i < len; i++){
unstuffed[j] = stuffed[i];
j++;

if(stuffed[i] == '1'){
count ++;

if(count == 5){
i++; //Skip the stuffed zero
count = 0;
}
}else{
count = 0;
}

}
unstuffed[j] = '\0';
std::cout<<"Unstuffed Bits: "<<unstuffed<<std::endl;
return 0;
}
