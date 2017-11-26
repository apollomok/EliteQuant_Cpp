package com.ib.client;

import java.io.IOException;
import java.io.ObjectInput;
import java.io.ObjectOutput;


public abstract class OperatorCondition extends OrderCondition {
	
	private boolean m_isMore;

	protected abstract String valueToString();
	protected abstract void valueFromString(String v);
	
	
	@Override
	public void readExternal(ObjectInput in) throws IOException,
			ClassNotFoundException {
		super.readExternal(in);
		
		m_isMore = in.readBoolean();
		
		valueFromString(in.readUTF());
	}
	
	@Override
	public String toString() {
		return " is " + (isMore() ? ">= " : "<= ") + valueToString();
	}
	
	@Override
	public void writeExternal(ObjectOutput out) throws IOException {
		super.writeExternal(out);
		out.writeBoolean(m_isMore);
		out.writeUTF(valueToString());
	}
	
	public boolean isMore() {
		return m_isMore;
	}

	public void isMore(boolean m_isMore) {
		this.m_isMore = m_isMore;
	}
}