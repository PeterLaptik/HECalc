#ifndef OUTPUT_DATA_H_INCLUDED
#define OUTPUT_DATA_H_INCLUDED

class HeatExchanger;

enum HeType
{
    SHELL_TUBE_HE = 0
};

class OutputData
{
    public:
        static OutputData& GetInstance(void);
        ~OutputData();

        double Re_in;
        double Re_out;

        HeatExchanger* GetEquipmentUnit(void);

    private:
        OutputData();

        HeatExchanger *he;
        HeType m_type;
};

#endif // OUTPUT_DATA_H_INCLUDED
