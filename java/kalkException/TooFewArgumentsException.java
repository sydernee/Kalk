package kalkException;

public class TooFewArgumentsException extends RuntimeException {
	private static final long serialVersionUID = 1L;
	
	public TooFewArgumentsException() {
		super();
	}
	
	public TooFewArgumentsException(String s) {
		super(s);
	}
}
