package jmetal.encodings.solutionType;

import java.util.Random;

import jmetal.core.Problem;
import jmetal.core.SolutionType;
import jmetal.core.Variable;
import jmetal.encodings.variable.Int;
import jmetal.problems.singleObjective.CuttingStockProblem;

/**
 * Class representing the solution type of solutions composed of peaces of cutting Stock problem 
 */
public class CuttingStockSolutionType extends IntSolutionType {

	
	/**
	 * Constructor
	 * @param problem  Problem to solve
	 */
	public CuttingStockSolutionType(Problem problem) {
		super(problem);
	} // constructor

	
	/**
	 * Creates the variables of the solution
	 */
	@Override
	public Variable[] createVariables() {
		Variable[] variables = new Variable[problem_.getNumberOfVariables()];
		Random random = new Random();
		int index = random.nextInt((problem_.getNumberOfVariables()-1) - 0 + 1);
		CuttingStockProblem problem = (CuttingStockProblem) this.problem_;
		int[][] pecas = problem.getPecas();
		int[] quantidades = problem.getQuant();
		int[] placa = problem.getPlaca();
		
		int maiorAltura = 0;
		int maiorLargura = 0;
		int larguraPlaca = placa[0];
		int alturaPlaca = placa[1];
		int maiorPeca = 0;
		for (int var = 0; var < problem_.getNumberOfVariables(); var++){
			
			int larguraPeca = pecas[index][0];
			int alturaPeca = pecas[index][0];
			int quantidadePeca = quantidades[index];
			int quantidadeAtual = 0;
			
			for(int i = 0; i < quantidadePeca; i++){
				
				boolean coube = false;
				while(!coube){
					if((alturaPlaca - maiorAltura) > alturaPeca ){ // Se peca couber na altura, verficar se cabe na largura
						if((maiorLargura + larguraPeca) < larguraPlaca){
							maiorLargura = maiorLargura + larguraPeca; //Se couber na largura alocar placa
							quantidadeAtual++;
							coube = true;
							if(alturaPeca > maiorPeca) //Verifica se a peca atual é a mais alta
								maiorPeca = alturaPeca;
						}else{ // Se não couber na largura tenta alocar um nivel acima
							maiorAltura = maiorAltura + maiorPeca;
							maiorPeca = maiorLargura =  0;
							coube = false;
						}
					}else{
						break;
					}
				}
			
			}
			variables[index] = new Int(quantidadeAtual, 0, quantidadePeca);
			index++;
			if(index == problem_.getNumberOfVariables()){
				index = 0;
			}
		}

		return variables;
	}//createVariables

} //CuttingStockSolutionType