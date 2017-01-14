
public class LinkedQueue<T> implements QueueADT<T> {

	//makes our size() operation much more efficient O(1) rather than O(n)
	private int count;
	private LinearNode<T> front, rear;


	public LinkedQueue(){
		count=0;
		front=rear=null;
	}

	public void enqueue (T element){
		//to create the new node to add to our linked list
		LinearNode<T> newNode = new LinearNode<T>(element);

		//if there isn't an element yet both the front  (and later rear)
		// will reference this first element
		if( this.isEmpty() ){
			front = newNode;	
		}
		else{
			//we want to add to the end, so we put the new linear node after
			// the one that is currently the rear (this is about to change)
			rear.setNext(newNode);
		}

		//add the new node to the rear
		//   update the rear reference to be the new node at the end of the linked list
		rear = newNode;
		//update the count of nodes in the linked list
		count++;

	}

	public T dequeue() throws EmptyCollectionException {
		if (this.isEmpty()){
			// a throw is like a return - it will exit the method immediately
			//   however, there is no return value 
			throw new EmptyCollectionException ("Queue is empty");
		}
		// get the element from the first linear node to return to the calling context
		T result = front.getElement();

		//update the front to be the one following the current front
		//   this essentially removes the linear node, since it will now be garbage collected
		//   -->it definitely removes it from our list
		front = front.getNext();
		//reduce count
		count--;

		//checking if we removed the last node in the list
		//  if so, make sure to update rear (we already made front null above)
		if( this.isEmpty()){
			rear = null;
		}

		return result;
	}

	public boolean isEmpty(){
		return count==0;
	}

	public int size(){
		return count;
	}

}
