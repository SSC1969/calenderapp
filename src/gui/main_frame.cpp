#include "gui/main_frame.h"
#include "gui/calender.h"
#include "gui/todo.h"
#include <wx/anybutton.h>
#include <wx/event.h>
#include <wx/gdicmn.h>
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/wx.h>

MainFrame::MainFrame(const wxString &title)
    : wxFrame(nullptr, wxID_ANY, title) {

    createControls();
    setUpSizers();
    bindEventHandlers();
}

void MainFrame::createControls() {
    SetBackgroundColour(wxColour("green"));
    wxFont main_font(wxFontInfo(wxSize(0, 20)));

    panel = new wxPanel(this);
    panel->SetFont(main_font);

    notebook = new wxNotebook(panel, wxID_ANY, wxDefaultPosition,
                              wxDefaultSize, wxNB_LEFT | wxNB_NOPAGETHEME);

    todo_panel = new TodoPanel(notebook);
    todo_panel->init();

    calender_panel = new CalenderPanel(notebook);
    calender_panel->init();

    CreateStatusBar();
}

void MainFrame::setUpSizers() {
    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(notebook, wxSizerFlags().Expand().Proportion(1));
    notebook->AddPage(todo_panel, "To-Do");
    notebook->AddPage(calender_panel, "Calender");

    panel->SetSizer(sizer);
    sizer->SetSizeHints(this);
}

void MainFrame::bindEventHandlers() {}
