/* Author: Saumya Saxena
CS536: Computer Graphics - Assignment 3
Date: November 9, 2018
Description: Bi-cubic Bezier Patch
*/

/* Header Files */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <string.h>
#include <fstream>
#include <math.h>

using namespace std;

struct point
{
    double x,y,z;
};

/* Blending Function1 */
double bernstein1(double u)
{
    double b1 = pow((1.000 - u),3);
    return b1;
}

/* Blending Function2 */
double bernstein2(double u)
{
    double b2 = 3.000 * u * pow((1.000 - u),2.0);
    return b2;
}

/* Blending Function3 */
double bernstein3(double u)
{
    double b3 = 3.000 * pow(u,2) * (1.000 - u);
    return b3;
}

/* Blending Function4 */
double bernstein4(double u)
{
    double b3 = pow(u,3);
    return b3;
}

/* Function to calculate the 3-D points */
struct point bernsteinsPolynomial(double u, double v,struct point points[100])
{
    double bernsteinPolynomial_x =  bernstein1(u)*bernstein1(v)*points[0].x +
                                    bernstein1(u)*bernstein2(v)*points[4].x +
                                    bernstein1(u)*bernstein3(v)*points[8].x +
                                    bernstein1(u)*bernstein4(v)*points[12].x +
                                    bernstein2(u)*bernstein1(v)*points[1].x +
                                    bernstein2(u)*bernstein2(v)*points[5].x +
                                    bernstein2(u)*bernstein3(v)*points[9].x +
                                    bernstein2(u)*bernstein4(v)*points[13].x +
                                    bernstein3(u)*bernstein1(v)*points[2].x +
                                    bernstein3(u)*bernstein2(v)*points[6].x +
                                    bernstein3(u)*bernstein3(v)*points[10].x +
                                    bernstein3(u)*bernstein4(v)*points[14].x +
                                    bernstein4(u)*bernstein1(v)*points[3].x +
                                    bernstein4(u)*bernstein2(v)*points[7].x +
                                    bernstein4(u)*bernstein3(v)*points[11].x +
                                    bernstein4(u)*bernstein4(v)*points[15].x;

    double bernsteinPolynomial_y =  bernstein1(u)*bernstein1(v)*points[0].y +
                                    bernstein1(u)*bernstein2(v)*points[4].y +
                                    bernstein1(u)*bernstein3(v)*points[8].y +
                                    bernstein1(u)*bernstein4(v)*points[12].y +
                                    bernstein2(u)*bernstein1(v)*points[1].y +
                                    bernstein2(u)*bernstein2(v)*points[5].y +
                                    bernstein2(u)*bernstein3(v)*points[9].y +
                                    bernstein2(u)*bernstein4(v)*points[13].y +
                                    bernstein3(u)*bernstein1(v)*points[2].y +
                                    bernstein3(u)*bernstein2(v)*points[6].y +
                                    bernstein3(u)*bernstein3(v)*points[10].y +
                                    bernstein3(u)*bernstein4(v)*points[14].y +
                                    bernstein4(u)*bernstein1(v)*points[3].y +
                                    bernstein4(u)*bernstein2(v)*points[7].y +
                                    bernstein4(u)*bernstein3(v)*points[11].y +
                                    bernstein4(u)*bernstein4(v)*points[15].y;

    double bernsteinPolynomial_z =  bernstein1(u)*bernstein1(v)*points[0].z +
                                    bernstein1(u)*bernstein2(v)*points[4].z +
                                    bernstein1(u)*bernstein3(v)*points[8].z +
                                    bernstein1(u)*bernstein4(v)*points[12].z +
                                    bernstein2(u)*bernstein1(v)*points[1].z +
                                    bernstein2(u)*bernstein2(v)*points[5].z +
                                    bernstein2(u)*bernstein3(v)*points[9].z +
                                    bernstein2(u)*bernstein4(v)*points[13].z +
                                    bernstein3(u)*bernstein1(v)*points[2].z +
                                    bernstein3(u)*bernstein2(v)*points[6].z +
                                    bernstein3(u)*bernstein3(v)*points[10].z +
                                    bernstein3(u)*bernstein4(v)*points[14].z +
                                    bernstein4(u)*bernstein1(v)*points[3].z +
                                    bernstein4(u)*bernstein2(v)*points[7].z +
                                    bernstein4(u)*bernstein3(v)*points[11].z +
                                    bernstein4(u)*bernstein4(v)*points[15].z;

    struct point p;

