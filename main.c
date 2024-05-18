#include "bspline_uniform.h"
#include "codeRunnerFile.h"
#include <stdio.h>

float a[100][100], b[100][100], resuilt[100][100];
int p, n, d;
void bsplineUniformVersion1();
void bsplineUniformVersion2();
void bsplineNonUniform();
void bsplineCurve(int k);
int main()
{
   
    int k;
    printf("------------------------------------------------------\n");
    printf("\t|PROGRAM TO CALCULATE B-SPLINE CURVE|");
    printf("\n\t\t-----------------\n\n");
    printf("Choose the type of curve B-spline\n1. B-spline Non-uniform.\n2. B-spline Uniform.\nChoose:");
    scanf("%d",&k);

    bsplineCurve(k);
    
   
    return 0;
}

void bsplineVersion1(int k)
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
    if (k == 1) vectorPointNonUniform(u, p, n); else vectorPointUniform(u,p,n);
    printf("\n\n\t --------------------------------------------\n");
    printf("VECTO NUT");

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
    multMatrix(b, a, resuilt,n, n, d);
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
void bsplineCurve(int k){
   
    int z;
    float det;
    int p, n, d;
    printf("\nChoose the data input method for the problem\n");
    printf("1. Input from keyboard.\n2. Input from the file Input.txt\n");
    printf("Choose:");
    scanf("%d", &z);

    if(z==1){
        bsplineVersion1(k);

    }else{
        readFile(&p,&n,&d,a);
        if(k == 1)   vectorPointNonUniform(u, p, n); else vectorPointUniform(u,p,n);
        matrix(b, n);
        inverseMatrix(b, n, &det);
        multMatrix(b, a, resuilt, n,n, d);
        writeFile(&p,&n,&d,a,u,resuilt);
        writeFileNurbs(&p,&n,&d,a,u,resuilt);
        printf("\n\nTHE PROGRAM'S RESULT HAS BEEN SAVED TO THE FILE Output.txt\n");    }

   

}
