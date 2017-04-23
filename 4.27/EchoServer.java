/**
 * An echo server listening on port 6007. This server reads from the client
 * and echoes back the result. When the client enters the character '.' - the
 * server closes the connection.
 *
 */

import java.net.*;
import java.io.*;

public class  EchoServer 
{
	public static final int DEFAULT_PORT = 6007;

	public static void main(String[] args) throws IOException {
		ServerSocket sock = null;

		try {
			// establish the socket
			sock = new ServerSocket(DEFAULT_PORT);

			while (true) {
				/**
				 * now listen for connections
				 * and service the connection in a separate thread.
				 */
				Thread worker = new Thread(new Connection(sock.accept()));
				worker.start();
			}
		}
		catch (IOException ioe) { }
		finally {
			if (sock != null)
				sock.close();
		}
	}
}
