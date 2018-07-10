
import java.util.Arrays;

public class RandomGeneration {
	public static void main(String[] args) {
		int arraySize = Integer.parseInt(args[0]);
		int generateTime = Integer.parseInt(args[1]);
		
		StdOut.println(arraySize);
		for(int i = 0; i < generateTime; ++i) {
			for(int j = 0; j < arraySize; ++j) {
				// random numbers are from 0 to 100
				StdOut.printf("%d ", StdRandom.uniform(100));
			}
			StdOut.println();
		}
	}
}
