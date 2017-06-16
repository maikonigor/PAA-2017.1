import java.io.IOException;

import jmetal.metaheuristics.singleObjective.particleSwarmOptimization.PSO_main;
import jmetal.util.JMException;

public class Main {

	public static void main(String[] args) {
		
		try {
			
			
			for (int i = 0; i < 30; i++) {
				PSO_main.main("instance1.txt");
				PSO_main.main("instance2.txt");
				PSO_main.main("instance5.txt");
				PSO_main.main("instance7.txt");
				PSO_main.main("instance9.txt");
				PSO_main.main("instance12.txt");
				PSO_main.main("instance13.txt");
				PSO_main.main("instance14.txt");
				PSO_main.main("instance17.txt");
			}
			
//			PSO_main.main("instance2.txt");
			
		} catch (ClassNotFoundException | JMException | IOException e) {
			e.printStackTrace();
		}
		

	}
	
	
	
	

}
