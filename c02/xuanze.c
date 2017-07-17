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

						int k = 0;
							int j = 0;
								for(i = 0 ; i < 5 ; i++)
											{
															k = i;
																	for(j = i ; j < 5 ; j++)
																					{
																										if(arr[k] < arr[j])
																															{
																																					k = j;
																																								}
																												}
																			if(k != i)
																							{
																												int t = arr[k];
																															arr[k] = arr[i];
																																		arr[i] = t;
																																					printf("qwe\n");
																																							}
																				}

									for(i = 0 ; i < 5 ; i++)
												{
																printf("%d\t",arr[i]);
																	}
										putchar('\n');



											return 0;
}


