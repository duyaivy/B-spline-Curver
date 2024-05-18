#include <stdio.h>

void readFile(int *p, int *n, int *d, float a[100][100])
{
    FILE *file;
    file = fopen("inputccc.txt", "r");

    fscanf(file, "%d", p);
    fscanf(file, "%d", d);
    fscanf(file, "%d", n);

    if (*d == 2)

    {
        int i, j;
        for (i = 0; i <= *n; i++)
        {

            for (j = 0; j < *d; j++)
                fscanf(file, "%f", &a[i][j]);
        }
    }
    else
    {
        int i, j;
        for (i = 0; i <= *n; i++)
        {
            for (j = 0; j < *d; j++)
                fscanf(file, "%f", &a[i][j]);
        }
    }
}

void writeFile(int *p, int *n, int *d, float a[][100], float u[100], float resuilt[100][100])
{

    FILE *file;
    file = fopen("output.txt", "w");

    // in thong tin chuong trinh
    fprintf(file, "\n\n\t --------------------------------------------\n");
    fprintf(file, "\t\t\t\tPROGRAM INFORMATION\n"); // degree p, data point, coordinates of the data points
    fprintf(file, "\nDegree (p): %d\t Number of dimensions(d): %d\t Data point(n): %d\n", *p, *d, *n + 1);
    fprintf(file, "\nCoordinates of the data points\n\n");

    char tmp = 'A';
    int cnt = 0;
    int i;
    for (i = 0; i <= *n; i++)
    {
        if (cnt == 3)
        {
            fprintf(file, "\n\n");
            cnt = 0;
        }
        if (*d == 2)
        {
            fprintf(file, "%c( %0.2f , %0.2f );\t", tmp++, a[i][0], a[i][1]);
            cnt++;
        }
        else
        {
            fprintf(file, "%c( %0.2f , %0.2f , %0.2f );\t", tmp++, a[i][0], a[i][1], a[i][2]);
            cnt++;
        }
    }

    // for (int i = 0; i <= *n + *p + 2; i++)
    //     fprintf(file,"U[%d] = %0.2f\t", i, u[i]);
    fprintf(file, "\n\n\t --------------------------------------------\n");

    // in ket qua chuong trinh
    // fprintf(file, "\n\t------------------------------------------\n\n");
    fprintf(file, "\t\t\t\tPROGRAM RESULT: \n\n");
    // in vector point
    fprintf(file, "\n\nThe coordinates of the Vector Point:\n\n");

    cnt = 0;
    for (int i = 0; i <= *n + *p + 2; i++)
    {
        if (cnt == 4)
        {
            fprintf(file, "\n\n");
            fprintf(file, "U[%d] = %0.2f;\t", i, u[i]);
            cnt = 1;
        }
        else
        {
            fprintf(file, "U[%d] = %0.2f;\t", i, u[i]);
            cnt++;
        }
    }

    // in gia tri
    fprintf(file, "\n\n\n\nThe value of the control vertices P: \n\n");
    cnt = 1;
    if (*d == 2)
    {
        fprintf(file, "P(%d) = ( %0.3f , %0.3f )\n\n", cnt++, a[0][0], a[0][1]);
        for (int i = 0; i < *n; i++)
        {
            fprintf(file, "P(%d) = ( %0.3f , %0.3f )\n\n", cnt++, resuilt[i][0], resuilt[i][1]);
        }
        fprintf(file, "P(%d) = ( %0.3f , %0.3f )\n\n", cnt++, a[*n][0], a[*n][1]);
    }
    else
    {
        fprintf(file, "P(%d) = ( %0.3f , %0.3f , %0.3f )\n\n", cnt++, a[0][0], a[0][1], a[0][2]);
        for (int i = 0; i < *n; i++)
        {
            fprintf(file, "P(%d) = ( %0.3f , %0.3f , %0.3f )\n\n", cnt++, resuilt[i][0], resuilt[i][1], resuilt[i][2]);
        }
        fprintf(file, "P(%d) = ( %0.3f , %0.3f , %0.3f )\n\n", cnt++, a[*n][0], a[*n][1], a[*n][2]);
    }
}

// xuat file nurbscalculator
//
void writeFileNurbs(int *p, int *n, int *d, float a[][100], float u[100], float resuilt[100][100])
{
    FILE *file;
    file = fopen("outputNurbsData.txt", "w");
    char x = '"';
    fprintf(file, "{ %cdiscretization%c: 100, %cdegree%c: 3,%ccontrolPoints%c: [\n",x,x,x,x,x,x);


    if(*d == 2){
        fprintf(file, "%f , %f, 0, 1, " ,a[0][0], a[0][1]);
    for(int i =0; i<*n;i++){
        fprintf(file, "%f , %f, 0, 1, ", resuilt[i][0], resuilt[i][1]);
    }
        fprintf(file, "%f , %f, 0, 1" ,a[*n][0], a[*n][1]);


    }else {
         fprintf(file, "%f,%f,%f,1," ,a[0][0], a[0][1], a[0][2]);
    for(int i =0; i<*n;i++){
        fprintf(file, "%f,%f,%f,1,", resuilt[i][0], resuilt[i][1], resuilt[i][2]);
    }
        fprintf(file, "%f,%f,%f,1" ,a[*n][0], a[*n][1],a[*n][2]);

    }



        fprintf(file, "],\n%cknots%c:   [\n",x,x);
            for (int i = 0; i < *n + *p + 2; i++)
            fprintf(file, "%f,", u[i]);
            fprintf(file, "%f", u[*n + *p + 2]);
            fprintf(file, "]\n}\n",x,x);


}
