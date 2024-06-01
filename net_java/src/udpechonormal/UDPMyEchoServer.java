package udpechonormal;// ������: javac UDPMyEchoServer.java
// ����: java UDPMyEchoServer 3000

import java.net.*;
import java.io.*;
public class UDPMyEchoServer {
	final int MAXBUFFER = 512;
	
	public static void main (String[] args) {
		int arg_port = Integer.parseInt(args[0]);		// ��Ʈ ��ȣ�� ������ ����
		new UDPMyEchoServer().work(arg_port);
	}
	void work(int arg_port) {
		int port = arg_port;
		byte buffer[] = new byte[MAXBUFFER];
		try{
			DatagramSocket Socket = new DatagramSocket(port);		// �񿬰��� ���� ���� ��ü ����
			DatagramPacket recv_packet;
			System.out.println("Running the UDP Echo Server... ");
			
			while (true){
				// ������ ����
				recv_packet = new DatagramPacket (buffer, buffer.length);
				Socket.receive (recv_packet);
				
				String sentence = new String(recv_packet.getData()); 
           			String capitalizedSentence = sentence.toUpperCase(); 
         				byte tx_buffer[] = new byte[MAXBUFFER];
           			tx_buffer = capitalizedSentence.getBytes(); 

				// ���� ������ ���� �� �۽�: �۽ſ� ��Ŷ ����
				DatagramPacket send_packet = new DatagramPacket
			              //(recv_packet.getData(), recv_packet.getLength(),
				       (tx_buffer, recv_packet.getLength(),
			                 recv_packet.getAddress(), recv_packet.getPort());
						
				Socket.send(send_packet);
			}
		} catch (IOException e) {
			System.out.println(e);
		}
	}
}
	
// End of File 			