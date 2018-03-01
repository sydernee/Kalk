package dataTypes;

import java.util.ArrayList;
import java.lang.NegativeArraySizeException;
import kalkException.*;

public class Matrix extends DataType {
	//fields
	private int row;
	private int col;
	private ArrayList<Double> matrix;
	
	//constructors
	
	public Matrix(int row, int col) throws NegativeArraySizeException {
		if (row <= 0 || col <= 0)
			throw new NegativeArraySizeException("Matrix constructor: Invalid matrix dimensions.");
		this.row = row;
		this.col = col;
		this.matrix = new ArrayList<Double>(row * col);
		fill(0.0);
	}
	
	public Matrix(int row, int col, int defaultValue) throws NegativeArraySizeException {
		this(row, col);
		fill(Double.valueOf(defaultValue));
	}
	
	public Matrix(int row, int col, Double defaultValue) throws NegativeArraySizeException {
		this(row, col);
		fill(defaultValue);
	}
	
	public Matrix(Matrix mat) {
		this.row = mat.row;
		this.col = mat.col;
		this.matrix = mat.matrix;
	}
	
	public Matrix(int row, int col, double... numbers) 
		throws 	NegativeArraySizeException,
				TooFewArgumentsException, 
				TooManyArgumentsException 
	{
		this(row, col);
		
		int i = 0;
		for (double d : numbers) {
			if (i >= row * col)
				throw new TooManyArgumentsException("Matrix(): Too many arguments given.");
			matrix.set(i, Double.valueOf(d));
			i++;
		}
		
		if (i < row * col)
			throw new TooFewArgumentsException("Matrix(): Too few arguments given. Set " + (col*row-i) + " more values.");
	}
	
	//get matrix[i,j]
	public Double get(int row, int col) throws IndexOutOfBoundsException {
		if (row >= getRow() || col >= getCol())
			throw new IndexOutOfBoundsException("get(): Invalid matrix indexes.");
		
		return matrix.get(row * getCol() + col);
	}
	
	//set matrix[i,j] to value
	
	public void set(int row, int col, Double value) throws IndexOutOfBoundsException {
		if (row >= getRow() || col >= getCol())
			throw new IndexOutOfBoundsException("set(): Invalid matrix indexes.");
		
		matrix.set(row * getCol() + col, value);
	}
	
	//set matrix[i,j] to value
	public void set(int row, int col, double value) throws IndexOutOfBoundsException {
		if (row >= getRow() || col >= getCol())
			throw new IndexOutOfBoundsException("set(): Invalid matrix indexes.");
		
		matrix.set(row * getCol() + col, Double.valueOf(value));
	}
	
	//getters
	
	public int getRow() {
		return row;
	}
	
	public int getCol() {
		return col;
	}
	
	//Object overriding
	
	@Override
	public String toString() {
		String res = "";
		for (int i = 0; i < getRow(); i++) {
			for (int j = 0; j < getCol(); j++) {
				res += "\t" + get(i,j).toString();
			}
			res += "\n";
		}
		return res;
	}
	
	@Override
	public boolean equals(Object obj) {
		if (!(obj instanceof Matrix))
			return false;
		Matrix mat = (Matrix)obj;
		
		if (getRow() != mat.getRow() || getCol() != mat.getCol())
			return false;
		
		//check matrix cells
		for (int i = 0; i < getRow(); i++)
			for (int j = 0; j < getCol(); j++)
				if (get(i,j) != mat.get(i,j))
					return false;
		
		return true;
	}
	
	//utility methods
	
	public void fill(Double value, Double range) {
		matrix.clear();
		for (int i = 0; i < getRow()*getCol(); i++) {
			matrix.add(value + Double.valueOf(i)*range);
		}
	}
	
	public void fill(Double value) {
		fill(value, 0.0);
	}
	
	//restituisce un reference a un Matrix costruito dall'oggetto di invocazione senza la colonna i
	public Matrix removeCol(int i) throws NegativeArraySizeException, IndexOutOfBoundsException {
		if (i < 0)
			throw new NegativeArraySizeException("removeCol() method: invalid matrix index.");
		
		if (i >= getCol())
			throw new IndexOutOfBoundsException("removeCol() method: out of bound matrix index.");
		
		int val = 0; //variabile fittizia per impostare le celle correttamente dopo aver saltato la colonna i
		Matrix res = new Matrix(getRow(), getCol()-1); //Matrix da restituire
		for (int j = 0; j < getRow(); j++) {
			for (int k = 0; k < getCol(); k++) {
				if (k == i) 
					val = 1;
				else 
					res.set(j, k-val, get(j, k));
			}
			val = 0;
		}
		return res;
	}
	
	//restituisce un reference a un Matrix costruito dall'oggetto di invocazione senza la riga i
	public Matrix removeRow(int i) throws NegativeArraySizeException, IndexOutOfBoundsException {
		if (i < 0)
			throw new NegativeArraySizeException("removeRow() method: invalid matrix index.");
		
		if (i >= getCol())
			throw new IndexOutOfBoundsException("removeRow() method: out of bound matrix index.");
		
		int val = 0; //variabile fittizia per impostare le celle correttamente dopo aver saltato la colonna i
		Matrix res = new Matrix(getRow()-1, getCol()); //Matrix da restituire
		for (int j = 0; j < getRow(); j++) {
			if (j == i)
				val++;
			else
				for (int k = 0; k < getCol(); k++) {
					res.set(j-val, k, get(j,k));
				}
		}
		return res;
	}
	
	//operations
	
	public Matrix add(Matrix mat) throws InvalidMatrixIndex {
		if (getRow() != mat.getRow() || getCol() != mat.getCol())
			throw new InvalidMatrixIndex("add() method: Matrixes dimensions don't match.");
		
		Matrix res = new Matrix(getRow(), getCol());
		for (int i = 0; i < matrix.size(); i++)
			res.matrix.set(i, matrix.get(i) + mat.matrix.get(i));
		return res;
	}
	
	public Matrix sub(Matrix mat) throws InvalidMatrixIndex {
		if (getRow() != mat.getRow() || getCol() != mat.getCol())
			throw new InvalidMatrixIndex("sub() method: Matrixes dimensions don't match.");
		
		Matrix res = new Matrix(getRow(), getCol());
		for (int i = 0; i < matrix.size(); i++)
			res.matrix.set(i, matrix.get(i) - mat.matrix.get(i));
		return res;
	}
	
	//prodotto per uno scalare
	public Matrix multiply(double value) {
	    Matrix res = new Matrix(row, col);
	    for (int i = 0; i < row; i++)
	        for (int j = 0; j < col; j++)
	            res.set(i,j,get(i,j) * value);

	    return res;
	}
	
	//prodotto scalare
	public Matrix multiply(Matrix mat) throws InvalidMatrixIndex {
		if (getCol() != mat.getRow())
			throw new InvalidMatrixIndex("multiply() method: invalid matrixes' indexes.");
		
		Matrix res = new Matrix(getRow(), mat.getCol());
	    for (int i = 0; i < getRow(); i++)
	        for (int j = 0; j < mat.getCol(); j++) {
	            double sum = 0; //accumulatore
	            for (int k = 0; k < getCol(); k++)
	                sum += get(i,k) * mat.get(k, j);
	            res.set(i,j,sum);
	    }
	    return res;
	}
	
	//Matrix transposed
	public Matrix transposed() {
		Matrix res = new Matrix(col, row);
		for (int i = 0; i < getCol(); i++)
			for (int j = 0; j < getRow(); j++)
				res.set(i, j, get(j,i));
		return res;
	}
}
