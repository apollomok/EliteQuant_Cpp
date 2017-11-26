package com.ib.client;

import java.util.ArrayList;

public interface ContractLookuper {
	ArrayList<ContractDetails> lookupContract(Contract contract);
}