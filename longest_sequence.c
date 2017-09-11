// 2nd cycle programme no 1 
/*Create a programme that displays the longest Increasing or decreasing sequence Numbers stored in a 2D array

Example: array - {{10,11,15,18,99,25,24},{21,20,19,18,45,1,12,0,18,99,5}}---> Output = {99,25,24,21,20,19,18}
*/

#include<stdio.h>
#include<stdlib.h>
int *read_array(int n)
{
	int *a,i;
	a=malloc(n*sizeof(int));
	printf("Enter the elements of the array\n");

	for(int i=0;i<n;i++)
	{
		scanf("%d",a+i);
	}

	return a;
}

void display(int *a, int n)
{
	for(int i=0;i<n;i++)
	{
		printf("%d\n",*(a+i));
	}
}

int *resize(int **q,int n_structures,int n_elements)
{
	int *new_array;
	int new_size=n_structures*n_elements;
	new_array=malloc(sizeof(int)*new_size);
	for(int i=0;i<n_structures;i++)
	{
		for(int j=0;j<n_elements;j++)
		{
			new_array[i*n_elements+j]=*(q[i]+j);
		}
	}

	return new_array;
}

struct sequence
{
	int beg;
	int end;
	int length;
};


struct sequence *find_index_increasing(int *a,int n)
{
	struct sequence *s;
	struct sequence temp;
	s=malloc(sizeof(temp)*100);
	int count=0;
	int index=0;
	for(int i=0;i<n-1;i++)
	{	

		if(a[i]<a[i+1])
		{
		
			if(count==0)
			{
				s[index].beg=i;
			//	printf("\nbeg index%d",i);
			}
			count++;
		//	printf("%d",a[i]);
		}
		else
		{
		//	printf("\nend index is %d",i);
			s[index].length=count;
			s[index].end=i;
			count=0;
			index++;
		}
		
	}

return s;
		
}


struct sequence *find_index_decreasing(int *a,int n)
{
	struct sequence *s;
	struct sequence temp;
	s=malloc(sizeof(temp)*100);
	int count=0;
	int index=0;
	for(int i=0;i<n-1;i++)
	{	

		if(a[i]>a[i+1])
		{
		
			if(count==0)
			{
				s[index].beg=i;
			//	printf("\nbeg index%d",i);
			}
			count++;
		//	printf("%d",a[i]);
		}
		else
		{
		//	printf("\nend index is %d",i);
			s[index].length=count;
			s[index].end=i;
			count=0;
			index++;
		}
		
	}

return s;
		
}





int findmax(struct sequence *s)
{
	int max=0,index=0;
	for(int i=0;i<100;i++)
	{
		if((s+i)->length>max)
		{
			max=(s+i)->length;
			index=i;
		}
	}
	return index;

}

	

void main()
{
	int n,i,**q,n_structures,n_elements,index;
	printf("Enter the no of structures you want to enter\n");
	scanf("%d",&n_structures);
	printf("Enter the no of elements in each structure\n");
	scanf("%d",&n_elements);
	q=malloc(sizeof(int)*n_structures);
	
	for(int i=0;i<n_structures;i++)
	{
		q[i]=read_array(n_elements);
	}
	
	int *linear=resize(q,n_structures,n_elements);
	struct sequence *s_inc=find_index_increasing(linear,n_structures*n_elements);
	struct sequence *s_dec=find_index_decreasing(linear,n_structures*n_elements);
	int max_index_inc=findmax(s_inc);
	int max_index_dec=findmax(s_dec);
	struct sequence s=s_inc[max_index_inc];
	int beg=s_inc[max_index_inc].beg;
	int end=s_inc[max_index_inc].end;
	if(s_inc[max_index_inc].length<s_dec[max_index_dec].length)
	{
		s=s_dec[max_index_dec];
		beg=s_dec[max_index_dec].beg;
		end=s_dec[max_index_dec].end;
	}
	printf("The biggest sequence is\n");
	for(i=beg;i<=end;i++)
	{
		printf("%d\n",linear[i]);
	}
}
