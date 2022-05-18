#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double(*function)(double x);
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double df1(double x);
extern double df2(double x);
extern double df3(double x);

int iteration;


// if true - case 1 (tangent method - take right point, chord method - right segment)
int method_case (function f, function g, double a, double b) {
	double F1 = f(a/2 + b/2) - g(a/2 + b/2);
	double F2 = (f(a) - g(a) + f(b) - g(b))/2;
	double Fa = f(a) - g(a);

	// Fa > 0 => decreases, else => increases
	// F1 - F2 > 0 => above chord, else - below
	return (Fa * (F1 - F2)) > 0;
}

// [*A, *B] - segment after 1 iteration of chord method
double chord_method_seg (function f, function g, double a, double b, double *A, double *B) {
	int mcase = method_case(f, g, a, b);

	double Fa = f(a) - g(a);
	double Fb = f(b) - g(b);

	double chord = (a * Fb - b * Fa) / (Fb - Fa);

	if (mcase) {
		*A = chord;
	} else {
		*B = chord;
	}
}


// [*A, *B] - segment after 1 iteration of tangent method
double tangent_method_seg (function f, function g, function df, function dg, double a, double b, double *A, double *B)
{
	double d = a;
	int mcase = method_case(f, g, a, b);

	if (mcase) {
		d = b;
	}

	double Fd = f(d) - g(d);
	double dFd = df(d) - dg(d);
	double tangent = d - Fd/ dFd;

	if (mcase) {
		*B = tangent;
	} else {
		*A = tangent;
	}
}


// use combined method (both chord and tangent) to find root  of f(x) - g(x) = 0, count iterations
double combined_method (function f, function g, function df, function dg, double a, double b, double eps1, int *iter)
{

	if ((f(a) - g(a)) * (f(b) - g(b)) > 0.0) {
		printf("Segment selected unsuccessfully. Try other boundaries.\n");
		return NAN;
	}

	if (b - a < eps1)
	{
		return a/2 + b/2;
	}

	double A = a, B = b;

	tangent_method_seg(f, g, df, dg, a, b, &A, &B);
	chord_method_seg(f, g, a, b, &A, &B);

	if (iter != NULL) {
		(*iter)++;
	}
	return combined_method(f, g, df, dg, A, B, eps1, iter);
}

// -iter
void iterations(double eps1, double eps2) {
	printf("Iterations:\n");

	int iter = 0;

	double x1 = combined_method(f1, f3, df1, df3, -2, 0, eps1, &iter);
	printf("  f1, f3: \t x = %lf \t\t iterations:  \t%d\n", x1, iter);
	iter = 0;
	double x2 = combined_method(f2, f3, df2, df3, 0, 2, eps1, &iter);
	printf("  f2, f3: \t x = %lf \t\t iterations:  \t%d\n", x2, iter);
	iter = 0;
	double x3 = combined_method(f1, f2, df1, df2, 0, 2, eps1, &iter);
	printf("  f1, f2: \t x = %lf \t\t iterations:  \t%d\n", x3, iter);
	iter = 0;

	printf("Area = %lf\n", area_I(x1, x2, x3, eps2));
}

int main (int argc, char *argv[]){
	double fst13 = -5, lst13 = -0,005;
	double fst23 = -5, lst23 = -0,005;
	double fst12 = -5, lst12 = 5;

	double eps1 = 0.00001;
	double eps2 = 0.00001;

	for (int i = 1; i < argc; i++){
		if (!strcmp(argv[i], "--test-integral")){

		}

		if (!strcmp(argv[i], "--test-root")){

		}

		if (!strcmp(argv[i], "--help")){
			printf(
				"Hello there!\nHelp:\nCommands, which you allowed to use:\n\n--points : Prints intersection points\n--iterations : Prints number of iterations, used in counting approximate intersection points\n--area : Prints area of figure\n--test-integral : Test integral function\n--test-root : Test root function\n"
			);
		}

		if (!strcmp(argv[i], "--points")){

		}

		if (!strcmp(argv[i], "--iterations")){
                iterations(eps1, eps2);
		}

		if (!strcmp(argv[i], "--area")){

		}
	}

    return 0;
}
