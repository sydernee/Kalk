package dataTypes;

import kalkException.TooFewArgumentsException;
import kalkException.TooManyArgumentsException;
import java.util.ArrayList;

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
	
	public ArrayList<Double> nonZeroRow(int i) throws IndexOutOfBoundsException, NegativeArraySizeException {
		if (i >=  getRows())
			throw new IndexOutOfBoundsException("SparseMatrix.nonZeroRow(): out of bounds index.");
		else if (i < 0)
			throw new NegativeArraySizeException("SparseMatrix.nonZeroRow(): invalid negative index.");
		
		ArrayList<Double> res = new ArrayList<Double>();
		for (int j = 0; j < getCols(); j++) {
			if (get(i, j) != 0)
				res.add(get(i,j));
		}
		return res;
	}
	
	public ArrayList<Double> nonZeroCol(int j) throws IndexOutOfBoundsException, NegativeArraySizeException {
		if (j >=  getCols())
			throw new IndexOutOfBoundsException("SparseMatrix.nonZeroRow(): out of bounds index.");
		else if (j < 0)
			throw new NegativeArraySizeException("SparseMatrix.nonZeroRow(): invalid negative index.");
		
		ArrayList<Double> res = new ArrayList<Double>();
		for (int i = 0; i < getRows(); i++) {
			if (get(i, j) != 0)
				res.add(get(i,j));
		}
		return res;
	}
}
