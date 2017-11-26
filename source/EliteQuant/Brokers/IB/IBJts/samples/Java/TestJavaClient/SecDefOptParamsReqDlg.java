package TestJavaClient;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JDialog;

import apidemo.util.UpperField;
import apidemo.util.VerticalPanel;

public class SecDefOptParamsReqDlg extends JDialog {
	final UpperField m_idFld = new UpperField("0");
	final UpperField m_underlyingSymbolFld = new UpperField();
	final UpperField m_futFopExchangeFld = new UpperField();
//	final UpperField m_currencyFld = new UpperField();
	final UpperField m_underlyingSecTypeFld = new UpperField();
	final UpperField m_underlyingConIdFld = new UpperField();
	private int m_id;
	private String m_underlyingSymbol;
	private String m_futFopExchange;
	private String m_underlyingSecType;
//	private String m_currency;
	private int m_underlyingConId;
	private boolean m_isOk;
	
	public SecDefOptParamsReqDlg(SampleFrame owner) {
		super(owner);
		
		VerticalPanel paramsPanel = new VerticalPanel();
		JButton ok = new JButton("OK");
		JButton cancel = new JButton("Cancel");
		
		ok.addActionListener(new ActionListener() { @Override public void actionPerformed(ActionEvent e) { onOK(); } });
		cancel.addActionListener(new ActionListener() { @Override public void actionPerformed(ActionEvent e) { onCancel(); } });
		
		paramsPanel.add("Underlying symbol", m_underlyingSymbolFld);			
		paramsPanel.add("FUT-FOP exchange", m_futFopExchangeFld);			
//		paramsPanel.add("Currency", m_currencyFld);			
		paramsPanel.add("Underlying security type", m_underlyingSecTypeFld);			
		paramsPanel.add("Underlying contract id", m_underlyingConIdFld);			
		paramsPanel.add(ok);
		paramsPanel.add(cancel);
		setLayout(new BorderLayout());
		add(paramsPanel, BorderLayout.NORTH);
		pack();
	}

	protected void onCancel() {
		m_isOk = false;
		
		dispose();
	}

	protected void onOK() {
		m_id = m_idFld.getInt();
		m_underlyingSymbol = m_underlyingSymbolFld.getText();
		m_futFopExchange = m_futFopExchangeFld.getText();
//		m_currency = m_currencyFld.getText();
		m_underlyingSecType = m_underlyingSecTypeFld.getText();
		m_underlyingConId = m_underlyingConIdFld.getInt();
		m_isOk = true;

		dispose();
	}
	
	public boolean isOK() {
		return m_isOk;
	}
	
	public int id() {
		return m_id;
	}

	public String underlyingSecType() {
		return m_underlyingSecType;
	}

	public String underlyingSymbol() {
		return m_underlyingSymbol;
	}

	public String futFopExchange() {
		return m_futFopExchange;
	}

	public int underlyingConId() {
		return m_underlyingConId;
	}
	
//	public String currency() {
//		return m_currency;
//	}
}
