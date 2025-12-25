#pragma once
#include "gui/calender.h"
#include "gui/todo.h"
#include <wx/event.h>
#include <wx/notebook.h>
#include <wx/wx.h>

class MainFrame : public wxFrame {
  public:
    MainFrame(const wxString &title);

  private:
    // Setup methods
    void createControls();
    void setUpSizers();
    void bindEventHandlers();

    // Event handlers

    // Other private methods

    // Control members
    wxPanel *panel;
    wxNotebook *notebook;
    wxPanel *todo_border;
    TodoPanel *todo_panel;
    wxPanel *calender_border;
    CalenderPanel *calender_panel;
};
