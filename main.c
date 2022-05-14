#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef double(*function)(double x);
																										  //asm functions
extern double f1(double x);
extern double f2(double x);
extern double f3(double x);
extern double df1(double x);
extern double df2(double x);
extern double df3(double x);

int iterations;																					  //iteration counter

double root(function fx1, function fx2, double a, double b, function dfx1, function dfx2, double eps1){
	iterations = 0;

	double x0 = (a + b) / 2;
	double x1  = x0 - (fx1(x0) - fx2(x0)) / (dfx1(x0) - dfx2(x0));					  //Newton's method

	while (fabs(x1 - x0) > eps1){
		iterations++;

		x0 = x1;
		x1 = x0 - (fx1(x0) - fx2(x0)) / (dfx1(x0) - dfx2(x0));
	}

	return x1;
}

double integral(function f, double a, double b, double eps2){
	double ans = 0.0;
	double delta = (b - a) / 25;															     //divide interval to increase accuracy

	for (int i = 1; i <= 25; i++){
		ans += ((delta) / 6) * (f(a + delta * (i - 1)) + 4 * f((a + delta * (i - 1) + a + delta * i) / 2) + f(a + delta * i));
	}

	return ans;																    					  //Simpson's rule
}

void test_intg(function f1, function f2, function f3, double eps){
	double temp;

	printf("TESTING f1:\n");
	printf("Test 1\n");
	printf("Left: 0.000000\nRight: 10.000000\nAccuracy: 0.0001\n");
	temp = integral(f1, 0.000000, 10.000000, 0.0001);
	printf("Counted integral: %f\n", temp);
	printf("Integral to 4 digits after point: %f\n", 6.736600);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(temp - 6.736600) < eps) ? printf("YES\n\n") : printf("NO\n\n");

	printf("Test 2\n");
	printf("Left: -5.000000\nRight: 1.000000\nAccuracy: 0.0001\n");
	temp = integral(f1, -5.000000, 1.000000, 0.0001);
	printf("Counted integral: %f\n", temp);
	printf("Integral to 4 digits after point: %f\n", 4.216900);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(temp - 4.216900) < eps) ? printf("YES\n\n") : printf("NO\n\n");

	printf("Test 3\n");
	printf("Left: 1.000000\nRight: 17.000000\nAccuracy: 0.0001\n");
	temp = integral(f1, 1.000000, 17.000000, 0.0001);
	printf("Counted integral: %f\n", temp);
	printf("Integral to 4 digits after point: %f\n", 4.525200);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(temp - 4.525200) < eps) ? printf("YES\n\n\n") : printf("NO\n\n\n");


	printf("TESTING f2:\n");
	printf("Test 1\n");
	printf("Left: 0.000000\nRight: 1.000000\nAccuracy: 0.0001\n");
	temp = integral(f2, 0.000000, 1.000000, 0.0001);
	printf("Counted integral: %f\n", temp);
	printf("Integral to 6 digits after point: %f\n", 0.989043);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(temp - 0.989043) < eps) ? printf("YES\n\n") : printf("NO\n\n");

	printf("Test 2\n");
	printf("Left: 0.000000\nRight: 3.000000\nAccuracy: 0.0001\n");
	temp = integral(f2, 0.000000, 3.000000, 0.0001);
	printf("Counted integral: %f\n", temp);
	printf("Integral to 5 digits after point: %f\n", 4.129560);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(temp - 4.129560) < eps) ? printf("YES\n\n") : printf("NO\n\n");

	printf("Test 3\n");
	printf("Left: 1.000000\nRight: 17.000000\nAccuracy: 0.0001\n");
	temp = integral(f2, 1.000000, 17.000000, 0.0001);
	printf("Counted integral: %f\n", temp);
	printf("Integral to 4 digits after point: %f\n", 47.580400);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(temp - 47.580400) < eps) ? printf("YES\n\n\n") : printf("NO\n\n\n");


	printf("TESTING f3:\n");
	printf("Test 1\n");
	printf("Left: -2.000000\nRight: 2.000000\nAccuracy: 0.0001\n");
	temp = integral(f3, -2.000000, 2.000000, 0.0001);
	printf("Counted integral: %f\n", temp);
	printf("Integral to 4 digits after point: %f\n", 7.253700);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(temp - 7.253700) < eps) ? printf("YES\n\n") : printf("NO\n\n");

	printf("Test 2\n");
	printf("Left: -1.000000\nRight: 7.000000\nAccuracy: 0.0001\n");
	temp = integral(f3, -1.000000, 7.000000, 0.0001);
	printf("Counted integral: %f\n", temp);
	printf("Integral to 4 digits after point: %lf\n", 2.717400);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(temp - 2.717400) < eps) ? printf("YES\n\n") : printf("NO\n\n");

	printf("Test 3\n");
	printf("Left: 0.000000\nRight: 1.000000\nAccuracy: 0.0001\n");
	temp = integral(f3, 0.000000, 1.000000, 0.0001);
	printf("Counted integral: %f\n", temp);
	printf("Integral to 5 digits after point: %lf\n", 0.632120);
	printf("Does the counted integral support 0.001 accuracy? ");
	(fabs(temp - 0.632120) < eps) ? printf("YES\n\n\n") : printf("NO\n\n\n");

}

