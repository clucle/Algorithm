#include <stdio>

int main() {
	int T;
	scanf("%d", &T);

	int P, M, F, C;
	int num_chicken;
	int my_coupon;
	int possible_coupon;
	int count;
	
	while (T--) {
		scanf("%d %d %d %d", &P, &M, &F, &C);
		
		count = 0;
		
		num_chicken = M / P;
		my_coupon = num_chicken * C;//25Àå
		possible_coupon = my_coupon / F;

		my_coupon -= possible_coupon * F;
		my_coupon += possible_coupon * C;
		possible_coupon = my_coupon / F;

		while (possible_coupon >= 1){
			count += possible_coupon;
			my_coupon -= possible_coupon * F;
			my_coupon += possible_coupon * C;
			possible_coupon = my_coupon / F;
		}
		printf("%d\n", count);
	}
	return 0;
}