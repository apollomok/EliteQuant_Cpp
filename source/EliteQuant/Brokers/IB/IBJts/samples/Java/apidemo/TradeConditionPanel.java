package apidemo;

import com.ib.client.ExecutionCondition;
import com.ib.client.OrderCondition;

import apidemo.util.UpperField;

public class TradeConditionPanel extends OnOKPanel {
	private ExecutionCondition m_condition;
	private final UpperField m_secType = new UpperField();
	private final UpperField m_exchange =  new UpperField();
	private final UpperField m_symbol = new UpperField();
	
	public TradeConditionPanel(ExecutionCondition condition) {
		m_condition = condition;
		
		m_secType.setText(m_condition.secType());;
		m_exchange.setText(m_condition.exchange());
		m_symbol.setText(m_condition.symbol());;
		
		add("Underlying", m_symbol);
		add("Exchange", m_exchange);
		add("Type", m_secType);
	}
	
	public OrderCondition onOK() {
		m_condition.symbol(m_symbol.getText());
		m_condition.exchange(m_exchange.getText());
		m_condition.secType(m_secType.getText());
		
		return m_condition;
	}
}
