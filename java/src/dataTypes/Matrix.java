package dataTypes;

import java.util.ArrayList;
import java.lang.NegativeArraySizeException;
import kalkException.*;

public class Matrix extends DataType {
	//fields
	private int rows;
	private int cols;
	private ArrayList<Double> matrix;
	
	//constructors
	
	public Matrix(int rows, int cols) throws NegativeArraySizeException {
		if (rows <= 0 || cols <= 0)
			throw new NegativeArraySizeException("Matrix constructor: Invalid matrix dimensions.");
		this.rows = rows;
		this.cols = cols;
		this.matrix = new ArrayList<Double>(rows * cols);
		fill(0.0);
	}
	
	public Matrix(int rows, int cols, int defaultValue) throws NegativeArraySizeException {
		this(rows, cols);
		fill(Double.valueOf(defaultValue));
	}
	
	public Matrix(int rows, int cols, Double defaultValue) throws NegativeArraySizeException {
		this(rows, cols);
		fill(defaultValue);
	}
	
	public Matrix(Matrix mat) {
		this.rows = mat.rows;
		this.cols = mat.cols;
		this.matrix = mat.matrix;
	}
	
	public Matrix(int rows, int cols, double... numbers) 
		throws 	NegativeArraySizeException,
				TooFewArgumentsException, 
				TooManyArgumentsException 
	{
		this(rows, cols);
		
		int i = 0;
		for (double d : numbers) {
			if (i >= rows * cols)
				throw new TooManyArgumentsException("Matrix(): Too many arguments given.");
			matrix.set(i, Double.valueOf(d));
			i++;
		}
		
		if (i < rows * cols)
			throw new TooFewArgumentsException("Matrix(): Too few arguments given. Set " + (cols*rows-i) + " more values.");
	}
	
	//get matrix[i,j]
	public Double get(int rows, int cols) throws IndexOutOfBoundsException {
		if (rows >= getRows() || cols >= getCols())
			throw new IndexOutOfBoundsException("get(): Invalid matrix indexes.");
		
		return matrix.get(rows * getCols() + cols);
	}
	
	//set matrix[i,j] to value
	public void set(int rows, int cols, Double value) throws IndexOutOfBoundsException {
		if (rows >= getRows() || cols >= getCols())
			throw new IndexOutOfBoundsException("set(): Invalid matrix indexes.");
		
		matrix.set(rows * getCols() + cols, value);
	}
	
	//set matrix[i,j] to value
	public void set(int rows, int cols, double value) throws IndexOutOfBoundsException {
		if (rows >= getRows() || cols >= getCols())
			throw new IndexOutOfBoundsException("set(): Invalid matrix indexes.");
		
		matrix.set(rows * getCols() + cols, Double.valueOf(value));
	}
	
	//getters
	
	public int getRows() {
		return rows;
	}
	
	public int getCols() {
		return cols;
	}
	
	//Object overriding
	
