#include <stdio.h>
 
int main()
{
			int arr[5] = {0};
				int i = 0;
					for(i = 0 ; i < 5 ; i++)
								{
					scanf("%d",&arr[i]);
					while(getchar() != '\n');
															}
						
					int max = arr[0], min = arr[0];
					int mi = 0 , mj = 0;

						for(i = 0 ; i < 5 ; i++)
						{
						if(max < arr[i])
																			{
																								max = arr[i];
																								mi = i;
																													}
																							if(min > arr[i])
																					{
																										min = arr[i];
																													mj = i;
																															}
																		}

									int tmp = arr[mi];
										arr[mi] = arr[mj];
											arr[mj] = tmp;
												
												for(i = 0 ; i < 5 ; i++)
															{
																			printf("%d\n",arr[i]);
																				}
													
													
													
													
													
													
													
												



													return 0;
}


