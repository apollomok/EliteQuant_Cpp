/* Copyright (C) 2013 Interactive Brokers LLC. All rights reserved.  This code is subject to the terms
 * and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable. */

package com.ib.client;

import java.text.DateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Set;

public class EWrapperMsgGenerator {
    public static final String SCANNER_PARAMETERS = "SCANNER PARAMETERS:";
    public static final String FINANCIAL_ADVISOR = "FA:";
    
	static public String tickPrice( int tickerId, int field, double price, int canAutoExecute) {
    	return "id=" + tickerId + "  " + TickType.getField( field) + "=" + price + " " + 
        ((canAutoExecute != 0) ? " canAutoExecute" : " noAutoExecute");
    }
	
    static public String tickSize( int tickerId, int field, int size) {
    	return "id=" + tickerId + "  " + TickType.getField( field) + "=" + size;
    }
    
    static public String tickOptionComputation( int tickerId, int field, double impliedVol,
    		double delta, double optPrice, double pvDividend,
    		double gamma, double vega, double theta, double undPrice) {
    	String toAdd = "id=" + tickerId + "  " + TickType.getField( field) +
    		": vol = " + ((impliedVol >= 0 && impliedVol != Double.MAX_VALUE) ? Double.toString(impliedVol) : "N/A") +
    		" delta = " + ((Math.abs(delta) <= 1) ? Double.toString(delta) : "N/A") +
    		" gamma = " + ((Math.abs(gamma) <= 1) ? Double.toString(gamma) : "N/A") +
    		" vega = " + ((Math.abs(vega) <= 1) ? Double.toString(vega) : "N/A") +
    		" theta = " + ((Math.abs(theta) <= 1) ? Double.toString(theta) : "N/A") +
    		" optPrice = " + ((optPrice >= 0 && optPrice != Double.MAX_VALUE) ? Double.toString(optPrice) : "N/A") +
    		" pvDividend = " + ((pvDividend >= 0 && pvDividend != Double.MAX_VALUE) ? Double.toString(pvDividend) : "N/A") +
    		" undPrice = " + ((undPrice >= 0 && undPrice != Double.MAX_VALUE) ? Double.toString(undPrice) : "N/A");
		return toAdd;
    }
    
    static public String tickGeneric(int tickerId, int tickType, double value) {
    	return "id=" + tickerId + "  " + TickType.getField( tickType) + "=" + value;
    }
    
    static public String tickString(int tickerId, int tickType, String value) {
    	return "id=" + tickerId + "  " + TickType.getField( tickType) + "=" + value;
    }
    
    static public String tickEFP(int tickerId, int tickType, double basisPoints,
			String formattedBasisPoints, double impliedFuture, int holdDays,
			String futureLastTradeDate, double dividendImpact, double dividendsToLastTradeDate) {
    	return "id=" + tickerId + "  " + TickType.getField(tickType)
		+ ": basisPoints = " + basisPoints + "/" + formattedBasisPoints
		+ " impliedFuture = " + impliedFuture + " holdDays = " + holdDays +
		" futureLastTradeDate = " + futureLastTradeDate + " dividendImpact = " + dividendImpact +
		" dividends to expiry = "	+ dividendsToLastTradeDate;
    }
    
    static public String orderStatus( int orderId, String status, double filled, double remaining,
            double avgFillPrice, int permId, int parentId, double lastFillPrice,
            int clientId, String whyHeld) {
    	return "order status: orderId=" + orderId + " clientId=" + clientId + " permId=" + permId +
        " status=" + status + " filled=" + filled + " remaining=" + remaining +
        " avgFillPrice=" + avgFillPrice + " lastFillPrice=" + lastFillPrice +
        " parent Id=" + parentId + " whyHeld=" + whyHeld;
    }
    
