package dataTypes;

import kalkException.InvalidMatrixIndex;

public class Main {
	public static void main(String[] args) {
		try {
			Matrix a = new Matrix(4,5);
			a.fill(5.0, 1.0);
//			System.out.println(a);
//			System.out.println(a.get(1,1));
//			System.out.println(a.get(1,2));
			a.set(0, 1, 5);
			a.set(1, 1, 6.0);
			a.set(2, 2, 7.0);
			System.out.println(a);
			
//			SparseMatrix b = new SparseMatrix(4,5);
//			
//			b.set(1, 1, 3.9);
//			if(!((SparseMatrix)b).isDense())
//				System.out.println(a.add((Matrix)b));
//			
//			System.out.println(b.getSparsity());
			
//			Matrix c = a.removeCol(3);
//			System.out.println(c);
//			
//			c = c.removeRow(2);
//			System.out.println(c);
//			
//			SquareMatrix d = new SquareMatrix(5);
//			d.fill(0.0, 2.0);
//			System.out.println(d);
//			
//			d = d.getMinor(0, 2);
//			System.out.println(d);
//			
//			System.out.println(d.determinant());
			
			SquareMatrix b = new SquareMatrix(3);
			b.fill(1.0, 1.0);
			System.out.println(b);
			b.set(1, 0, 2);
			b.set(1, 1, -1);
			b.set(1, 2, 1);
			b.set(2, 0, 1);
			b.set(2, 1, 1);
			b.set(2, 2, 2);
			System.out.println(b.determinant());
			
			SquareMatrix c = new SquareMatrix(4);

			c.set(0, 0, 2);
			c.set(0, 1, 5);
			c.set(0, 2, -3);
			c.set(0, 3, -2);
			c.set(1, 0, -2);
			c.set(1, 1, -3);
			c.set(1, 2, 2);
			c.set(1, 3, -5);
			c.set(2, 0, 1);
			c.set(2, 1, 3);
			c.set(2, 2, -2);
			c.set(2, 3, 0);
			c.set(3, 0, -1);
			c.set(3, 1, -6);
			c.set(3, 2, 4);
			c.set(3, 3, 0);
			System.out.println(c);
			
			System.out.println(c.determinant());
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
