#include <wx/wx.h>
#include <vector>

char keys[15] ={
	'1', '2', '3', '4', '5',
	'6', '7', '8', '9', '0',
	'+', '-', '/', '*', '='
};
#define OPERATION_ADD 1
#define OPERATION_SUB 0
#define OPERATION_MUL 2
#define OPERATION_DIV 3
class CalcWindow : public wxFrame{
	public:
		CalcWindow( wxString window, wxPoint point, wxSize size ):
		wxFrame(NULL, wxID_ANY, window, point, size, wxSYSTEM_MENU | wxCLOSE_BOX | wxMINIMIZE_BOX | wxCAPTION){
			result = new wxTextCtrl(this, 44, "0", wxDefaultPosition, wxSize(300, 40), wxTE_READONLY);
			equation = new wxTextCtrl(this, 45, "", wxDefaultPosition, wxSize(300, 40), wxTE_READONLY);
			vert = new wxBoxSizer(wxVERTICAL);
			grid = new wxGridSizer(5, 5, 3, 3);
			for(int i = 0; i < 15; ++i){
				buttons.push_back(new wxButton(this, i+wxID_HIGHEST, keys[i]));
			}
			buttons.push_back(new wxButton(this, 15+wxID_HIGHEST, "CLS"));
			vert->Add(equation, 0, wxALIGN_CENTER, 10);	
			vert->Add(result, 0, wxALIGN_CENTER, 30);	
			vert->Add(grid, 0, wxALIGN_CENTER, 30);
			for( auto &b : buttons ){
				grid->Add(b, 0, 0, 5);
			}
			grid->SetSizeHints(this);
			vert->SetSizeHints(this);
			SetAutoLayout(TRUE);
			SetSizer(vert);
		}
		void OnUpdate(){
			complete_temp_buffer();
			wxString display;	
			display << num1;
			display << " ";
			switch(current_operation){
				case 0: 
					display << "-";
					break;
				case 1:
					display << "+";
					break;
				case 2:
					display << "*";
					break;
				case 3:
					display << "/";
					break;
				default:
					break;
			}
			display << " ";
			display << num2;
			equation->SetLabel(display);
		}
	private:
		void Math( wxCommandEvent& ev ){
			complete_temp_buffer();
			OnUpdate();
			wxString res;
			switch(current_operation){
				case 0: 
					res << num1 - num2;
					break;
				case 1:
					res << num1 + num2;
					break;
				case 2:
					res << num1 * num2;
					break;
				case 3:
					res << num1 / num2;
					break;
				default:
					break;
			}
			num2active = false;
			result->SetLabel(res);
			tBuf_2.Clear();
			tBuf_1.Clear();
		}
		void complete_temp_buffer(){
				tBuf_2.ToLong(&num2);
				tBuf_1.ToLong(&num1);
		}
		void OperationAdd( wxCommandEvent& ev ){
			current_operation = OPERATION_ADD;
			OnUpdate();
			num2active = true;
		}
		void OperationSub( wxCommandEvent& ev ){
			current_operation = OPERATION_SUB;
			OnUpdate();
			num2active = true;
		}
		void OperationMul( wxCommandEvent& ev ){
			current_operation = OPERATION_MUL;
			OnUpdate();
			num2active = true;
		}
		void OperationDiv( wxCommandEvent& ev ){
			current_operation = OPERATION_DIV;
			OnUpdate();
			num2active = true;
		}
		DECLARE_EVENT_TABLE()
		void Number( wxCommandEvent& ev ){
			OnUpdate();
			switch(ev.GetId()){
					case 0+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 1; }
						else{ tBuf_1 << 1; }
						break;
					case 1+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 2; }
						else{ tBuf_1 << 2; }
						break;
					case 2+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 3; }
						else{ tBuf_1 << 3; }
						break;
					case 3+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 4; }
						else{ tBuf_1 << 4; }
						break;
					case 4+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 5; }
						else{ tBuf_1 << 5; }
						break;
					case 5+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 6; }
						else{ tBuf_1 << 6; }
						break;
					case 6+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 7; }
						else{ tBuf_1 << 7; }
						break;
					case 7+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 8; }
						else{ tBuf_1 << 8; }
						break;
					case 8+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 9; }
						else{ tBuf_1 << 9; }
						break;
					case 9+wxID_HIGHEST:
						if(num2active){ tBuf_2 << 0; }
						else{ tBuf_1 << 0; }
						break;
			}
			complete_temp_buffer();
			OnUpdate();
		}
		void Reset(wxCommandEvent& ev){
			tBuf_1.Clear();
			tBuf_2.Clear();
			num1 = 0;
			num2 = 0;
			result->SetLabel("0");
			equation->SetLabel("");
			num2active = false;
		}
		int current_operation = 0;
		long num1=0;
		long num2=0;
		wxString tBuf_1;
		wxString tBuf_2;
		wxTextCtrl* result = nullptr;
		wxTextCtrl* equation = nullptr;
		wxBoxSizer* vert = nullptr;
		wxGridSizer* grid = nullptr;
		bool num2active = false;
		std::vector<wxButton*> buttons;
};

wxBEGIN_EVENT_TABLE( CalcWindow, wxFrame )
	EVT_BUTTON(10+wxID_HIGHEST, CalcWindow::OperationAdd)	
	EVT_BUTTON(11+wxID_HIGHEST, CalcWindow::OperationSub)	
	EVT_BUTTON(12+wxID_HIGHEST, CalcWindow::OperationDiv)	
	EVT_BUTTON(13+wxID_HIGHEST, CalcWindow::OperationMul)	
	EVT_BUTTON(14+wxID_HIGHEST, CalcWindow::Math)	
	EVT_BUTTON(15+wxID_HIGHEST, CalcWindow::Reset)	

	EVT_BUTTON(0+wxID_HIGHEST, CalcWindow::Number)
	EVT_BUTTON(1+wxID_HIGHEST, CalcWindow::Number)
	EVT_BUTTON(2+wxID_HIGHEST, CalcWindow::Number)
	EVT_BUTTON(3+wxID_HIGHEST, CalcWindow::Number)
	EVT_BUTTON(4+wxID_HIGHEST, CalcWindow::Number)
	EVT_BUTTON(5+wxID_HIGHEST, CalcWindow::Number)
	EVT_BUTTON(6+wxID_HIGHEST, CalcWindow::Number)
	EVT_BUTTON(7+wxID_HIGHEST, CalcWindow::Number)
	EVT_BUTTON(8+wxID_HIGHEST, CalcWindow::Number)
	EVT_BUTTON(9+wxID_HIGHEST, CalcWindow::Number)
wxEND_EVENT_TABLE()

class Calculator : public wxApp{
	public:
		bool OnInit(){
			win = new CalcWindow( "Calculator in wxWidgets", wxPoint(1680/2, 1050/2), wxSize(1000, 500));
			win->Show( true );
			return true;
		}
	private:
		CalcWindow* win = nullptr;
};
IMPLEMENT_APP(Calculator)
