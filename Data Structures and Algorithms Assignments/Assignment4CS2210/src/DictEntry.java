/**
 * DictEntry represents a data entry into the BST containing the position and color.
 * The position is used as a key.
 * 
 * @author Peter Valovcik
 * @version 1.0, 9/11/15
 */

public class DictEntry {

	private Position pos; // represents an (x, y) position of a pixel
	private int color; // represents a color of a pixel

	/**
	 * Creates a new DictEntry with the specified data for Position and color
	 * 
	 * @param p, position which represents (x,y) of a pixel; also used as a key
	 * @param color, int representing the color of a pixel
	 */

	public DictEntry(Position p, int color){	
		this.pos = p;
		this.color = color;
	}

	/**
	 * Returns the position of the DictEntry
	 * 
	 * @return pos, the position which represent (x,y) of a pixel; also used as a key
	 */

	public Position getPosition(){
		return this.pos;
	}

	/**
	 * Returns the color of the DictEntry
	 *
	 * @return color, int representing the color of a pixel
	 */

	public int getColor(){
		return this.color;
	}	
}