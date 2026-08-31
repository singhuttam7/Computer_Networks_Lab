//Implement stop and wait ARQ for 10 frames frame[10] 
//frame[0] = {20, 30, 45, 75, 65, 89, 93, 47, 25, 37}
//Assume every 3rd frame is lost and need retransmission.
//Print the frame received  and acknowledgement received
//In c++, srand() and rand() are used to generate pseudo random numbers
//time(0) gives the current time 
#include <iostream>
#include <ctime>

int main(){
srand(time(0));
int n;
std::cout<<"Enter the total number of frames you want to send."<<std::endl;
std::cin>>n;
std::vector<int> frames(n);

//Taking frames as input

for (int i = 0; i < n; i++){
std::cout<<"Enter Frame"<<i+1<<": "<<std::endl;
std::cin>>frames[i];

}
//Displaying the frames
std::cout<<"Displaying the frames"<<std::endl;
for(int i = 0; i < n; i++){
std::cout<<"Frame"<<i+1<<": "<<frames[i]<<std::endl;
}

std::cout<<"=====================Stop and Wait ARQ==============================="<<std::endl;

for(int i = 0; i< n; i++){
std::cout<<"Sender sends frames"<<": "<<i+1<<std::endl;
if((i+1)%3 == 0){
std::cout<<"Frame:"<<i+1<<" is lost!"<<std::endl;
std::cout<<"Timeout! sender resends the frame"<<i+1<<std::endl;
//Retransmission
std::cout<<"Sender retransmits the frame"<<i+1<<"again:"<<frames[i+1]<<std::endl;
}
//Receiver receives the frame
std::cout<<"Receiver receives frame"<<i+1<<frames[i+1]<<std::endl;

}


return 0;
}