    p.x = bernsteinPolynomial_x;
    p.y = bernsteinPolynomial_y;
    p.z = bernsteinPolynomial_z;

    return p;
}

/* Function to calculate differentiated B(u)[0] */
double tangent1(double u)
{
    double t1 = (-3.00) * pow((1.00-u),2);
    return t1;
}

/* Function to calculate differentiated B(u)[1] */
double tangent2(double u)
{
    double t2 = (3.00)*pow((1.00-u),2) - (6.00 *u *(1.00-u));
    return t2;
}

/* Function to calculate differentiated B(u)[2] */
double tangent3(double u)
{
    double t3 = (6.00*u*(1.00-u)) - (3.00*pow(u,2));
    return t3;
}

/* Function to calculate differentiated B(u)[3] */
double tangent4(double u)
{
    double t4 = 3.00*pow(u,2);
    return t4;
}

/* Function to calculate the normals */
struct point normalPoint(double u,double v,struct point points[100])
{

    double tangentCrossProd_xu = tangent1(u)*bernstein1(v)*points[0].x +
                                 tangent1(u)*bernstein2(v)*points[4].x +
                                 tangent1(u)*bernstein3(v)*points[8].x +
                                 tangent1(u)*bernstein4(v)*points[12].x +
                                 tangent2(u)*bernstein1(v)*points[1].x +
                                 tangent2(u)*bernstein2(v)*points[5].x +
                                 tangent2(u)*bernstein3(v)*points[9].x +
                                 tangent2(u)*bernstein4(v)*points[13].x +
                                 tangent3(u)*bernstein1(v)*points[2].x +
                                 tangent3(u)*bernstein2(v)*points[6].x +
                                 tangent3(u)*bernstein3(v)*points[10].x +
                                 tangent3(u)*bernstein4(v)*points[14].x +
                                 tangent4(u)*bernstein1(v)*points[3].x +
                                 tangent4(u)*bernstein2(v)*points[7].x +
                                 tangent4(u)*bernstein3(v)*points[11].x +
                                 tangent4(u)*bernstein4(v)*points[15].x;

    double tangentCrossProd_yu = tangent1(u)*bernstein1(v)*points[0].y +
                                 tangent1(u)*bernstein2(v)*points[4].y +
                                 tangent1(u)*bernstein3(v)*points[8].y +
                                 tangent1(u)*bernstein4(v)*points[12].y +
                                 tangent2(u)*bernstein1(v)*points[1].y +
                                 tangent2(u)*bernstein2(v)*points[5].y +
                                 tangent2(u)*bernstein3(v)*points[9].y +
                                 tangent2(u)*bernstein4(v)*points[13].y +
                                 tangent3(u)*bernstein1(v)*points[2].y +
                                 tangent3(u)*bernstein2(v)*points[6].y +
                                 tangent3(u)*bernstein3(v)*points[10].y +
                                 tangent3(u)*bernstein4(v)*points[14].y +
                                 tangent4(u)*bernstein1(v)*points[3].y +
                                 tangent4(u)*bernstein2(v)*points[7].y +
                                 tangent4(u)*bernstein3(v)*points[11].y +
                                 tangent4(u)*bernstein4(v)*points[15].y;

    double tangentCrossProd_zu = tangent1(u)*bernstein1(v)*points[0].z +
                                 tangent1(u)*bernstein2(v)*points[4].z +
                                 tangent1(u)*bernstein3(v)*points[8].z +
                                 tangent1(u)*bernstein4(v)*points[12].z +
                                 tangent2(u)*bernstein1(v)*points[1].z +
                                 tangent2(u)*bernstein2(v)*points[5].z +
                                 tangent2(u)*bernstein3(v)*points[9].z +
                                 tangent2(u)*bernstein4(v)*points[13].z +
                                 tangent3(u)*bernstein1(v)*points[2].z +
                                 tangent3(u)*bernstein2(v)*points[6].z +
                                 tangent3(u)*bernstein3(v)*points[10].z +
                                 tangent3(u)*bernstein4(v)*points[14].z +
                                 tangent4(u)*bernstein1(v)*points[3].z +
                                 tangent4(u)*bernstein2(v)*points[7].z +
                                 tangent4(u)*bernstein3(v)*points[11].z +
                                 tangent4(u)*bernstein4(v)*points[15].z;

