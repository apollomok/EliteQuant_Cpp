package com.ib.client;

import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;
import java.util.ArrayList;

public abstract class ContractCondition extends OperatorCondition {

	@Override
	public String toString() {
		return toString(null);
	}
	
	public String toString(ContractLookuper lookuper) {
		Contract c = new Contract();
		
		c.conid(conId());
		c.exchange(exchange());
		
		ArrayList<ContractDetails> list = lookuper.lookupContract(c);		
		String strContract = list.size() > 0 ? 
				list.get(0).contract().symbol() + " " + list.get(0).contract().secType() + " on " + list.get(0).contract().exchange() :
				conId() + "";
		
		return type() + " of " + strContract + super.toString();
	}

	private int m_conId;
	private String m_exchange;

	@Override
	public void readExternal(ObjectInput in) throws IOException,
			ClassNotFoundException {
		super.readExternal(in);
		
		m_conId = in.readInt();
		m_exchange = in.readUTF();
	}

	@Override
	public void writeExternal(ObjectOutput out) throws IOException {
		super.writeExternal(out);
		out.writeInt(m_conId);
		out.writeUTF(m_exchange);
	}

	public int conId() {
		return m_conId;
	}

	public void conId(int m_conId) {
		this.m_conId = m_conId;
	}

	public String exchange() {
		return m_exchange;
	}

	public void exchange(String exchange) {
		this.m_exchange = exchange;
	}
}