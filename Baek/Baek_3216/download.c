#include <stdio.h>
main()
{
	int N;
	int D, V;
	
	scanf("%d",&N);

	int i;
	int Dt, Vt;
	
	scanf("%d%d",&D,&V);
	Dt = D;
	Vt = V;
	
	for (int i = 1; i < N; i++) {
		scanf("%d%d",&D,&V);
		if (V-Dt >= 0) {
			Vt += V-Dt;
			Dt = D;
		} else {
			Dt = Dt - V + D;
		}
	}
	printf("%d", Vt);
}
