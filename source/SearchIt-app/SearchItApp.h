//---------------------------------------------------------------------------

#ifndef SearchItAppH
#define SearchItAppH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.ImgList.hpp>
#include <System.ImageList.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMemo *SearchTextMemo;
	TOpenDialog *OpenDialog1;
	TButton *OpenButton;
	TMemo *ResultsText;
	TEdit *PatternInput;
	TButton *Search;
	TLabel *SelectedFileName;
	TLabel *Label2;
	TImageList *ImageList1;
	TLabel *LabelTitle;
	TGlyph *Glyph1;
	TGlyph *Glyph2;
	TRadioButton *RadioButtonKMP;
	TRadioButton *RadioButtonBM;
	TLabel *Label4;
	TLabel *Label3;
	TLabel *Label1;
	void __fastcall OpenButtonClick(TObject *Sender);
	void __fastcall SearchClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
