#pragma once

namespace Burov {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	float exLines[] = {
		// голова
		0.5f,3.f,1.f,4.5f,        // от левой щеки вверх до уха
		1.f,4.5f,0.5f,6.f,        // левое ухо слева снизу вверх
		0.5f,6.f,0.5f,7.5f,       // левое ухо слева
		0.5f,7.5f,1.f,8.f,        // левое ухо верх слева
		1.f,8.f,1.5f,8.f,         // левое ухо верх середина
		1.5f,8.f,2.f,7.5f,        // левое ухо верх справа
		2.f,7.5f,1.5f,6.f,        // левое ухо справа сверху вниз
		1.5f,6.f,1.5f,4.5f,       // левое ухо справа до макушки
		1.5f,4.5f,3.f,4.5f,       // макушка
		3.f,4.5f,3.f,6.f,         // правое ухо слева снизу вверх
		3.f,6.f,2.5f,7.5f,        // правое ухо слева
		2.5f,7.5f,3.f,8.f,        // правое ухо верх слева
		3.f,8.f,3.5f,8.f,         // правое ухо верх середина
		3.5f,8.f,4.f,7.5f,        // правое ухо верх справа
		4.f,7.5f,4.f,6.f,         // правое ухо сверху вниз
		4.f,6.f,3.5f,4.5f,        // правое ухо справа
		3.5f,4.5f,4.f,3.f,        // от правого уха вниз до щеки
		4.f,3.f,3.5f,1.5f,        // правая скула
		3.5f,1.5f,2.5f,1.f,       // подбородок справа
		2.5f,1.f,2.f,1.f,         // подбородок снизу
		2.f,1.f,1.f,1.5f,         // подбородок слева
		1.f,1.5f,0.5f,3.f,        // левая скула

		// туловище
		4.f,3.f,5.5f,3.5f,        // спина от головы вправо
		5.5f,3.5f,7.f,3.5f,       // спина верх
		7.f,3.5f,7.5f,2.5f,       // спина сверху до хвоста
		7.5f,2.5f,8.f,2.5f,       // хвост сверху
		8.f,2.5f,8.f,2.f,         // хвост справа
		8.f,2.f,7.5f,2.f,         // хвост низ справа налево
		7.5f,2.f,7.5f,0.5f,       // задняя нога справа сверху вниз
		7.5f,0.5f,6.5f,0.5f,      // задняя нога низ
		6.5f,0.5f,6.5f,1.f,       // задняя нога слева
		6.5f,1.f,6.f,1.f,         // между задних ног
		6.f,1.f,6.f,0.5f,         // левая задняя нога справа
		6.f,0.5f,5.f,0.5f,        // левая задняя нога низ
		5.f,0.5f,5.f,1.f,         // левая задняя нога слева
		5.f,1.f,4.f,1.f,          // между задними и передними ногами
		4.f,1.f,4.f,0.5f,         // правая передняя нога справа
		4.f,0.5f,3.f,0.5f,        // правая передняя нога низ
		3.f,0.5f,3.f,1.f,         // правая передняя нога слева
		3.f,1.f,2.5f,1.f,         // между передних ног
		2.5f,1.f,2.5f,0.5f,       // передняя нога справа
		2.5f,0.5f,1.5f,0.5f,      // передняя нога низ
		1.5f,0.5f,1.5f,1.25f,     // передняя нога слева

		// левый глаз
		1.5f,3.5f,1.5f,3.f,       // левый глаз слева сверху вниз
		1.5f,3.f,2.f,3.f,         // левый глаз низ
		2.f,3.f,2.f,3.5f,         // левый глаз справа
		2.f,3.5f,1.5f,3.5f,       // левый глаз верх

		// правый глаз
		2.5f,3.5f,2.5f,3.f,       // правый глаз слева
		2.5f,3.f,3.f,3.f,         // правый глаз снизу
		3.f,3.f,3.f,3.5f,         // правый глаз справа
		3.f,3.5f,2.5f,3.5f,       // правый глаз сверху

		// ушные раковины
		1.f,5.5f,1.f,7.f,         // левая ушная раковина
		3.5f,5.5f,3.5f,7.f,       // правая ушная раковина

		// нос
		2.f,2.5f,2.5f,2.5f,       // нос сверху
		2.5f,2.5f,2.25f,2.f,      // нос справа
		2.25f,2.f,2.f,2.5f        // нос слева
	};

	unsigned int exArrayLength = sizeof(exLines) / sizeof(float);
	float exVx = 8.5f;
	float exVy = 8.5f;
	float exAspectFig = exVx / exVy;

