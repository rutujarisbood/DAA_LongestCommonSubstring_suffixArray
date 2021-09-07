//student id: 1001843943
//name: Rutuja Risbood

// Derived from
//ref :  http://ranger.uta.edu/~weems/NOTES5311/LAB/LAB3SPR21/SAcommonSubStr2.trace.c

// Use suffix array and LCP to compute
// longest common substring of two input strings. BPW

// This version outputs multiple candidate solutions.

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char s[1000000], s1[500000], s2[500000], s3[500000];
int n,           // length of s[] including \0
sa[1000000],   // suffix array for s[]
rank[1000000], // rank[i] gives the rank (subscript) of s[i] in sa[]
lcp[1000000],  // lcp[i] indicates the number of identical prefix symbols
			   // for s[sa[i-1]] and s[sa[i]]
	myVal[3],
	t[100000];

int suffixCompare(const void* xVoidPt, const void* yVoidPt)
{
	// Used in qsort call to generate suffix array.
	int* xPt = (int*)xVoidPt, * yPt = (int*)yVoidPt;
	return strcmp(&s[*xPt], &s[*yPt]);
}

void computeRank()
{
	// Computes rank as the inverse permutation of the suffix array
	int i;

	for (i = 0;i < n;i++)
		rank[sa[i]] = i;
}

void computeLCP()
{
	//Kasai et al linear-time construction
	int h, i, j, k;

	h = 0;  // Index to support result that lcp[rank[i]]>=lcp[rank[i-1]]-1
	for (i = 0;i < n;i++)
	{
		k = rank[i];
		if (k == 0)
			lcp[k] = (-1);
		else
		{
			j = sa[k - 1];
			// Attempt to extend lcp
			while (i + h < n && j + h < n && s[i + h] == s[j + h])
				h++;
			lcp[k] = h;
		}
		if (h > 0)
			h--;  // Decrease according to result
	}
}

int fibIndex = 0;

//void fib(k)
////int k;
//{
//    if (k == 0)
//        s[fibIndex++] = '1';
//    else if (k == 1)
//        s[fibIndex++] = '0';
//    else
//    {
//        fib(k - 1);
//        fib(k - 2);
//    }
//}

int main()
{
	int i, j, k, m, p, hashPos, dollarPos, LCSpos = -1, LCSlength = 0;


	scanf("%s", s1);
	scanf("%s", s2);
	scanf("%s", s3);

	// Concatenate the two input strings, but with a $ separator.
	for (i = 0;s1[i] != '\0';i++)
		s[i] = s1[i];
	hashPos = i;
	s[i++] = '#';
	for (j = 0;s2[j] != '\0';j++)
		s[i + j] = s2[j];
	dollarPos = i + j;
	s[i + j++] = '$';
	for (m = 0;s3[m] != '\0';m++)
		s[i + j + m] = s3[m];
	s[i + j + m] = '\0';
	n = i + j + m + 1;


	//n=strlen(s)+1;
	printf("n is %d\n", n);

	// Quick-and-dirty suffix array construction
	for (i = 0;i < n;i++)
		sa[i] = i;
	qsort(sa, n, sizeof(int), suffixCompare);
	computeRank();
	computeLCP();
	if (n < 3000)
	{
		printf("i     sa    suffix                              lcp   t s  rank   lcp[rank]\n");
		int strNo = 0;
		for (i = 0;i < n;i++) {

			if (sa[i] < hashPos) {
				strNo = 0;
			}
			else if (sa[i] > hashPos && sa[i] < dollarPos) {
				strNo = 1;
			}
			else if (sa[i] > dollarPos) {
				strNo = 2;
			}
			t[i] = strNo;
			printf("%-5d %-5d %-35.35s %-5d %-1d %c  %-5d  %-5d\n",
				i, sa[i], &s[sa[i]], lcp[i], strNo,
				s[i], rank[i], lcp[rank[i]]);
		}
	}
	int temp, x;
	for (i = 0;i < n;i++) {
		if (t[i] != t[i + 1]) {
			for (j = i + 1;j < n - 1;j++) {
				myVal[1] = t[j];
				if (t[j + 1] == t[i])
				{
					break;;
				}
				else if (t[j] != t[j + 1]) {
					for (k = j + 1;k < n - 1;k++) {
						if (t[k] != t[j] && t[k] != t[i]) {
							myVal[2] = t[k];
							//we have set of all 3 strings
							//temp = 99999;
							//temp = lcp[i];
							temp = lcp[i + 1];
							for (x = i + 1;x <= k;x++) {
								if (lcp[x] < temp) {
									temp = lcp[x];
								}
							}
							if (temp > LCSlength)
							{
								printf("x=%d y=%d z=%d\n", t[i], t[j], t[k]);
								LCSpos = i;
								LCSlength = temp;
								printf("Length of longest common substring is %d at positions %d\t%d\t%d\n", LCSlength, i, j, k);
								printf("%.*s\n", LCSlength, s + sa[LCSpos]);
							}
							break;
						}
					}
					break;
				}

				//break;
			}
		}

	}


}
