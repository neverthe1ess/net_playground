package udpechothread;// ������: javac UDPMyEcho.java
// ����: java UDPMyEcho localhost 3000

import java.net.*;
import java.io.*;

public class UDPMyEcho {
	final static int MAXBUFFER = 512;
	public static void main(String [] args){
		if(args.length != 2){
			System.out.println("����: java UDPMyEcho host-ip port");
			System.exit(0);
		}
		byte buffer[] = new byte[MAXBUFFER];
		int bufferLength = 0;
		int port = Integer.parseInt(args[1]);	// �Է� ��Ʈ ��ȣ ����
		
		try{
			InetAddress inetaddr = InetAddress.getByName(args[0]);
			DatagramSocket Socket = new DatagramSocket();	// �񿬰��� Ŭ���̾�Ʈ ���� ����
			DatagramPacket send_packet;					// �۽ſ� �����ͱ׷� ��Ŷ
			DatagramPacket recv_packet;					// ���ſ� �����ͱ׷� ��Ŷ
			
			while(true){
				// Ű���� �Է� �б�
				System.out.print("Input Data : ");
				// ǥ�� �Է� ��Ʈ������ ����� �Է��� ����Ʈ ��̿� ����
				bufferLength = System.in.read(buffer);
				// ������ �۽�
				send_packet = new DatagramPacket(buffer, buffer.length, inetaddr, port);
				Socket.send(send_packet);
				// ���� ������ ����
				recv_packet = new DatagramPacket(buffer, buffer.length);
				Socket.receive(recv_packet);
				
				// ȭ�� ����� ���� ���۸� ��Ʈ������ ����
				// ������ ������ ��(���� 2����Ʈ) �����鼭 ����
				//String result = new String(buffer, 0, bufferLength - 2);
				String result = new String(buffer, 0, bufferLength);
				System.out.println("Echo Data : " + result);
				
				if(result.indexOf("BYE") >= 0) // BYE �Է½� ����
				break;
			}
			Socket.close();
		}catch(UnknownHostException ex){	// �߸��� ���� �ּҷ� ���ٽ�
			System.out.println("Error in the host address ");
		}catch(IOException e){
			System.out.println(e);
		}
	}
}