	float myLines[] = {
		//бабочка
		3.f, 0.5f, 3.f, 3.5f,
		3.f, 3.5f, 5.f, 1.5f,
		3.f, 0.5f, 5.f, 2.5f,
		5.f, 2.5f, 7.f, 0.5f,
		5.f, 1.5f, 7.f, 3.5f,
		7.f, 3.5f, 7.f, 0.5f,
		//декор бабочки
		3.f, 1.5f, 3.5f, 1.f, //треугольник
		3.f, 2.f, 3.5f, 2.5f, //треугольник
		3.5f, 2.5f, 3.f, 3.f, //треугольник
		3.5f, 1.5f, 4.f, 1.5f,
		//квадрат слева
		4.f, 1.5f, 4.f, 2.f,
		4.f, 2.f, 3.5f, 2.f,
		3.5f, 2.f, 3.5f, 1.5f,
		//квадрат справа
		6.f, 2.f, 6.f, 2.5f,
		6.f, 2.5f, 6.5f, 2.5f,
		6.5f, 2.5f, 6.5f, 2.f,
		6.5f, 2.f, 6.f, 2.f,
		//треугольники справа
		7.f, 2.5f, 6.5f, 3.f,
		7.f, 2.f, 6.5f, 1.5f,
		6.5f, 1.5f, 7.f, 1.f,

		//нижняя часть головы 1
		4.5f, 3.f, 5.5f, 3.f,
		5.5f, 3.f, 7.5f, 4.f,
		7.5f, 4.f, 8.f, 5.f,
		8.f, 5.f, 8.f, 7.5f,

		//влево
		2.5f, 4.f, 4.5f, 3.f,
		2.5f, 4.f, 2.f, 5.f,
		2.f, 5.f, 2.f, 7.5f,
		//левая часть прически
		2.f, 5.f, 1.f, 6.f,
		1.f, 6.f, 1.5f, 7.5f,
		1.5f, 7.5f, 1.f, 6.5f,
		1.f, 6.5f, 0.5f, 7.f,
		0.5f, 7.f, 1.f, 8.f,
		1.f, 8.f, 0.5f, 7.5f,
		0.5f, 7.5f, 0.5f, 8.5f,
		0.5f, 8.5f, 2.5f, 11.f,
		2.5f, 11.f, 3.f, 10.5f,
		//переход к правой части прически (низ шляпы)
		3.f, 10.5f, 4.f, 11.f,
		4.f, 11.f, 6.f, 11.f,
		6.f, 11.f, 7.f, 10.5f,
		7.f, 10.5f, 7.5f, 11.f,

		//шляпа
		2.5f, 11.f, 2.5f, 11.5f,
		2.5f, 11.5f, 3.5f, 12.f,
		3.5f, 12.f, 3.f, 13.f,
		3.f, 13.f, 3.5f, 14.f,
		3.5f, 14.f, 4.f, 14.5f,
		4.f, 14.5f, 6.f, 14.5f,
		6.f, 14.5f, 6.5f, 14.f,
		6.5f, 14.f, 7.f, 13.f,
		7.f, 13.f, 6.5f, 12.f,
		6.5f, 12.f, 7.5f, 11.5f,
		//правая часть прически
		7.5f, 11.5f, 7.5f, 11.f,
		7.5f, 11.f, 9.5f, 8.5f,
		9.5f, 8.5f, 9.5f, 7.5f,
		9.5f, 7.5f, 9.f, 8.f,
		9.f, 8.f, 9.5f, 7.f,
		9.5f, 7.f, 9.f, 6.5f,
		9.f, 6.5f, 8.5f, 7.5f,
		8.5f, 7.5f, 9.f, 6.f,
		9.f, 6.f, 8.f, 5.f,
		//украшение на шляпе
		6.f ,11.5f, 7.5f, 12.5f,
		7.5f, 12.5f, 8.5f, 12.5f,
		8.5f, 12.5f, 8.f, 13.f,
		8.f, 12.5f, 8.f, 13.5f,
		8.f, 13.5f, 7.5f, 13.f,
		7.f, 13.f, 8.f, 13.f,
		7.f, 13.f, 7.5f, 12.5f,
		7.5f, 12.5f, 7.5f, 12.f,
		7.5f, 12.f, 8.f, 12.5f,
		7.5f, 12.5f, 7.5f, 13.f,
		//рот
		5.f, 4.f, 6.5f, 4.5f,
		6.5f, 4.5f, 8.f, 5.5f,
		8.f, 6.f, 7.5f, 6.5f,
		7.5f, 6.5f, 7.f, 6.5f, //переход к носу
		7.f, 6.5f, 6.5f, 6.f,
		6.5f, 6.f, 5.f, 5.5f, //середина верхней части
		5.f, 5.5f, 3.5f, 6.f,
		3.5f, 6.f, 3.f, 6.5f,
		3.f, 6.5f, 2.5f, 6.5f,
		2.5f, 6.5f, 2.f, 6.f,
		2.f, 5.5f, 3.5f, 4.5f,
		3.5f, 4.5f,5.f, 4.f,
		//улыбка
		5.f, 4.5f, 6.5f, 5.f,
		6.5f, 5.f, 7.f, 5.5f,
		7.5f, 5.5f, 7.f, 6.f,

		5.f, 4.5f, 3.5f, 5.f,
		3.5f, 5.f, 3.f, 5.5f,
		2.5f, 5.5f, 3.f, 6.f,

		//нос
		7.f, 6.5f, 6.5f, 7.5f,
		6.5f, 7.5f, 5.5f, 8.f,

		6.5f, 8.f, 3.5f, 8.f,//линия над носом
		6.5f, 8.f, 7.5f, 8.5f,
		7.5f, 8.5f, 8.f, 7.5f,
		3.5f, 8.f, 2.5f, 8.5f,
		2.5f, 8.5f, 2.f, 7.5f,
		
		4.5f, 8.f, 3.5f, 7.5f,//левая чатсь носа
		3.5f, 7.5f, 3.f, 6.5f,

		//глаза
		4.5f, 8.f, 5.5f, 10.5f, //правый глаз
		5.5f, 10.5f, 6.5f, 10.5f,
		6.5f, 10.5f, 7.5f, 9.5f,
		7.5f, 9.5f, 7.5f, 8.5f,

		5.5f, 8.f, 4.5f, 10.5f, //левый глаз
		4.5f, 10.5f, 3.5f, 10.5f,
		3.5f, 10.5f, 2.5f, 9.5f,
		2.5f, 9.5f, 2.5f, 8.5f,

		3.5f, 8.f, 3.f, 8.5f, //левый зрачок
		3.f, 8.5f, 3.5f, 9.5f,
		3.5f, 9.5f, 4.f, 9.5f,
		4.f, 9.5f, 4.5f, 8.5f,
		4.5f, 8.5f, 4.f, 8.f,
		4.f, 8.f, 4.f, 8.5f,
		4.f, 8.5f, 3.5f, 8.5f,
		3.5f, 8.5f, 3.5f, 8.f,

		6.f, 8.f, 5.5f, 8.5f,
		5.5f, 8.5f, 6.f, 9.5f,
		6.f, 9.5f, 6.5f, 9.5f,
		6.5f, 9.5f, 7.f, 8.5f,
		7.f, 8.5f, 6.5f, 8.f,
		6.5f, 8.f, 6.5f, 8.5f,
		6.5f, 8.5f, 6.f, 8.5f,
		6.f, 8.5f, 6.f, 8.f

	};

