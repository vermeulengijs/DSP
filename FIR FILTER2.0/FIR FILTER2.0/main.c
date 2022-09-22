#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define pi (4*atan(1.0))
#define size(x) (sizeof(x)/sizeof(x[0]))

void convolution(double in1[], int in1len, double in2[], int in2len, double *out);
void DFT(double *in, int N, double *out_Re, double *out_Im, double *out_mag, double *out_phase);
void generate_sinewave(double Amp, double freq, double freqs, double phase, int amount, double *output);
void add_waves(int N, double *in1, double *in2, double *out);

int main(int argc, char *argv[]){

	double *wave1, *wave2, *som, *X_Re, *X_Im, *X_mag, *X_phase, *Y_Re, *Y_Im, *Y_mag, *Y_phase;
	double A = 1, f = 2000, fs = 16000, phase = 0;
	int samples = 16;
	int i;
	double h[20] = { 0.0024299026793099168,
		-0.0036194227325605918,
		-0.0045823837540180812,
		0.023830888614483733,
		-0.034411729138247721,
		0.0059983453227902619,
		0.060983749757701378,
		-0.10332269715906811,
		0.0083691782273127985,
		0.54469607713356805,
		0.54469607713356805,
		0.0083691782273127985,
		-0.10332269715906811,
		0.060983749757701378,
		0.0059983453227902619,
		-0.034411729138247721,
		0.023830888614483733,
		-0.0045823837540180812,
		-0.0036194227325605918,
		0.0024299026793099168 };
	double *y;
	int somlen = 4 * samples;
	int hlen = size(h);


	y = (double*)calloc((4 * samples), sizeof(double));
	wave1 = (double*)calloc(4 * samples, sizeof(double));
	wave2 = (double*)calloc(4 * samples, sizeof(double));
	som = (double*)calloc(4 * samples, sizeof(double));
	X_Re = (double*)calloc(samples, sizeof(double));
	X_Im = (double*)calloc(samples, sizeof(double));
	X_mag = (double*)calloc(samples, sizeof(double));
	X_phase = (double*)calloc(samples, sizeof(double));
	Y_Re = (double*)calloc(samples, sizeof(double));
	Y_Im = (double*)calloc(samples, sizeof(double));
	Y_mag = (double*)calloc(samples, sizeof(double));
	Y_phase = (double*)calloc(samples, sizeof(double));

	generate_sinewave(A, f, fs, phase, 4 * samples, wave1);
	A = 1;
	f = 6000;
	phase = 0;
	generate_sinewave(A, f, fs, phase, 4 * samples, wave2);
	add_waves(4 * samples, wave1, wave2, som);
	DFT(som, samples, X_Re, X_Im, X_mag, X_phase);

	convolution(som, somlen, h, hlen, y);
	DFT(y + (3 * samples), samples, Y_Re, Y_Im, Y_mag, Y_phase);

	printf("DFT of original sequence:\n---------------------\n");
	for (i = 0; i < samples; i++){
		printf("%.15lf\n", X_mag[i]);
	}
	printf("DFT of filtered sequence:\n---------------------\n");
	for (i = 0; i < samples; i++){
		printf("%.15lf\n", Y_mag[i]);
	}

	return 0;
}

void generate_sinewave(double Amp, double freq, double freqs, double phase, int N, double *out){
	int i;
	for (i = 0; i < N; i++){
		out[i] = Amp*sin((2 * pi*i*freq / freqs) + phase);
	}

}
void add_waves(int N, double *in1, double *in2, double *out){
	int i;
	for (i = 0; i < N; i++){
		out[i] = in1[i] + in2[i];
	}
}
void DFT(double *in, int N, double *out_Re, double *out_Im, double *out_mag, double *out_phase){

	int m, n;

	for (m = 0; m < N; m++){
		for (n = 0; n < N; n++){
			out_Re[m] = out_Re[m] + (in[n] * (cos(2 * pi*m*n / N)));
			out_Im[m] = out_Im[m] + (in[n] * (-sin(2 * pi*m*n / N)));
		}
		out_mag[m] = sqrt((out_Re[m] * out_Re[m]) + (out_Im[m] * out_Im[m]));
		out_phase[m] = atan(out_Im[m] / out_Re[m]) * 180 / pi;
	}
}
void convolution(double *x, int xlen, double *h, int hlen, double *y){
	int kmax;
	int kmin;
	int k;
	int n;

	for (n = 0; n < (xlen + hlen - 1); n++){
		if (n <= (xlen - 1)){
			kmax = n;
		}
		else{
			kmax = (xlen - 1);
		}

		if (n <= (hlen - 1)){
			kmin = 0;
		}
		else{
			kmin = n - (hlen - 1);
		}
		for (k=kmin; k <= kmax; k++){
			y[n] = y[n] + (x[k] * h[n - k]);
		}
	}
}
