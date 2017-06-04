package jmetal.problems.singleObjective;

import java.io.File;
import java.io.FileNotFoundException;
import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.Scanner;
import java.util.StringTokenizer;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.encodings.solutionType.BinaryRealSolutionType;
import jmetal.encodings.solutionType.IntSolutionType;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.util.JMException;

public class CuttingStockProblem extends Problem{
	
	int numberBin;
	int[] placa;
	int[][] dimensions;
	int [] quant;
	
	
	public CuttingStockProblem(String filename) {
		
		readConfig("src/instances/"+filename);
		
	    numberOfVariables_   = numberBin ;
	    numberOfObjectives_  = 1;
	    numberOfConstraints_ = 0;
	    problemName_         = "CuttingStock";
	        
	    upperLimit_ = new double[numberOfVariables_];
	    lowerLimit_ = new double[numberOfVariables_];
	    for (int var = 0; var < numberOfVariables_; var++){
	      lowerLimit_[var] = 0;
	      upperLimit_[var] = quant[var];
	    } // for
	        
	    try{
			solutionType_ = new IntSolutionType(this);
		}
		catch (Exception e){
			e.printStackTrace();
		}

	  } // CuttingSock

	@Override
	public void evaluate(Solution solution) throws JMException {
		
		
	}
	
	public void readConfig(String filename) {

		try {
			Scanner scn = new Scanner(new File(filename));
			
			String caracter=scn.nextLine();
			StringTokenizer tokens = new StringTokenizer(caracter);
			
			placa = new int[2];
			
			placa[0]= Integer.parseInt(tokens.nextToken().trim());
			placa[1]= Integer.parseInt(tokens.nextToken().trim());
			numberBin = Integer.parseInt(tokens.nextToken().trim());
			
			dimensions = new int[numberBin][2];
			quant = new int[numberBin]; 
			
			for (int i = 0; i < numberBin; i++) {
				caracter=scn.nextLine();
				tokens = new StringTokenizer(caracter);
				dimensions[i][0] = Integer.parseInt(tokens.nextToken().trim());
				dimensions[i][1] = Integer.parseInt(tokens.nextToken().trim());
				quant[i] = Integer.parseInt(tokens.nextToken().trim());
			}
			
			
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
	}

}
