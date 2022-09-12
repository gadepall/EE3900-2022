#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct
{
	double Re; 
	double Im;
} complex;

void fft(complex *X, int n)
{
	if(n <= 1) return;
	
	//Arrays for Odd and Even halves
	complex *X_odd = (complex *) malloc(n/2 * sizeof(complex));
	complex *X_even = (complex *) malloc(n/2 * sizeof(complex));
	
	for(int i = 0; i < n/2; i++) 
	{
		X_even[i] = X[2*i];
		X_odd[i] = X[2*i+1];
	}
	
	//Recursive Calls
	fft(X_even, n/2);	 	
	fft(X_odd, n/2);		
	
	//FFT computation
	for(int i = 0; i < n/2; i++) 
	{
		double cosine = cos(2*M_PI*i/n);
		double sine = sin(2*M_PI*i/n);
		
		complex z;
		
		z.Re = cosine * X_odd[i].Re + sine * X_odd[i].Im;	
		z.Im = cosine * X_odd[i].Im - sine * X_odd[i].Re;	
		
		X[i].Re = X_even[i].Re + z.Re;
		X[i].Im = X_even[i].Im + z.Im;
		
		X[i+n/2].Re = X_even[i].Re - z.Re;
		X[i+n/2].Im = X_even[i].Im - z.Im;
	}
	
	free(X_odd);
	free(X_even);
}

int main()
{	
	int n = 8;  
	double x[] = {1,2,3,4,2,1,4,3};
	
	complex *X = (complex *) malloc(n * sizeof(complex));
	
	for(int i = 0; i < n; i++) 
	{
		X[i].Re = x[i];
		X[i].Im = 0;
	}
	fft(X, n);
	
	for(int i = 0; i < n; i++) 
		printf("(%.5lf, %.5lf)\n", X[i].Re, X[i].Im);
}

