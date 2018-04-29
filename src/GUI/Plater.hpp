#ifndef PLATER_HPP
#define PLATER_HPP
#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif

#include <wx/notebook.h>

#include <stack>

#include "libslic3r.h"
#include "Model.hpp"
#include "Print.hpp"
#include "Config.hpp"

#include "Plater/Plater2DObject.hpp"
#include "Plater/Plate2D.hpp"
#include "Settings.hpp"

namespace Slic3r { namespace GUI {

using UndoOperation = int;

class Plater2DObject;
class Plate2D;

class Plater : public wxPanel 
{
public:
    Plater(wxWindow* parent, const wxString& title, std::shared_ptr<Settings> _settings);
    void add();

private:
    std::shared_ptr<Slic3r::Print> print {std::make_shared<Print>(Slic3r::Print())};
    std::shared_ptr<Slic3r::Model> model {std::make_shared<Model>(Slic3r::Model())};
    std::shared_ptr<Settings> settings {};

    std::shared_ptr<Slic3r::Config> config { Slic3r::Config::new_from_defaults(
        {"bed_shape", "complete_objects", "extruder_clearance_radius", "skirts", "skirt_distance", 
        "brim_width", "serial_port", "serial_speed", "host_type", "print_host", "octoprint_apikey",
        "shortcuts", "filament_colour"})};

    bool processed {false};

    std::vector<Plater2DObject> objects {};

    std::stack<UndoOperation> undo {}; 
    std::stack<UndoOperation> redo {}; 

    wxNotebook* preview_notebook {new wxNotebook(this, -1, wxDefaultPosition, wxSize(335,335), wxNB_BOTTOM)};

    Plate2D* canvas2D {};

};



} } // Namespace Slic3r::GUI

#endif  // PLATER_HPP
