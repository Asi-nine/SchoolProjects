public class Event {

private String eventType;
private double eventTime;
private int eventNumItems;
private final int impossibleNumItemsValue=-1;

// Constructor
public Event(double time,String type,int numItems) {
eventType=type;
eventTime=time;
eventNumItems=numItems;
}

// getters and setters

public String getEventType() {
return(eventType);
}

public double getEventTime() {
return(eventTime);
}

public int getEventNumItems() {
return(eventNumItems);
}

public void setEventType(String type) {
eventType=type;
}

public void setEventTime(double time) {
eventTime=time;
}

public void setEventNumItems(int NumItems) {
eventNumItems=NumItems;
}

public String toString() {
String s;
if(eventNumItems!=impossibleNumItemsValue)
s="Time: " + Service.doubleFormat(eventTime) + " Type: " + eventType + 
  " Number of items: " + eventNumItems;
else
s="Time: " + Service.doubleFormat(eventTime) + " Type: " + eventType +
  " Number of items not specified"; 
return(s);
}

}
