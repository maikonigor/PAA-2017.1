package jmetal.util.wrapper;

import jmetal.core.Solution;
import jmetal.core.SolutionType;
import jmetal.encodings.solutionType.CuttingStockSolutionType;
import jmetal.encodings.variable.ArrayInt;
import jmetal.util.Configuration;
import jmetal.util.JMException;

public class XCutStock extends ArrayInt{

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private Solution solution_ ;
	private SolutionType type_ ;

	/**
	 * Constructor
	 */
  private XCutStock() {
	} // Constructor

	/**
	 * Constructor
	 * @param solution
	 */
	public XCutStock(Solution solution) {
		this() ;
		type_ = solution.getType() ;
		solution_ = solution ;
	}

	/**
	 * Gets value of a encodings.variable
	 * @param index Index of the encodings.variable
	 * @return The value of the encodings.variable
	 * @throws JMException
	 */
	public int getValue(int index) throws JMException {
		if (type_.getClass() == CuttingStockSolutionType.class){
			ArrayInt array = (ArrayInt) solution_.getDecisionVariables()[index];
			return array.getValue(1); // retorna a quantidade de uma determinada peca	
		}else {
			Configuration.logger_.severe("jmetal.util.wrapper.CuttingStock.getValue, solution type " +
					type_ + "+ invalid") ;		
		}
		return 0;
	} // Get value
	
	/**
	 * swippe positions of variable depending on velocity
	 * @param index index of the encondings.variable
	 * @param newPosition index of the position to change
	 */
	public void changePosition(int index, int newPosition){
		newPosition = Math.abs(newPosition);
		
		if(newPosition > (solution_.getDecisionVariables().length -1)){
			newPosition = (solution_.getDecisionVariables().length -1);
		}
		
		ArrayInt array = (ArrayInt) solution_.getDecisionVariables()[index];
		ArrayInt array2 = (ArrayInt) solution_.getDecisionVariables()[newPosition];
		ArrayInt aux = (ArrayInt) array.deepCopy();
		
		try {
			setValue(index, 0, array2.getValue(0));
			setValue(index, 1, array2.getValue(1));
			setValue(newPosition, 0, aux.getValue(0));
			setValue(newPosition, 1, aux.getValue(1));
		} catch (JMException e) {
			e.printStackTrace();
		}
		
			
	}

	/**
	 * Sets the value of a encodings.variable
	 * @param index Index of the encodings.variable
	 * @param value Value to be assigned
	 * @throws JMException
	 */
	public void setValue(int index, int value) throws JMException {
		if (type_.getClass() == CuttingStockSolutionType.class){
			ArrayInt array = (ArrayInt) solution_.getDecisionVariables()[index];
			array.setValue(1, value);
//			solution_.getDecisionVariables()[index].setValue(value) ;
		}
		else
			Configuration.logger_.severe("jmetal.util.wrapper.CuttingStock.setValue, solution type " +
					type_ + "+ invalid") ;		
	} // setValue
	
	public void setValue(int indexVariable, int indexPosition, int value) throws JMException{
		if (type_.getClass() == CuttingStockSolutionType.class){
			ArrayInt array = (ArrayInt) solution_.getDecisionVariables()[indexVariable];
			array.setValue(indexPosition, value);
//			solution_.getDecisionVariables()[index].setValue(value) ;
		}
		else
			Configuration.logger_.severe("jmetal.util.wrapper.CuttingStock.setValue, solution type " +
					type_ + "+ invalid") ;	
	}

	/**
	 * Gets the lower bound of a encodings.variable
	 * @param index Index of the encodings.variable
	 * @return The lower bound of the encodings.variable
	 * @throws JMException
	 */
	public double getLowerBound(int index) throws JMException {
		if (type_.getClass() == CuttingStockSolutionType.class)
			return (int)solution_.getDecisionVariables()[index].getLowerBound() ;
		else {
			Configuration.logger_.severe("jmetal.util.wrapper.CuttingStock.getLowerBound, solution type " +
					type_ + "+ invalid") ;		
		}
		return 0 ;
	} // getLowerBound

	/**
	 * Gets the upper bound of a encodings.variable
	 * @param index Index of the encodings.variable
	 * @return The upper bound of the encodings.variable
	 * @throws JMException
	 */
	public double getUpperBound(int index) throws JMException {
		if (type_.getClass() == CuttingStockSolutionType.class)		
			return (int)solution_.getDecisionVariables()[index].getUpperBound() ;
		else
			Configuration.logger_.severe("jmetal.util.wrapper.CuttingStock.getUpperBound, solution type " +
					type_ + "+ invalid") ;		

		return 0 ;
	} // getUpperBound

	/**
	 * Returns the number of variables of the solution
	 * @return
	 */
	public int getNumberOfDecisionVariables() {
		if (type_.getClass() == CuttingStockSolutionType.class)		
			return solution_.getDecisionVariables().length ;
		else
			Configuration.logger_.severe("jmetal.util.wrapper.CuttingStock.size, solution type " +
					type_ + "+ invalid") ;		
		return 0 ;
	} // size
} // XInt

