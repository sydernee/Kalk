package dataTypes;

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
			
			SquareMatrix c = 
					new SquareMatrix(12,
							0,1,1,2,1,2,3,4,23,1,2,3,
							4,5,6,3,2,-1,4,4,1,2,3,4,
							5,6,7,34,2,-1,3,2,1,5,1,1,
							1,1,1,1,2,3,4,2,1,-1,2,1,
							3,0,2,3,4,5,6,3,12,12,3,2,
							3,-1,4,5,1,2,3,2,1,-5,-12,
							1,1,-4,1,2,-5,-5,2,3,4,-8,-8,-8,
							-8,-8,-8,-8,-8,3,2,1,5,1,1,1,
							1,1,1,2,3,4,2,1,4,3,3,-8,
							3,2,1,5,1,1,1,1,1,1,2,3,
							4,2,1,4,3,3,-8,2,3,-1,4,5,
							1,2,3,2,1,-8,-8,-8,-8,-8,-8,12);

			System.out.println(c);
			
			Matrix p1 = new Matrix(2,3,
					0, 1, 2,
					2, 3, 4);
			
			Matrix p2 = new Matrix(3, 2,
					1, 4,
					3, 2,
					1, 2);
			
			Matrix res = p1.multiply(p2);
			System.out.println(res);
//			System.out.println(c.determinant());
		}
		catch(RuntimeException exc) {
			System.err.println(exc.getClass().getName() + " -> " + exc.getMessage());
		}
	}
}
