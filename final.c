#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double df1(double x);
extern double df2(double x);
extern double df3(double x);

// if true - case 1 (tangent method - take right point, chord method - right segment)
int method_case (double f (double), double g (double), double a, double b) {
	double F1 = f(a/2 + b/2) - g(a/2 + b/2);
	double F2 = (f(a) - g(a) + f(b) - g(b))/2;
	double Fa = f(a) - g(a);

	// Fa > 0 => decreases, else => increases
	// F1 - F2 > 0 => above chord, else - below
	return (Fa * (F1 - F2)) > 0;
}

// [*A, *B] - segment after 1 iteration of chord method
double chord_method_seg (double f (double), double g (double), double a, double b, double *A, double *B) {
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
double tangent_method_seg (double f (double), double g (double), double df (double), double dg (double) , double a, double b, double *A, double *B)
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
double combined_method (double f (double) , double g (double), double df (double), double dg (double), double a, double b, double eps1, int *iter)
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

// Integrate f(x) spliting segment [a, b] into n parts
double integral_n(double f (double), double a, double b, double eps2, double Iprev, int n){
	double h = (b - a)/n;
	double In = 0;

	for (int i = 0; i < n; ++i) {
		In += f(a + h * (i+0.5));
	}

	In *= h;

	if (n > 1000000) {
		printf ("Integration takes too many (> 1 000 000) iterations.\n");
		return In;
	}

	if (fabs(Iprev - In)/3 < eps2) {
		return In;
	} else {
		return integral_n(f, a, b, eps2, In, 2 * n);
	}
}


// Area between curves calculate integrals
double area_I(double x1, double x2, double x3, double eps2) {

	double I1 = integral_n(f1, x1, x3, eps2, 0.0, 5);
	double I2 = integral_n(f2, x2, x3, eps2, 0.0, 5);
	double I3 = integral_n(f3, x1, x2, eps2, 0.0, 5);
	return -I1 + I2 + I3;
}

// Area between curves with an accuracy of eps
double curves_area (double a13, double b13, double a23, double b23, double a12, double b12, double eps1, double eps2) {
	double x1 = combined_method(f1, f3, df1, df3, a13, b13, eps1, NULL);
	double x2 = combined_method(f2, f3, df2, df3, a23, b23, eps1, NULL);
	double x3 = combined_method(f1, f2, df1, df2, a12, b12, eps1, NULL);

	double I = area_I(x1, x2, x3, eps2);

	return I;
}


// -root
void intersection(double eps1, double eps2) {
	printf("Intersection:\n");

	double x1 = combined_method(f1, f3, df1, df3, -4, -1, eps1, NULL);
	printf("  f1, f3: \t x = %lf \t\t iterations:  \t%lf\n", x1, f1(x1));

	double x2 = combined_method(f2, f3, df2, df3, -5, -0.005, eps1, NULL);
	printf("  f2, f3: \t x = %lf \t\t iterations:  \t%lf\n", x2, f2(x2));

	double x3 = combined_method(f1, f2, df1, df2, -5, 2, eps1, NULL);
	printf("  f1, f2: \t x = %lf \t\t iterations:  \t%lf\n", x3, f1(x3));

}

// -iter
void iterations(double eps1, double eps2) {
	printf("Iterations:\n");

	int iter = 0;

	double x1 = combined_method(f1, f3, df1, df3, -4, -1, eps1, &iter);
	printf("  f1, f3: \t x = %lf \t\t iterations:  \t%d\n", x1, iter);
	iter = 0;
	double x2 = combined_method(f2, f3, df2, df3, -5, -0.005, eps1, &iter);
	printf("  f2, f3: \t x = %lf \t\t iterations:  \t%d\n", x2, iter);
	iter = 0;
	double x3 = combined_method(f1, f2, df1, df2, -5, 2, eps1, &iter);
	printf("  f1, f2: \t x = %lf \t\t iterations:  \t%d\n", x3, iter);
	iter = 0;

}

void test_integral(double a13, double b13, double a23, double b23, double a12, double b12, double eps1, double eps2){
	double x1 = combined_method(f1, f3, df1, df3, a13, b13, eps1, NULL);
	double x2 = combined_method(f2, f3, df2, df3, a23, b23, eps1, NULL);
	double x3 = combined_method(f1, f2, df1, df2, a12, b12, eps1, NULL);
	
	printf("Insert the number of function, which you want to integrate");
	int n;
	scanf("%d", &n);
	
	if(n == 1){
	double I1 = integral_n(f1, x1, x3, eps2, 0.0, 5);
	printf("Counted integral: %lf\n", I1);
	printf("Integral to 6 digits after point: %lf\n", 10.689474);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(I1 - 10.689488) < eps2) ? printf("YES\n\n") : printf("NO\n\n");
	}
	if(n == 2){
	double I1 = integral_n(f2, x2, x3, eps2, 0.0, 5);
	printf("Counted integral: %lf\n", I1);
	printf("Integral to 6 digits after point: %lf\n", 13.145205);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(I1 - 13.145205) < eps2) ? printf("YES\n\n") : printf("NO\n\n");
	}
	if(n == 3){
	double I1 = integral_n(f3, x1, x2, eps2, 0.0, 5);
	printf("Counted integral: %lf\n", I1);
	printf("Integral to 6 digits after point: %lf\n", 7.351228);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(I1 - 7.351228) < eps2) ? printf("YES\n\n") : printf("NO\n\n");
	}
}