    static public String openOrder( int orderId, Contract contract, Order order, OrderState orderState) {
        String msg = "open order: orderId=" + orderId +
        " action=" + order.getAction() +
        " quantity=" + order.totalQuantity() +
        " conid=" + contract.conid() + 
        " symbol=" + contract.symbol() + 
        " secType=" + contract.getSecType() + 
        " lastTradeDate=" + contract.lastTradeDateOrContractMonth() + 
        " strike=" + contract.strike() + 
        " right=" + contract.getRight() + 
        " multiplier=" + contract.multiplier() + 
        " exchange=" + contract.exchange() + 
        " primaryExch=" + contract.primaryExch() + 
        " currency=" + contract.currency() + 
        " localSymbol=" + contract.localSymbol() + 
        " tradingClass=" + contract.tradingClass() + 
        " type=" + order.getOrderType() +
        " lmtPrice=" + Util.DoubleMaxString(order.lmtPrice()) +
        " auxPrice=" + Util.DoubleMaxString(order.auxPrice()) +
        " TIF=" + order.getTif() +
        " localSymbol=" + contract.localSymbol() +
        " client Id=" + order.clientId() +
        " parent Id=" + order.parentId() +
        " permId=" + order.permId() +
        " outsideRth=" + order.outsideRth() +
        " hidden=" + order.hidden() +
        " discretionaryAmt=" + order.discretionaryAmt() +
        " displaySize=" + order.displaySize() +
        " triggerMethod=" + order.getTriggerMethod() +
        " goodAfterTime=" + order.goodAfterTime() +
        " goodTillDate=" + order.goodTillDate() +
        " faGroup=" + order.faGroup() +
        " faMethod=" + order.getFaMethod() +
        " faPercentage=" + order.faPercentage() +
        " faProfile=" + order.faProfile() +
        " shortSaleSlot=" + order.shortSaleSlot() +
        " designatedLocation=" + order.designatedLocation() +
        " exemptCode=" + order.exemptCode() +
        " ocaGroup=" + order.ocaGroup() +
        " ocaType=" + order.getOcaType() +
        " rule80A=" + order.getRule80A() +
        " allOrNone=" + order.allOrNone() +
        " minQty=" + Util.IntMaxString(order.minQty()) +
        " percentOffset=" + Util.DoubleMaxString(order.percentOffset()) +
        " eTradeOnly=" + order.eTradeOnly() +
        " firmQuoteOnly=" + order.firmQuoteOnly() +
        " nbboPriceCap=" + Util.DoubleMaxString(order.nbboPriceCap()) +
        " optOutSmartRouting=" + order.optOutSmartRouting() +
        " auctionStrategy=" + order.auctionStrategy() +
        " startingPrice=" + Util.DoubleMaxString(order.startingPrice()) +
        " stockRefPrice=" + Util.DoubleMaxString(order.stockRefPrice()) +
        " delta=" + Util.DoubleMaxString(order.delta()) +
        " stockRangeLower=" + Util.DoubleMaxString(order.stockRangeLower()) +
        " stockRangeUpper=" + Util.DoubleMaxString(order.stockRangeUpper()) +
        " volatility=" + Util.DoubleMaxString(order.volatility()) +
        " volatilityType=" + order.getVolatilityType() +
        " deltaNeutralOrderType=" + order.getDeltaNeutralOrderType() +
        " deltaNeutralAuxPrice=" + Util.DoubleMaxString(order.deltaNeutralAuxPrice()) +
        " deltaNeutralConId=" + order.deltaNeutralConId() +
        " deltaNeutralSettlingFirm=" + order.deltaNeutralSettlingFirm() +
        " deltaNeutralClearingAccount=" + order.deltaNeutralClearingAccount() +
        " deltaNeutralClearingIntent=" + order.deltaNeutralClearingIntent() +
        " deltaNeutralOpenClose=" + order.deltaNeutralOpenClose() +
        " deltaNeutralShortSale=" + order.deltaNeutralShortSale() +
        " deltaNeutralShortSaleSlot=" + order.deltaNeutralShortSaleSlot() +
        " deltaNeutralDesignatedLocation=" + order.deltaNeutralDesignatedLocation() +
        " continuousUpdate=" + order.continuousUpdate() +
        " referencePriceType=" + order.getReferencePriceType() +
        " trailStopPrice=" + Util.DoubleMaxString(order.trailStopPrice()) +
        " trailingPercent=" + Util.DoubleMaxString(order.trailingPercent()) +
        " scaleInitLevelSize=" + Util.IntMaxString(order.scaleInitLevelSize()) +
        " scaleSubsLevelSize=" + Util.IntMaxString(order.scaleSubsLevelSize()) +
        " scalePriceIncrement=" + Util.DoubleMaxString(order.scalePriceIncrement()) +
        " scalePriceAdjustValue=" + Util.DoubleMaxString(order.scalePriceAdjustValue()) +
        " scalePriceAdjustInterval=" + Util.IntMaxString(order.scalePriceAdjustInterval()) +
        " scaleProfitOffset=" + Util.DoubleMaxString(order.scaleProfitOffset()) +
        " scaleAutoReset=" + order.scaleAutoReset() +
        " scaleInitPosition=" + Util.IntMaxString(order.scaleInitPosition()) +
        " scaleInitFillQty=" + Util.IntMaxString(order.scaleInitFillQty()) +
        " scaleRandomPercent=" + order.scaleRandomPercent() +
        " hedgeType=" + order.getHedgeType() +
        " hedgeParam=" + order.hedgeParam() +
        " account=" + order.account() +
        " modelCode = " + order.modelCode() +
        " settlingFirm=" + order.settlingFirm() +
        " clearingAccount=" + order.clearingAccount() +
        " clearingIntent=" + order.clearingIntent() +
        " notHeld=" + order.notHeld() +
        " whatIf=" + order.whatIf() +
        " solicited=" + order.solicited() +
        " randomize size=" + order.randomizeSize() +
        " randomize price=" + order.randomizePrice();
        

        if ("BAG".equals(contract.getSecType())) {
        	if (contract.comboLegsDescrip() != null) {
        		msg += " comboLegsDescrip=" + contract.comboLegsDescrip();
        	}
        	
           	msg += " comboLegs={";
            if (contract.comboLegs() != null) {
            	for (int i = 0; i < contract.comboLegs().size(); ++i) {
            		ComboLeg comboLeg = contract.comboLegs().get(i);
            		msg += " leg " + (i+1) + ": "; 
            		msg += "conId=" +  comboLeg.conid();
            		msg += " ratio=" +  comboLeg.ratio();
            		msg += " action=" +  comboLeg.getAction();
            		msg += " exchange=" +  comboLeg.exchange();
            		msg += " openClose=" +  comboLeg.getOpenClose();
            		msg += " shortSaleSlot=" +  comboLeg.shortSaleSlot();
            		msg += " designatedLocation=" +  comboLeg.designatedLocation();
            		msg += " exemptCode=" +  comboLeg.exemptCode();
            		if (order.orderComboLegs() != null && contract.comboLegs().size() == order.orderComboLegs().size()) {
            			OrderComboLeg orderComboLeg = order.orderComboLegs().get(i);
            			msg += " price=" +  Util.DoubleMaxString(orderComboLeg.price());
            		}
            		msg += ";";
            	}
            }
           	msg += "}";
           	
        	if (order.basisPoints() != Double.MAX_VALUE) {
        		msg += " basisPoints=" + Util.DoubleMaxString(order.basisPoints());
        		msg += " basisPointsType=" + Util.IntMaxString(order.basisPointsType());
        	}
        }
        
    	if (contract.underComp() != null) {
    		DeltaNeutralContract underComp = contract.underComp();
    		msg +=
    			" underComp.conId =" + underComp.conid() +
    			" underComp.delta =" + underComp.delta() +
    			" underComp.price =" + underComp.price();
    	}
    	
        if (!Util.StringIsEmpty(order.getAlgoStrategy())) {
    		msg += " algoStrategy=" + order.getAlgoStrategy();
    		msg += " algoParams={";
    		if (order.algoParams() != null) {
    			ArrayList<TagValue> algoParams = order.algoParams();
    			for (int i = 0; i < algoParams.size(); ++i) {
    				TagValue param = algoParams.get(i);
    				if (i > 0) {
    					msg += ",";
    				}
    				msg += param.m_tag + "=" + param.m_value;
    			}
    		}
    		msg += "}";
    	}
    	
        if ("BAG".equals(contract.getSecType())) {
        	msg += " smartComboRoutingParams={";
        	if (order.smartComboRoutingParams() != null) {
        		ArrayList<TagValue> smartComboRoutingParams = order.smartComboRoutingParams();
        		for (int i = 0; i < smartComboRoutingParams.size(); ++i) {
        			TagValue param = smartComboRoutingParams.get(i);
        			if (i > 0) {
        				msg += ",";
        			}
        			msg += param.m_tag + "=" + param.m_value;
        		}
        	}
        	msg += "}";
        }
    
        String orderStateMsg =
        	" status=" + orderState.getStatus()
        	+ " initMargin=" + orderState.initMargin()
        	+ " maintMargin=" + orderState.maintMargin()
        	+ " equityWithLoan=" + orderState.equityWithLoan()
        	+ " commission=" + Util.DoubleMaxString(orderState.commission())
        	+ " minCommission=" + Util.DoubleMaxString(orderState.minCommission())
        	+ " maxCommission=" + Util.DoubleMaxString(orderState.maxCommission())
        	+ " commissionCurrency=" + orderState.commissionCurrency()
        	+ " warningText=" + orderState.warningText()
		;

        return msg + orderStateMsg;
    }
    
