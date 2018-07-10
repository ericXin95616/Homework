
import java.lang.Math;

public class HW1 {
	public static void func1() {
		int f = 0;
		int g = 1;
		for(int i = 0; i <= 15; ++i) {
			StdOut.println(f);
			f = f + g;
			g = f - g;
		}
	}
	
	public static double sqrt(double t) {
		double temp = t;
		while(Math.abs(t - temp / t) > 1.0e-6) {
			t = (temp / t + t) / 2.0;
		}
		return t;
	}
	
	public static int sum1() {
		int sum = 0;
		for(int i = 1; i < 1000; ++i)
			for(int j = 0; j < i; ++j)
				++sum;
		return sum;
	}
	
	public static int sum2() {
		int sum = 0;
		for(int i = 1; i < 1000; i *= 2)
			for(int j = 0; j < 1000; ++j)
				++sum;
		return sum;
	}
	
	public static String intToBinary(int num) {
		String s = "";
		while(num != 0) {
			s = num % 2 + s;
			num = num / 2;
		}
		return s;
	}
	
	public static void print2DArray(int row, int col) {
		boolean[][] arr = new boolean[row][col];
		for(int i = 0; i < row; ++i) {
			for(int j = 0; j < col; ++j) {
				if(StdRandom.uniform(0.0, 1.0) < 0.5) 
					arr[i][j] = true;
				else arr[i][j] = false;
			}
		}
		
		StdOut.printf("  ");
		for(int i = 0; i < col ; ++i) {
			StdOut.printf("%d ", i);
		}
		StdOut.println();
		
		for(int i = 0; i < row; ++i) {
			StdOut.printf("%d ", i);
			for(int j = 0; j < col; ++j) {
				StdOut.printf("%c ", arr[i][j] ? '*' : ' ');
			}
			StdOut.println();
		}
	}
	
	public static String exR1(int n) {
		if(n <= 0) return "";
		return exR1(n - 3) + n + exR1(n - 2) + n;
	}
	
	public static long Fibonacci1(int N) {
		if( N == 0) return 0;
		if( N == 1) return 1;
		return Fibonacci1(N - 1) + Fibonacci1(N - 2);
	}
	
	public static long Fibonacci2(int N, long n0, long n1) {
		if(N == 0) return n0;
		if(N == 1) return n1;
		return Fibonacci2(--N, n1, n1 + n0);
	}
	
	public static void randomConnection(int N, double p) {
		StdDraw.setXscale(-1.0, 1.0);
		StdDraw.setYscale(-1.0, 1.0);
		StdDraw.circle(0.0, 0.0, 1.0);
		StdDraw.setPenRadius(1.0e-6);
		
		double[][] arr = new double[N][2];
		for(int i = 0; i < N; ++i) {
				arr[i][0] = Math.cos(2*i*Math.PI/N);
				arr[i][1] = Math.sin(2*i*Math.PI/N);
		}
		for(int i = 0; i < N; ++i) {
			StdDraw.point(arr[i][0], arr[i][1]);
		}
		StdDraw.setPenColor(StdDraw.GRAY);
		for(int i = 0; i < N; ++i) {
			for(int j = i + 1; j < N; ++j) {
				if(StdRandom.uniform(0.0, 1.0) < p)
					StdDraw.line(arr[i][0], arr[i][1], arr[j][0], arr[j][1]);
			}
		}
	}
	
	public static void main(String[] args) {
		//func1();
		StdOut.printf("%.5f\n", sqrt(9.0));
		StdOut.println(sum1());
		StdOut.println(sum2());
		System.out.println('b');
		System.out.println('b' + 'c');
		System.out.println((char)('a' + 4));
		StdOut.println(intToBinary(23897));
		StdOut.println(Integer.toBinaryString(23897));
		print2DArray(10, 10);
		StdOut.println(exR1(6));
		randomConnection(Integer.parseInt(args[0]), Double.parseDouble(args[1]));
		/*
		StdOut.println("Fibonacci1:");
		for(int i = 0; i < 50; ++i) {
			StdOut.println(i + " " + Fibonacci1(i));
		}
		
		StdOut.println("Fibonacci2:");
		for(int i = 0; i < 100; ++i) {
			StdOut.println(i + " " + Fibonacci2(i, 0, 1));
		}
		*/
	}
}



