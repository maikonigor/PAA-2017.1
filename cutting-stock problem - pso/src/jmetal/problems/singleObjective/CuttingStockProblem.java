package jmetal.problems.singleObjective;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;
import java.util.StringTokenizer;

import jmetal.core.Problem;
import jmetal.core.Solution;
import jmetal.core.Variable;
import jmetal.encodings.solutionType.CuttingStockSolutionType;
import jmetal.encodings.variable.ArrayInt;
import jmetal.util.JMException;

public class CuttingStockProblem extends Problem {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	int numberBin;
	int[] placa;
	int[][] pecas;
	int[] quant;

	public CuttingStockProblem(String filename) {

		this.readConfig("src/instances/" + filename);

		numberOfVariables_ = numberBin;
		numberOfObjectives_ = 1;
		numberOfConstraints_ = 0;
		problemName_ = "CuttingStock";

		upperLimit_ = new double[numberOfVariables_];
		lowerLimit_ = new double[numberOfVariables_];
		for (int var = 0; var < numberOfVariables_; var++) {
			lowerLimit_[var] = 0;
			upperLimit_[var] = quant[var];
		} // for

		try {
			// solutionType_ = new IntSolutionType(this);
			solutionType_ = new CuttingStockSolutionType(this);
		} catch (Exception e) {
			e.printStackTrace();
		}

	} // CuttingSock

	@Override
	public void evaluate(Solution solution) throws JMException {
		double value = 0.0;

		boolean cabeNaPlaca = isCabenaPlaca(solution);

		if (cabeNaPlaca) {
			value = calculaSobra(solution);
		} else {
//			value = 5;
			reparo2(solution);
			value = calculaSobra(solution);
			
		}

		solution.setObjective(0, value);

	}

	public double calculaSobra(Solution solution) throws JMException {
		Variable[] decisionVariables = solution.getDecisionVariables();
		double areaOcupada = 0.0;
		double areaPlaca = placa[0] * placa[1];
		for (int var = 0; var < numberOfVariables_; var++) {
			ArrayInt array = (ArrayInt) decisionVariables[var];
			int peca = array.getValue(0);
			int qtd = array.getValue(1);
			double area = (pecas[peca][0] * pecas[peca][1]) * qtd;
			areaOcupada += area;
		}

		double sobra = areaPlaca - areaOcupada;

		return sobra / areaPlaca;
	}

	public boolean isCabenaPlaca(Solution solution) {
		Variable[] decisionVariables = solution.getDecisionVariables();
		int larguraPlaca = placa[0];
		int alturaPlaca = placa[1];
		int maiorAltura = 0;
		int maiorPeca = 0;
		int maiorLargura = 0;
		try {
			for (int var = 0; var < numberOfVariables_; var++) {
				ArrayInt array = (ArrayInt) decisionVariables[var];
				int peca = array.getValue(0);
				int qtd = array.getValue(1);

				int alturaPeca = pecas[peca][1];
				int larguraPeca = pecas[peca][0];
				boolean coube = true;
				for (int i = 0; i < qtd; i++) {
					while (coube) {
						if ((alturaPlaca - maiorAltura) > alturaPeca) { // Se
																		// peca
																		// couber
																		// na
																		// altura,
																		// verficar
																		// se
																		// cabe
																		// na
																		// largura
							if ((maiorLargura + larguraPeca) < larguraPlaca) {
								maiorLargura = maiorLargura + larguraPeca; // Se
																			// couber
																			// na
																			// largura
																			// alocar
																			// placa
								coube = true;
								if (alturaPeca > maiorPeca) // Verifica se a
															// peca atual é a
															// mais alta
									maiorPeca = alturaPeca;
								break;
							} else { // Se não couber na largura tenta alocar
										// um nivel acima
								maiorAltura = maiorAltura + maiorPeca;
								maiorPeca = maiorLargura = 0;
								continue;

							}
						} else {
							coube = false; // não coube na largura
							return coube;
						}
					}

				}

			}

		} catch (JMException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return true;
	}
	
	public void reparo(Solution solution) throws JMException {

		Variable[] decisionVariables = solution.getDecisionVariables();
		Random r = new Random();

		while (!isCabenaPlaca(solution)) {
			int var = r.nextInt(numberOfVariables_);
			ArrayInt array = (ArrayInt) decisionVariables[var];
			int qtd = array.getValue(1);
			if (qtd > 0) {
				array.setValue(1,(qtd - 1));
			}
			decisionVariables[var] = array;
		}

		solution.setDecisionVariables(decisionVariables);
		
	}

	public void reparo2(Solution solution) throws JMException {

		Variable[] decisionVariables = solution.getDecisionVariables();
		Random r = new Random();

		while (!isCabenaPlaca(solution)) {

			ArrayList<Object> posicao = posicaoValida(decisionVariables);

			int var = r.nextInt(posicao.size());
			ArrayInt array = (ArrayInt) decisionVariables[(int) posicao.get(var)];
			int qtd = array.getValue(1);
			array.setValue(1, qtd - 1);
//			decisionVariables[var] = array;
		}

		solution.setDecisionVariables(decisionVariables);

	}

	public ArrayList<Object> posicaoValida(Variable[] decisionVariables) throws JMException {

		ArrayList<Object> posicaoValida = new ArrayList<>();

		for (int i = 0; i < decisionVariables.length; i++) {
			ArrayInt test = (ArrayInt) decisionVariables[i];
			if (test.getValue(1) > 0) {
				posicaoValida.add(i);
			}
		}

		return posicaoValida;

	}

	public void readConfig(String filename) {

		try {
			Scanner scn = new Scanner(new File(filename));
			System.out.println(filename);
			String caracter = scn.nextLine();
			StringTokenizer tokens = new StringTokenizer(caracter);

			placa = new int[2];

			placa[0] = Integer.parseInt(tokens.nextToken().trim());
			placa[1] = Integer.parseInt(tokens.nextToken().trim());
			numberBin = Integer.parseInt(tokens.nextToken().trim());

			pecas = new int[numberBin][2];
			quant = new int[numberBin];

			for (int i = 0; i < numberBin; i++) {
				caracter = scn.nextLine();
				tokens = new StringTokenizer(caracter);
				pecas[i][0] = Integer.parseInt(tokens.nextToken().trim());
				pecas[i][1] = Integer.parseInt(tokens.nextToken().trim());
				quant[i] = Integer.parseInt(tokens.nextToken().trim());
			}

		} catch (FileNotFoundException e) {
			System.out.println("Arquivo " + filename + " Não encontrado");
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