    static public String openOrderEnd() {
    	return " =============== end ===============";
    }
    
    static public String updateAccountValue(String key, String value, String currency, String accountName) {
    	return "updateAccountValue: " + key + " " + value + " " + currency + " " + accountName;
    }
    
    static public String updatePortfolio(Contract contract, int position, double marketPrice,
    									 double marketValue, double averageCost, double unrealizedPNL,
    									 double realizedPNL, String accountName) {
    	String msg = "updatePortfolio: "
    		+ contractMsg(contract)
    		+ position + " " + marketPrice + " " + marketValue + " " + averageCost + " " + unrealizedPNL + " " + realizedPNL + " " + accountName;
    	return msg;
    }
    
    static public String updateAccountTime(String timeStamp) {
    	return "updateAccountTime: " + timeStamp;
    }
    
    static public String accountDownloadEnd(String accountName) {
    	return "accountDownloadEnd: " + accountName;
    }
    
    static public String nextValidId( int orderId) {
    	return "Next Valid Order ID: " + orderId;
    }
    
    static public String contractDetails(int reqId, ContractDetails contractDetails) {
    	Contract contract = contractDetails.contract();
    	String msg = "reqId = " + reqId + " ===================================\n"
    		+ " ---- Contract Details begin ----\n"
    		+ contractMsg(contract) + contractDetailsMsg(contractDetails)
    		+ " ---- Contract Details End ----\n";
    	return msg;
    }
    
