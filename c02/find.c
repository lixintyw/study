#include <stdio.h>

int main()
{
			int arr[10] = {0,1,2,2,1,1,0,0,1,2};
				int i = 0;
					int index[3] = {0};
						for(i = 0 ; i < 10 ; i++)
									{
													index[arr[i]]++;
														}
							printf("0:%d\t1:%d\t2:%d\n",index[0],index[1],index[2]);
								return 0;
}

