#include "substance_list.h"
#include "../../io/filereader.h"
#include <wx/filename.h>
#include <wx/dir.h>
#include <wx/file.h>

// Folder paths
static const wxString PATH_FOLDER = "base";
static const wxString PATH_DB = "substances.txt";
// Columns width
static const int NUM_WIDTH = 60;
static const int VISC_WIDTH = 80;
static const int NAME_WIDTH = 100;
static const int NOTES_WIDTH = 120;
static const int TYPE_WIDTH = 85;
static const int END_MARGIN = 25;
// Columns types
static const long COL_NAME = 0;
static const long COL_HEAT_CAPACITY = 1;
static const long COL_DENSITY = 2;
static const long COL_CONDENSATION_HEAT = 3;
static const long COL_EVAPORATION_HEAT = 4;
static const long COL_THERMAL_CONDUCTIVITY = 5;
static const long COL_VISCOSITY = 6;
static const long COL_TYPE = 7;
static const long COL_NOTES = 8;


SubstanceList::SubstanceList(wxWindow *parent,
                wxWindowID id,
                const wxPoint &pos,
                const wxSize &size,
                long style,
                const wxValidator &validator,
                const wxString &name)
                : wxListCtrl(parent, id, pos,
                             wxSize(5*NUM_WIDTH + VISC_WIDTH + NAME_WIDTH +
                                    NOTES_WIDTH + TYPE_WIDTH + END_MARGIN, 300),
                             style,
                             validator,
                             name)
{
    this->AppendColumns();
    ReadSubstances();
}

SubstanceList::~SubstanceList()
{ }


void SubstanceList::AppendColumns()
{
    int col_counter = 0;

	wxListItem col_0;
	col_0.SetId(col_counter++);
	col_0.SetText(_(wxT("Name")));
	col_0.SetWidth(NAME_WIDTH);
	this->InsertColumn(col_counter++, col_0);

	wxListItem col_1;
	col_1.SetId(col_counter++);
	col_1.SetText(_(wxT("c")));
	col_1.SetWidth(NUM_WIDTH);
	this->InsertColumn(col_counter++, col_1);

	wxListItem col_2;
	col_2.SetId(col_counter++);
	col_2.SetText(_(wxT("v")));
	col_2.SetWidth(NUM_WIDTH);
	this->InsertColumn(col_counter++, col_2);

	wxListItem col_3;
	col_3.SetId(col_counter++);
	col_3.SetText(_(wxT("r1")));
	col_3.SetWidth(NUM_WIDTH);
	this->InsertColumn(col_counter++, col_3);

	wxListItem col_4;
	col_4.SetId(col_counter++);
	col_4.SetText(_(wxT("r2")));
	col_4.SetWidth(NUM_WIDTH);
	this->InsertColumn(col_counter++, col_4);

	wxListItem col_5;
	col_5.SetId(col_counter++);
	col_5.SetText(_(wxT("l")));
	col_5.SetWidth(NUM_WIDTH);
	this->InsertColumn(col_counter++, col_5);

	wxListItem col_6;
	col_6.SetId(col_counter++);
	col_6.SetText(_(wxT("m")));
	col_6.SetWidth(VISC_WIDTH);
	this->InsertColumn(col_counter++, col_6);

	wxListItem col_7;
	col_7.SetId(col_counter++);
	col_7.SetText(_(wxT("Type")));
	col_7.SetWidth(TYPE_WIDTH);
	this->InsertColumn(col_counter++, col_7);

	wxListItem col_8;
	col_8.SetId(col_counter++);
	col_8.SetText(_(wxT("Notes")));
	col_8.SetWidth(NOTES_WIDTH);
	this->InsertColumn(col_counter++, col_8);
}

wxString SubstanceList::OnGetItemText(long item, long column) const
{
    const Substance &s = m_substances[item];
    wxString result;

    switch(column)
    {
        case COL_NAME:
            return s.name;
        case COL_HEAT_CAPACITY:
            return result<<s.heat_capacity;
        case COL_DENSITY:
            return result<<s.density;
        case COL_CONDENSATION_HEAT:
            return result<<s.heat_condensation;
        case COL_EVAPORATION_HEAT:
            return result<<s.heat_vaporization;
        case COL_THERMAL_CONDUCTIVITY:
            return result<<s.thermal_conductivity;
        case COL_VISCOSITY:
            return result<<s.viscosity;
        case COL_TYPE:
            return Substance::GetTypeNameFor(s.type);
        case COL_NOTES:
            return s.notes;
    }
    return _("err");
}

// Read substances from a text file
void SubstanceList::ReadSubstances()
{
    wxString path = wxFileName::GetCwd() + wxFileName::GetPathSeparator() + PATH_FOLDER;

    if(!wxDir::Exists(path))
        wxDir::Make(path);

    path<<wxFileName::GetPathSeparator()<<PATH_DB;
    if(!wxFileName::Exists(path))
        CreateDefaultBaseFile(path);

    // Read data
    Substance item;
    m_substances.clear();

    FileReader reader(path.ToStdString());
    reader.OpenFile();

    while(reader.ReadLine())
    {
        if(reader.StartsWith()=='#')
            continue;

        item.name = reader.GetString();
        item.heat_capacity = reader.GetDouble();
        item.density = reader.GetDouble();
        item.heat_vaporization = reader.GetDouble();
        item.heat_condensation = reader.GetDouble();
        item.thermal_conductivity = reader.GetDouble();
        item.viscosity = reader.GetDouble();
        item.type = static_cast<FluidType>(reader.GetInteger());
        item.notes = reader.GetString();
        m_substances.push_back(item);
    }
    reader.CloseFile();

    this->SetItemCount(m_substances.size());
}

// Creates a data file if the one does not exist
// The file will contain one substance - water
void SubstanceList::CreateDefaultBaseFile(const wxString &path)
{
    Substance dummy_substance;
    wxFile file;
    file.Create(path);

    wxString line;
    file.Open(path, wxFile::write);

    line<<"#\tName"
        <<"\tHeat capacity, J/(kg*K)"
        <<"\tDensity, kg/cub.m"
        <<"\tEvaporation heat, J/kg"
        <<"\tCondensation heat, J/kg"
        <<"\tThermal conductivity, W/(m*K)"
        <<"\tviscosity, Pa*sec"
        <<"\ttype"
        <<"\tNotes\n";
    file.Write(line);

    line.Clear();
    line<<dummy_substance.name<<'\t'
        <<dummy_substance.heat_capacity<<'\t'
        <<dummy_substance.density<<'\t'
        <<dummy_substance.heat_vaporization<<'\t'
        <<dummy_substance.heat_condensation<<'\t'
        <<dummy_substance.thermal_conductivity<<'\t'
        <<dummy_substance.viscosity<<'\t'
        <<static_cast<int>(dummy_substance.type)<<'\t'
        <<dummy_substance.notes
        <<'\n';
    file.Write(line);
    file.Flush();
    file.Close();
}

// Get substance by index in the list
Substance SubstanceList::GetSubstance(int index) const
{
    Substance result;

    if(index<m_substances.size())
        result = m_substances.at(index);

    return result;
}
