/**
 * Figure implementing FigureADT.
 * This class represents a 2-D picture (figure) that is composed of many pixels of various colors to
 * be used in a game. The figure can be player controlled, AI controlled, a target for the player to
 * gather, or a static "wall-like" figure. Figures cannot overlap and have collision detection.
 * 
 * @author Peter Valovcik
 * @version 1.0, 19/11/15
 */

public class Figure implements FigureADT {

	private int id;						// identifier
	private int width;					// width of the figure
	private int height;					// height of the figure
	private int type;					// type of figure (fixed, user, computer, target)
	private Position pos;				// offset of figure's position
	private BinarySearchTree tree;		// tree holding the figure's pixels' data (positions and colors)

	/**
	 * creates a figure containing all parameters
	 * 
	 * @param id, identifier
	 * @param width, width of the figure
	 * @param height, height of the figure
	 * @param type, type of figure (fixed, user, computer, target)
	 * @param pos, offset of figure's position
	 */

	public Figure(int id, int width, int height, int type, Position pos){
		this.id = id;
		this.width = width;
		this.height = height;
		this.type = type;
		this.pos = pos;
		this.tree = new BinarySearchTree();
	}

	/**
	 * sets the type of the figure
	 * 
	 * @param t, type of figure
	 */

	public void setType(int t) {
		this.type = t;

	}

	/**
	 * gets the width of the figure
	 * 
	 * @return width, the width of the figure
	 */

	public int getWidth() {

		return this.width;
	}

	/**
	 * gets the height of the figure
	 * 
	 * @return height, the height of the figure
	 */

	public int getHeight() {

		return this.height;
	}

	/**
	 * gets the type of the figure
	 * 
	 * @return type, the int representing the type of the figure
	 */

	public int getType() {

		return this.type;
	}

	/**
	 * gets the id of the figure
	 * 
	 * @return id, the id of the figure
	 */

	public int getId() {

		return this.id;
	}

	/**
	 * gets the offset of the figure
	 * 
	 * @return pos, the Position representing offset of the figure
	 */

	public Position getOffset() {
		return this.pos;
	}

	/**
	 * gets the BST holding data of the figure
	 * 
	 * @return tree, the BST holding data of the figure
	 */

	private BinarySearchTree getBST(){
		return this.tree;
	}

	/**
	 * sets the offset of the figure
	 * 
	 * @param value, the amount to set the figure offset to
	 */

	public void setOffset(Position value) {
		this.pos = value;
	}

	/**
	 * Stores a pixel of the figure in the figure's BST as a position and color
	 * 
	 * @param x, int representing an x coordinate
	 * @param y, int representing a y coordinate
	 * @param rgb, int representing the color
	 */

	public void addPixel(int x, int y, int rgb) throws BSTException {
		Position posi = new Position(x, y);
		DictEntry entry = new DictEntry(posi, rgb);
		this.tree.insert(entry);
	}

	/**
	 * Determines if two figures intersect, first by checking if the boxes that contain them
	 * intersect, and then performing pixel by pixel analysis if the boxes do.
	 * 
	 * @return boolean, true if intersection occurs, false if it does not
	 */

	public boolean intersects(Figure fig) {
		//  both if statements check to make sure that the corners are not overlapping ( box overlap check )
		if (this.pos.getX() + this.getWidth() < fig.pos.getX() || this.pos.getX() > fig.pos.getX() + fig.getWidth()){
			return false;
		}
		if (this.pos.getY() + this.getHeight() < fig.pos.getY() || this.pos.getY() > fig.pos.getY() + fig.getHeight()){
			return false;
		}
		
		// get the smallest from one of the figures trees and modify it with the offsets
		Position compare = fig.getBST().smallest().getPosition();
		Position track = compare; // keeps track of pixel
		int x1 = compare.getX() + fig.getOffset().getX() - this.getOffset().getX();
		int y1 = compare.getY() + fig.getOffset().getY() - this.getOffset().getY();
		compare = new Position(x1, y1);
		if(this.tree.find(compare) != null){
			return true;
		}

		// loop until either every pixel was searched for in the other tree or a pixel was found
		// to exist in both trees meaning a collision occurs
		while(this.tree.find(compare) == null && fig.getBST().successor(track) != null){	
			compare = fig.getBST().successor(track).getPosition();
			track = compare;
			x1 = compare.getX() + fig.getOffset().getX() - this.getOffset().getX();
			y1 = compare.getY() + fig.getOffset().getY() - this.getOffset().getY();
			compare = new Position(x1, y1);
			if(this.tree.find(compare) != null){
				return true;
			}
		}
		return false;
	}

}