void test_root(function fx1, function fx2, function fx3, function dfx1, function dfx2, function dfx3){
	char a[3];
	char b[3];
	function func_1, func_2, dfunc_1, dfunc_2;
	double left, right, epsilon;
	double temp;


	printf("Input example: f1 f2 1.0 3.0 0.001\n");
	printf("Input name of first function, second function, left and right borders, epsilon\n");
	scanf("%s %s %lf %lf %lf", a, b, &left, &right, &epsilon);

	if (!strcmp(a, "f1")){
		func_1 = fx1;
		dfunc_1 = dfx1;
	}
	else if (!strcmp(a, "f2")){
		func_1 = fx2;
		dfunc_1 = dfx2;
	}
	else if (!strcmp(a, "f3")){
		func_1 = fx3;
		dfunc_1 = dfx3;
	}

	if (!strcmp(b, "f1")){
		func_2 = fx1;
		dfunc_2 = dfx1;
	}
	else if (!strcmp(b, "f2")){
		func_2 = fx2;
		dfunc_2 = dfx2;
	}
	else if (!strcmp(b, "f3")){
		func_2 = fx3;
		dfunc_2 = dfx3;
	}

	temp = root(func_1, func_2, left, right, dfunc_1, dfunc_2, epsilon);

	if (!isnan(temp)){
		printf("Root of %s(x) = %s(x) is %lf", a, b, temp);
	}
	else{
		printf("No root on this interval\n");
	}

}

int main(int argc, char* argv[]){															  //driver function
	printf("Type --help to see available commands\n\n");								  //intro

	double eps1 = 0.0001;
	double eps2 = 0.0001;
	double eps = 0.001;

	double f1_U_f2 = root(f1, f2, 1.0, 2.0, df1, df2, eps1);							  //intersection point
	int iterations_f1_f2 = iterations;														  //memorize iteration count
	double f2_U_f3 = root(f2, f3, -1.0, 1.0, df2, df3, eps1);						  //intersection point
	int iterations_f2_f3 = iterations;												        //memorize iteration count
	double f1_U_f3 = root(f1, f3, -1.0, 1.0, df1, df3, eps1);						  //intersection point
	int iterations_f1_f3 = iterations;														  //memorize iteration count

	double integral_a_b = integral(f1, f1_U_f3, f1_U_f2, eps2);						  //area of whole figure equals
	double integral_a_c = integral(f3, f1_U_f3, f2_U_f3, eps2);						  //area of figure under f1 from f1_U_f3 to f1_U_f2 without 2 areas:
	double integral_c_b = integral(f2, f2_U_f3, f1_U_f2, eps2);						  //area under f3 from f1_U_f3 to f2_U_f3 and area under f2 from f2_U_f3 to f1_U_f2

	double ans = integral_a_b - integral_a_c - integral_c_b;

	for (int i = 1; i < argc; i++){
		if (!strcmp(argv[i], "--test-integral")){
			test_intg(f1, f2, f3, eps);
		}

		if (!strcmp(argv[i], "--test-root")){
			test_root(f1, f2, f3, df1, df2, df3);
		}

		if (!strcmp(argv[i], "--help")){
			printf(
				"Guten Tag!\nHelp:\nCommands available:\n\n--points : Prints intersection points\n--iterations : Prints number of iterations, used in counting approximate intersection points\n--area : Prints area of figure\n--test-integral : Test integral function\n--test-root : Test root function\n"
			);
		}

		if (!strcmp(argv[i], "--points")){
			printf("Intersection of f1 and f2: (%f, %f)\n", f1_U_f2, f1(f1_U_f2));
			printf("Intersection of f2 and f3: (%f, %f)\n", f2_U_f3, f2(f2_U_f3));
			printf("Intersection of f1 and f3: (%f, %f)\n", f1_U_f3, f1(f1_U_f3));
		}

		if (!strcmp(argv[i], "--iterations")){
			printf("Iterations of f1: %d\n", iterations_f1_f2);
			printf("Iterations of f2: %d\n", iterations_f2_f3);
			printf("Iterations of f3: %d\n", iterations_f1_f3);
		}

		if (!strcmp(argv[i], "--area")){
			printf("\nArea of figure: %lf\n", ans);
		}
	}

	return 0;
}
