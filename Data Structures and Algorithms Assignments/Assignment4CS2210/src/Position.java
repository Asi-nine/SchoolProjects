/**
 * Position represents the x and y coordinates of a pixel.
 * 
 * @author Peter Valovcik
 * @version 1.0, 9/11/15
 */

public class Position {

	private int x; // x position

	private int y; // y position

	/**
	 * Creates a new Position with the specified x and y coordinates
	 * 
	 * @param x, position which represents the x coordinate of a pixel
	 * @param y, position which represents the y coordinate of a pixel
	 */

	public Position(int x, int y){
		this.x = x;
		this.y = y;
	}

	/**
	 * Gets the x coordinate
	 * 
	 * @return x, position which represents the x coordinate of a pixel
	 */

	public int getX(){
		return this.x;
	}

	/**
	 * Gets the y coordinate
	 * 
	 * @return y, position which represents the y coordinate of a pixel
	 */

	public int getY(){
		return this.y;
	}

	/**
	 * Compares an input position to the one the method is invoked on and determines
	 * which one is greater.
	 * 
	 * @return  1, when input position is less than position method is invoked on
	 * @return	0, when the positions are equal
	 * @return -1, when input position is greater than position method is invoked on
	 */

	public int compareTo(Position p){
		if (p.getY() < this.getY() || (p.getY() == this.getY() && p.getX() < this.getX())){
			return 1;
		} else if(p.getY() == this.getY() && p.getX() == this.getX()){
			return 0;
		}else {
			return -1;
		}
	}

}
