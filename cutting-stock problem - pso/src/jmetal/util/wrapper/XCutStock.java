package jmetal.util.wrapper;

import jmetal.core.Solution;
import jmetal.core.SolutionType;
import jmetal.encodings.solutionType.CuttingStockSolutionType;
import jmetal.util.Configuration;
import jmetal.util.JMException;

public class XCutStock {

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
			return (int)solution_.getDecisionVariables()[index].getValue() ;			
		}else {
			Configuration.logger_.severe("jmetal.util.wrapper.CuttingStock.getValue, solution type " +
					type_ + "+ invalid") ;		
		}
		return 0;
	} // Get value

	/**
	 * Sets the value of a encodings.variable
	 * @param index Index of the encodings.variable
	 * @param value Value to be assigned
	 * @throws JMException
	 */
	public void setValue(int index, int value) throws JMException {
		if (type_.getClass() == CuttingStockSolutionType.class)
			solution_.getDecisionVariables()[index].setValue(value) ;
		else
			Configuration.logger_.severe("jmetal.util.wrapper.CuttingStock.setValue, solution type " +
					type_ + "+ invalid") ;		
	} // setValue	

	/**
	 * Gets the lower bound of a encodings.variable
	 * @param index Index of the encodings.variable
	 * @return The lower bound of the encodings.variable
	 * @throws JMException
	 */
	public int getLowerBound(int index) throws JMException {
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
	public int getUpperBound(int index) throws JMException {
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

