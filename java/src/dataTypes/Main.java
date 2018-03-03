package dataTypes;

public class Main {
	public static void main(String[] args) {
		try {

			Matrix a = new Matrix(4,4,
					0, 1, 2, 3,
					2, 4, 5, 6,
					0, 0, -1, 2,
					0, 1, 4, -2);
			
			System.out.println(a);
			a.substituteRow(0, 2, 3);
			System.out.println(a);
		}
		catch(RuntimeException exc) {
			System.err.println(exc.getClass().getName() + " -> " + exc.getMessage());
		}
	}
}