    private static String contractDetailsMsg(ContractDetails contractDetails) {
    	String msg = "marketName = " + contractDetails.marketName() + "\n"
        + "minTick = " + contractDetails.minTick() + "\n"
        + "price magnifier = " + contractDetails.priceMagnifier() + "\n"
        + "orderTypes = " + contractDetails.orderTypes() + "\n"
        + "validExchanges = " + contractDetails.validExchanges() + "\n"
        + "underConId = " + contractDetails.underConid() + "\n"
        + "longName = " + contractDetails.longName() + "\n"
        + "contractMonth = " + contractDetails.contractMonth() + "\n"
        + "industry = " + contractDetails.industry() + "\n"
        + "category = " + contractDetails.category() + "\n"
        + "subcategory = " + contractDetails.subcategory() + "\n"
        + "timeZoneId = " + contractDetails.timeZoneId() + "\n"
        + "tradingHours = " + contractDetails.tradingHours() + "\n"
        + "liquidHours = " + contractDetails.liquidHours() + "\n"
        + "evRule = " + contractDetails.evRule() + "\n"
        + "evMultiplier = " + contractDetails.evMultiplier() + "\n"
        + contractDetailsSecIdList(contractDetails);
    	return msg;
    }
    
	static public String contractMsg(Contract contract) {
    	String msg = "conid = " + contract.conid() + "\n"
        + "symbol = " + contract.symbol() + "\n"
        + "secType = " + contract.getSecType() + "\n"
        + "lastTradeDate = " + contract.lastTradeDateOrContractMonth() + "\n"
        + "strike = " + contract.strike() + "\n"
        + "right = " + contract.getRight() + "\n"
        + "multiplier = " + contract.multiplier() + "\n"
        + "exchange = " + contract.exchange() + "\n"
        + "primaryExch = " + contract.primaryExch() + "\n"
        + "currency = " + contract.currency() + "\n"
        + "localSymbol = " + contract.localSymbol() + "\n"
        + "tradingClass = " + contract.tradingClass() + "\n";
    	return msg;
    }
	
