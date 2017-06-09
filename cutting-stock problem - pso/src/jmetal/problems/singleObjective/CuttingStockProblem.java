package jmetal.problems.singleObjective;

import java.io.File;
import java.io.FileNotFoundException;
import java.text.DecimalFormat;
import java.util.Arrays;
import java.util.Scanner;
import java.util.StringTokenizer;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.BinaryRealSolutionType;
import jmetal.encodings.solutionType.CuttingStockSolutionType;
import jmetal.encodings.solutionType.IntSolutionType;
import jmetal.encodings.solutionType.RealSolutionType;
import jmetal.encodings.variable.ArrayInt;
import jmetal.util.JMException;

public class CuttingStockProblem extends Problem{
	
	int numberBin;
	int[] placa;
	int[][] pecas;
	int [] quant;
	
	
	public CuttingStockProblem(String filename) {
		
		this.readConfig("src/instances/"+filename);
		
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
			//solutionType_ = new IntSolutionType(this);
	    	solutionType_ = new CuttingStockSolutionType(this);
		}
		catch (Exception e){
			e.printStackTrace();
		}

	  } // CuttingSock

	@Override
	public void evaluate(Solution solution) throws JMException {
		double value = 0.0;
		Variable[] decisionVariables  = solution.getDecisionVariables();
		double areaOcupada = 0.0;
		double areaPlaca = placa[0] * placa[1];
		for (int var = 0; var < numberOfVariables_; var++) {
			ArrayInt array = (ArrayInt)decisionVariables[var];
			int peca = array.getValue(0);
			int qtd = array.getValue(1);
			double area = (pecas[peca][0] * pecas[peca][1]) * qtd;
			areaOcupada += area;
		}
		
		double sobra = areaPlaca - areaOcupada;
		if(areaOcupada > areaPlaca){
			value = 5 ;
		}else{
			value = sobra/areaPlaca;
		}
		
		
		solution.setObjective(0, value);
		
	}
	
	public void readConfig(String filename) {

		try {
			Scanner scn = new Scanner(new File(filename));
			System.out.println(filename);
			String caracter=scn.nextLine();
			StringTokenizer tokens = new StringTokenizer(caracter);
			
			placa = new int[2];
			
			placa[0]= Integer.parseInt(tokens.nextToken().trim());
			placa[1]= Integer.parseInt(tokens.nextToken().trim());
			numberBin = Integer.parseInt(tokens.nextToken().trim());
			
			pecas = new int[numberBin][2];
			quant = new int[numberBin]; 
			
			for (int i = 0; i < numberBin; i++) {
				caracter=scn.nextLine();
				tokens = new StringTokenizer(caracter);
				pecas[i][0] = Integer.parseInt(tokens.nextToken().trim());
				pecas[i][1] = Integer.parseInt(tokens.nextToken().trim());
				quant[i] = Integer.parseInt(tokens.nextToken().trim());
			}
			
			
		} catch (FileNotFoundException e) {
			System.out.println("Arquivo "+ filename + " Não encontrado");
		}
		
		
	}

	public int[] getPlaca() {
		return placa;
	}

	public void setPlaca(int[] placa) {
		this.placa = placa;
	}

	public int[][] getPecas() {
		return this.pecas;
	}

	public void setPecas(int[][] pecas) {
		this.pecas = pecas;
	}

	public int[] getQuant() {
		return quant;
	}

	public void setQuant(int[] quant) {
		this.quant = quant;
	}
	
	

}
