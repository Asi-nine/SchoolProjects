import java.text.*;
import java.lang.*;
import java.lang.Math;
import java.lang.Double;

public class Service {
// ignoired here
private final int arrivalStream=1; // customer interarrival times
private final int itemsStream=2;   // number of items purchased
private final int counterStream=3; // number of an empty counter


// The interarrival time of the next customer is
// exponentially disttributed
public static double getInterArrivalTime(double arrivalRate) {
final double secondsInHour=3600.0;
double r=Math.random();
// log is natural log
return(doubleFormat(-secondsInHour/arrivalRate*Math.log(r)));
}

// The number of items purchased is geometrically 
// distributed with meanItems (20 usually)
public static int getNumItems(int meanItems) {
double r=Math.random();
return((int) (Math.ceil(Math.log(r)/(Math.log(1.0-1.0/meanItems)))));
}

// get a random counter number number within the range [low:high]
public static int getCounterNumber(int low,int high) {
double r;
int counterNum;
// Robust code:
// Math.min(low,high) is definitely the lowest
// Math.max(low,high) is definitely the highest
do 
  {
  r=Math.random();
  r=((double) (Math.max(low,high)))*r;
  counterNum=(int) (Math.ceil(r));
  } 
while(!(counterNum >= Math.min(low,high))); // until counterNum >= lowest
return counterNum;
}

public static double doubleFormat(double d)
{
// Convert double d to a formatted string, 
// then parse that string as a double 
DecimalFormat myFormatter = new DecimalFormat("######0.00");
String stg = myFormatter.format(d);
double x = Double.parseDouble(stg);
return(x);
}

// currently this method unused
public static int random_int(int Min, int Max) {
return (int) (Math.random()*(Math.max(Min,Max)-Math.min(Min,Max))+
              Math.min(Min,Max));
}

// currently this method unused
public static double randomWithRange(double min, double max) {
   double range = Math.abs(Math.max(min,max) - Math.min(min,max));     
   return (Math.random() * range) + (min <= max ? min : max);
}

// currently this method unused
public static int randomWithRange(int min, int max) {
   int range = Math.abs(Math.max(min,max) - Math.min(min,max)) + 1;     
   return (int)(Math.random() * range) + (min <= max ? min : max);
}

}
