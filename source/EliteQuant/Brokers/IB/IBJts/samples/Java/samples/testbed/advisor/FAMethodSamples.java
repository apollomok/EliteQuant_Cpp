package samples.testbed.advisor;

public class FAMethodSamples {
	
	//! [faonegroup]
	public static String FaOneGroup = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            + "<ListOfGroups>"
            + "<Group>"
                + "<name>Equal_Quantity</name>"
                + "<ListOfAccts varName=\"list\">"
                    //Replace with your own accountIds
                    + "<String>DU119915</String>"
                    + "<String>DU119916</String>"
                + "</ListOfAccts>"
                + "<defaultMethod>EqualQuantity</defaultMethod>"
            + "</Group>"
        + "</ListOfGroups>";
	//! [faonegroup]
	
	//! [fatwogroups]
    public static String FaTwoGroups = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            +"<ListOfGroups>"
            + "<Group>"
                + "<name>Equal_Quantity</name>"
                + "<ListOfAccts varName=\"list\">"
                    //Replace with your own accountIds
                    + "<String>DU119915</String>"
                    + "<String>DU119916</String>"
                + "</ListOfAccts>"
                + "<defaultMethod>EqualQuantity</defaultMethod>"
            + "</Group>"
            + "<Group>"
                + "<name>Pct_Change</name>"
                + "<ListOfAccts varName=\"list\">"
                    //Replace with your own accountIds
                    + "<String>DU119915</String>"
                    + "<String>DU119916</String>"
                + "</ListOfAccts>"
                + "<defaultMethod>PctChange</defaultMethod>"
            + "</Group>"
        + "</ListOfGroups>";
    //! [fatwogroups]
    
  //! [faoneprofile]
    public static String FaOneProfile = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            + "<ListOfAllocationProfiles>"
            + "<AllocationProfile>"
                + "<name>Percent_60_40</name>"
                + "<type>1</type>"
                + "<ListOfAllocations varName=\"listOfAllocations\">"
                    + "<Allocation>"
                        //Replace with your own accountIds
                        + "<acct>DU119915</acct>"
                        + "<amount>60.0</amount>"
                    + "</Allocation>"
                    + "<Allocation>"
                        //Replace with your own accountIds
                        + "<acct>DU119916</acct>"
                        + "<amount>40.0</amount>"
                    + "</Allocation>"
                + "</ListOfAllocations>"
            + "</AllocationProfile>"
        + "</ListOfAllocationProfiles>";
    //! [faoneprofile]
    
    //! [fatwoprofiles]
    public static String FaTwoProfiles = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
            + "<ListOfAllocationProfiles>"
            + "<AllocationProfile>"
                + "<name>Percent_60_40</name>"
                + "<type>1</type>"
                + "<ListOfAllocations varName=\"listOfAllocations\">"
                    + "<Allocation>"
                        //Replace with your own accountIds
                        + "<acct>DU119915</acct>"
                        + "<amount>60.0</amount>"
                    + "</Allocation>"
                    + "<Allocation>"
                        //Replace with your own accountIds
                        + "<acct>DU119916</acct>"
                        + "<amount>40.0</amount>"
                    + "</Allocation>"
                + "</ListOfAllocations>"
            + "</AllocationProfile>"
            + "<AllocationProfile>"
                + "<name>Ratios_2_1</name>"
                + "<type>1</type>"
                + "<ListOfAllocations varName=\"listOfAllocations\">"
                    + "<Allocation>"
                        //Replace with your own accountIds
                        + "<acct>DU119915</acct>"
                        + "<amount>2.0</amount>"
                    + "</Allocation>"
                    + "<Allocation>"
                        //Replace with your own accountIds
                        + "<acct>DU119916</acct>"
                        + "<amount>1.0</amount>"
                    + "</Allocation>"
                + "</ListOfAllocations>"
            + "</AllocationProfile>"
        + "</ListOfAllocationProfiles>";
    //! [fatwoprofiles]
    
}
