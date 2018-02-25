package dataTypes;

public class SparseMatrix extends Matrix {
	//fields
	private boolean dirtyBit; //matrice modificata?
	private Double sparsity;
	
	public SparseMatrix(int row, int col) throws NegativeArraySizeException {
		super(row, col);
		this.sparsity = -1.0;
		this.dirtyBit = false;
	}
	
	public void clear() {
		fill(0.0);
	}
	
	public Double getSparsity() {
		if (!dirtyBit && sparsity != -1)
			return sparsity;
		
		dirtyBit = false;
		Double cumulator = 0.0;
		for (int i = 0; i < getRow(); i++)
			for (int j = 0; j < getCol(); j++)
				if (get(i,j) == 0)
					cumulator++;
		sparsity = cumulator / Double.valueOf(getRow() * getCol());
		return sparsity;
	}
	
	@Override
	public void set(int row, int col, Double value) throws IndexOutOfBoundsException {
		super.set(row, col, value);
		dirtyBit = true; //modified
	}
	
	//DA CONTROLLARE j = i+1
	public boolean isSymmetric() {
	    if (getRow() != getCol())
	        return false;
	    int n = getRow();
	    for (int i = 0; i < n; i++)
	        for (int j = i+1; j < n; j++)
	            if (j > i && get(i,j) != get(j,i))
	                return false;
	    return true;
	}
	
	//Matrix density
	public boolean isDense() {
		if (getSparsity() <= 0.5)
			return true;
		return false;
		
	}
}
