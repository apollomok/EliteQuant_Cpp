package com.ib.client;


public class EJavaSignal implements EReaderSignal {
	Object monitor = new Object();
	Boolean open = false;
	
	@Override
	public void issueSignal() {
	    synchronized (monitor) {
	        open = true;
	        monitor.notifyAll();
	      }
	}

	@Override
	public void waitForSignal() {
		 synchronized (monitor) {
		      while (!open) {
		          try {
					monitor.wait();
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
		      }
		      
		      open = false;
		    }
	}

}
