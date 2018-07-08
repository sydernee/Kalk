package dataTypes;

import kalkException.InvalidMatrixIndex;
import kalkException.TooFewArgumentsException;
import kalkException.TooManyArgumentsException;

public class SquareMatrix extends Matrix {
	//constructors
	
	public SquareMatrix(int dim) throws NegativeArraySizeException {
		super(dim, dim);
	}
	
	public SquareMatrix(int dim, Double value) throws NegativeArraySizeException {
		super(dim, dim, value);
	}
	
	public SquareMatrix(int dim, double... numbers)
		throws 	NegativeArraySizeException,
				TooFewArgumentsException, 
				TooManyArgumentsException
	{
		super(dim, dim, numbers);
	}
	
	//Matrix determinant
	public Double determinant() {
		if (getCols() == 1)
			return get(0,0);
		
	    if (getCols() == 2)
	        return get(0,0) * get(1,1) - get(0,1) * get(1,0);

	    if (getCols() == 3) { //Sarrus rule
	        return 	get(0,0) * get(1,1) * get(2,2) +
	                get(0,1) * get(1,2) * get(2,0) +
	                get(0,2) * get(1,0) * get(2,1) -
	                get(0,2) * get(1,1) * get(2,0) -
	                get(0,1) * get(1,0) * get(2,2) -
	                get(0,0) * get(1,2) * get(2,1);
	    }
	    
	    Double cumulator = 0.0;
	    for (int i = 0; i < getRows(); i++) {
	    	if (get(0,i) != 0.0)
	    		cumulator += get(0,i) * ((i % 2 == 0) ? 1 : -1) * getMinor(0,i).determinant();
	    }
	    
	    return cumulator;
	}
	
	//is matrix infTriangular?
	public boolean infTriangular() {
	    for (int i = 0; i < getRows(); i++)
	        for (int j = i+1; j < getCols(); j++)
	            if ((i < j && get(i,j) != 0))
	                return false;
	    return true;
	}
	
	//is matrix supTriangular?
	public boolean supTriangular() {
	    for (int i = 0; i < getRows(); i++)
	        for (int j = 0; j < i; j++)
	            if (/*(i == j && get(i,i) == 0) || */(i > j && get(i,j) != 0))
	                return false;
	    return true;
	}
	
	//diagonal matrix?
	public boolean isDiagonal() {
	    for (int i = 0; i < getRows(); i++)
	        for (int j = 0; j < getCols(); j++)
	            if (i != j && get(i,j) != 0)
	                return false;
	    return true;
	}
	
	//operations 
	
	@Override
	public SquareMatrix add(Matrix mat) throws InvalidMatrixIndex {
		if (!(mat instanceof SquareMatrix) || getRows() != mat.getRows())
			throw new InvalidMatrixIndex("add() method: Matrixes dimensions don't match.");
		
		SquareMatrix res = new SquareMatrix(getRows());
		for (int i = 0; i < getRows(); i++) {
			for (int j = 0; j < getCols(); j++)
				res.set(i, j, get(i,j) + mat.get(i, j));
		}
		return res;
	}
	
	@Override
	public SquareMatrix sub(Matrix mat) throws InvalidMatrixIndex {
		if (!(mat instanceof SquareMatrix) || getRows() != mat.getRows())
			throw new InvalidMatrixIndex("sub() method: Matrixes dimensions don't match.");
		
		SquareMatrix res = new SquareMatrix(getRows());
		for (int i = 0; i < getRows(); i++) {
			for (int j = 0; j < getCols(); j++)
				res.set(i, j, get(i,j) - mat.get(i, j));
		}
		return res;
	}
	
	//prodotto per uno scalare
	@Override
	public SquareMatrix multiply(double value) {
	    SquareMatrix res = new SquareMatrix(getRows());
	    for (int i = 0; i < getRows(); i++)
	        for (int j = 0; j < getCols(); j++)
	            res.set(i,j,get(i,j) * value);
	    return res;
	}
	
	//prodotto scalare
	@Override
	public SquareMatrix multiply(Matrix mat) throws InvalidMatrixIndex {
		if (mat.getRows() != mat.getCols() || getCols() != mat.getRows())
			throw new InvalidMatrixIndex("multiply() method: invalid matrixes' indexes.");
		
		SquareMatrix res = new SquareMatrix(getRows());
	    for (int i = 0; i < getRows(); i++)
	        for (int j = 0; j < mat.getCols(); j++) {
	            double sum = 0; //accumulatore
	            for (int k = 0; k < getCols(); k++)
	                sum += get(i,k) * mat.get(k, j);
	            res.set(i,j,sum);
	    }
	    return res;
	}
	
	public SquareMatrix getMinor(int i, int j) throws NegativeArraySizeException, IndexOutOfBoundsException {
		/** Estrae la sottomatrice mat = new SquareMatrix(getRows()-1) tale che mat è this a cui sono state rimosse 
		 la riga i e la colonna j */
		
		if (i < 0 || j < 0)
			throw new NegativeArraySizeException("getMinor() method: invalid matrix indexes.");
		
		if (i >= getRows() || j >= getRows())
			throw new IndexOutOfBoundsException("getMinor() method: out of bound matrix indexes.");
		
		
		SquareMatrix res = new SquareMatrix(getRows()-1); //SquareMatrix da restituire
		int rowSkipFlag = 0;
		int colSkipFlag = 0;
		
		for (int k = 0; k < getRows(); k++) {
			if (k == i)
				rowSkipFlag = 1;
			else
				for (int l = 0; l < getCols(); l++) {
					if (l == j)
						colSkipFlag = 1;
					else
						res.set(k-rowSkipFlag, l-colSkipFlag, get(k,l));
				}
			colSkipFlag = 0;
		}
		return res;
	}
	
	//SquareMatrix transposed
	@Override
	public SquareMatrix transposed() {
		SquareMatrix res = new SquareMatrix(getRows());
		for (int i = 0; i < getRows(); i++)
			for (int j = 0; j < getCols(); j++)
				res.set(i, j, get(j,i));
//		SquareMatrix res = (SquareMatrix)super.transposed();
		return res;
	}
	
	//matrici quadrate speciali
	
	//Matrice identità
	public static SquareMatrix identityMatrix(int n) throws NegativeArraySizeException {
		if (n <= 0)
			throw new NegativeArraySizeException("identityMatrix() method: invalid dimension given.");
		
		SquareMatrix res = new SquareMatrix(n, 0.0);
		for (int i = 0; i < n; i++) 
			res.set(i, i, 1);
		return res;
	}
	
	//Matrice di zeri
	public static SquareMatrix zeroMatrix(int n) throws NegativeArraySizeException {
		if (n <= 0)
			throw new NegativeArraySizeException("zerMatrix() method: invalid dimension given.");
		
		return new SquareMatrix(n, 0.0);
	}
	
}
