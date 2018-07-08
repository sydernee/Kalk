package kalkException;

public class InvalidMatrixIndex extends RuntimeException {
	private static final long serialVersionUID = 1L;
	
	public InvalidMatrixIndex() {
		super();
	}
	
	public InvalidMatrixIndex(String s) {
		super(s);
	}
}