    double tangentCrossProd_xv = bernstein1(u)*tangent1(v)*points[0].x +
                                 bernstein1(u)*tangent2(v)*points[4].x +
                                 bernstein1(u)*tangent3(v)*points[8].x +
                                 bernstein1(u)*tangent4(v)*points[12].x +
                                 bernstein2(u)*tangent1(v)*points[1].x +
                                 bernstein2(u)*tangent2(v)*points[5].x +
                                 bernstein2(u)*tangent3(v)*points[9].x +
                                 bernstein2(u)*tangent4(v)*points[13].x +
                                 bernstein3(u)*tangent1(v)*points[2].x +
                                 bernstein3(u)*tangent2(v)*points[6].x +
                                 bernstein3(u)*tangent3(v)*points[10].x +
                                 bernstein3(u)*tangent4(v)*points[14].x +
                                 bernstein4(u)*tangent1(v)*points[3].x +
                                 bernstein4(u)*tangent2(v)*points[7].x +
                                 bernstein4(u)*tangent3(v)*points[11].x +
                                 bernstein4(u)*tangent4(v)*points[15].x;

    double tangentCrossProd_yv = bernstein1(u)*tangent1(v)*points[0].y +
                                 bernstein1(u)*tangent2(v)*points[4].y +
                                 bernstein1(u)*tangent3(v)*points[8].y +
                                 bernstein1(u)*tangent4(v)*points[12].y +
                                 bernstein2(u)*tangent1(v)*points[1].y +
                                 bernstein2(u)*tangent2(v)*points[5].y +
                                 bernstein2(u)*tangent3(v)*points[9].y +
                                 bernstein2(u)*tangent4(v)*points[13].y +
                                 bernstein3(u)*tangent1(v)*points[2].y +
                                 bernstein3(u)*tangent2(v)*points[6].y +
                                 bernstein3(u)*tangent3(v)*points[10].y +
                                 bernstein3(u)*tangent4(v)*points[14].y +
                                 bernstein4(u)*tangent1(v)*points[3].y +
                                 bernstein4(u)*tangent2(v)*points[7].y +
                                 bernstein4(u)*tangent3(v)*points[11].y +
                                 bernstein4(u)*tangent4(v)*points[15].y;

    double tangentCrossProd_zv = bernstein1(u)*tangent1(v)*points[0].z +
                                 bernstein1(u)*tangent2(v)*points[4].z +
                                 bernstein1(u)*tangent3(v)*points[8].z +
                                 bernstein1(u)*tangent4(v)*points[12].z +
                                 bernstein2(u)*tangent1(v)*points[1].z +
                                 bernstein2(u)*tangent2(v)*points[5].z +
                                 bernstein2(u)*tangent3(v)*points[9].z +
                                 bernstein2(u)*tangent4(v)*points[13].z +
                                 bernstein3(u)*tangent1(v)*points[2].z +
                                 bernstein3(u)*tangent2(v)*points[6].z +
                                 bernstein3(u)*tangent3(v)*points[10].z +
                                 bernstein3(u)*tangent4(v)*points[14].z +
                                 bernstein4(u)*tangent1(v)*points[3].z +
                                 bernstein4(u)*tangent2(v)*points[7].z +
                                 bernstein4(u)*tangent3(v)*points[11].z +
                                 bernstein4(u)*tangent4(v)*points[15].z;

    struct point normal;

    normal.x = (tangentCrossProd_yu*tangentCrossProd_zv - tangentCrossProd_yv*tangentCrossProd_zu);
    normal.y = (tangentCrossProd_zu*tangentCrossProd_xv - tangentCrossProd_zv*tangentCrossProd_xu);
    normal.z = (tangentCrossProd_xu*tangentCrossProd_yv - tangentCrossProd_xv*tangentCrossProd_yu);

      /*normal.x = tangentCrossProd_xu * tangentCrossProd_xv;
        normal.y = tangentCrossProd_yu * tangentCrossProd_yv;
        normal.z = tangentCrossProd_zu * tangentCrossProd_zv;*/

    return normal;
}