    static public String bondContractDetails(int reqId, ContractDetails contractDetails) {
        Contract contract = contractDetails.contract();
        String msg = "reqId = " + reqId + " ===================================\n"	
        + " ---- Bond Contract Details begin ----\n"
        + "symbol = " + contract.symbol() + "\n"
        + "secType = " + contract.getSecType() + "\n"
        + "cusip = " + contractDetails.cusip() + "\n"
        + "coupon = " + contractDetails.coupon() + "\n"
        + "maturity = " + contractDetails.maturity() + "\n"
        + "issueDate = " + contractDetails.issueDate() + "\n"
        + "ratings = " + contractDetails.ratings() + "\n"
        + "bondType = " + contractDetails.bondType() + "\n"
        + "couponType = " + contractDetails.couponType() + "\n"
        + "convertible = " + contractDetails.convertible() + "\n"
        + "callable = " + contractDetails.callable() + "\n"
        + "putable = " + contractDetails.putable() + "\n"
        + "descAppend = " + contractDetails.descAppend() + "\n"
        + "exchange = " + contract.exchange() + "\n"
        + "currency = " + contract.currency() + "\n"
        + "marketName = " + contractDetails.marketName() + "\n"
        + "tradingClass = " + contract.tradingClass() + "\n"
        + "conid = " + contract.conid() + "\n"
        + "minTick = " + contractDetails.minTick() + "\n"
        + "orderTypes = " + contractDetails.orderTypes() + "\n"
        + "validExchanges = " + contractDetails.validExchanges() + "\n"
        + "nextOptionDate = " + contractDetails.nextOptionDate() + "\n"
        + "nextOptionType = " + contractDetails.nextOptionType() + "\n"
        + "nextOptionPartial = " + contractDetails.nextOptionPartial() + "\n"
        + "notes = " + contractDetails.notes() + "\n"
        + "longName = " + contractDetails.longName() + "\n"
        + "evRule = " + contractDetails.evRule() + "\n"
        + "evMultiplier = " + contractDetails.evMultiplier() + "\n"
        + contractDetailsSecIdList(contractDetails)
        + " ---- Bond Contract Details End ----\n";
        return msg;
    }
    
    static public String contractDetailsSecIdList(ContractDetails contractDetails) {
        String msg = "secIdList={";
        if (contractDetails.secIdList() != null) {
            ArrayList<TagValue> secIdList = contractDetails.secIdList();
            for (int i = 0; i < secIdList.size(); ++i) {
                TagValue param = secIdList.get(i);
                if (i > 0) {
                    msg += ",";
                }
                msg += param.m_tag + "=" + param.m_value;
            }
        }
        msg += "}\n";
        return msg;
    }

    static public String contractDetailsEnd(int reqId) {
    	return "reqId = " + reqId + " =============== end ===============";
    }
    
    static public String execDetails( int reqId, Contract contract, Execution execution) {
        String msg = " ---- Execution Details begin ----\n"
        + "reqId = " + reqId + "\n"
        + "orderId = " + execution.orderId() + "\n"
        + "clientId = " + execution.clientId() + "\n"
        + contractMsg(contract)
        + "execId = " + execution.execId() + "\n"
        + "time = " + execution.time() + "\n"
        + "acctNumber = " + execution.acctNumber() + "\n"
        + "executionExchange = " + execution.exchange() + "\n"
        + "side = " + execution.side() + "\n"
        + "shares = " + execution.shares() + "\n"
        + "price = " + execution.price() + "\n"
        + "permId = " + execution.permId() + "\n"
        + "liquidation = " + execution.liquidation() + "\n"
        + "cumQty = " + execution.cumQty() + "\n"
        + "avgPrice = " + execution.avgPrice() + "\n"
        + "orderRef = " + execution.orderRef() + "\n"
        + "evRule = " + execution.evRule() + "\n"
        + "evMultiplier = " + execution.evMultiplier() + "\n"
        + "modelCode = " + execution.modelCode() + "\n"
        + " ---- Execution Details end ----\n";
        return msg;
    }
    
