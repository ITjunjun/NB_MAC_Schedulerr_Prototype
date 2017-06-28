#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double uniform_rng()
{
  double random;
  random = (double)(rand()%RAND_MAX)/((double)RAND_MAX);
  //LOG_D(OTG,"Uniform taus random number= %lf\n", random);
  return random;
}

// Uniform Distribution using the Uniform_Random_Number_Generator

double uniform_dist(int min, int max)
{
  double uniform_rn;
  uniform_rn = (max - min) * uniform_rng() + min;
  //  LOG_T(OTG,"Uniform Random Nb = %lf, (min %d, max %d)\n", uniform_rn, min, max);
  //printf("Uniform Random Nb = %lf, (min %d, max %d)\n", uniform_rn, min, max);
  return uniform_rn;
}


double pareto_dist(double scale, double shape)
{
  double pareto_rn;

  if ((scale<=0)||(shape<=0)) {
    printf("Pareto :: scale=%.2f or shape%.2f <0 , adjust new values: sale=3, shape=4 \n", scale,shape);
    scale=3;
    shape=4;
  }

  pareto_rn=scale * pow(1/(1-uniform_rng()), 1/shape);
  // printf("Pareto Random Nb = %lf (scale=%.2f, shape=%.2f)\n", pareto_rn,scale,shape);
  return pareto_rn;
}


int main(int argc, char const *argv[])
{
	srand(time(NULL));
	double PC[3]={0.6,0.2,0};//CE leve(0,1,2)-->(40%,40%,20%), ratio of devices in period_UL report.
	int CE_Level,Num_CE_Level[3]={0};
	for (int i = 0; i < 100000; ++i)
	{
		double pc=uniform_rng();
		if(pc>PC[0])	Num_CE_Level[0]++;
		else if((pc<PC[0])&&(pc>PC[1]))	Num_CE_Level[1]++;
		else if((pc>=PC[2])&&(pc<PC[1]))	Num_CE_Level[2]++;
	}
	int Total=Num_CE_Level[0]+Num_CE_Level[1]+Num_CE_Level[2];
	double p_CE0,p_CE1,p_CE2;
	p_CE0=(double)Num_CE_Level[0]/Total;
	p_CE1=(double)Num_CE_Level[1]/Total;
	p_CE2=(double)Num_CE_Level[2]/Total;
	printf("CE0:%lf,CE1:%lf,CE2:%lf\n",p_CE0,p_CE1,p_CE2);
	system("pause");

	printf("RAND_MAX:%d\n", RAND_MAX);
	for (int i = 0; i < 1000; ++i)
	{
		double payloadSize=pareto_dist(20,2.5);
		if(payloadSize>200)
		{
			payloadSize=200;
			// printf("pareto_dist[%d]:%lf\n", i,payloadSize);
		}
		else
			payloadSize=floor(payloadSize+0.5);
		printf("pareto_dist[%d]:%lf\n", i,payloadSize);
		// printf("uniform_rng:%lf\n",uniform_rng());
		// printf("uniform_dist(0,10):%lf\n", uniform_dist(0,10));
		// printf("%d\n",rand());
		// printf("%lf\n",(double)rand()/RAND_MAX );
	}
	// if(rand()/RAND_MAX)
	return 0;
}
