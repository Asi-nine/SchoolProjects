import java.util.*;
import java.io.*;

public class Main {

////////////////////////////////////////////////////////////////////
// main method
////////////////////////////////////////////////////////////////////
public static void main(String[] args) {

EventQueue eventQueue=new EventQueue();
Event event;

// Java constant holding the largest positive 
// finite value of type double
double minAllDoneTime=Double.MAX_VALUE;

double eventTime;
String eventType;
String junk;
int eventNumItems;
final int impossibleNumItemsValue=-1;
boolean debug=true;

StringTokenizer tokenizer;
int ct=0;


InStringFile eventFileReader=new InStringFile(args[0]);

do {
ct++;
String fileLine = eventFileReader.read();
// read token "Time:" first
tokenizer=new StringTokenizer(fileLine);
junk=tokenizer.nextToken();
eventTime=Double.parseDouble(tokenizer.nextToken());
// read "Type:" first
junk=tokenizer.nextToken();
// read eventType as string
eventType=tokenizer.nextToken();

if(!(eventType.equals("SNAPSHOT") || eventType.equals("ALL_DONE")))
    {
    // read "Num:" first
    junk=tokenizer.nextToken();
    // read eventNumItems as integer
    eventNumItems=Integer.parseInt(tokenizer.nextToken());
    }
else
    {
    eventNumItems=impossibleNumItemsValue;
    }
if(eventType.equals("ALL_DONE")) 
   if(minAllDoneTime > eventTime) minAllDoneTime=eventTime;

if(eventNumItems!=impossibleNumItemsValue)
  System.out.format("%3d  Time: %7.2f Type: %-12s Number of items: %d\n",
                      ct,eventTime,eventType,eventNumItems);
else
  System.out.format("%3d  Time: %7.2f Type: %-12s\n",ct,eventTime,eventType);

event=new Event(eventTime,eventType,eventNumItems);
eventQueue.insertEvent(event,debug);

} while (!eventFileReader.endOfFile());

System.out.println("\n" + ct + 
                   " events read and inserted in order in the eventQueue");

eventQueue.deleteEvents(minAllDoneTime,debug);
}

}
