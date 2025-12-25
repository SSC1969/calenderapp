#include "gui/widgets/datetimepicker.h"

bool wxCustomDateTimePickerPopup::Create(wxWindow *parent) {
    if (!wxPanel::Create(parent, wxID_ANY, wxDefaultPosition,
                         wxDefaultSize,
                         wxBORDER_RAISED | wxTAB_TRAVERSAL)) {
        return false;
    }

    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_FRAMEBK));

    wxBoxSizer *mainSizer = new wxBoxSizer(wxVERTICAL);
    wxBoxSizer *subSizer = new wxBoxSizer(wxHORIZONTAL);

    m_calendar =
        new wxCalendarCtrl(this, wxID_ANY, wxDefaultDateTime,
                           wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
    mainSizer->Add(m_calendar,
                   wxSizerFlags().Expand().Border(wxALL, FromDIP(2)));

    m_timePicker = new wxTimePickerCtrl(this, wxID_ANY);
    subSizer->Add(m_timePicker,
                  wxSizerFlags(3).Expand().Border(wxALL, FromDIP(2)));

    wxButton *OKButton = new wxButton(this, wxID_OK);
    OKButton->Bind(wxEVT_COMMAND_BUTTON_CLICKED,
                   &wxCustomDateTimePickerPopup::OnOKButtonClicked, this);
    subSizer->Add(OKButton,
                  wxSizerFlags(2).Expand().Border(wxALL, FromDIP(2)));

    mainSizer->Add(subSizer, wxSizerFlags().Expand());
    SetSizerAndFit(mainSizer);

    return true;
}

wxString wxCustomDateTimePickerPopup::GetStringValue() const {
    return GetDisplayDateTimeString(GetDateTime());
}

wxSize
wxCustomDateTimePickerPopup::GetAdjustedSize(int WXUNUSED(minWidth),
                                             int WXUNUSED(prefHeight),
                                             int WXUNUSED(maxHeight)) {
    //@fixme: if possible, take into account the method parameters
    return GetSize();
}

void wxCustomDateTimePickerPopup::OnPopup() {
    wxCustomDateTimePicker *picker = GetCustomDateTimePicker();

    if (picker)
        SetDateTime(picker->GetDateTime());
}

wxDateTime wxCustomDateTimePickerPopup::GetDateTime() const {
    wxCHECK(IsCreated(), wxInvalidDateTime);

    wxDateTime dateOnly, timeOnly;

    dateOnly = m_calendar->GetDate();
    wxCHECK(dateOnly.IsValid(), wxInvalidDateTime);

    timeOnly = m_timePicker->GetValue();
    wxCHECK(timeOnly.IsValid(), wxInvalidDateTime);

    return wxDateTime(dateOnly.GetDay(), dateOnly.GetMonth(),
                      dateOnly.GetYear(), timeOnly.GetHour(),
                      timeOnly.GetMinute(), timeOnly.GetSecond());
}

void wxCustomDateTimePickerPopup::SetDateTime(const wxDateTime &dateTime) {
    wxCHECK_RET(IsCreated(), "Call Create() before calling SetDateTime()");

    m_calendar->SetDate(dateTime);
    m_timePicker->SetValue(dateTime);
}

wxString wxCustomDateTimePickerPopup::GetDisplayDateTimeString(
    const wxDateTime &dateTime) {
    wxCHECK(dateTime.IsValid(), wxString(_("Invalid date and/or time")));

    // @fixme: change the format string as needed
    return dateTime.Format("%a %b %e, %I:%M%p");
}

wxCustomDateTimePicker *
wxCustomDateTimePickerPopup::GetCustomDateTimePicker() {
    wxCHECK(IsCreated(), NULL);

    return dynamic_cast<wxCustomDateTimePicker *>(GetComboCtrl());
}

void wxCustomDateTimePickerPopup::OnOKButtonClicked(wxCommandEvent &) {
    wxCustomDateTimePicker *picker = GetCustomDateTimePicker();

    if (picker)
        picker->SetDateTime(GetDateTime());
    Dismiss();
}

// wxCustomDateTimePicker definition

wxCustomDateTimePicker::wxCustomDateTimePicker(wxWindow *parent,
                                               const wxDateTime &dateTime)
    : wxComboCtrl(parent, wxID_ANY, wxEmptyString, wxDefaultPosition,
                  wxDefaultSize, wxCB_READONLY),
      m_dateTime(dateTime) {
    UseAltPopupWindow();
    m_popup = new wxCustomDateTimePickerPopup();
    SetPopupControl(m_popup);

    SetDateTime(m_dateTime);

    // make the combo control fit the date and time string
    wxSize size = GetMinClientSize();
    const wxString dateTimeStr =
        wxCustomDateTimePickerPopup::GetDisplayDateTimeString(m_dateTime);

    size.SetWidth(GetSizeFromTextSize(
                      GetTextExtent(wxString::Format(" %s ", dateTimeStr)))
                      .GetWidth());
    SetMinClientSize(size);
}

void wxCustomDateTimePicker::SetDateTime(const wxDateTime &dateTime) {
    m_dateTime = dateTime;
    SetValue(
        wxCustomDateTimePickerPopup::GetDisplayDateTimeString(m_dateTime));
}
