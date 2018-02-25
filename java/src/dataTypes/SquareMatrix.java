package dataTypes;

public class SquareMatrix extends Matrix {
	
	//constructors
	
	public SquareMatrix(int dim) {
		super(dim, dim);
	}
	
	public SquareMatrix(int dim, Double value) {
		super(dim, dim, value);
	}
	
	//matrix determinant
	//TODO determinant n >= 4
	public Double determinant() {
	    if (getCol() == 2)
	        return get(0,0) * get(1,1) - get(0,1) * get(1,0);

	    if (getCol() == 3) { //Sarrus rule
	        return 	get(0,0) * get(1,1) * get(2,2) +
	                get(0,1) * get(1,2) * get(2,0) +
	                get(0,2) * get(1,0) * get(2,1) -
	                get(0,2) * get(1,1) * get(2,0) -
	                get(0,1) * get(1,0) * get(2,2) -
	                get(0,0) * get(1,2) * get(2,1);
	    }   
	    return 0.0; //n x n?
	}
	
	//is matrix infTriangular?
	public boolean infTriangular() {
	    for (int i = 0; i < getRow(); i++)
	        for (int j = 0; j < getCol(); j++)
	            if ((i == j && get(i,i) != 1) || (i < j && get(i,j) != 0))
	                return false;
	    return true;
	}
	
	//is matrix supTriangular?
	public boolean supTriangular() {
	    for (int i = 0; i < getRow(); i++)
	        for (int j = 0; j < getCol(); j++)
	            if ((i == j && get(i,i) != 1) || (i > j && get(i,j) != 0))
	                return false;
	    return true;
	}
	
	//diagonal matrix?
	public boolean isDiagonal() {
	    for (int i = 0; i < getRow(); i++)
	        for (int j = 0; j < getCol(); i++)
	            if (i != j && get(i,j) != 0)
	                return false;
	    return true;
	}
}
