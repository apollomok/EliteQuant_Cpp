package samples.testbed.orders;

import java.util.ArrayList;

import com.ib.client.Order;
import com.ib.client.TagValue;

public class AvailableAlgoParams {
	
	//! [arrivalpx_params]
	public static void FillArrivalPriceParams(Order baseOrder, double maxPctVol, String riskAversion, String startTime, String endTime, boolean forceCompletion, boolean allowPastTime) {
		
		baseOrder.algoStrategy("ArrivalPx");
		baseOrder.algoParams(new ArrayList<TagValue>());
		baseOrder.algoParams().add(new TagValue("maxPctVol", String.valueOf(maxPctVol)));
		baseOrder.algoParams().add(new TagValue("riskAversion", riskAversion));
		baseOrder.algoParams().add(new TagValue("startTime", startTime));
		baseOrder.algoParams().add(new TagValue("endTime", endTime));
		baseOrder.algoParams().add(new TagValue("forceCompletion", forceCompletion ? "1" : "0"));
		baseOrder.algoParams().add(new TagValue("allowPastEndTime", allowPastTime ? "1" : "0"));
		
	}
	//! [arrivalpx_params]
	
	//! [darkice_params]
	public static void FillDarkIceParams(Order baseOrder, int displaySize, String startTime, String endTime, boolean allowPastEndTime) {
		
		baseOrder.algoStrategy("DarkIce");
		baseOrder.algoParams(new ArrayList<TagValue>());
		baseOrder.algoParams().add(new TagValue("displaySize", String.valueOf(displaySize)));
		baseOrder.algoParams().add(new TagValue("startTime", startTime));
		baseOrder.algoParams().add(new TagValue("endTime", endTime));
		baseOrder.algoParams().add(new TagValue("allowPastEndTime", allowPastEndTime ? "1" : "0"));
		
	}
	//! [darkice_params]
	
	//! [pctvol_params]
	public static void FillPctVolParams(Order baseOrder, double pctVol, String startTime, String endTime, boolean noTakeLiq) {
		
		baseOrder.algoStrategy("PctVol");
		baseOrder.algoParams(new ArrayList<TagValue>());
		baseOrder.algoParams().add(new TagValue("pctVol", String.valueOf(pctVol)));
		baseOrder.algoParams().add(new TagValue("startTime", startTime));
		baseOrder.algoParams().add(new TagValue("endTime", endTime));
		baseOrder.algoParams().add(new TagValue("noTakeLiq", noTakeLiq ? "1" : "0"));
		
	}
	//! [pctvol_params]
	
	//! [twap_params]
	public static void FillTwapParams(Order baseOrder, String strategyType, String startTime, String endTime, boolean allowPastEndTime) {
		
		baseOrder.algoStrategy("Twap");
		baseOrder.algoParams(new ArrayList<TagValue>());
		baseOrder.algoParams().add(new TagValue("strategyType", strategyType));
		baseOrder.algoParams().add(new TagValue("startTime", startTime));
		baseOrder.algoParams().add(new TagValue("endTime", endTime));
		baseOrder.algoParams().add(new TagValue("allowPastEndTime", allowPastEndTime ? "1" : "0"));
		
	}
	//! [twap_params]
	
	//! [vwap_params]
	public static void FillVwapParams(Order baseOrder, double maxPctVol, String startTime, String endTime, boolean allowPastEndTime, boolean noTakeLiq) {
		
		baseOrder.algoStrategy("Vwap");
		baseOrder.algoParams(new ArrayList<TagValue>());
		baseOrder.algoParams().add(new TagValue("maxPctVol", String.valueOf(maxPctVol)));
		baseOrder.algoParams().add(new TagValue("startTime", startTime));
		baseOrder.algoParams().add(new TagValue("endTime", endTime));
		baseOrder.algoParams().add(new TagValue("allowPastEndTime", allowPastEndTime ? "1" : "0"));
		baseOrder.algoParams().add(new TagValue("noTakeLiq", noTakeLiq ? "1" : "0"));
		
	}
	//! [vwap_params]
	
	//! [ad_params]
	public static void FillAccumulateDistributeParams(Order baseOrder, int componentSize, int timeBetweenOrders, boolean randomizeTime20, boolean randomizeSize55,
            int giveUp, boolean catchUp, boolean waitOrFill, String startTime, String endTime) {
		
		baseOrder.algoStrategy("AD");
		baseOrder.algoParams(new ArrayList<TagValue>());
		baseOrder.algoParams().add(new TagValue("componentSize", String.valueOf(componentSize)));
		baseOrder.algoParams().add(new TagValue("timeBetweenOrders", String.valueOf(timeBetweenOrders)));
		baseOrder.algoParams().add(new TagValue("randomizeTime20", randomizeTime20 ? "1" : "0"));
		baseOrder.algoParams().add(new TagValue("randomizeSize55", randomizeSize55 ? "1" : "0"));
		baseOrder.algoParams().add(new TagValue("giveUp", String.valueOf(giveUp)));
		baseOrder.algoParams().add(new TagValue("catchUp", catchUp ? "1" : "0"));
		baseOrder.algoParams().add(new TagValue("waitOrFill", waitOrFill ? "1" : "0"));
		baseOrder.algoParams().add(new TagValue("startTime", startTime));
		baseOrder.algoParams().add(new TagValue("endTime", endTime));
		
	}
	//! [ad_params]
	
	//! [balanceimpactrisk_params]
	public static void FillBalanceImpactRiskParams(Order baseOrder, double maxPctVol, String riskAversion, boolean forceCompletion) {
		
		baseOrder.algoStrategy("BalanceImpactRisk");
		baseOrder.algoParams(new ArrayList<TagValue>());
		baseOrder.algoParams().add(new TagValue("maxPctVol", String.valueOf(maxPctVol)));
		baseOrder.algoParams().add(new TagValue("riskAversion", riskAversion));
		baseOrder.algoParams().add(new TagValue("forceCompletion", forceCompletion ? "1" : "0"));
		
	}
	//! [balanceimpactrisk_params]
	
	//! [minimpact_params]
	public static void FillMinImpactParams(Order baseOrder, double maxPctVol) {
		
		baseOrder.algoStrategy("BalanceImpactRisk");
		baseOrder.algoParams(new ArrayList<TagValue>());
		baseOrder.algoParams().add(new TagValue("maxPctVol", String.valueOf(maxPctVol)));
		
	}
	//! [minimpact_params]
	
	//! [adaptive_params]
	public static void FillAdaptiveParams(Order baseOrder, String priority) {

		baseOrder.algoStrategy("Adaptive");
		baseOrder.algoParams(new ArrayList<TagValue>());
		baseOrder.algoParams().add(new TagValue("adaptivePriority", priority));

	}
	//! [adaptive_params]	
}