    static public String execDetailsEnd(int reqId) {
    	return "reqId = " + reqId + " =============== end ===============";
    }
    
    static public String updateMktDepth( int tickerId, int position, int operation, int side,
    									 double price, int size) {
    	return "updateMktDepth: " + tickerId + " " + position + " " + operation + " " + side + " " + price + " " + size;
    }
    
    static public String updateMktDepthL2( int tickerId, int position, String marketMaker,
    									   int operation, int side, double price, int size) {
    	return "updateMktDepth: " + tickerId + " " + position + " " + marketMaker + " " + operation + " " + side + " " + price + " " + size;
    }
    
    static public String updateNewsBulletin( int msgId, int msgType, String message, String origExchange) {
    	return "MsgId=" + msgId + " :: MsgType=" + msgType +  " :: Origin=" + origExchange + " :: Message=" + message;
    }
    
    static public String managedAccounts( String accountsList) {
    	return "Connected : The list of managed accounts are : [" + accountsList + "]";
    }
    
    static public String receiveFA(int faDataType, String xml) {
    	return FINANCIAL_ADVISOR + " " + EClient.faMsgTypeName(faDataType) + " " + xml;
    }
    
    static public String historicalData(int reqId, String date, double open, double high, double low,
                      					double close, int volume, int count, double WAP, boolean hasGaps) {
    	return "id=" + reqId +
        " date = " + date +
        " open=" + open +
        " high=" + high +
        " low=" + low +
        " close=" + close +
        " volume=" + volume +
        " count=" + count +
        " WAP=" + WAP +
        " hasGaps=" + hasGaps;
    }
	public static String realtimeBar(int reqId, long time, double open,
			double high, double low, double close, long volume, double wap, int count) {
        return "id=" + reqId +
        " time = " + time +
        " open=" + open +
        " high=" + high +
        " low=" + low +
        " close=" + close +
        " volume=" + volume +
        " count=" + count +
        " WAP=" + wap;
	}
	
    static public String scannerParameters(String xml) {
    	return SCANNER_PARAMETERS + "\n" + xml;
    }
    
    static public String scannerData(int reqId, int rank, ContractDetails contractDetails,
    								 String distance, String benchmark, String projection,
    								 String legsStr) {
        Contract contract = contractDetails.contract();
    	return "id = " + reqId +
        " rank=" + rank +
        " symbol=" + contract.symbol() +
        " secType=" + contract.getSecType() +
        " lastTradeDate=" + contract.lastTradeDateOrContractMonth() +
        " strike=" + contract.strike() +
        " right=" + contract.getRight() +
        " exchange=" + contract.exchange() +
        " currency=" + contract.currency() +
        " localSymbol=" + contract.localSymbol() +
        " marketName=" + contractDetails.marketName() +
        " tradingClass=" + contract.tradingClass() +
        " distance=" + distance +
        " benchmark=" + benchmark +
        " projection=" + projection +
        " legsStr=" + legsStr;
    }
    
    static public String scannerDataEnd(int reqId) {
    	return "id = " + reqId + " =============== end ===============";
    }
    
    static public String currentTime(long time) {
		return "current time = " + time +
		" (" + DateFormat.getDateTimeInstance().format(new Date(time * 1000)) + ")";
    }

    static public String fundamentalData(int reqId, String data) {
		return "id  = " + reqId + " len = " + data.length() + '\n' + data;
    }
    
