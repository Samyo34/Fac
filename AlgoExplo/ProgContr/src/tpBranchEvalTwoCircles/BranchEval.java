
package tpBranchEvalTwoCircles;

import java.util.Stack;

import util.*;

public class BranchEval {

	Constraint[] ctrs;     // list of constraints

	Box[] solutions;       // list of solutions

	int numSolutions;      // number of solutions found

	public BranchEval(Constraint[] _ctrs) {
		this.ctrs = _ctrs;
		this.solutions = new Box[1000];
		this.numSolutions = 0;
	}

	public boolean solve(Box x0, double eps) {

		this.numSolutions = 0;

		int N=x0.dim();

		Stack<Box> s=new Stack<Box>();

		s.push(x0);
		int count=0; // number of branchings

		while (!s.empty()) {

			Box x=s.pop();
			if(!(ctrs[0].violated(x) || ctrs[1].violated(x))){
				if(!x.isEmpty() && x.maxDiam() <= eps){
					solutions[numSolutions++] = x;
				}else{
					Pair<Box,Box> sol = x.bisect();
					s.add(sol.fst);
					s.add(sol.snd);
				}
						
			}
			count++;

		}

		// Print solutions:

		System.out.println("Number of potential solutions = " + numSolutions + 
				" found with " + count + " branchings !");     
		System.out.print("List of solutions: ");
		for (int i=0; i < numSolutions; i++) {
			System.out.print(solutions[i] + " | ");
		}
		System.out.println("");
		return (numSolutions > 0);
	}
}
