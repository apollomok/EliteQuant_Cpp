package apidemo;

import com.ib.client.ContractCondition;
import com.ib.client.ContractLookuper;
import com.ib.client.OrderCondition;
import com.ib.client.VolumeCondition;

public class VolumeConditionPanel extends ContractConditionPanel<VolumeCondition> {

	public VolumeConditionPanel(ContractCondition condition, ContractLookuper lookuper) {
		super(condition, lookuper);
		
		m_value.setText(condition().volume());
		
		add("Operator", m_operator);
		add("Volume", m_value);
	}

	@Override
	public OrderCondition onOK() {
		super.onOK();
		
		condition().volume(m_value.getInt());
		
		return condition();
	}
}