int main(int argc, char** argv)
{
    string filename;
    filename = "patchPoints.txt";
    double num_u = 11,num_v = 11;
    double du,dv,radius = 0.1;
    int flat_shaded = 0;
    int smooth_shaded = 0;

    // loop to take arguments from command line else take up default values
    for (int i = 0; i < argc; ++i)
    {
        if( strcmp(argv[i],"-f") == 0)
        {
            i++;
            filename = argv[i];
        }
        else if(strcmp(argv[i], "-u") == 0)
        {
            i++;
            num_u = atof(argv[i]);
            //cout<<argv[i]<<" ";
        }
        else if(strcmp(argv[i], "-v") == 0)
        {
            i++;
            num_v = atof(argv[i]);
            //cout<<argv[i]<<" ";
        }
        else if(strcmp(argv[i], "-r") == 0)
        {
            i++;
            radius = atof(argv[i]);
            //cout<<argv[i]<<" ";
        }
        else if(strcmp(argv[i], "-S") == 0)
        {
            smooth_shaded = 1;
            //cout<<argv[i]<<" ";
        }
        else if(strcmp(argv[i], "-F") == 0)
        {
           flat_shaded = 1;
           //cout<<argv[i]<<" ";
        }
    }

    if(smooth_shaded == 0 && flat_shaded == 0)
       flat_shaded = 1;

    du = 1.00/(num_u - 1);
    dv = 1.00/(num_v - 1);

    ifstream file;
    string line;
    file.open(filename.c_str());
    struct point points[100];

    int n = 0;

    // loop to read from the input file
    for(;;)
    {
       getline(file,line);
       if(file.eof()) {
           break;
        }

        struct point p;

        std::stringstream linestream(line);

        double value;

        linestream >> value;

        p.x = value;

        linestream >> value;

        p.y = value;

        linestream >> value;

        p.z = value;

        points[n] = p;

        n++;
    }

    struct point vertices[20][20];

    int numberOfPoints = 0;
    cout<<"#Inventor V2.0 ascii\n";

    cout << "ShapeHints {";
    cout << " vertexOrdering"<<"        "<<"COUNTERCLOCKWISE\n";
    cout <<"}\n";

    cout <<"Separator {\n";
    cout <<" Coordinate3 {\n";
    cout <<"   point [\n";
    int i = 0,j = 0;

    //Loop to calculate 3-D points and store in 2-D array
    for(double u = 0.0 ;u <= 1.0;u += du)
    {
       for(double v = 0.0 ;v <= 1.0;v += dv)
       {
            struct point p = bernsteinsPolynomial(v,u,points);
            vertices[i][j] = p;
            numberOfPoints++;
            cout<<vertices[i][j].x << " " << vertices[i][j].y << " " << vertices[i][j].z << ",\n";
            j++;
        }
        i++;
        j = 0;
    }
    cout<<"]\n";
    cout<<"}\n";

    //Check if want to print smooth-shaded
    if(smooth_shaded == 1)
    {
        cout <<"NormalBinding {\n";
        cout <<"value        PER_VERTEX_INDEXED\n";
        cout <<"}\n\n";
        cout <<"Normal {\n";
        cout <<"vector [\n";
        //Loop to calculate the normals and print them
        for(double u = 0.0 ;u <= 1.0;u += du)
        {
            for(double v = 0.0 ;v <= 1.0;v += dv)
            {
                struct point normal = normalPoint(v,u,points);
                cout << (-1)*normal.x <<" "<<(-1)*normal.y<< " "<<(-1)*normal.z<<"\n";
            }
        }
    cout << "]\n";
    cout <<"}\n";
    }

    cout<<"IndexedFaceSet {\n";
    cout<<"coordIndex [\n";

    int coords1,coords2,coords3,coords4,coords5,coords6;
    coords1 = 0;
    coords2 = num_u-1;
    coords3 = num_u;
    coords4 = 0;
    coords5 = num_u;
    coords6 = 1;

    cout << coords4 <<" "<<coords5<<" "<<coords6<<" "<<"-1"<<"\n";

    //Loop to print the triangle indexes
    for(i = 0 ;i < num_u ;i++)
    {
        for(j  = 0 ;j < num_v - 1;j++)
        {
            coords1++;
            coords2++;
            coords3++;
            coords4++;
            coords5++;
            coords6++;
            if(coords1!=num_u*num_v && coords2!=num_u*num_v && coords3!=num_u*num_v &&  coords4!=num_u*num_v && coords5!=num_u*num_v && coords6!=num_u*num_v)
            {
                cout << coords1 <<" "<<coords2<<" "<<coords3<<" "<<"-1,"<<"\n";
                cout << coords4 <<" "<<coords5<<" "<<coords6<<" "<<"-1,"<<"\n";
            }
        }
    }


    cout<<"     ]\n";
    cout<<" }\n";
    cout<<"}\n";

    for(int i=0;i<n;i++)
    {
        cout<<"Separator {LightModel {model PHONG}Material {    diffuseColor 1.0 1.0 1.0}\n";
        cout<<"Transform {translation\n";
        cout<<points[i].x<<" "<<points[i].y<<" "<<points[i].z;
        cout<<"}Sphere {              radius " <<radius<<" }}";
    }
    
    return 0;
}