/**
 * Server.java
 *
 * This is the date server where each client is serviced in a separate thread.
 *
 * The server listens on port 6013.
 */

import java.net.*;

public class Server
{
	private ServerSocket	s;
	private Socket		client;
        
	public Server()
	{
		// create the socket the server will listen to
		try {
			s = new ServerSocket(6013);
		}
		catch (java.io.IOException e) {
			System.out.println(e);
			System.exit(1);
		}

		// OK, now listen for connections

		System.out.println("Server is listening ....");

		try {
			while (true) {
				client = s.accept();

				// create a separate thread
				// to service the request
				(new Thread(new Connection(client))).start();
			}
		}
		catch (java.io.IOException e) {
			System.out.println(e);
		}
	}

	public static void main(String args[]) {
		Server fortuneServer = new Server();
	}

}
