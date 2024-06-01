package udpechothread;//2020.06.04
// ������: javac ServerUdpThread.java
// ����: java ServerUdpThrea Port-No

import java.net.*;
import java.io.*;
import java.util.HashSet;
import java.util.Set;

class ServerUDPThread extends Thread { 
   DatagramSocket datasoc;
   int num;

   public ServerUDPThread(DatagramSocket datasoc, int num) {
         this.datasoc = datasoc;
         this.num = num;
   }

   public void run() {
      byte[] receiveData = new byte[1024]; 
      byte[] sendData  = new byte[1024];  

      while(true) { 
           try {
                DatagramPacket receivePacket =
                  new DatagramPacket(receiveData, receiveData.length);
               datasoc.receive(receivePacket); 
               String sentence = new String(receivePacket.getData()); 
  
               InetAddress IPAddress = receivePacket.getAddress(); 
               int port = receivePacket.getPort(); 
  
               String capitalizedSentence = sentence.toUpperCase(); 
               sendData = capitalizedSentence.getBytes(); 
  
               DatagramPacket sendPacket = 
                 new DatagramPacket(sendData, sendData.length, IPAddress,  port);

              datasoc.send(sendPacket); 
	    System.out.println("Thread-" + num + " ���� �� - - - :");
         }
         catch (IOException e) { e.printStackTrace(); }
      } 
  } //end of run()

  public static void main(String args[]) throws Exception {
     if(args.length != 1) {
          System.out.println("����: java ServerUDP port-��ȣ");
	System.exit(0);
     }
     int port = Integer.parseInt(args[0]);
     DatagramSocket datasoc = new DatagramSocket(port); 

     for(int num = 0; num < 3 ; num ++)  {// Thread 3�� ����
	ServerUDPThread serv = new ServerUDPThread(datasoc, num);
	serv.start();
    }
 } //end of main() 
} //end of class   

// End of File 
