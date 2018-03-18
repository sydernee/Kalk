package dataTypes;

import kalkException.TooFewArgumentsException;
import kalkException.TooManyArgumentsException;

public class SparseMatrix extends Matrix {
	//fields
	private boolean dirtyBit; //matrice modificata?
	private Double sparsity;
	
	public SparseMatrix(int rows, int cols) throws NegativeArraySizeException {
		super(rows, cols);
		this.sparsity = -1.0;
		this.dirtyBit = false;
	}
	
	public SparseMatrix(int rows, int cols, double... numbers)
			throws 	NegativeArraySizeException,
					TooFewArgumentsException, 
					TooManyArgumentsException
		{
			super(rows, cols, numbers);
			this.sparsity = -1.0;
			this.dirtyBit = false;
		}
	
	public void clear() {
		fill(0.0);
	}
	
	public Double getSparsity() {
		if (!dirtyBit && sparsity != -1)
			return sparsity;
		
		dirtyBit = false;
		Double cumulator = 0.0;
		for (int i = 0; i < getRows(); i++)
			for (int j = 0; j < getCols(); j++)
				if (get(i,j) == 0)
					cumulator++;
		sparsity = cumulator / Double.valueOf(getRows() * getCols());
		return sparsity;
	}
	
	@Override
	public void set(int row, int col, Double value) throws IndexOutOfBoundsException {
		super.set(row, col, value);
		dirtyBit = true; //modified
	}
	
	//DA CONTROLLARE j = i+1
	public boolean isSymmetric() {
	    if (getRows() != getCols())
	        return false;
	    int n = getRows();
	    for (int i = 0; i < n; i++)
	        for (int j = i+1; j < n; j++)
	            if (j > i && get(i,j) != get(j,i))
	                return false;
	    return true;
	}
	
	//Matrix density
	public boolean isDense() {
		if (getSparsity() <= 0.5)
			return true;
		return false;
		
	}
}
