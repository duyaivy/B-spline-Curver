#include <stdio.h>
#include <math.h>
float u[100];
void vectorPointNonUniform(float U[], int p, int n);
void vectorPointUniform(float U[], int p, int n);
float basicFunc(int i, float u, float U[]);
void matrix(float N[][100], int n);
//void multMatrix(float a[][100], float b[][100], float resuilt[][100], int m, int n, int p);
void inverseMatrix(float a[][100], int n, float *dinhThuc);
void printInfor(int p, int d, int n, float a[][100]);

// ham tinh gia tri cac vector nut co n dinh kiem soat bac p
void vectorPointNonUniform(float U[], int p, int n)
{
	int i;
	for ( i = 0; i <= n + p + 2 + 1; i++)
	{
		if (i < p)
			U[i] = 0;
		else if (i >=p && i <= n+2+1)
			U[i] = U[i - 1] +1;
		else 
			U[i] = U[i - 1];
	}
}
void vectorPointUniform(float U[], int p, int n)
{int i;
	for ( i = 0; i <= n + p + 2 + 1; i++)
	{
		U[i] = i;
	}
}

// ham tinh gia tri theo cong thuc khai trien
float basicFunc(int i, float u, float U[])
{
	float N03 = (u - U[i]) * (u - U[i]) * (u - U[i]) / ((U[i + 1] - U[i]) * (U[i + 2] - U[i]) * (U[i + 3] - U[i]));
	float N13 = (u - U[i]) * (u - U[i]) * (U[i + 2] - u) / ((U[i + 2] - U[i]) * (U[i + 2] - U[i + 1]) * (U[i + 3] - U[i])) + (u - U[i]) * (U[i + 3] - u) * (u - U[i + 1]) / ((U[i + 2] - U[i + 1]) * (U[i + 3] - U[i + 1]) * (U[i + 3] - U[i])) + (U[i + 4] - u) * (u - U[i + 1]) * (u - U[i + 1]) / ((U[i + 4] - U[i + 1]) * (U[i + 3] - U[i + 1]) * (U[i + 2] - U[i + 1]));

	float N23 = (u - U[i]) * (U[i + 3] - u) * (U[i + 3] - u) / ((U[i + 3] - U[i]) * (U[i + 3] - U[i + 1]) * (U[i + 3] - U[i + 2])) + (U[i + 4] - u) * (U[i + 3] - u) * (u - U[i + 1]) / ((U[i + 4] - U[i + 1]) * (U[i + 3] - U[i + 1]) * (U[i + 3] - U[i + 2])) +
				(U[i + 4] - u) * (U[i + 4] - u) * (u - U[i + 2]) / ((U[i + 4] - U[i + 1]) * (U[i + 4] - U[i + 2]) * (U[i + 3] - U[i + 2]));

	float N33 = (U[i + 4] - u) * (U[i + 4] - u) * (U[i + 4] - u) / ((U[i + 4] - U[i + 1]) * (U[i + 4] - U[i + 2]) * (U[i + 4] - U[i + 3]));

	if ((U[i] <= u) && (u < U[i + 1]))
		return N03;
	if ((U[i + 1] <= u) && (u < U[i + 2]))
		return N13;
	if ((U[i + 2] <= u) && (u < U[i + 3]))
		return N23;
	if ((U[i + 3] <= u) && (u < U[i + 4]))
		return N33;
	else
		return 0;
}

// bieu dien he phuong trinh duoi dang ma tran
void matrix(float N[][100], int n)
{
	float point = n + 1;
	int i, j;
	for (i = 0; i < point; i++)
	{
		for (j = 0; j < point; j++)
		{
			if (i == 0 && j == 0)
			{
				N[i][j] = 3;
			}
			else if (i == 0 && j == 1)
			{
				N[i][j] = -1;
			}
			else if (i == point - 1 && j == point - 2)
			{
				N[i][j] = -1;
			}
			else if (i == point - 1 && j == point - 1)
			{
				N[i][j] = 3;
			}
			else if (i != 0 && i != point - 1)
			{
				N[i][j] = 0;
			}
		}
	}
	int k = 1;
	for (i = 1; i < point - 1; i++)
	{
		for (j = 0; j < point; j++)
		{
			N[i][j] = basicFunc(k, u[i + 3], u);
			k++;
		}
		k = 1;
	}
}

