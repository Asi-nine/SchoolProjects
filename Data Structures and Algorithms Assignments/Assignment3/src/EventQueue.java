public class EventQueue {
final int impossibleNumItemsValue=-1;

QueueADT<Event> eventQueue;

// Constructor
public EventQueue() {
eventQueue=new LinkedQueue<Event>();
}

/////////////////////////////////////////////////////////////////
// Insert events one at a time in sorted order on eventTime
/////////////////////////////////////////////////////////////////
public void insertEvent(Event insertEvent,boolean debug) {
String s;

if(debug)
   {
   System.out.format("\nINSERT EVENT:\nEvent time: %7.2f Event type: %s",
                      insertEvent.getEventTime(),insertEvent.getEventType());
   if(insertEvent.getEventNumItems()!=impossibleNumItemsValue)
     System.out.format(" Event number of items: %d",insertEvent.getEventNumItems());
   System.out.format("\n");
  }

if(debug)
{
System.out.println("\nEvent Queue before new event enqueued");
System.out.println("-------------------------------------");
s=eventQueue.toString();

if(!s.equals(""))
System.out.println(s);
else
System.out.println("Empty Queue");

System.out.println("\n");
}

// Insert your code here to do the insertion
double comparisonNumber = insertEvent.getEventTime();
LinkedQueue<Event> tempQueue = new LinkedQueue<Event>();

if (eventQueue.isEmpty()){
	eventQueue.enqueue(insertEvent);
}
else{
	int queueSize = eventQueue.size();
	for (int i = 0; i < queueSize; i++){
		Event tempEvent = eventQueue.dequeue();
		if (tempEvent.getEventTime() < comparisonNumber){
			tempQueue.enqueue(tempEvent);
		}
		if (tempEvent.getEventTime() >= comparisonNumber){
			tempQueue.enqueue(insertEvent);
			tempQueue.enqueue(tempEvent);
			for (int j = i+1; j < queueSize; j++, i++){
				Event tempEventTwo = eventQueue.dequeue();
				tempQueue.enqueue(tempEventTwo);
			}
		}
	}
	if(queueSize == tempQueue.size()){
		tempQueue.enqueue(insertEvent);
	}
	eventQueue = tempQueue;
}

if(debug)
{
System.out.println("\nEvent Queue after new event enqueued");
System.out.println("------------------------------------");
s=eventQueue.toString();

if(!s.equals(""))
System.out.println(s);
else
System.out.println("Empty Queue");

System.out.println("\n");
}
}

/////////////////////////////////////////////////////////////////////////
// Delete all events from order queue whose eventTime >= minAllDoneTime
/////////////////////////////////////////////////////////////////////////
public void deleteEvents(double minAllDoneTime,boolean debug) {
// this method assumes that the queue is already sorted
// We dequeue events from eventQueue until the eventTime >= minAllDoneTime
// and enqueue them in backwards order in tempQueue.
// The first ALL_DONE event whose eventTime is
// equal to minAllDoneTime is enqueued in tempQueue as well.
// The eventQueue is then emptied and lastly tempQueue is copied back into
// now empty eventQueue in correct sorted order.

String s;

if(debug)
{
System.out.println("\nEvent Queue before all events with eventTime >" + 
                      minAllDoneTime + " deleted");
System.out.println("------------------------------------------------------");
s=eventQueue.toString();

if(!s.equals(""))
System.out.println(s);
else
System.out.println("Empty Queue");

System.out.println("\n");
}

// Insert your code here to do the deletion
LinkedQueue<Event> tempQueue = new LinkedQueue<Event>();
LinkedQueue<Event> testQueue = new LinkedQueue<Event>();
int eventQueueSize = eventQueue.size();

for (int i = 0; i < eventQueueSize; i++){
	Event tempEvent = eventQueue.dequeue();
	if (tempEvent.getEventType().equals("ALL_DONE") && tempEvent.getEventTime() <= minAllDoneTime){
	
		tempQueue.enqueue(tempEvent);
		testQueue.enqueue(tempEvent);
		for (int j = i+1; j < eventQueueSize; j++, i++){
			eventQueue.dequeue();
		}

	}
	else{
		tempQueue.enqueue(tempEvent);
		testQueue.enqueue(tempEvent);
	}
}




int tempQueueSize = tempQueue.size();
for(int i = 0; i < tempQueueSize; i++){
	eventQueue.enqueue(tempQueue.dequeue());
}

int numAllDone = 0;
Event test;
int testQueueSize = testQueue.size();
for (int i = 0; i < testQueueSize; i++){
	test = testQueue.dequeue();
	if(test.getEventType().equals("ALL_DONE")){
		numAllDone = numAllDone + 1;
	}
}

if (numAllDone < 1){
	System.err.println("WARNING: THERE ARE NO ALL_DONE EVENTS PRESENT IN THE DATA.");
}


if(debug)
{
System.out.println("\nEvent Queue after all events with eventTime >" + 
                      minAllDoneTime + " deleted");
System.out.println("-----------------------------------------------------");
s=eventQueue.toString();

if(!s.equals(""))
System.out.println(s);
else
System.out.println("Empty Queue");

System.out.println("\n");
}

}

}
