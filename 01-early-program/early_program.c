/* Author: Daniel Zhang 
 * Date: 7/14/2026
 * Program name:Taylor's Spellbook 
 * File: early_program.c
 *
 * Problem: Approximate 1/(1-x) using a Taylor series:
 * 1 + x + x^2 + x^3 + ... (valid only for |x| < 1)
 */
#include <stdio.h>
#include <math.h>

int main(void) {
    double x;
    double approx = 0;
    double actual = 0;
    int terms;

    while(1){
    printf("Enter x: ");
    scanf("%lf", &x);
    if (fabs(x) >= 1)           //we have to use fabs for absolute value for x because abs() is for integers but x is a double from math.h
    {
        printf("Invalid x value, please write another\n");
    }
    else 
    {
        while(fabs(x) < 1)
        {
            printf("Enter number of terms: ");
            scanf("%d", &terms);
            if (terms <= 0)
            {
                printf("Invalid terms, please write another\n");
            }
            else
            {
                for(int n = 0; n < terms; n++)
                {
                approx += (pow(x,n));       //pow(variable,exponent) is the one we use for exponents and its is from math.h
                }
            actual = 1/(1-x);
            printf("The actual value is: %.3lf\n", actual);             //%.3lf is to print 3 decimal points (.3)
            printf("The Taylor approximation is: %.3lf", approx);
            break;
            }
        }
        break;
    }

}
    return 1;       //return a success and stop the program
}