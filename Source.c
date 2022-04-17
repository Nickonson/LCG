#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#ifdef _WIN32
    printf("Hey Windows OS.\n");
  
// Checking for mac OS with
// __APPLE__ macro
#elif __APPLE__
	
#endif

unsigned long long pw(long long numb, int degree);

unsigned long long GCD(unsigned long long a, unsigned long long b);

int poker_check(unsigned long long *numbs);

unsigned long long get_C(unsigned long long c, unsigned long long m);

int get_S(unsigned long long a, unsigned long long m);

void get_pr(long *stirlings, long double *pr, unsigned long long d);

int main()
{
	unsigned long long a, m, c, x;
	unsigned int s;
	char choice;
	int k;

	// gettin 'x'
	srand(time(NULL));
	x = abs(rand());
	printf("x = %llu\n", x);

	m = pw(2, 32);
	printf("m = %llu\n", m);
	
	// gettin 'c'
	c = get_C(c, m);
	printf("c = %llu\n", c);

	// getting 'a'
	for (a = m / 2 + 32537; a % 8 != 5; a++);
	printf("a = %llu\n", a);

	// getting 's'
	s = get_S(a, m);
	printf("s = %d\n", s);


	//stir numbs for r = {1, 2, 3, 4, 5}, k = 5
	long stirlings[5] = {1, 15, 25, 10, 1};
	long double pr[5];
	unsigned long long d = 52;
	
	get_pr(stirlings, pr, d);
	for(int i = 0; i < 5; i++)
		printf("%.40Lf \n", pr[i]);
	


	
	//gettin data for h^2
	unsigned long long temp_numbs_for_h_sq[5];
	int data_of_nmb_grps[5];
	for(int i = 0; i < 5; i++)
		data_of_nmb_grps[i] = 0;

	for(int i = 0; i < 100000; i++)
	{
		for(int z = 0; z < 5; z++)
		{
			x = (a * x + c) % m;
			temp_numbs_for_h_sq[z] = x % d;
		}
		data_of_nmb_grps[poker_check(temp_numbs_for_h_sq) - 1] += 1;
	}
	printf("\n");
	for(int i = 0; i < 5; i++)
		printf("%d ", data_of_nmb_grps[i]);
	printf("\n");

	long double h_square = 0;
	for(int i = 0; i < 5; i++)
	{
		h_square +=  ((pr[i] - 100000 * pr[i]) * (pr[i] - 100000 * pr[i])) / (100000 * pr[i]);
	}
	printf("%.20Lf \n", h_square);
	// checking the perdiod... 'n' should the same as 'm'
	/*
	unsigned long long temp = x;
	x = (a * x + c) % m;
	unsigned long long n = 1;
	while (temp != x)
	{
		x = (a * x + c) % m;
		n++;
	}
	printf("n = %llu", n);
	*/
	
	// x(n+1) = (a * xn + c) % m
	
}

unsigned long long pw(long long numb, int degree)
{
	if (degree == 0)
		return 1;
	else if (degree < 0)
		return -1;
	else if (degree == 1)
		return numb;

	long long temp = numb;
	int i = 1;
	while(i < degree)
	{
		if (2 * i <= degree)
		{
			temp *= temp;
			i *= 2;
		}
		else
		{
			temp *= numb;
			i++;
		}
	}
	return temp;
}

unsigned long long GCD(unsigned long long a, unsigned long long b)
{
	if (a == 0 || b == 0)
		return 1;
	while (a != 0 && b != 0)
	{
		if (a > b)
			a %= b;
		else
			b %= a;
	}
	if (a == 0)
		return b;
	else
		return a;
}

int poker_check(unsigned long long *numbs)
{
	unsigned long long results[2][5];
	
		for(int z = 0; z < 5; z++)
		{
			results[0][z] = 0;
			results[1][z] = 0;
		}
	int end = 0;
	for(int i = 0; i < 5; i++)
	{
		int added = 0;
		int z;
		for(z = 0; z < end + 1 && !added; z++)
		{
			if(results[0][z] == numbs[i])
			{
				results[1][z] += 1;
				added = 1;
			}
		}
		if(added == 0 && end < 5)
		{
			results[0][z - 1] = numbs[i];
			results[1][z - 1] = 1;
			end++;
			added = 1;
		}

	}
	return end;
}

unsigned long long get_C(unsigned long long c, unsigned long long m)
{
	for (c = 39027341287453; GCD(c, m) != 1; c += 2);
	
	return c;
}

int get_S(unsigned long long a, unsigned long long m)
{
	int found = 0;
	unsigned long long temp = a - 1;
	int s = 1;
	while (s < 1000 && !found)
	{
		if (temp % m != 0)
			temp *= (a - 1);
		else
			found = 1;
		s++;
	}
	return s;
}

void get_pr(long *stirlings, long double *pr, unsigned long long d)
{
	for(int i = 0; i < 5; i++)
	{
		pr[i] = stirlings[i];
		
		for(int r = 1; r <= i + 1; r++)
		{
			pr[i] *= (long double)(d - r + 1);
		}
		for(int r = 0; r < 5; r++)
			pr[i] /= (long double)d;
	}
}
