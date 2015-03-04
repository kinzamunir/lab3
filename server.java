package lab3;


import java.io.*;
import java.net.*;

class server {

    private final static String fileOutput = "E:\\workspace\\lab3\\src\\lab3\\output.txt";

    public static void main(String args[]) {

        while (true) {
            ServerSocket socket = null;
            Socket conn_socket = null;
            byte[] arraybyte = new byte[1];
            int bytesRead;
            InputStream inputstream = null;

            try {
                socket = new ServerSocket(55555);
                System.out.println("Waiting for the connection...");
                conn_socket = socket.accept();
                inputstream = conn_socket.getInputStream();
            } catch (IOException ex) {
            	 System.out.println("Error establishing connection!");
            }
            ByteArrayOutputStream baos = new ByteArrayOutputStream();
            System.out.println("Client connected!");
            if (inputstream != null) {
                FileOutputStream filestream = null;
                BufferedOutputStream outstream = null;
              

                try {
                	filestream = new FileOutputStream( fileOutput );
                    outstream = new BufferedOutputStream(filestream);
                    bytesRead = inputstream.read(arraybyte, 0, arraybyte.length);

                    do {
                            baos.write(arraybyte);
                            bytesRead = inputstream.read(arraybyte);
                    } while (bytesRead != -1);

                    outstream.write(baos.toByteArray());
                    outstream.flush();
                    outstream.close();
                    conn_socket.close();
                } catch (IOException ex) {
                    // Do exception handling
                }
            }
        }
    }
}