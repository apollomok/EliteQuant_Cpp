package apidemo;

import com.ib.client.MarginCondition;
import com.ib.client.OrderCondition;

public class MarginContidionPanel extends OperatorConditionPanel<MarginCondition> {
	
	public MarginContidionPanel(MarginCondition condition) {
		super(condition);
		
		m_value.setText(condition().percent());
		
		add("Operator", m_operator);
		add("Cushion (%)", m_value);
	}
	
	public OrderCondition onOK() {
		super.onOK();
		condition().percent(m_value.getInt());
		
		return condition();
	}
}