	unsigned int myArrayLength = sizeof(myLines) / sizeof(float);
	float myVx = 10.f;
	float myVy = 15.f;
	float myAspectFig = myVx / myVy;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->DoubleBuffered = true;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->Resize += gcnew System::EventHandler(this, &MyForm::MyForm_Resize);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: bool keepAspectRatio; // значение-сохранять ли соотношение сторон рисунка?
			 bool showExample;
	private: System::Void MyForm_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
		Graphics^ g = e->Graphics;
		g->Clear(Color::Aquamarine);

		Pen^ blackPen = gcnew Pen(Color::Black, 2);

		float* lines;
		float Vx, Vy, aspectFig;
		unsigned int arrayLength;

		if (showExample) {
			lines = exLines;
			Vx = exVx;
			Vy = exVy;
			aspectFig = exAspectFig;
			arrayLength = exArrayLength;
		}
		else {
			lines = myLines;
			Vx = myVx;
			Vy = myVy;
			aspectFig = myAspectFig;
			arrayLength = myArrayLength;
		}

		float Wx = ClientRectangle.Width;
		float Wy = ClientRectangle.Height;
		float aspectForm = Wx / Wy; // соотношение сторон окна рисования

		float Sx, Sy;
		if (keepAspectRatio) {
			// Сохраняем соотношение сторон
			Sx = Sy = (aspectFig < aspectForm) ? Wy / Vy : Wx / Vx;
		}
		else {
			// Растягиваем под окно
			Sx = Wx / Vx;
			Sy = Wy / Vy;
		}

		float Ty = Sy * Vy;  // смещение по Y

		// Рисуем все отрезки
		for (int i = 0; i < arrayLength; i += 4) {
			g->DrawLine(blackPen,
				Sx * lines[i],           // x1
				Ty - Sy * lines[i + 1],  // y1
				Sx * lines[i + 2],       // x2
				Ty - Sy * lines[i + 3]); // y2
		}


	}
	private: System::Void MyForm_Resize(System::Object^ sender, System::EventArgs^ e) {
		Refresh();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		keepAspectRatio = true; // начальное значение: сохранять соотношение сторон рисунка
		showExample = true;
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode) {
		case Keys::M:
			keepAspectRatio = !keepAspectRatio;  // переключение режима
			break;
		case Keys::N:
			showExample = !showExample;
			break;
		default:
			break;
		}
		Refresh();  // обновить изображение
	}
	};
}
