#include <stdio.h> 
#include <stdlib.h> 
#include <math.h> 



double frand()
{
	return 2 * ((rand() / (double)RAND_MAX) - 0.5);
}
const float Q = 0.022;
float R = 0.617;

float before[20] = {0,};
float P_last[20] = {0,};
float kalman(int index, float v) {
	printf("%f %f\n",v, before[index]);
	if (before[index] == 0) {
		before[index] = v;
		return v;
	}
	else {
		float x_temp_est = before[index];
		float P_temp = P_last[index] + Q;

		float K = P_temp * (1.0 / (P_temp + R));

		float x_est = x_temp_est + K * (v - x_temp_est);
		float P = (1 - K) * P_temp;

		printf("now b%f %f %f\n",x_temp_est, x_est, K * (v - x_temp_est));

		before[index] = x_est;
		P_last[index] = P;
		return x_est;
	}
}


int main() {
	//initial values for the kalman filter    
	float x_est_last = 0;
	float P_last = 0;

	//the noise in the system     

	float K;
	float P;
	float P_temp;
	float x_temp_est;
	float x_est;

	int z_measured;
	//the 'noisy' value we measured   
	int z_real = 1;
	//the ideal value we wish to measure         
	srand(0);
	//initialize with a measurement     
	x_est_last = z_real + frand() * 0.09;
	float sum_error_kalman = 0;
	float sum_error_measure = 0;
	

	if(1)
		for (size_t i = 0; i < 30; i++)
		{
			z_measured = z_real + frand() * 3;
			float k = kalman(0, z_measured);

			sum_error_measure += fabs(z_real-z_measured);
			sum_error_kalman += fabs(z_real-k);

		}
	else
	
	
	for (int i = 0; i < 30; i++) {
		//do a prediction         
		x_temp_est = x_est_last;
		P_temp = P_last + Q;
		//calculate the Kalman gain         
		K = P_temp * (1.0 / (P_temp + R));
		//measure         
		z_measured = z_real + frand() * 0.09;
		//the real measurement plus noise        
		//correct         
		x_est = x_temp_est + K * (z_measured - x_temp_est);
		P = (1 - K) * P_temp;
		//we have our new system                  
		printf("Ideal position: %6.3f \n", z_real);
		printf("Mesaured position: %6.3f [diff:%.3f]\n", z_measured, fabs(z_real - z_measured));
		printf("Kalman position: %6.3f [diff:%.3f]\n", x_est, fabs(z_real - x_est));
		sum_error_kalman += fabs(z_real - x_est);
		sum_error_measure += fabs(z_real - z_measured);
		//update our last's         
		P_last = P;
		x_est_last = x_est;
	}
	printf("Total error if using raw measured: %f\n", sum_error_measure);
	printf("Total error if using kalman filter: %f\n", sum_error_kalman);
	printf("Reduction in error: %d%% \n", 100 - (int)((sum_error_kalman / sum_error_measure) * 100));              return 0;
}