package apidemo;

import com.ib.client.OrderCondition;

import apidemo.util.VerticalPanel;

public abstract class OnOKPanel extends VerticalPanel {
	public abstract OrderCondition onOK();
}