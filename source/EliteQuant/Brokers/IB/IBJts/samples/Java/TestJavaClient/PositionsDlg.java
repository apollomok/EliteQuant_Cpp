/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved.  This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

package TestJavaClient;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JDialog;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;


public class PositionsDlg extends JDialog {

    public boolean m_rc;

    private JTextField 	m_id = new JTextField("0");
    private JTextField 	m_account = new JTextField();
    private JTextField 	m_modelCode = new JTextField();
    private JCheckBox 	m_ledgerAndNLV = new JCheckBox("LedgerAndNLV", false);
    private JButton 	m_ok = new JButton( "OK");
    private JButton 	m_cancel = new JButton( "Cancel");

    int m_retId;
    String m_retAccount;
    String m_retModelCode;
    boolean m_retLedgerAndNLV;

    public PositionsDlg( JFrame owner) {
        super( owner, true);

        // create button panel
        JPanel buttonPanel = new JPanel();
        buttonPanel.add( m_ok);
        buttonPanel.add( m_cancel);

        // create action listeners
        m_ok.addActionListener( new ActionListener() {
            public void actionPerformed( ActionEvent e) {
                onOk();
            }
        });
        m_cancel.addActionListener( new ActionListener() {
            public void actionPerformed( ActionEvent e) {
                onCancel();
            }
        });
        
        // create mid summary panel
        JPanel midPanel = new JPanel( new GridLayout( 0, 1, 5, 5) );
        midPanel.add( new JLabel( "Id") );
        midPanel.add( m_id);
        midPanel.add( new JLabel( "Account") );
        midPanel.add( m_account);
        midPanel.add( new JLabel( "Model Code") );
        midPanel.add( m_modelCode);
        midPanel.add( m_ledgerAndNLV);

        // create dlg box
        getContentPane().add( midPanel, BorderLayout.CENTER);
        getContentPane().add( buttonPanel, BorderLayout.SOUTH);
        setTitle( "Request Positions/Account Updates");
        pack();
    }

    void onOk() {
        m_rc = false;

        try {
            m_retId = Integer.parseInt( m_id.getText());
            m_retAccount = m_account.getText().trim();
            m_retModelCode = m_modelCode.getText().trim();
            m_retLedgerAndNLV = m_ledgerAndNLV.isSelected();
        }
        catch( Exception e) {
            Main.inform( this, "Error - " + e);
            return;
        }

        m_rc = true;
        setVisible( false);
    }

    void onCancel() {
        m_rc = false;
        setVisible( false);
    }
}