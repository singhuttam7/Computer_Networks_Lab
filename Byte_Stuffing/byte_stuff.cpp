/*
==========================================================
                    BYTE STUFFING
==========================================================

Definition:
Byte Stuffing is a technique used in byte-oriented communication
to prevent special control bytes (Flag and Escape) from appearing
as normal data.

Flag:
- A Flag is a special byte used to indicate the
  beginning and end of a data frame.
- Example: Flag = 'F'

Escape:
- Escape is a special byte inserted before every
  Flag or Escape byte present in the data.
- Example: Escape = 'E'

Rule:
1. Scan the data byte by byte (character by character).
2. If the current byte is a Flag ('F') or an Escape ('E'),
   insert an Escape ('E') before it.
3. Copy the current byte to the output.
4. Add the Flag byte at the beginning and end of the frame.
5. At the receiver, the inserted Escape byte is removed
   (Byte Destuffing) to recover the original data.

Purpose:
- Prevents the Flag byte from being interpreted as
  the start or end of a frame.
- Ensures correct frame synchronization.
- Enables reliable data transmission.

Example:
Flag   = 'F'
Escape = 'E'

Original Data : ABFECD
Stuffed Data  : ABEFEECD

Frame Sent:
F ABEFEECD F

Here,
- First F  -> Start Flag
- Last F   -> End Flag
- EF       -> Original data byte 'F'
- EE       -> Original data byte 'E'

==========================================================
*/

#include<iostream>
#include<cstring>
//#using namespace std;
int main(){
char input[100];
char output[200];
int j = 0;
std::cout<<"Enter the characters: "<<std::endl;
std::cin.getline(input, 100);//If we are using character array
std::cout<<"Original Characters: "<<input<<std::endl;

for(int i = 0; input[i] != '\0'; i++){
if(input[i] == 'F' || input[i] == 'E'){
output[j] = 'E';
j++;
}
output[j] = input[i];
j++;
}
output[j] = '\0';

std::cout<<"Stuffed data: "<<output<<std::endl;

return 0;
}