	@Override
	public String toString() {
		String res = "";
		for (int i = 0; i < getRows(); i++) {
			for (int j = 0; j < getCols(); j++) {
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
		
		if (getRows() != mat.getRows() || getCols() != mat.getCols())
			return false;
		
		//check matrix cells
		for (int i = 0; i < getRows(); i++)
			for (int j = 0; j < getCols(); j++)
				if (get(i,j) != mat.get(i,j))
					return false;
		
		return true;
	}
	
	//utility methods
	
	public void fill(Double value, Double range) {
		matrix.clear();
		for (int i = 0; i < getRows()*getCols(); i++) {
			matrix.add(value + Double.valueOf(i)*range);
		}
	}
	
	public void fill(Double value) {
		fill(value, 0.0);
	}
	
	//restituisce un reference a un Matrix costruito dall'oggetto di invocazione senza la colonna i
	public Matrix removeCol(int i) throws NegativeArraySizeException, InvalidMatrixIndex {
		if (i < 0)
			throw new NegativeArraySizeException("removeCol() method: invalid matrix index.");
		
		if (i >= getCols())
			throw new InvalidMatrixIndex("removeCol() method: invalid matrix index.");
		
		int val = 0; //variabile fittizia per impostare le celle correttamente dopo aver saltato la colonna i
		Matrix res = new Matrix(getRows(), getCols()-1); //Matrix da restituire
		for (int j = 0; j < getRows(); j++) {
			for (int k = 0; k < getCols(); k++) {
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
	public Matrix removeRow(int i) throws NegativeArraySizeException, InvalidMatrixIndex {
		if (i < 0)
			throw new NegativeArraySizeException("removeRow() method: invalid matrix index.");
		
		if (i >= getCols())
			throw new InvalidMatrixIndex("removeRow() method: invalid matrix index.");
		
		int val = 0; //variabile fittizia per impostare le celle correttamente dopo aver saltato la colonna i
		Matrix res = new Matrix(getRows()-1, getCols()); //Matrix da restituire
		for (int j = 0; j < getRows(); j++) {
			if (j == i)
				val++;
			else
				for (int k = 0; k < getCols(); k++) {
					res.set(j-val, k, get(j,k));
				}
		}
		return res;
	}
	
	//Elementary rows/cols operations
	
	public void swapRows(int i, int j) throws NegativeArraySizeException, InvalidMatrixIndex {
	/** scambia le righe i e j della matrice di invocazione. */
	 
		if (i < 0 || j < 0)
			throw new NegativeArraySizeException("swapRows() method: invalid negative matrix index.");
		
		if (i >= getRows() || j >= getRows())
			throw new InvalidMatrixIndex("swapRows() method: invalid matrix index.");
		
		for (int k = 0; k < getRows(); k++) {
			Double temp = get(i,k);
			set(i, k, get(j,k));
			set(j, k, temp);
		}
	}
	
	public void swapCols(int i, int j) throws NegativeArraySizeException, InvalidMatrixIndex {
		/** scambia le colonne i e j della matrice di invocazione. */
		if (i < 0 || j < 0)
			throw new NegativeArraySizeException("swapCols() method: invalid negative matrix index.");
		
		if (i >= getCols() || j >= getCols())
			throw new InvalidMatrixIndex("swapCols() method: invalid matrix index.");
		
		for (int k = 0; k < getCols(); k++) {
			Double temp = get(k,i);
			set(k, i, get(k,j));
			set(k, j, temp);
		}
	}
	
	public void multiplyRow(int i, double val) throws NegativeArraySizeException, InvalidMatrixIndex, ZeroMultiplierException {
		/** moltiplica per val ogni elemento della riga i della matrice di invocazione */
		if (i < 0)
			throw new NegativeArraySizeException("multiplyRow() method: invalid negative matrix index.");
		
		if (i >= getRows())
			throw new InvalidMatrixIndex("multiplyRow() method: invalid matrix index.");
		
		if (val == 0)
			throw new ZeroMultiplierException("multiplyRow() method: cannot multiply per 0.");
		
		for (int j = 0; j < getRows(); j++) {
			set(i, j, val * get(i,j));
		}
	}
	
	public void multiplyCol(int j, double val) throws NegativeArraySizeException, InvalidMatrixIndex, ZeroMultiplierException {
		/** moltiplica per val ogni elemento della colonna j della matrice di invocazione */
		if (j < 0)
			throw new NegativeArraySizeException("multiplyRow() method: invalid negative matrix index.");
		
		if (j >= getCols())
			throw new InvalidMatrixIndex("multiplyRow() method: invalid matrix index.");
		
		if (val == 0)
			throw new ZeroMultiplierException("multiplyRow() method: cannot multiply per 0.");
		
		for (int i = 0; i < getRows(); i++) {
			set(i, j, val * get(i,j));
		}
	}
	
	public void substituteRow(int sourceRow, int destRow, double factor) throws NegativeArraySizeException, InvalidMatrixIndex {
		if (sourceRow < 0 || destRow < 0)
			throw new NegativeArraySizeException("substituteRow() method: invalid negative matrix index.");
		
		if (sourceRow >= getRows() || sourceRow >= getRows())
			throw new InvalidMatrixIndex("substituteRow() method: invalid matrix index.");
		
		if (factor != 0)
			for (int i = 0; i < getRows(); i++) {
				set(sourceRow, i, get(sourceRow,i) + get(destRow,i) * factor);
			}
	}
	
	//Operations
	
	public Matrix add(Matrix mat) throws InvalidMatrixIndex {
		if (getRows() != mat.getRows() || getCols() != mat.getCols())
			throw new InvalidMatrixIndex("add() method: Matrixes dimensions don't match.");
		
		Matrix res = new Matrix(getRows(), getCols());
		for (int i = 0; i < matrix.size(); i++)
			res.matrix.set(i, matrix.get(i) + mat.matrix.get(i));
		return res;
	}
	
	public Matrix sub(Matrix mat) throws InvalidMatrixIndex {
		if (getRows() != mat.getRows() || getCols() != mat.getCols())
			throw new InvalidMatrixIndex("sub() method: Matrixes dimensions don't match.");
		
		Matrix res = new Matrix(getRows(), getCols());
		for (int i = 0; i < matrix.size(); i++)
			res.matrix.set(i, matrix.get(i) - mat.matrix.get(i));
		return res;
	}
	
	//prodotto per uno scalare
	public Matrix multiply(double value) {
	    Matrix res = new Matrix(rows, cols);
	    for (int i = 0; i < rows; i++)
	        for (int j = 0; j < cols; j++)
	            res.set(i,j,get(i,j) * value);

	    return res;
	}
	
	//prodotto scalare
	public Matrix multiply(Matrix mat) throws InvalidMatrixIndex {
		if (getCols() != mat.getRows())
			throw new InvalidMatrixIndex("multiply() method: invalid matrixes' indexes.");
		
		Matrix res = new Matrix(getRows(), mat.getCols());
	    for (int i = 0; i < getRows(); i++)
	        for (int j = 0; j < mat.getCols(); j++) {
	            double sum = 0; //accumulatore
	            for (int k = 0; k < getCols(); k++)
	                sum += get(i,k) * mat.get(k, j);
	            res.set(i,j,sum);
	    }
	    return res;
	}
	
	//Matrix transposed
	public Matrix transposed() {
		Matrix res = new Matrix(cols, rows);
		for (int i = 0; i < getCols(); i++)
			for (int j = 0; j < getRows(); j++)
				res.set(i, j, get(j,i));
		return res;
	}
}
