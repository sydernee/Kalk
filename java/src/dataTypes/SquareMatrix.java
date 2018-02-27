package dataTypes;

public class SquareMatrix extends Matrix {
	
	//constructors
	
	public SquareMatrix(int dim) throws NegativeArraySizeException {
		super(dim, dim);
	}
	
	public SquareMatrix(int dim, Double value) throws NegativeArraySizeException {
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
	    
	    Double cumulator = 0.0;
	    for (int i = 0; i < getRow(); i++) {
	    	//a00 * c00 * getMinor(0,0).determinant() +
	    	//a01 * c01 * getMinor(0,1).determinant() +
	    	//a02 * c02 * getMinor(0,2).determinant() +
	    	//a03 * c03 * getMinor(0,3).determinant() +
	    	//a04 * c04 * getMinor(0,4).determinant()
	    	if (get(0,i) != 0.0)
	    		cumulator += get(0,i) * ((i % 2 == 0) ? 1 : -1) * getMinor(0,i).determinant();
	    }
	    
	    return cumulator; //TODO n x n?
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
	
	public SquareMatrix getMinor(int i, int j) throws NegativeArraySizeException, IndexOutOfBoundsException {
		if (i < 0 || j < 0)
			throw new NegativeArraySizeException("getMinor() method: invalid matrix indexes.");
		
		if (i >= getRow() || j >= getRow())
			throw new IndexOutOfBoundsException("getMinor() method: out of bound matrix indexes.");
		
		
		SquareMatrix res = new SquareMatrix(getRow()-1); //SquareMatrix da restituire
		int rowSkipFlag = 0;
		int colSkipFlag = 0;
		
		for (int k = 0; k < getRow(); k++) {
			if (k == i)
				rowSkipFlag = 1;
			else
				for (int l = 0; l < getCol(); l++) {
					if (l == j)
						colSkipFlag = 1;
					else
						res.set(k-rowSkipFlag, l-colSkipFlag, get(k,l));
				}
			colSkipFlag = 0;
		}
		return res;
	}
}