void inverseMatrix(float a[][100], int n, float *dinhThuc)
{
	int i, j, k, sign = 1;
	float temp;
	float det = 1;
	n = n + 1;

	// khoi tao 2 ma tran phu
	float b[100][100], c[100][100];

	// gan ma tran c bang ma tran b
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			c[i][j] = a[i][j];

	for (i = 0; i < n - 1; i++)
	{
		if (c[i][i] == 0)
		{
			k = i + 1;
			while (k < n && c[k][i] == 0)
				k++;
			if (k == n)
			{
				printf("\ndet(a) = 0");
				break;
			}
			for (j = i; j < n; j++)
			{
				temp = c[i][j];
				c[i][j] = c[k][j];
				c[k][j] = temp;
			}
			sign = -sign;
		}
		for (j = i + 1; j < n; j++)
		{
			temp = -c[j][i] / c[i][i];
			for (k = i + 1; k < n; k++)
				c[j][k] += temp * c[i][k];
		}
		det *= c[i][i]; // Tinh det(a)
	}

	// nhan det voi phan tu cuoi cheo chinh
	det *= c[n - 1][n - 1];
	*dinhThuc = det;
	// Tinh ma tran nguoc
	if (det != 0)
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (i == j)
					b[i][j] = 1;
				else
					b[i][j] = 0;
		// xu ly tu hang dau den hang cuoi
		for (i = 0; i < n; i++)
		{
			// neu gap phan tu tren duong cheo chinh bang 0 thi doi hang
			if (a[i][i] == 0)
			{
				k = i + 1;
				while (k < n && a[k][i] == 0)
					k++;
				for (j = 0; j < n; j++)
				{
					temp = a[i][j];
					a[i][j] = a[k][j];
					a[k][j] = temp;
					temp = b[i][j];
					b[i][j] = b[k][j];
					b[k][j] = temp;
				}
			}
			temp = a[i][i];
			for (j = i; j < n; j++)
				a[i][j] /= temp;
			for (j = 0; j < n; j++)
				b[i][j] /= temp;
			for (j = i + 1; j < n; j++)
			{
				temp = -a[j][i];
				for (k = i; k < n; k++)
					a[j][k] += temp * a[i][k];
				for (k = 0; k < n; k++)
					b[j][k] += temp * b[i][k];
			}
		}
		// ket thuc qua trinh Gauss

		// bat dau qua trinh Jordan
		for (i = n - 1; i > 0; i--)
			for (j = i - 1; j >= 0; j--)
			{
				temp = -a[j][i];
				for (k = n - 1; k >= i; k--)
					a[j][k] += temp * a[i][k];
				for (k = 0; k < n; k++)
					b[j][k] += temp * b[i][k];
			}
	}

	// Sao chep ma tran a tu ma tran b va ket thuc
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			a[i][j] = b[i][j];
		}
	}
}

// ham nhan 2 ma tran

void multMatrix(float a[][100], float b[][100], float resuilt[][100], int m, int n, int p){
	// nhan 2 ma tran b
	int i,j,k;
	    for ( i = 0; i < m; i++) {
        for ( j = 0; j < p; j++) {
            resuilt[i][j] = 0;
            for ( k = 0; k < n; k++) {
                resuilt[i][j] += a[i][k] * b[k][j];
            }
        }
    }


}



// void multMatrix(float a[][100], float b[][100], float resuilt[][100], int n, int p)
// { // nhan ma tran a(nxn) va b(nxp) ket qua tra ve resuilt[][];
// 	int i, j;
// 	// nhan 2 ma tran b
// 	for (i = 0; i <= n; i++)
// 	{
// 		if (i == 0 || i == n)
// 		{
// 			for (j = 0; j < p; j++)
// 			{
// 				b[i][j] *= 2;
// 			}
// 		}
// 	}
// 	for (i = 0; i <= n; i++)
// 	{
// 		for (j = 0; j < p; j++)
// 		{
// 			resuilt[i][j] = 0;
// 			for (int k = 0; k <= n; k++)
// 			{
// 				resuilt[i][j] += a[i][k] * b[k][j];
// 			}
// 		}
// 	}
// 	// chia 2 ma tran b ve binh thuong
// 	for (i = 0; i <= n; i++)
// 	{
// 		if (i == 0 || i == n)
// 		{
// 			for (j = 0; j < p; j++)
// 			{
// 				b[i][j] /= 2;
// 			}
// 		}
// 	}
// }

void printInfor(int p, int d, int n, float a[100][100])
{
	printf("\n\n\t --------------------------------------------\n");
	printf("\t\t\t\tPROGRAM INFORMATION\n");
	printf("\nDegree (p): %d\t Number of dimensions(d): %d\t Data point(n): %d\n", p, d, n+1);
	printf("\nCoordinates of the data points\n");

	char tmp = 'A';
	int cnt = 0;
	// int i;
	for (int i = 0; i <= n; i++)
	{
		if (cnt == 3)
		{
			printf("\n\n");
			cnt = 0;
		}
		if (d == 2)
		{
			printf("%c( %0.2f , %0.2f );\t",tmp++, a[i][0], a[i][1]);
			cnt++;
		}
		else
		{
			printf("%c( %0.2f , %0.2f , %0.2f );\t",tmp++, a[i][0], a[i][1], a[i][2]);
			cnt++;
		}
	}

	printf("The coordinates of the Vector Point:");
	printf("\n");
	int i;
    for ( i = 0; i <= n + p + 2; i++)
        printf("U[%d] = %0.2f\t", i, u[i]);
}