void test_root(double eps1, double eps2) {
	printf("Between which functions do you want to find root?\n\n1 for f1 and f3\n\n2 for f2 anf f3\n\n3 for f1 and f2");
	int ncase;
	scanf("%d", &ncase);
	printf("Between which borders do you want to find the root?");
	double fst1, lst2;
	scanf("%lf %lf", &fst1, &lst2);
	
	if(ncase == 1){
	double x1 = combined_method(f1, f3, df1, df3, fst1, lst2, eps1, NULL);
	printf("Counted integral: %lf\n", x1);
	printf("Root to 6 digits after point: %lf\n", -2.390537);
	printf("Does the counted root support 0.001 accuracy? ");
	(fabs(x1 - -2.390537) < eps2) ? printf("YES\n\n") : printf("NO\n\n");
	}
	if(ncase == 2){
	double x1 = combined_method(f1, f3, df1, df3, fst1, lst2, eps1, NULL);
	printf("Counted integral: %lf\n", x1);
	printf("Root to 6 digits after point: %lf\n", -0.549510);
	printf("Does the counted root support 0.001 accuracy? ");
	(fabs(x1 - -0.549510) < eps2) ? printf("YES\n\n") : printf("NO\n\n");
	}
	if(ncase == 3){
	double x1 = combined_method(f1, f3, df1, df3, fst1, lst2, eps1, NULL);
	printf("Counted integral: %lf\n", x1);
	printf("Root to 6 digits after point: %lf\n", 1.251758);
	printf("Does the counted root support 0.001 accuracy? ");
	(fabs(x1 - 1.251758) < eps2) ? printf("YES\n\n") : printf("NO\n\n");
	}
}

int main (int argc, char *argv[]){
	double fst13 = -5, lst13 = -0.005;
	double fst23 = -5, lst23 = -0.005;
	double fst12 = -5, lst12 = 5;

	double eps1 = 0.00001;
	double eps2 = 0.00001;

	for (int i = 1; i < argc; i++){
		if (!strcmp(argv[i], "--test-integral")){
			test_integral(fst13, lst13, fst23, lst23, fst12, lst12, 0.00001, 0.00001);
		}

		if (!strcmp(argv[i], "--test-root")){
			test_root(eps1, eps2);
		}

		if (!strcmp(argv[i], "--help")){
			printf(
				"Hello there!\nHelp:\nCommands, which you allowed to use:\n\n--points : Prints intersection points\n--iterations : Prints number of iterations, used in counting approximate intersection points\n--area : Prints area of figure\n--test-integral : Test integral double (double)\n--test-root : Test root double (double)\n"
			);
		}

		if (!strcmp(argv[i], "--points")){
			intersection(eps1, eps2);
		}

		if (!strcmp(argv[i], "--iterations")){
                iterations(eps1, eps2);
		}

		if (!strcmp(argv[i], "--area")){
			printf("Area = %lf\n", curves_area(fst13, lst13, fst23, lst23, fst12, lst12, 0.00001, 0.00001));
		}
	}

    return 0;
}
