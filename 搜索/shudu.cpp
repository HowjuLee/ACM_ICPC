//////简单搜索之数独



/*
·标记：
    本题的思路不难。可以对于数表中的每一个位置，定义一个标记向量tag[9]，其中如果该位置可以填写数字i，那么tag[i]的值为1，否则，tag[i]值为0。
	对于数表中所有的数字，可以定义三维数组：tag[9][9][9],其中：tag[i][j][k]标记了第i行第j列中，是否可以填入数字k。

·初始化：
    当整个数表为空时，每一个位置都可以填入1-9中的每一个数，因此一开始tag数组中的所有元素的值均为1。
	然后处理程序输入的要求解的数独方阵，当第i行第j列填入数字k时，就将tag[i][j][1]、tag[i][j][2]、.....、tag[i][j][9]全部置为0，
	同时和位置(i,j)在同一行、同一列、同一个九宫的所有位置均不可以填入数字k，因此将其对应的tag元素置为0。

·搜索：
    数表的初始情况处理完成后，就可以进行搜索了。
	搜索的方向可以是从上到下、从左到右，一次将空白的位置填入可以填入的数字，然后更新同一行、同一列、同一九宫的其他位置的标记向量。
	然后再递归地搜索下一个位置。
    当最后一个位置的数字也填写完毕时，求解结束，找到了一组合法的解；当到达某一位置，查找该位置的标记向量，发现1-9所有的数字均不可以填入时，
	说明当前的填写策略不可行，需要回溯到上一个位置重新选择数字填入。

·搜索优化：
    从上到下，从左到右的搜索策略未必是最优的。
	最好的搜索策略是每次选择可以填入的数字的个数最少的位置，这样就可以使得后续的分支情况尽可能地少。
	因此，利用count[9][9]动态地记录当前局面下每个位置合法的数字的个数，在每次进行搜索前，找到count值最小的位置进行搜索，可以达到更好的算法效率。
*/


#include<stdio.h>
#include<stdlib.h>


// Record the soduku.
int s[9][9];

// Record if the number is available in each grid.
int tags[9][9][9];

// Record how many number is available in each grid.
int count[9][9];

/*
 * This function print the soduku.
 * Parameters:
 *		None.
 * Returns:
 *		None.
 */
void print(void) {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			printf("%d ", s[i][j]);
		}
		printf("\n");
	}	
}

/*
 * This function used to search the result.
 * Parameters:
 *		@num: The current number of iterate.
 * Returns:
 *		If the result is legal, returns 1, or returns 0.
 */
int search(int num) {

	int x, y; 
	int min = 10;
	
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			if(s[i][j] == 0 && min > count[i][j]) {
				min = count[i][j];
				x = i;
				y = j;
			}
		}
	}
	
	if(min == 10) {
		return 1;
	} 
	
	for(int i = 1; i <= 9; i++) {
		if(tags[x][y][i - 1] == 0) {
			s[x][y] = i;
			for(int c = 0; c < 9; c++) {
				if(tags[x][c][i - 1] == 0) {
					tags[x][c][i - 1] = num;
					count[x][c]--;
				}
				if(tags[c][y][i - 1] == 0) {
					tags[c][y][i - 1] = num;
					count[c][y]--;
				}
			}
			
			int area = x / 3 * 3 + y / 3;
			for(int r = area / 3 * 3; r < area / 3 * 3 + 3; r++) {
				for(int c = area % 3 * 3; c < area % 3 * 3 + 3; c++) {
					if(r != x && c != y && tags[r][c][i - 1] == 0) {
						tags[r][c][i - 1] = num;
						count[r][c]--;
					}
				}
			}
			
			int result = search(num + 1);
			if(result == 1) {
				return 1;
			}
			
			s[x][y] = 0;
			for(int c = 0; c < 9; c++) {
				if(tags[x][c][i - 1] == num) {
					tags[x][c][i - 1] = 0;
					count[x][c]++;
				}
				if(tags[c][y][i - 1] == num) {
					tags[c][y][i - 1] = 0;
					count[c][y]++;
				}
			}
			
			for(int r = area / 3 * 3; r < area / 3 * 3 + 3; r++) {
				for(int c = area % 3 * 3; c < area % 3 * 3 + 3; c++) {
					if(r != x && c != y && tags[r][c][i - 1] == num) {
						tags[r][c][i - 1] = 0;
						count[r][c]++;
					}
				}
			}
		}
	}
	
	return 0;
}

/*
 * This function deals with one test case.
 * Parameters:
 *		None.
 * Returns:
 *		None.
 */
void function(void) {
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			count[i][j] = 9;
			for(int k = 0; k < 9; k++) {
				tags[i][j][k] = 0;
			}
		}
	}
	
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			scanf("%d", &s[i][j]);
			if(s[i][j] != 0) {
				for(int c = 0; c < 9; c++) {
					if(tags[i][c][s[i][j] - 1] == 0) {
						tags[i][c][s[i][j] - 1] = 1;
						count[i][c]--;
					}
					if(tags[c][j][s[i][j] - 1] == 0) {
						tags[c][j][s[i][j] - 1] = 1;
						count[c][j]--;
					}	
				}
				
				int area = i / 3 * 3 + j / 3;
				for(int r = area / 3 * 3; r < area / 3 * 3 + 3; r++) {
					for(int c = area % 3 * 3; c < area % 3 * 3 + 3; c++) {
						if(r != i && c != j && tags[r][c][s[i][j] - 1] == 0) {
							tags[r][c][s[i][j] - 1] = 1;
							count[r][c]--;
						}
					}
				}
			}
		}
	}
	
	search(2);
	print();
}

/*
 * The main program.
 */
int main(void) {
	int t;
	scanf("%d", &t);
	
	for(int i = 0; i < t; i++) {
		function(); 
	}
	
	return 0;
}