/** 원하는 seed 값을 받아 서버에게 전달하여 로또 번호 6개를 받는다.
 *  Compile -> javac LottoServiceClient.java
 *  Execute -> java LottoServiceClient 127.0.0.1 [port-num]
 * */

package udplottoservice;

import java.io.IOException;
import java.net.*;
import java.util.*;

public class LottoServiceClient {
    public static void main(String[] args) {
        if(args.length != 2) {
            System.out.println("사용법: java LottoServiceClient <dst ip> <port>");
            System.exit(0);
        }
        byte[] buffer = new byte[512];
        int bufferLength = 0;
        int port = Integer.parseInt(args[1]);

        try {
            InetAddress dstIp = InetAddress.getByName("localhost");
            DatagramSocket socket = new DatagramSocket();
            DatagramPacket send_packet;
            DatagramPacket recv_packet;

            while(true){
                // 씨드 넘버 입력 창 출력
                System.out.print("seed number을 입력하세요 : ");
                bufferLength = System.in.read(buffer);

                send_packet = new DatagramPacket(buffer, bufferLength, dstIp, port);
                socket.send(send_packet);

                recv_packet = new DatagramPacket(buffer, bufferLength);
                socket.receive(recv_packet);

                String result = new String(recv_packet.getData());
                String[] splitResult = result.split(" ");

                List<Integer> numbers = new ArrayList<Integer>();

                for(String number : splitResult){
                    numbers.add(Integer.parseInt(number));
                }
                System.out.print("로또 번호는 : ");
                for(int number : numbers){
                    System.out.println(number + " ");
                }
            }
        } catch (UnknownHostException e) {
            System.out.println("Error in the host address ");
        } catch (IOException e) {
            System.out.println(e);
        }

    }
}