    static public String deltaNeutralValidation(int reqId, DeltaNeutralContract underComp) {
    	return "id = " + reqId
    	+ " underComp.conId =" + underComp.conid()
    	+ " underComp.delta =" + underComp.delta()
    	+ " underComp.price =" + underComp.price();
    }
    static public String tickSnapshotEnd(int tickerId) {
    	return "id=" + tickerId + " =============== end ===============";
    }
    
    static public String marketDataType(int reqId, int marketDataType){
    	return "id=" + reqId + " marketDataType = " + MarketDataType.getField(marketDataType);
    }
    
    static public String commissionReport( CommissionReport commissionReport) {
        String msg = "commission report:" +
        " execId=" + commissionReport.m_execId +
        " commission=" + Util.DoubleMaxString(commissionReport.m_commission) +
        " currency=" + commissionReport.m_currency +
        " realizedPNL=" + Util.DoubleMaxString(commissionReport.m_realizedPNL) +
        " yield=" + Util.DoubleMaxString(commissionReport.m_yield) +
        " yieldRedemptionDate=" + Util.IntMaxString(commissionReport.m_yieldRedemptionDate);
        return msg;
    }
    
    static public String position( String account, Contract contract, double pos, double avgCost) {
        String msg = " ---- Position begin ----\n"
        + "account = " + account + "\n"
        + contractMsg(contract)
        + "position = " + Util.DoubleMaxString(pos) + "\n"
        + "avgCost = " + Util.DoubleMaxString(avgCost) + "\n"
        + " ---- Position end ----\n";
        return msg;
    }    

    static public String positionEnd() {
        return " =============== end ===============";
    }

    static public String accountSummary( int reqId, String account, String tag, String value, String currency) {
        String msg = " ---- Account Summary begin ----\n"
        + "reqId = " + reqId + "\n"
        + "account = " + account + "\n"
        + "tag = " + tag + "\n"
        + "value = " + value + "\n"
        + "currency = " + currency + "\n"
        + " ---- Account Summary end ----\n";
        return msg;
    }

    static public String accountSummaryEnd( int reqId) {
    	return "id=" + reqId + " =============== end ===============";
    }

    static public String positionMulti( int reqId, String account, String modelCode, Contract contract, double pos, double avgCost) {
        String msg = " ---- Position begin ----\n"
        + "id = " + reqId + "\n"
        + "account = " + account + "\n"
        + "modelCode = " + modelCode + "\n"
        + contractMsg(contract)
        + "position = " + Util.DoubleMaxString(pos) + "\n"
        + "avgCost = " + Util.DoubleMaxString(avgCost) + "\n"
        + " ---- Position end ----\n";
        return msg;
    }    

    static public String positionMultiEnd( int reqId) {
        return "id = " + reqId + " =============== end ===============";
    }

    static public String accountUpdateMulti( int reqId, String account, String modelCode, String key, String value, String currency) {
        String msg = " id = " + reqId + " account = " + account + " modelCode = " + modelCode + 
        		" key = " + key + " value = " + value + " currency = " + currency;
        return msg;
    }

    static public String accountUpdateMultiEnd( int reqId) {
    	return "id = " + reqId + " =============== end ===============";
    }    

	public static String securityDefinitionOptionalParameter(int reqId, String exchange, int underlyingConId, String tradingClass,
			String multiplier, Set<String> expirations, Set<Double> strikes) {
		String expirationsStr = "";
		
		for (String expiration : expirations) {
			expirationsStr += expiration + ", ";			
		}
		
		String strikesStr = "";
		
		for (Double strike : strikes) {
			strikesStr += strike + ", ";
		}
		
		String msg = " id = " + reqId + "exchange = " + exchange + " underlyingConId = " + underlyingConId + " tradingClass = " + tradingClass + " multiplier = " + 
			multiplier + " expirations: " + expirationsStr + " strikes: " + strikesStr;

		return msg;
	}

    public static String error( Exception ex) { return "Error - " + ex;}
    public static String error( String str) { return str;}

	public static String error(int id, int errorCode, String errorMsg) {
		String err = Integer.toString(id);
        err += " | ";
        err += Integer.toString(errorCode);
        err += " | ";
        err += errorMsg;
        return err;
	}

	public static String connectionClosed() {
		return "Connection Closed";
	}
}
