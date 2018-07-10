
import java.util.Arrays;
import java.lang.Thread;

public class VisualTrackOfSortAlgorithm {
	public static void main(String[] args) {
		// read the size of sorted array
		int arraySize = StdIn.readInt();
		int[] array = new int[arraySize];
		StdDraw.setCanvasSize(800,800);
		StdDraw.setScale(-0.05, 1.05);
		while(!StdIn.isEmpty()) {
			// read the whole array
			for(int i = 0; i < arraySize; ++i) {
				array[i] = StdIn.readInt();
			}
			
			// using StdDraw to present it
			StdDraw.clear();
			for(int i = 0; i < arraySize; ++i) {
				double x = 1.0*i/arraySize;
				double y = array[i]/200.0;
				double rw = 0.5 / arraySize;
				double rh = array[i]/200.0;
				StdDraw.rectangle(x, y, rw, rh);
			}
			try {
				Thread.sleep(1000);
			} catch(InterruptedException ex){
				//Thread.currentThread().interrept();
			}
		}
	}
}
