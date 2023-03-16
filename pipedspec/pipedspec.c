#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include "cpgplot.h"
#include <fftw3.h>

#define NFFT 4096

void linspace(double *arra, double low_value, double high_value, int N_points)
{
	int i;
	double res;
	res = (high_value-low_value)/N_points;
	for (i=0; i<N_points; i++)
	{
		arra[i]=low_value+(i*res);
	}
}			

float array_min(float *in_array, int N_points)
{
    float min = in_array[0];
    int i;
    for(i=1; i<N_points; i++)
    {
        if(in_array[i] < min)
        {
            min = in_array[i];
        }
    }
    return min;
}

float array_max(float *in_array, int N_points)
{
	float max = in_array[0];
    int i;
    for(i=1; i<N_points; i++)
    {
        if(in_array[i] > max)
        {
            max = in_array[i];
        }
    }
    return max;
}

void plot(double *xpts, double *ypts, int N_points)
{
	float x_vals[N_points];
	float y_vals[N_points];
	int i;
	// char title[100];	
	for (i=0; i<N_points;i++)
	{
		x_vals[i] = (float)xpts[i];
		y_vals[i] = (float)(log((double)ypts[i]));
        // y_vals[i] = (float)ypts[i];

	}
	cpgopen("/xserve"); 
	cpgenv(x_vals[0], x_vals[N_points-1], array_min(y_vals, N_points)*0.9, array_max(y_vals, N_points), 0, 1); 
	cpgline(N_points, x_vals, y_vals); 
	// cpgtext(x_vals[N_points/2-10], array_min(y_vals, N_points)*1.2-(array_max(y_vals, N_points)-array_min(y_vals, N_points))/10.0, "Freq (MHZ)");
	// cpgptxt(x_vals[0] - (x_vals[4]-x_vals[0]), (array_min(y_vals, N_points)+array_max(y_vals, N_points))/2, 90.0, 0.0, "Power (arb dB)");
	
	cpgclos(); 
}

int main()
{
    int i, k, naver, r;

    fftw_plan p;
    double x_here[NFFT], power_spectrum[NFFT], avg_power_spec[NFFT];
    fftw_complex *inp_data, *out;
    unsigned char read_buffer[NFFT*4];

    inp_data = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NFFT);
    out      = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * NFFT);

    p = fftw_plan_dft_1d((int)NFFT, inp_data, out, FFTW_FORWARD, FFTW_MEASURE);    
    
    linspace(x_here, -2.048000/2, 2.048000/2, NFFT);
    int fft_index=0;

  while (1)
    {
        for (i=0; i<NFFT; i++)
        {
            avg_power_spec[i] = 0.0;
        }

        for (naver=0; naver<10; naver++)
        {

            r = read(STDIN_FILENO, read_buffer, NFFT*4);

            for (i=0; i<NFFT; i++)
            {
                inp_data[i][0] = (double)(read_buffer[i*4 + 0]*256 + read_buffer[i*4 + 1]);
                inp_data[i][1] = (double)(read_buffer[i*4 + 2]*256 + read_buffer[i*4 + 3])*0;
            }
            fftw_execute(p);

            for (k = 0; k < NFFT; ++k)
            {
                fft_index = (NFFT/2 + k) % NFFT;
                power_spectrum[k] = (out[fft_index][0]*out[fft_index][0] + out[fft_index][1]*out[fft_index][1]);
            }

            for (i=0; i<NFFT; i++)
            {
                avg_power_spec[i] += power_spectrum[i];
            }
        }
        plot(x_here, avg_power_spec, NFFT);
        // usleep(100000);
    }
    fftw_destroy_plan(p);
    fftw_free(inp_data); 
    fftw_free(out);
    return 0;
}
