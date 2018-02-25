package dataTypes;

import kalkException.InvalidMatrixIndex;

public class Main {
	public static void main(String[] args) {
		try {
			Matrix a = new Matrix(4,5);
			a.fill(5.0, 1.0);
			System.out.println(a);
			System.out.println(a.get(1,1));
			System.out.println(a.get(1,2));
			a.set(0, 1, 5);
			a.set(1, 1, 6.0);
			a.set(2, 2, 7.0);
			System.out.println(a);
			
			SparseMatrix b = new SparseMatrix(5,5);
			
			b.set(1, 1, 3.9);
			if(!((SparseMatrix)b).isDense())
				System.out.println(a.add((Matrix)b));
			
			System.out.println(b.getSparsity());
		}
		catch(NegativeArraySizeException exc) {
			System.err.println("NegativeArraySizeException in " + exc.getMessage());
		}
		catch(IndexOutOfBoundsException exc) {
			System.err.println("IndexOutOfBoundException in " + exc.getMessage());
		}
		catch(InvalidMatrixIndex exc) {
			System.err.println("InvalidMatrixException in " + exc.getMessage());	
		}
	}
}
