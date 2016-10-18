/**
*	UDP Client Program
*	Connects to a UDP Server
*	Receives a line of input from the keyboard and sends it to the server
*	Receives a response from the server and displays it.
*
*	@author: Sarah Monroe
@	version: 2.1
*/

import java.io.*;
import java.net.*;

class UDPClient {
	
    public static void main(String args[]) throws Exception
    {

      BufferedReader inFromUser = new BufferedReader(new InputStreamReader(System.in));

      DatagramSocket clientSocket = new DatagramSocket();

      InetAddress IPAddress = InetAddress.getByName("10.49.139.88");

      byte[] sendData = new byte[1024];
      byte[] receiveData = new byte[1024];
	  
	  int PROTOCOL = 0;
	  boolean msgSENT = false;
	  
	  String sentence = "100 BLUE";
	  sendData = sentence.getBytes();
	  DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
      clientSocket.send(sendPacket);
	  PROTOCOL = 100;
	  
	  while(PROTOCOL == 100){
		  if(!msgSENT){
			  System.out.println("CONNECTED TO SERVER, WAITING FOR SECOND CLIENT.");
			  msgSENT = true;
		  }
		   DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		   clientSocket.receive(receivePacket);
		   String modifiedSentence = new String(receivePacket.getData());
		   if(modifiedSentence != null){
		   PROTOCOL = 200;
		   msgSENT = false;
		   }
	  }
	  	  while(PROTOCOL == 200){
		  if(!msgSENT){
			  System.out.println("READY TO COMMUNICATE");
			  msgSENT = true;
		  }
		   DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
		   clientSocket.receive(receivePacket);
		   String modifiedSentence = new String(receivePacket.getData());
		   if(modifiedSentence != null){
		   //System.out.println("");
		   PROTOCOL = 200;
		   }
	  }

      // sentence = inFromUser.readLine();
      // sendData = sentence.getBytes();
	  // DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, 9876);
      // clientSocket.send(sendPacket);

      // DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
      // clientSocket.receive(receivePacket);
      // String modifiedSentence = new String(receivePacket.getData());

      // System.out.println("FROM SERVER:" + modifiedSentence);
      clientSocket.close();
      }
}
