#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

template<typename P> struct Cmp
{
    bool operator()(const P &p1, const P &p2)
    {
        if(p1.first < p2.first) return true;
        if(p1.first == p2.first) return p1.second < p2.second;
        return false;
    }
};
 
int max_width;

void print_height_star(int prev_height, int arr[], int cnt) {
	int i, j;
	int prev_width = 0;
	
	for (i = 0; i < 3; i++) {
		prev_width = 0;
		for (j = 0; j < cnt; j++) {
			while(prev_width != arr[j]) {
				printf("   ");
				prev_width++;
				
			}
			
			if (i == 0) printf("  *   ");
			else if (i == 1) printf(" * *  ");
			else printf("***** ");
			
			prev_width+=2;
			
		}
		
		while(prev_width < max_width) {
			printf("   ");
			prev_width++;
		}
		printf("\n");
	}
	
}


main() {
	int N;
	scanf("%d", &N);
	
	int k = N/3;
	max_width = k * 2;
	
	int h;
	for (h = 0; k != 0; h++) {
		k /= 2;
	}
	
	vector<pair<int, int> > vec;
	vector<pair<int, int> > newVec;
	int i, j;
	
	
	int space;
	
	vec.push_back(make_pair(0,0));	
	for (i = 1; i < h; i++) {
		
		space = 1;
		for (j = 1; j < i; j++) {
			space *= 2;
		}
		
		for (vector<pair<int, int> >::iterator pos = vec.begin(); pos != vec.end(); ++pos) {
		   newVec.push_back(make_pair(pos->first + space, pos->second));
		   newVec.push_back(make_pair(pos->first + space, pos->second + space * 2));
		   newVec.push_back(make_pair(pos->first, pos->second + space));
		}
		
		vec.clear();
		sort(newVec.begin(), newVec.end(), Cmp<pair<int, int> >());
		vec = newVec;
		newVec.clear();
	}
	
	int prev_height = 0;
	int element_by_height = 0;
	
	
	
	int arr[1024];
	for (vector<pair<int, int> >::const_iterator pos = vec.begin(); pos != vec.end(); ++pos) {
		if (prev_height != pos->first) {
			print_height_star(prev_height, arr, element_by_height);
			element_by_height = 0;
			prev_height++;
		}
		
		arr[element_by_height] = pos->second;
		element_by_height++;
	}
	
	print_height_star(prev_height, arr, element_by_height);
}


