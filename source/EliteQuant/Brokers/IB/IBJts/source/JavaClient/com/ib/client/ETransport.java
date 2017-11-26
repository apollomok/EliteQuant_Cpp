package com.ib.client;

import java.io.IOException;

public interface ETransport {
	void send(EMessage msg) throws IOException;
}
