/**
 *
 * This is the separate thread that services each
 * incoming echo client request.
 *
 */

import java.net.*;
import java.io.*;

public class Connection implements Runnable
{
    private Socket	client;
	private static Handler handler = new Handler();
    
	public Connection(Socket client) {
		this.client = client;
	}

	public void run() { 
		try {
			handler.process(client);
		}
		catch (java.io.IOException ioe) {
			System.err.println(ioe);
		}
	}

	
}

