#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

unsigned long long pw(long long numb, int degree);

unsigned long long GCD(unsigned long long a, unsigned long long b);

int poker_check(unsigned long long *numbs);

long double poker_h_sq(unsigned long long a, unsigned long long m, unsigned long long c, unsigned long long x, unsigned long long d);

unsigned long long get_C(unsigned long long c, unsigned long long m);

int get_S(unsigned long long a, unsigned long long m);

void get_pr(long *stirlings, long double *pr, unsigned long long d);

void check_period(unsigned long long a, unsigned long long m, unsigned long long c, unsigned long long x);

long double h_sq_freq_test(unsigned long long a, unsigned long long m, unsigned long long c, unsigned long long x);

void makeZeroArray(int *array, int length);

void makeTwoNArray(unsigned long long *array, int length);

int main()
{
	unsigned long long a, m, c, x;
	int s;
	
	// gettin 'x'
	srand(time(NULL));
	x = abs(rand());
	printf("x = %llu\n", x);

	m = pw(2, 32);
	printf("m = %llu\n", m);
	printf("%llu\n", m / 52);
	// gettin 'c'
	c = get_C(c, m);
	printf("c = %llu\n", c);

	// getting 'a'
	//for (a = m / 2 + 32537; a % 8 != 5; a++);
	for (a = m / 2; a % 8 != 5; a++);
	printf("a = %llu\n", a);

	// getting 's'
	s = get_S(a, m);
	printf("s = %d\n", s);

	long double h_square = poker_h_sq(a, m, c, x, 52);
	long double h_sq_without_creteriy = h_sq_freq_test(a, m, c, x);
	
	printf("poker h_sq == %.4Lf \n", h_square);
	printf("h_sq freq == %.4Lf \n", h_sq_without_creteriy);

	//check_period(a, m, c, x);
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
	unsigned long long results[5];
	
	for(int z = 0; z < 5; z++)
		results[z] = 0;
	int end = 0;
	int i = 0;
	while(i < 5)
	{
		int z = 0;
		while(z < end && results[z] != numbs[i])
			z++;
		if(z == end && z < 5)
		{
			results[z] = numbs[i];
			end++;
		}
		i++;
	}
	return end;
}

long double poker_h_sq(unsigned long long a, unsigned long long m, unsigned long long c, unsigned long long x, unsigned long long d)
{
	//stir numbs for r = {1, 2, 3, 4, 5}
	long stirlings[5] = {1, 15, 25, 10, 1};
	long double pr[5];
	get_pr(stirlings, pr, d);
	for(int i = 0; i < 5; i++)
		printf("%.20Lf \n", pr[i]);
	
	//gettin data for h^2
	unsigned long long temp_numbs_for_h_sq[5];
	int data_of_nmb_grps[5];
	makeZeroArray(data_of_nmb_grps, 5);

	int nn = 1000000;
	for(int i = 0; i < nn; i++)
	{
		for(int z = 0; z < 5; z++)
		{
			x = (a * x + c) % m;
			temp_numbs_for_h_sq[z] = (x / (m / d)) % d;
		}
		data_of_nmb_grps[poker_check(temp_numbs_for_h_sq) - 1] += 1;
	}

	for(int i = 0; i < 5; i++)
		printf("%d ", data_of_nmb_grps[i]);
	printf("\n");

	long double h_square = 0;
	for(int i = 0; i < 5; i++)
	{
		h_square +=  ((long double)(data_of_nmb_grps[i] - (long double)nn * pr[i]) * (data_of_nmb_grps[i] - (long double)nn * pr[i])) / (long double)(nn * pr[i]);
	}
	return h_square;
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
		{
			temp *= (a - 1);
			s++;
		}
		else
			found = 1;
		
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

void check_period(unsigned long long a, unsigned long long m, unsigned long long c, unsigned long long x)
{
	// checking the perdiod... 'n' should the same as 'm'
	
	unsigned long long temp = x;
	x = (a * x + c) % m;
	unsigned long long n = 1;
	while (temp != x)
	{
		x = (a * x + c) % m;
		n++;
	}
	printf("n = %llu, m = %llu \n", n, m);
}

long double h_sq_freq_test(unsigned long long a, unsigned long long m, unsigned long long c, unsigned long long x)
{
	int y[65536];
	makeZeroArray(y, 65536);
	int interval = 65536;
	long double h_sq = 0;
	long long summ = 0;
	for(int z = 0; z < 100; z++)
	{
		for(int i = 0; i < 65536; i++)
		{
			x = (x * a + c) % m;
			y[(x / interval)] += 1;
		}
	}

	// ps == 1 / 65536
	for(int i = 0; i < 65536; i++)
		h_sq += (y[i] - 65536.0 * 100 / 65536.0) * (y[i] - 65536.0 * 100 / 65536.0) / 6553600.0 * 65536.0;

		//h_sq += (y[i] - 100.0) * (y[i] - 100.0) / 100.0;
		//h_sq += (y[i] - 65536.0 * 100 / 65536.0) * (y[i] - 65536.0 * 100 / 65536.0) / 6553600 * 65536;
	return h_sq;
}

void makeZeroArray(int *array, int length)
{
	for(int i = 0; i < length; i++)
		array[i] = 0;
}

