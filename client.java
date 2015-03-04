package lab3;

import java.io.*;
import java.net.*;
import java.util.Scanner;

class client {

  
    private final static String myfile = "E:\\workspace\\lab3\\src\\lab3\\a.txt";
	private static String serverIP;
	private static int serverPort ;
   
	
    public static void main(String args[]) {
        Scanner in = new Scanner(System.in);
        
        Socket clientSocket = null;
        BufferedOutputStream send_client = null;
        
        //serverIP = "127.0.0.1";
        //serverPort = 55555;
        System.out.println("Enter the server address:");
        serverIP = in.nextLine();
        
        System.out.println("Enter the server port:");
        serverPort = in.nextInt();
        
      
        
        try {
            clientSocket = new Socket( serverIP , serverPort );
            send_client = new BufferedOutputStream(clientSocket.getOutputStream());
        } catch (IOException ex) {
        	System.out.println("Error creating output buffer stream!");
        }

        if (send_client != null) {
            File myFile = new File( myfile );
            byte[] bytearray = new byte[(int) myFile.length()];

            FileInputStream inputstream = null;

            try {
            	inputstream = new FileInputStream(myFile);
            } catch (FileNotFoundException ex) {
            	System.out.println("Error reading stream!");
            }
            BufferedInputStream buffInStream = new BufferedInputStream(inputstream);

            try {
            	buffInStream.read(bytearray, 0,bytearray.length);
                send_client.write(bytearray, 0, bytearray.length);
                System.out.println("Thank You for using  program!");
                send_client.flush();
                send_client.close();
                clientSocket.close();
                return;
            } catch (IOException ex) {
            	System.out.println("Error uploading file to server!");
            }
        }
    }
}