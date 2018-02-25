package dataTypes;

public class Main {
	public static void main(String[] args) {
		Matrix a = new Matrix(4,5);
		a.fill(5.0, 1.0);
		
		System.out.println(a);
		System.out.println(a.get(1,1));
		System.out.println(a.get(1,2));
		a.set(0, 1, 5.0);
		a.set(1, 1, 6.0);
		a.set(2, 2, 7.0);
		System.out.println(a);
	}
}
