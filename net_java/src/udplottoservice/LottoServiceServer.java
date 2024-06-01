/** 사용자가 입력하는 seed 값에 따라서 서버는 1 ~ 45 사이의 값을 중복없이 6번 추출하여 전달한다.
 *  Compile -> javac LottoServiceServer.java
 *  Execute -> java LottoServiceServer [port-num]
 *  thread implementation
 * */

package udplottoservice;

import java.io.IOException;
import java.net.*;
import java.util.*;

// 쓰레드
public class LottoServiceServer extends Thread {
    DatagramSocket datagramSocket;
    int threadIndex;

    public LottoServiceServer(DatagramSocket datagramSocket, int threadIndex) {
        this.datagramSocket = datagramSocket;
        this.threadIndex = threadIndex;
    }
    // run 메소드
    @Override
    public void run() {
        StringBuilder sb = new StringBuilder();
        byte[] receiveBuf = new byte[512];
        byte[] sendBuf;

        try {
            DatagramPacket receivePacket = new DatagramPacket(receiveBuf, receiveBuf.length);
            datagramSocket.receive(receivePacket);
            int seedNumber = Integer.parseInt(new String(receivePacket.getData()));

            InetAddress IPAddress = receivePacket.getAddress();
            int port = receivePacket.getPort();

            Random rand = new Random(seedNumber);
            Set<Integer> lottoNumberSet = new HashSet<Integer>();
            while(lottoNumberSet.size() < 6) {
                lottoNumberSet.add(rand.nextInt(45) + 1);
            }
            List<Integer> lottoNumberList = new ArrayList<>(lottoNumberSet);
            Collections.sort(lottoNumberList);

            for(int number : lottoNumberList) {
                sb.append(number).append(" ");
            }
            sendBuf = sb.toString().getBytes();

            DatagramPacket sendPacket = new DatagramPacket(sendBuf, sendBuf.length, IPAddress, port);
            datagramSocket.send(sendPacket);
            System.out.println("쓰레드 " + threadIndex + "번이 동작하여 메시지를 전송!");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        if(args.length != 1) {
            System.out.println("사용법: java LottoServiceServer [port]");
            System.exit(0);
        }
        int port = Integer.parseInt(args[0]);

        try {
            DatagramSocket dataSoc = new DatagramSocket(null);
            dataSoc.bind(new InetSocketAddress(port)); // 명시적인 바인딩
            for (int threadIndex = 0; threadIndex < 3; threadIndex++) {
                LottoServiceServer server = new LottoServiceServer(dataSoc, threadIndex);
                server.start();
            }
        } catch (SocketException e) {
            throw new RuntimeException(e);
        }
    }
}
