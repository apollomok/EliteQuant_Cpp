package apidemo;

import com.ib.client.OperatorCondition;
import com.ib.client.OrderCondition;

import apidemo.util.TCombo;
import apidemo.util.UpperField;

public class  OperatorConditionPanel<T> extends OnOKPanel {
	OperatorCondition m_condition;
	final TCombo<String> m_operator = new TCombo<String>("<=", ">=");
	final UpperField m_value = new UpperField();
	
	public OperatorConditionPanel(OperatorCondition condition) {
		m_condition = condition;
		
		m_operator.setSelectedIndex(m_condition.isMore() ? 1 : 0);
	}
	
	public OrderCondition onOK() {
		m_condition.isMore(m_operator.getSelectedIndex() == 1);
		
		return m_condition;
	}
	
	protected T condition() {
		return (T)m_condition;
	}
}
