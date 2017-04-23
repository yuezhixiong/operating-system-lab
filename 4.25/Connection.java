/**
 * Connection.java
 *
 * This is the separate thread that services each request.
 * This reads a random fortune from the list of fortunes.
 */

import java.net.*;
import java.io.*;

public class Connection implements Runnable
{
	private Socket	outputLine;

	public Connection(Socket s) {
		outputLine = s;
	}

	public void run() {
		// getOutputStream returns an OutputStream object
		// allowing ordinary file IO over the socket.

		try {
			// create a new PrintWriter with automatic flushing
			PrintWriter pout = new PrintWriter(outputLine.getOutputStream(), true);

			// now send the current date to the client
			pout.println(new java.util.Date() );

			// now close the socket
			outputLine.close();
		}
		catch (java.io.IOException e) {
			System.out.println(e);
		}
	}


}
