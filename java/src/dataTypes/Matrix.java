package dataTypes;

import java.util.ArrayList;

public class Matrix extends DataType {
	//fields
	private int row;
	private int col;
	private ArrayList<Double> matrix;
	
	//constructors
	
	public Matrix(int row, int col) {
		this.row = row;
		this.col = col;
		this.matrix = new ArrayList<Double>(row * col);
		fill(0.0);
	}
	
	public Matrix(int row, int col, int defaultValue) {
		this.row = row;
		this.col = col;
		this.matrix = new ArrayList<Double>(row * col);
		fill(Double.valueOf(defaultValue));
	}
	
	public Matrix(int row, int col, Double defaultValue) {
		this.row = row;
		this.col = col;
		this.matrix = new ArrayList<Double>(row * col);
		fill(defaultValue);
	}
	
	//Forse non serve
	
	public Matrix(Matrix mat) {
		this.row = mat.row;
		this.col = mat.col;
		this.matrix = mat.matrix;
	}
	
	//get matrix[i,j]
	public Double get(int row, int col) {
		return matrix.get(row * getCol() + col);
	}
	
	//set matrix[i,j] to value
	public void set(int row, int col, Double value) {
		matrix.set(row * getCol() + col, value);
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
	
	//private?
	public void fill(Double value, Double range) {
		matrix.clear();
		for (int i = 0; i < getRow()*getCol(); i++) {
			matrix.add(value + Double.valueOf(i)*range);
		}
	}
	
	public void fill(Double value) {
		fill(value, 0.0);
	}
	
	//operations
	
	//TODO exceptions
	public Matrix add(Matrix mat) /*throws MatrixException */{
//		if (getRow() != mat.getRow() || getCol() != mat.getCol())
//			throw new MatrixException();
		Matrix res = new Matrix(getRow(), getCol());
		for (int i = 0; i < matrix.size(); i++)
			res.matrix.set(i, matrix.get(i) + mat.matrix.get(i));
		return res;
	}
	
	//TODO exceptions
	public Matrix sub(Matrix mat) /*throws MatrixException */{
//		if (getRow() != mat.getRow() || getCol() != mat.getCol())
//			throw new MatrixException();
		Matrix res = new Matrix(getRow(), getCol());
		for (int i = 0; i < matrix.size(); i++)
			res.matrix.set(i, matrix.get(i) - mat.matrix.get(i));
		return res;
	}
	
	//
	
	//Matrix transposed
	public Matrix transposed() {
		Matrix res = new Matrix(col, row);
		for (int i = 0; i < getCol(); i++)
			for (int j = 0; j < getRow(); j++)
				res.set(i, j, get(j,i));
		return res;
	}
}