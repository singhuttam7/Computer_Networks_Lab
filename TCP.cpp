#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

//Structure to represent a TCP Segment
struct TCPSegment {
  bool SYN;
  bool ACK;
  int seq_num;
  int ack_num;
  };
  
  //Function prototypes for sender and receiver
  TCPSegment sender(int step, TCPSegment incoming_segment);
  TCPSegment receiver(int step, TCPSegment incoming_segment);
  
  
  int main(){
  //Send for random sequence numbers
  srand(time(0));
  cout<<"---TCP 3-Way Handshake Simulation---"<<endl<<endl;
  
  TCPSegment empty_segment = {false, false, 0, 0};
  TCPSegment segment_syn, segment_syn_ack, segment_ack;
  
  //Step 1: Client initiates connection
  segment_syn = sender(1, empty_segment);
  
  //Step 2: Server receives SYN and responds with SYN-ACK
  segment_syn_ack = receiver(2, segment_syn);
  
  //Step 3: Client receives SYN-ACK and responds with ACK
  segment_ack = sender(3, segment_syn_ack);
  
  //Step 4: Server receives final ACK and confirms connection
  receiver(4, segment_ack);
  
  return 0;
  }
  
  
  
  //Function simulating the client (Sender)
  TCPSegment sender(int step, TCPSegment incoming){
      TCPSegment outgoing;
      
      if(step == 1){
         //a) The client sends a SYN segment to the server to initiate a connection[cite: 1].
         outgoing.SYN = true;
         outgoing.ACK = false;
         outgoing.seq_num = rand() % 10000;
         outgoing.ack_num = 0;
         
         cout << "1. [Sender] Sending SYN..."<<endl;
         cout <<" Client initiates a connection. "<<endl;
         cout <<" Client SEQ = "<< outgoing.seq_num << endl << endl;
         }
         else if (step == 3){
         //c) The client sends an ACK segment to acknowledge the server's sequence number[cite: 1].
         outgoing.SYN = false;
         outgoing.ACK = true;
         outgoing.seq_num = incoming.ack_num;// Client's next sequence number
         outgoing.ack_num = incoming.seq_num + 1; //Acknowledging server's sequence
         
         cout <<"3. [Sender] Sending ACK..."<<endl;
         cout<<" Client acknowledges the server's sequence number."<<endl;
         cout<<" Client SEQ = " << outgoing.seq_num<<endl;
         cout<<" Client ACK = " << outgoing.ack_num<<endl<<endl;
         }
         return outgoing;
         }
         
         //Function simulating the Server (Receiver)
         TCPSegment receiver(int step, TCPSegment incoming){
             TCPSegment outgoing = {false, false, 0, 0};
             
             if(step == 2){
               //b) The Server responds with a SYN-ACK segment to acknowledge the client's request and synchronize its own sequence number[cite: 1].
               outgoing.SYN = true;
               outgoing.ACK = true;
               outgoing.seq_num = rand()%10000; //Server's own initial sequence number
               outgoing.ack_num = incoming.seq_num + 1; //Acknowledging client's sequence
               
               cout<<"2.[Receiver] Sending SYN-ACK..."<<endl;
               cout<<" Server acknowledges client's request and synchronizes sequence."<<endl;
               cout<<" Server SEQ = " << outgoing.seq_num<<endl;
               cout<<" Server ACK = "<< outgoing.ack_num<<endl<<endl;
             }
             else if(step == 4){
             // d) Display a message confirming that the TCP connection has been established successfully[cite: 1].
             cout<<"--------------------------------------------------------"<<endl;
cout<<"SUCCESS: The TCP connection has been established successfully!"<<endl;
cout<<"------------------------------------------------------"<<endl; 
             }
             return outgoing;
         }
