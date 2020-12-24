#include "CoefficientMatrix.h"

#ifdef DEBUG_TEST
    #include <iostream>
#endif // DEBUG_TEST


CoefficientMatrix::CoefficientMatrix()
{
    is_forced = true;
}

CoefficientMatrix::~CoefficientMatrix()
{ }


double CoefficientMatrix::GetHeatTransferCoefficientMin()
{
    FillCoefficients();

    if(is_forced)
        return coefficients_min_f[substance_1.type][substance_2.type];
    else
        return coefficients_min[substance_1.type][substance_2.type];
}


double CoefficientMatrix::GetHeatTransferCoefficientMax()
{
    FillCoefficients();

    if(is_forced)
        return coefficients_max_f[substance_1.type][substance_2.type];
    else
        return coefficients_max[substance_1.type][substance_2.type];
}


void CoefficientMatrix::FillCoefficients()
{
    static const int MATRIX_SIZE = 6;

    // Clear matrix
    for(int i=0; i<MATRIX_SIZE; i++)
    {
        for(int j=0; j<MATRIX_SIZE; j++)
        {
            coefficients_min_f[i][j] = coefficients_max_f[i][j] = 0;
            coefficients_min[i][j] = coefficients_max[i][j] = 0;
        }
    }

    // Forced flow
    // Minimum values
    // Gas
    coefficients_min_f[F_GAS][F_GAS] = 10;
    coefficients_min_f[F_GAS][F_LIQUID] = coefficients_min_f[F_LIQUID][F_GAS] = 10;
    coefficients_min_f[F_GAS][F_WATER] = coefficients_min_f[F_WATER][F_GAS] = 10;
    coefficients_min_f[F_GAS][F_CONDENSING_VAPOUR] = coefficients_min_f[F_CONDENSING_VAPOUR][F_GAS] = 10;
    coefficients_min_f[F_GAS][F_CONDENSING_VAPOUR_WATER] = coefficients_min_f[F_CONDENSING_VAPOUR_WATER][F_GAS] = 10;
    coefficients_min_f[F_GAS][F_BOILING_LIQUID] = coefficients_min_f[F_BOILING_LIQUID][F_GAS] = 10;

    // Liquid
    // Water
    coefficients_min_f[F_WATER][F_WATER] = 800;
    coefficients_min_f[F_WATER][F_LIQUID] = coefficients_min_f[F_LIQUID][F_WATER] = 120;
    coefficients_min_f[F_WATER][F_CONDENSING_VAPOUR_WATER] = coefficients_min_f[F_CONDENSING_VAPOUR_WATER][F_WATER] = 800;
    coefficients_min_f[F_WATER][F_CONDENSING_VAPOUR] = coefficients_min_f[F_CONDENSING_VAPOUR][F_WATER] = 300;
    coefficients_min_f[F_WATER][F_BOILING_LIQUID] = coefficients_min_f[F_BOILING_LIQUID][F_WATER] = 300;

    // Not water
    coefficients_min_f[F_LIQUID][F_LIQUID] = 120;
    coefficients_min_f[F_LIQUID][F_CONDENSING_VAPOUR] = coefficients_min_f[F_CONDENSING_VAPOUR][F_LIQUID] = 120;
    coefficients_min_f[F_LIQUID][F_CONDENSING_VAPOUR_WATER] = coefficients_min_f[F_CONDENSING_VAPOUR_WATER][F_LIQUID] = 120;
    coefficients_min_f[F_LIQUID][F_BOILING_LIQUID] = coefficients_min_f[F_BOILING_LIQUID][F_LIQUID] = 300;

    // Vapour
    coefficients_min_f[F_CONDENSING_VAPOUR][F_CONDENSING_VAPOUR] = 300;
    coefficients_min_f[F_CONDENSING_VAPOUR_WATER][F_CONDENSING_VAPOUR_WATER] = 300;
    coefficients_min_f[F_CONDENSING_VAPOUR][F_CONDENSING_VAPOUR_WATER] = coefficients_min_f[F_CONDENSING_VAPOUR_WATER][F_CONDENSING_VAPOUR] = 300;
    coefficients_min_f[F_CONDENSING_VAPOUR][F_BOILING_LIQUID] = coefficients_min_f[F_BOILING_LIQUID][F_CONDENSING_VAPOUR] = 300;

    // Boiling liquid
    coefficients_min_f[F_BOILING_LIQUID][F_BOILING_LIQUID] = 300;
    coefficients_min_f[F_CONDENSING_VAPOUR_WATER][F_BOILING_LIQUID] = coefficients_min_f[F_BOILING_LIQUID][F_CONDENSING_VAPOUR_WATER] = 300;


    // Maximum values
    // Gas
    coefficients_max_f[F_GAS][F_GAS] = 40;
    coefficients_max_f[F_GAS][F_LIQUID] = coefficients_max_f[F_LIQUID][F_GAS] = 60;
    coefficients_max_f[F_GAS][F_WATER] = coefficients_max_f[F_WATER][F_GAS] = 60;
    coefficients_max_f[F_GAS][F_CONDENSING_VAPOUR] = coefficients_max_f[F_CONDENSING_VAPOUR][F_GAS] = 60;
    coefficients_max_f[F_GAS][F_CONDENSING_VAPOUR_WATER] = coefficients_max_f[F_CONDENSING_VAPOUR_WATER][F_GAS] = 60;
    coefficients_max_f[F_GAS][F_BOILING_LIQUID] = coefficients_max_f[F_BOILING_LIQUID][F_GAS] = 60;

    // Liquid
    // Water
    coefficients_max_f[F_WATER][F_WATER] = 1700;
    coefficients_max_f[F_WATER][F_LIQUID] = coefficients_max_f[F_LIQUID][F_WATER] = 270;
    coefficients_max_f[F_WATER][F_CONDENSING_VAPOUR_WATER] = coefficients_max_f[F_CONDENSING_VAPOUR_WATER][F_WATER] = 3500;
    coefficients_max_f[F_WATER][F_CONDENSING_VAPOUR] = coefficients_max_f[F_CONDENSING_VAPOUR][F_WATER] = 800;
    coefficients_max_f[F_WATER][F_BOILING_LIQUID] = coefficients_max_f[F_BOILING_LIQUID][F_WATER] = 800;

    // Not water
    coefficients_max_f[F_LIQUID][F_LIQUID] = 270;
    coefficients_max_f[F_LIQUID][F_CONDENSING_VAPOUR] = coefficients_max_f[F_CONDENSING_VAPOUR][F_LIQUID] = 340;
    coefficients_max_f[F_LIQUID][F_CONDENSING_VAPOUR_WATER] = coefficients_max_f[F_CONDENSING_VAPOUR_WATER][F_LIQUID] = 340;
    coefficients_max_f[F_LIQUID][F_BOILING_LIQUID] = coefficients_max_f[F_BOILING_LIQUID][F_LIQUID] = 800;

    // Vapour
    coefficients_max_f[F_CONDENSING_VAPOUR][F_CONDENSING_VAPOUR] = 800;
    coefficients_max_f[F_CONDENSING_VAPOUR_WATER][F_CONDENSING_VAPOUR_WATER] = 2500;
    coefficients_max_f[F_CONDENSING_VAPOUR][F_CONDENSING_VAPOUR_WATER] = coefficients_max_f[F_CONDENSING_VAPOUR_WATER][F_CONDENSING_VAPOUR] = 2500;
    coefficients_max_f[F_CONDENSING_VAPOUR][F_BOILING_LIQUID] = coefficients_max_f[F_BOILING_LIQUID][F_CONDENSING_VAPOUR] = 2500;

    // Boiling liquid
    coefficients_max_f[F_BOILING_LIQUID][F_BOILING_LIQUID] = 2500;
    coefficients_max_f[F_CONDENSING_VAPOUR_WATER][F_BOILING_LIQUID] = coefficients_max_f[F_BOILING_LIQUID][F_CONDENSING_VAPOUR_WATER] = 2500;



    // Free (gravity) flow
    // Minimum values
    // Gas
    coefficients_min[F_GAS][F_GAS] = 4;
    coefficients_min[F_GAS][F_LIQUID] = coefficients_min[F_LIQUID][F_GAS] = 6;
    coefficients_min[F_GAS][F_WATER] = coefficients_min[F_WATER][F_GAS] = 6;
    coefficients_min[F_GAS][F_CONDENSING_VAPOUR] = coefficients_min[F_CONDENSING_VAPOUR][F_GAS] = 6;
    coefficients_min[F_GAS][F_CONDENSING_VAPOUR_WATER] = coefficients_min[F_CONDENSING_VAPOUR_WATER][F_GAS] = 6;
    coefficients_min[F_GAS][F_BOILING_LIQUID] = coefficients_min[F_BOILING_LIQUID][F_GAS] = 6;

    // Liquid
    // Water
    coefficients_min[F_WATER][F_WATER] = 140;
    coefficients_min[F_WATER][F_LIQUID] = coefficients_min[F_LIQUID][F_WATER] = 30;
    coefficients_min[F_WATER][F_CONDENSING_VAPOUR_WATER] = coefficients_min[F_CONDENSING_VAPOUR_WATER][F_WATER] = 300;
    coefficients_min[F_WATER][F_CONDENSING_VAPOUR] = coefficients_min[F_CONDENSING_VAPOUR][F_WATER] = 230;
    coefficients_min[F_WATER][F_BOILING_LIQUID] = coefficients_min[F_BOILING_LIQUID][F_WATER] = 230;

    // Not water
    coefficients_min[F_LIQUID][F_LIQUID] = 30;
    coefficients_min[F_LIQUID][F_CONDENSING_VAPOUR] = coefficients_min[F_CONDENSING_VAPOUR][F_LIQUID] = 60;
    coefficients_min[F_LIQUID][F_CONDENSING_VAPOUR_WATER] = coefficients_min[F_CONDENSING_VAPOUR_WATER][F_LIQUID] = 60;
    coefficients_min[F_LIQUID][F_BOILING_LIQUID] = coefficients_min[F_BOILING_LIQUID][F_LIQUID] = 230;

    // Vapour
    coefficients_min[F_CONDENSING_VAPOUR][F_CONDENSING_VAPOUR] = 230;
    coefficients_min[F_CONDENSING_VAPOUR_WATER][F_CONDENSING_VAPOUR_WATER] = 300;
    coefficients_min[F_CONDENSING_VAPOUR][F_CONDENSING_VAPOUR_WATER] = coefficients_min[F_CONDENSING_VAPOUR_WATER][F_CONDENSING_VAPOUR] = 300;
    coefficients_min[F_CONDENSING_VAPOUR][F_BOILING_LIQUID] = coefficients_min[F_BOILING_LIQUID][F_CONDENSING_VAPOUR] = 300;

    // Boiling liquid
    coefficients_min[F_BOILING_LIQUID][F_BOILING_LIQUID] = 300;
    coefficients_min[F_CONDENSING_VAPOUR_WATER][F_BOILING_LIQUID] = coefficients_min[F_BOILING_LIQUID][F_CONDENSING_VAPOUR_WATER] = 300;


    // Maximum values
    // Gas
    coefficients_max[F_GAS][F_GAS] = 12;
    coefficients_max[F_GAS][F_LIQUID] = coefficients_max[F_LIQUID][F_GAS] = 20;
    coefficients_max[F_GAS][F_WATER] = coefficients_max[F_WATER][F_GAS] = 20;
    coefficients_max[F_GAS][F_CONDENSING_VAPOUR] = coefficients_max[F_CONDENSING_VAPOUR][F_GAS] = 12;
    coefficients_max[F_GAS][F_CONDENSING_VAPOUR_WATER] = coefficients_max[F_CONDENSING_VAPOUR_WATER][F_GAS] = 12;
    coefficients_max[F_GAS][F_BOILING_LIQUID] = coefficients_max[F_BOILING_LIQUID][F_GAS] = 12;

    // Liquid
    // Water
    coefficients_max[F_WATER][F_WATER] = 430;
    coefficients_max[F_WATER][F_LIQUID] = coefficients_max[F_LIQUID][F_WATER] = 60;
    coefficients_max[F_WATER][F_CONDENSING_VAPOUR_WATER] = coefficients_max[F_CONDENSING_VAPOUR_WATER][F_WATER] = 1200;
    coefficients_max[F_WATER][F_CONDENSING_VAPOUR] = coefficients_max[F_CONDENSING_VAPOUR][F_WATER] = 460;
    coefficients_max[F_WATER][F_BOILING_LIQUID] = coefficients_max[F_BOILING_LIQUID][F_WATER] = 460;

    // Not water
    coefficients_max[F_LIQUID][F_LIQUID] = 60;
    coefficients_max[F_LIQUID][F_CONDENSING_VAPOUR] = coefficients_max[F_CONDENSING_VAPOUR][F_LIQUID] = 170;
    coefficients_max[F_LIQUID][F_CONDENSING_VAPOUR_WATER] = coefficients_max[F_CONDENSING_VAPOUR_WATER][F_LIQUID] = 170;
    coefficients_max[F_LIQUID][F_BOILING_LIQUID] = coefficients_max[F_BOILING_LIQUID][F_LIQUID] = 460;

    // Vapour
    coefficients_max[F_CONDENSING_VAPOUR][F_CONDENSING_VAPOUR] = 460;
    coefficients_max[F_CONDENSING_VAPOUR_WATER][F_CONDENSING_VAPOUR_WATER] = 2500;
    coefficients_max[F_CONDENSING_VAPOUR][F_CONDENSING_VAPOUR_WATER] = coefficients_max[F_CONDENSING_VAPOUR_WATER][F_CONDENSING_VAPOUR] = 2500;
    coefficients_max[F_CONDENSING_VAPOUR][F_BOILING_LIQUID] = coefficients_max[F_BOILING_LIQUID][F_CONDENSING_VAPOUR] = 2500;

    // Boiling liquid
    coefficients_max[F_BOILING_LIQUID][F_BOILING_LIQUID] = 2500;
    coefficients_max[F_CONDENSING_VAPOUR_WATER][F_BOILING_LIQUID] = coefficients_max[F_BOILING_LIQUID][F_CONDENSING_VAPOUR_WATER] = 2500;
}

#ifdef DEBUG_TEST
    void CoefficientMatrix::ShowMatrix()
    {
        FillCoefficients();
        std::cout<<"Values:"<<std::endl;
        for(int i=0; i<6; i++)
        {
            for(int j=0; j<6; j++)
            {
                std::cout<<coefficients_min[i][j]<<"-"<<coefficients_max[i][j]<<"\t\t";
            }
            std::cout<<std::endl;
        }
    }
#endif // DEBUG_TEST
