/*
 http://www.gamedev.net/topic/512260-number-generator-cmwc-4096-and-implementation/
*/

static unsigned long Q[4096], c=123;
unsigned long CMWC(void)
{
	unsigned long long t, a=18782LL;
	static unsigned long i=4095;
	unsigned long x, m=0xFFFFFFFE;

	i = (i + 1) & 4095;
	t = a * Q[i] + c;
	c = (t >> 32);
	x = t + c;
	if(x < c)
	{
		++x;
		++c;
	}
	return (Q[i] = m - x);
}


