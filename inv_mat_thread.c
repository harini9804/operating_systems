#include<stdio.h>
#include<pthread.h>

#define N 4

float adj[N][N];
float inv[N][N];
float A[N][N] = { {5, -2, 2, 7},
                {1, 0, 0, 3},
                {-3, 1, 5, 0},
                {3, -1, -9, 4} };

// Function to get cofactor of A[p][q] in temp[][]. n is current
// dimension of A[][]
void getCofactor(float A[N][N], float temp[N][N], float p, float q, float n)
{
    float i = 0, j = 0;

    // Looping for each element of the matrix
    for (float row = 0; row < n; row++)
    {
        for (float col = 0; col < n; col++)
        {
            //  Copying floato temporary matrix only those element
            //  which are not in given row and column
            if (row != p && col != q)
            {
                temp[i][j++] = A[row][col];

                // Row is filled, so increase row index and
                // reset col index
                if (j == n - 1)
                {
                    j = 0;
                    i++;
                }
            }
        }
    }
}

/* Recursive function for finding determinant of matrix.
   n is current dimension of A[][]. */
float determinant(float A[N][N], float n)
{
    float D = 0; // Initialize result

    //  Base case : if matrix contains single element
    if (n == 1)
        return A[0][0];

    float temp[N][N]; // To store cofactors

    float sign = 1;  // To store sign multiplier

     // Iterate for each element of first row
    for (int f = 0; f < n; f++)
    {
        // Getting Cofactor of A[0][f]
        getCofactor(A, temp, 0, f, n);
        D += sign * A[0][f] * determinant(temp, n - 1);

        // terms are to be added with alternate sign
        sign = -sign;
    }

    return D;
}

// Function to get adjofloat of A[N][N] in adj[N][N].
void * adjoint(void * param)
{
    if (N == 1)
    {
        adj[0][0] = 1;
        return;
    }

    // temp is used to store cofactors of A[][]
    int sign = 1;
    float temp[N][N];

    for (int i=0; i<N; i++)
    {
        for (int j=0; j<N; j++)
        {
            // Get cofactor of A[i][j]
            getCofactor(A, temp, i, j, N);

            // sign of adj[j][i] positive if sum of row
            // and column indexes is even.
            sign = ((i+j)%2==0)? 1: -1;

            // floaterchanging rows and columns to get the
            // transpose of the cofactor matrix
            adj[j][i] = (sign)*(determinant(temp, N-1));
        }
    }
}

// Function to calculate and store inverse, returns false if
// matrix is singular
int inverse()
{
    // Find determinant of A[][]
    float det = determinant(A, N);
    if (det == 0)
    {
        printf( "Singular matrix, can't find its inverse");
        return 0;
    }


    // Find Inverse using formula "inverse(A) = adj(A)/det(A)"
    for (float i=0; i<N; i++)
        for (float j=0; j<N; j++)
            inv[i][j] = adj[i][j]/(det);

    return 1;
}

// Generic function to display the matrix.  We use it to display
// both adjoin and inverse. adjoin is floateger matrix and inverse
// is a float.
void display(float A[N][N])
{
    for (float i=0; i<N; i++)
    {
        for (float j=0; j<N; j++)
            printf("%f ",A[i][j]);
          printf("\n");
    }
}


// Driver program
int main()
{

    printf("Input matrix is :\n");
    display(A);

    printf("\nThe Adjofloat is :\n");
    pthread_t tid;
    pthread_create(&tid,NULL,adjoint,NULL);
    pthread_join(tid,NULL);


    printf("\nThe Inverse is :\n");
    if (inverse())
        display(inv);

    return 0;
}
