#pragma once
#include <wx/calctrl.h>
#include <wx/combo.h>
#include <wx/datetime.h>
#include <wx/timectrl.h>
#include <wx/wx.h>

// Code sourced from
// https://forums.wxwidgets.org/viewtopic.php?p=186665#p186665 Thanks, PB!
class wxCustomDateTimePicker;

class wxCustomDateTimePickerPopup : public wxPanel, public wxComboPopup {
  public:
    bool Create(wxWindow *parent) wxOVERRIDE;

    wxWindow *GetControl() wxOVERRIDE { return this; }
    wxString GetStringValue() const wxOVERRIDE;
    wxSize GetAdjustedSize(int minWidth, int prefHeight,
                           int maxHeight) wxOVERRIDE;

    void OnPopup() wxOVERRIDE;

    static wxString GetDisplayDateTimeString(const wxDateTime &dateTime);

  private:
    wxCalendarCtrl *m_calendar;
    wxTimePickerCtrl *m_timePicker;

    wxCustomDateTimePicker *GetCustomDateTimePicker();

    wxDateTime GetDateTime() const;
    void SetDateTime(const wxDateTime &dateTime);

    void OnOKButtonClicked(wxCommandEvent &);
};

class wxCustomDateTimePicker : public wxComboCtrl {
  public:
    wxCustomDateTimePicker(wxWindow *parent,
                           const wxDateTime &dateTime = wxDateTime::Now());

    wxDateTime GetDateTime() const { return m_dateTime; }
    void SetDateTime(const wxDateTime &dateTime);

  private:
    wxDateTime m_dateTime;
    wxCustomDateTimePickerPopup *m_popup;
};
