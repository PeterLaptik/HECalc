#ifndef SUBSTANCE_H_INCLUDED
#define SUBSTANCE_H_INCLUDED

#include <wx/string.h>
#include <wx/translation.h>

typedef wxString string;

// Fluid types enumeration
enum FluidType
{
    F_GAS = 0,
    F_LIQUID = 1,
    F_CONDENSING_VAPOUR = 2,   // condensing vapour
    F_WATER = 3,
    F_CONDENSING_VAPOUR_WATER = 4, // condensing water vapour
    F_BOILING_LIQUID = 5
};


// The structure keeps substance name and physical properties

// Default properties (for water)
const string SUBSTANCE_DEFAULT_NAME = "Water";
const double SUBSTANCE_DEFAULT_DENSITY = 1000;
const double SUBSTANCE_DEFAULT_HEAT_CAPACITY = 4190;
const double SUBSTANCE_DEFAULT_THERMAL_CONDUCTIVITY = 0.662;
const double SUBSTANCE_DEFAULT_VISCOSITY = 0.00054;
const string SUBSTANCE_DEFAULT_COMMENT = "";


struct Substance
{
    string name;                    // Fluid name
    double density;                 // kg/cub.m
    double heat_capacity;           // J/(kg*K)
    double heat_vaporization;       // J/kg
    double heat_condensation;       // J/kg
    double thermal_conductivity;    // W/(m*K)
    double viscosity;               // Pa*sec
    string notes;                   // Notes
    FluidType type;                 // See enumeration above


    Substance()
          : name(SUBSTANCE_DEFAULT_NAME),
            density(SUBSTANCE_DEFAULT_DENSITY),
            heat_capacity(SUBSTANCE_DEFAULT_HEAT_CAPACITY),
            heat_vaporization(0),
            heat_condensation(0),
            thermal_conductivity(SUBSTANCE_DEFAULT_THERMAL_CONDUCTIVITY),
            viscosity(SUBSTANCE_DEFAULT_VISCOSITY),
            notes(SUBSTANCE_DEFAULT_COMMENT),
            type(F_WATER)
    { }


    static string GetTypeNameFor(FluidType fluid_type)
    {
        switch (fluid_type)
            {
            case (F_GAS):
                return _("gas");
            case (F_LIQUID):
                return _("liquid");
            case (F_BOILING_LIQUID):
                return _("boiling liquid");
            case (F_CONDENSING_VAPOUR):
                return _("condensing vapour");
            case (F_WATER):
                return _("water");
            case (F_CONDENSING_VAPOUR_WATER):
                return _("condensing water vapour");
            }

        return "error";
    }
};

#endif // SUBSTANCE_H_INCLUDED
