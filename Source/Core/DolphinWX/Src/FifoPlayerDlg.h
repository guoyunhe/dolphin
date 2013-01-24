// Copyright (C) 2003 Dolphin Project.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, version 2.0.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License 2.0 for more details.

// A copy of the GPL 2.0 should have been included with the program.
// If not, see http://www.gnu.org/licenses/

// Official SVN repository and contact information can be found at
// http://code.google.com/p/dolphin-emu/

#ifndef __FIFO_PLAYER_DLG_h__
#define __FIFO_PLAYER_DLG_h__

#include <vector>
#include <wx/wx.h>
#include <wx/notebook.h>

class wxSpinCtrl;
class wxSpinEvent;

class FifoPlayerDlg : public wxDialog
{
public:
	FifoPlayerDlg(wxWindow* parent);
	~FifoPlayerDlg();

private:
	void CreateGUIControls();

	void OnPaint( wxPaintEvent& event );
	void OnFrameFrom( wxSpinEvent& event );
	void OnFrameTo( wxSpinEvent& event );
	void OnObjectFrom( wxSpinEvent& event );
	void OnObjectTo( wxSpinEvent& event );
	void OnCheckEarlyMemoryUpdates( wxCommandEvent& event );
	void OnRecordStop( wxCommandEvent& event );
	void OnSaveFile( wxCommandEvent& event );	
	void OnNumFramesToRecord( wxSpinEvent& event );
	void OnCloseClick( wxCommandEvent& event );

	void OnBeginSearch(wxCommandEvent& event);
	void OnFindNextClick(wxCommandEvent& event);
	void OnFindPreviousClick(wxCommandEvent& event);
	void OnSearchFieldTextChanged(wxCommandEvent& event);
	void ChangeSearchResult(unsigned int result_idx);

	void OnRecordingFinished(wxEvent& event);
	void OnFrameWritten(wxEvent& event);

	void OnFrameListSelectionChanged(wxCommandEvent& event);
	void OnObjectListSelectionChanged(wxCommandEvent& event);
	void OnObjectCmdListSelectionChanged(wxCommandEvent& event);
	void OnObjectCmdListSelectionCopy(wxCommandEvent& WXUNUSED(event));

	void UpdatePlayGui();
	void UpdateRecorderGui();
	void UpdateAnalyzerGui();

	wxString CreateFileFrameCountLabel() const;
	wxString CreateCurrentFrameLabel() const;
	wxString CreateFileObjectCountLabel() const;
	wxString CreateRecordingFifoSizeLabel() const;
	wxString CreateRecordingMemSizeLabel() const;
	wxString CreateRecordingFrameCountLabel() const;
	wxString CreateIntegerLabel(int size, const wxString& label) const;

	bool GetSaveButtonEnabled() const;

	// Called from a non-GUI thread
	static void RecordingFinished();
	static void FileLoaded();
	static void FrameWritten();

	static wxEvtHandler *volatile m_EvtHandler;

	wxNotebook* m_Notebook;
	wxPanel* m_PlayPage;
	wxStaticText* m_NumFramesLabel;
	wxStaticText* m_CurrentFrameLabel;
	wxStaticText* m_NumObjectsLabel;
	wxStaticText* m_FrameFromLabel;
	wxSpinCtrl* m_FrameFromCtrl;
	wxStaticText* m_FrameToLabel;
	wxSpinCtrl* m_FrameToCtrl;
	wxStaticText* m_ObjectFromLabel;
	wxSpinCtrl* m_ObjectFromCtrl;
	wxStaticText* m_ObjectToLabel;
	wxSpinCtrl* m_ObjectToCtrl;
	wxCheckBox* m_EarlyMemoryUpdates;
	wxPanel* m_RecordPage;
	wxStaticText* m_RecordingFifoSizeLabel;
	wxStaticText* m_RecordingMemSizeLabel;
	wxStaticText* m_RecordingFramesLabel;
	wxButton* m_RecordStop;
	wxButton* m_Save;
	wxStaticText* m_FramesToRecordLabel;
	wxSpinCtrl* m_FramesToRecordCtrl;

	wxPanel* m_AnalyzePage;
	wxListBox* m_framesList;
	wxListBox* m_objectsList;
	wxListBox* m_objectCmdList;
	std::vector<u32> m_objectCmdOffsets;
	wxStaticText* m_objectCmdInfo;

	wxTextCtrl* m_searchField;
	wxButton* m_beginSearch;
	wxButton* m_findNext;
	wxButton* m_findPrevious;
	wxStaticText* m_numResultsText;

	struct SearchResult {
		int frame_idx;
		int obj_idx;
		int cmd_idx;
	};
	std::vector<SearchResult> search_results;
	unsigned int m_search_result_idx;

	wxButton* m_Close;

	s32 m_FramesToRecord;
};
#endif
