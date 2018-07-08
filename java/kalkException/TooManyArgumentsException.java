package kalkException;

public class TooManyArgumentsException extends RuntimeException {
	private static final long serialVersionUID = 1L;
	
	public TooManyArgumentsException() {
		super();
	}
	
	public TooManyArgumentsException(String s) {
		super(s);
	}
}
