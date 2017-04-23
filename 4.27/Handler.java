/**
 * Handler class containing the logic for echoing results back
 * to the client. 
 *
 */
 
import java.io.*;
import java.net.*;

public class Handler 
{
        public static final int BUFFER_SIZE = 256;
        
	/**
	 * this method is invoked by a separate thread
	 */
	public void process(Socket client) throws java.io.IOException {
		byte[] buffer = new byte[BUFFER_SIZE];
		InputStream  fromClient = null;
		OutputStream toClient = null;
		
		try {
			/**
			 * get the input and output streams associated with the socket.
			 */
			fromClient = new BufferedInputStream(client.getInputStream());
			toClient = new BufferedOutputStream(client.getOutputStream());
			int numBytes;

                        /** continually loop until the client closes the connection */
			while ( (numBytes = fromClient.read(buffer)) != -1) {
                                toClient.write(buffer,0,numBytes);
				toClient.flush();
			}
                        
                       		}
		catch (IOException ioe) {
			System.err.println(ioe);
		}
                finally {
                    // close streams and socket
                    if (fromClient != null)
                        fromClient.close();
                    if (toClient != null)
                        toClient.close();
                    if (client != null)
                        client.close();
                }
	}
}
