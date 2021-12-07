//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "SearchItApp.h"
#include "../SearchIt-cli/searchit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	// Setting the detault file name to empty
	SelectedFileName->Text = "";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::OpenButtonClick(TObject *Sender)
{
	// Handles when the Choose File button is clicked

	// Open the dialog allowing the user to select a file
	if (OpenDialog1->Execute() == true){

		// Show the selected file name in the UI label
		SelectedFileName->Text = OpenDialog1->FileName;

		// Load and show the file contents in the SearchTextMemo field
		SearchTextMemo->Lines->LoadFromFile(OpenDialog1->FileName);
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SearchClick(TObject *Sender)
{

	// Handles when the Search Now button is clicked


	// Lets first clear the results of any previous search run
	ResultsText->Lines->Clear();

	// Get the search pattern from the pattern input field
	System:String patternInput = PatternInput->Text;

	// Convert the search pattern from a System::String to a std::string
	std::string pattern_str = AnsiString(patternInput).c_str();

	// Convert the file name to a std::string
	//std::string file_str = AnsiString(SelectedFileName->Text).c_str();

    // Convert the text in the textmemo to a std::string
	std::string str = AnsiString(SearchTextMemo->Lines->GetText()).c_str();

	// Make sure we have a search patter and selected file
	if (pattern_str == "") {
		ShowMessage("Please enter a search pattern.");
		return;
	} else if (str == "") {
		ShowMessage("Please provide some text to search. Manually enter text or load from a file.");
		return;
    }

	// Create an instance of our Search program, passing it the text and pattern
	SearchIt searchIt(str, pattern_str);

	// Determine which type of search to perform (KMP or BM)
	std::string searchResults = "Doh!!!";

	if (RadioButtonKMP->IsChecked) {
		// Search using KMP!
		searchResults = searchIt.search("KMP");
	} else {
		// Search using BM!
		searchResults = searchIt.search("BM");
	}

    std::string foo = "";

	// Show the search results in our memo list
	ResultsText->Lines->Add(System::String(searchResults.c_str()));
}
//---------------------------------------------------------------------------



