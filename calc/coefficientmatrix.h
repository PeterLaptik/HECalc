#ifndef COEFFICIENTMATRIX_H
#define COEFFICIENTMATRIX_H

#include "Substance.h"

//#define DEBUG_TEST

// Keeps preliminary heat transfer coefficients matrix according to fluid types
// The values are hard-coded
class CoefficientMatrix
{
    public:
        CoefficientMatrix();
        virtual ~CoefficientMatrix();

        SetSubstance(const Substance &s1, const Substance &s2)
        {
            substance_1 = s1;
            substance_2 = s2;
        }

        void SetIsForcedFlow(bool value)
        {
            is_forced = value;
        }

        double GetHeatTransferCoefficientMin(void);
        double GetHeatTransferCoefficientMax(void);

        #ifdef DEBUG_TEST
            void ShowMatrix(void);
        #endif // DEBUG_TEST

    protected:

    private:

        #ifdef DEBUG_TEST
            CoefficientMatrix();
        #endif // DEBUG_TEST

        inline void FillCoefficients(void);

        // Forced flow
        double coefficients_min_f[6][6];  // hard coded as per fluid types number (see Substance.h)
        double coefficients_max_f[6][6];  // forced flow
        // Gravity flow
        double coefficients_min[6][6];  // free (gravity) flow
        double coefficients_max[6][6];

        bool is_forced;
        Substance substance_1;
        Substance substance_2;
};

#endif // COEFFICIENTMATRIX_H
