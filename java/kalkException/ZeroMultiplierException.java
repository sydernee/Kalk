package kalkException;

public class ZeroMultiplierException extends RuntimeException{
	private static final long serialVersionUID = 1L;
	
	public ZeroMultiplierException() {
		super();
	}
	
	public ZeroMultiplierException(String s) {
		super(s);
	}
}
