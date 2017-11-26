package samples.testbed.scanner;

import com.ib.client.ScannerSubscription;

public class ScannerSubscriptionSamples {
	
	public static ScannerSubscription HotUSStkByVolume() {
		
		//! [hotusvolume]
        //Hot US stocks by volume
		ScannerSubscription scanSub = new ScannerSubscription();
		scanSub.instrument("STK");
		scanSub.locationCode("STK.US.MAJOR");
		scanSub.scanCode("HOT_BY_VOLUME");
		//! [hotusvolume]
        return scanSub;
		
	}
	
	public static ScannerSubscription TopPercentGainersIbis() {
		
		//! [toppercentgaineribis]
        //Top % gainers at IBIS
        ScannerSubscription scanSub = new ScannerSubscription();
        scanSub.instrument("STOCK.EU");
        scanSub.locationCode("STK.EU.IBIS");
        scanSub.scanCode("TOP_PERC_GAIN");
      //! [toppercentgaineribis]
        return scanSub;
		
	}
	
	public static ScannerSubscription MostActiveFutSoffex()
    {
        //! [mostactivefutsoffex]
        //Most active futures at SOFFEX
        ScannerSubscription scanSub = new ScannerSubscription();
        scanSub.instrument("FUT.EU");
        scanSub.locationCode("FUT.EU.SOFFEX");
        scanSub.scanCode("MOST_ACTIVE");
        //! [mostactivefutsoffex]
        return scanSub;
    }
	
	public static ScannerSubscription HighOptVolumePCRatioUSIndexes() {
		
		//! [highoptvolume]
        //High option volume P/C ratio US indexes
        ScannerSubscription scanSub = new ScannerSubscription();
        scanSub.instrument("IND.US");
        scanSub.locationCode("IND.US");
        scanSub.scanCode("HIGH_OPT_VOLUME_PUT_CALL_RATIO");
        //! [highoptvolume]
        return scanSub;
		
	}

}
