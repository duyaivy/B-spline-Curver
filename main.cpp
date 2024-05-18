#include "bspline_uniform.h"
#include "codeRunnerFile.h"
#include <stdio.h>

float a[100][100], b[100][100], resuilt[100][100];
int p, n, d;
void bsplineUniformVersion1();
void bsplineUniformVersion2();

int main()
{
    
    bsplineUniformVersion2();
   
    return 0;
}

void bsplineUniformVersion1()
{
    char c = 'A';
    float det;
    int p, n, d;
    printf("Nhap so bac p:\t");
    scanf("%d", &p);
    printf("Nhap so chieu d:\t");
    scanf("%d", &d);
    printf("Nhap so diem du lieu n :\t");
    scanf("%d", &n);

    if (d == 2)

    {
        for (int i = 0; i <= n; i++)
        {
            printf("nhap %c(x,y)", c++);
            for (int j = 0; j < d; j++)
                scanf("%f", &a[i][j]);
        }
    }
    else
    {

        for (int i = 0; i <= n; i++)
        {
            printf("nhap %c(x,y,z)", c++);
            for (int j = 0; j < d; j++)
                scanf("%f", &a[i][j]);
        }
    }

    //In thong tin
    printInfor(p,d,n,a);


    // Bieu dien vector nut
    vectorPoint(u, p, n);
    printf("\n\n\t --------------------------------------------\n");
    printf("VECTO NUT");

    printf("\n");
    for (int i = 0; i <= n + p + 2; i++)
        printf("U[%d] = %0.2f\t", i, u[i]);

    // Ma tran bieu dien he phuong trinh D
    matrix(b, n);
    printf("\n\n\t-----------------------------------------\n");
    printf("\n\nMa tran bieu dien he phuong trinh D: \n\n");
    for (int i = 0; i <= n; i++)
    {
        printf(" |");
        for (int j = 0; j <= n; j++)
            printf("%.3f | ", b[i][j]);
        printf("\n\n");
    }

    // nghich dao ma tran N
    inverseMatrix(b, n, &det);
    printf("\n\n\t------------------------------------------\n");
    printf("\n\nDinh thuc ma tran N: Det(N) = %lf\n\n", det);
    if (det)
    {
        printf("Ma tran nghich dao N: \n\n");
        for (int i = 0; i <= n; i++)
        {
            printf(" |");
            for (int j = 0; j <= n; j++)
                printf("%.3f | ", b[i][j]);
            printf("\n\n");
        }
    }
    else
    {
        printf("\n\t\tKhong co ma tran nghich dao -> Bai toan VO NGHIEM!\n");
        return;
    }
    // nhan ma tran D voi ma tran nghich dao N de tim ma tran P
    multMatrix(b, a, resuilt, n, d);
    printf("\n\t------------------------------------------\n\n");
    printf("Ma tran ket qua la P: \n\n");
    for (int i = 0; i < n; i++)
    {
        printf(" |");
        for (int j = 0; j < d; j++)
            printf("%f | ", resuilt[i][j]);
        printf("\n\n");
    }


    // xuat ket qua toa do cac diem dieu khien 
    printf("\n\t------------------------------------------\n\n");
    printf("\n\nTap dinh dieu khien P co gia tri la: \n\n");
    int cnt = 1;
    if(d == 2){
    printf("P(%d) = ( %0.3f , %0.3f )\n\n", cnt ++, a[0][0], a[0][1]);
    for (int i = 0; i<n; i++){
        printf("P(%d) = ( %0.3f , %0.3f )\n\n", cnt ++, resuilt[i][0], resuilt[i][1]);
    }
    printf("P(%d) = ( %0.3f , %0.3f )\n\n", cnt ++, a[n][0], a[n][1]);

    }else {
        printf("P(%d) = ( %0.3f , %0.3f , %0.3f )\n\n", cnt ++, a[0][0], a[0][1], a[0][2]);
        for (int i = 0; i<n; i++){
        printf("P(%d) = ( %0.3f , %0.3f , %0.3f )\n\n", cnt ++, resuilt[i][0], resuilt[i][1], resuilt[i][2]);
    }
    printf("P(%d) = ( %0.3f , %0.3f , %0.3f )\n\n", cnt ++, a[n][0], a[n][1], a[n][2]);  
    }

}
void bsplineUniformVersion2(){
    int z;
    float det;
    int p, n, d;
    printf("1. Nhap tay\n2.Nhap tu file input.txt");
    scanf("%d", &z);

    if(z==1){
        bsplineUniformVersion1();

    }else{
        readFile(&p,&n,&d,a);
        vectorPoint(u, p, n);
        matrix(b, n);
        inverseMatrix(b, n, &det);
        multMatrix(b, a, resuilt, n, d);
        writeFile(&p,&n,&d,a,resuilt);
        printf("\n\nKET QUA CHUONG TRINH DA DUOC LUU VAO FILE output.txt\n");
    }



}