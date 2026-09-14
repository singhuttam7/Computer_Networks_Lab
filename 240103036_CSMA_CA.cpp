#include <iostream>
#include <vector>
#include<cstdlib>
#include<ctime>
using namespace std;

int main(){
srand(time(0));
int n;
cout<<"Enter the total number of devices"<<endl;
cin>> n;

vector<int> backoff(n, 0);
vector<bool> transmitted(n, false);

int remaining = n;
int slot = 0;

cout<<"\nCSMA CA SIMULATION\n"<<endl;
while(remaining > 0){
cout<<"\nTime slot"<<slot<< endl;

//Assign random backoff to devices that have not yet transmitted
for (int i = 0; i < n ; i++){
if(!transmitted[i] && backoff[i] == 0){
backoff[i] = rand()%5;
cout<<"Devices: "<<i +1<<"selects backoff of "<<backoff[i]<<endl;
}
}

//Find devices whose backoff reached to zero
vector<int> ready;

for (int i = 0; i < n; i++){
if(!transmitted[i] && backoff[i] == 0){
ready.push_back(i);
}
}

//No devices ready

if (ready.empty()){
for (int i = 0; i < n; i++){
if(!transmitted[i] && backoff[i] >0)
backoff[i] --;
}
slot ++;

continue;
}
//Only one device transmits
if(ready.size() == 1){
int device = ready[0];

cout<<"Channel is idle"<<endl;
cout<<"Device "<<device + 1<<"transmits data"<<endl;

cout<<"Device "<<device + 1<<"receives acknowledgement" <<endl;

transmitted[device] = true;
remaining --;

}
//More than one device transmits collision occurs
else{
cout<<"Channel is BUSY\n";
cout<<"Collision occured between devices.\n";
for(int device : ready){
cout<<"Device "<<device +  1<<"";
}
cout<<endl;
//Device will select new backoff value
//Reset backoff after collision
for(int device : ready){
backoff[device]= rand()%5 + 1;

}

}

//Decrease backoff for waiting device
for(int i = 0; i < n; i++){
if(!transmitted[i] && backoff[i]  > 0)
backoff[i]--;
}
slot ++;
}

cout<<"All devices transmitted successfully"<<endl;
cout<<"Total time slots used: "<<slot<<endl;

return 0;
}

