#include <max.h>
#include "utilapi.h"
#include <Qt/QmaxRollupContainer.h>
#include <Qt/QmaxSpinBox.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>

class PluginUI : public MaxSDK::QmaxRollupContainer
{
public:
	MaxSDK::QmaxDoubleSpinBox *spinBox;
	QPushButton *button;
	PluginUI() : MaxSDK::QmaxRollupContainer()
	{
		spinBox = new MaxSDK::QmaxDoubleSpinBox(this);
		spinBox->setRange(0.0, 100.0);
		spinBox->setValue(1.0);
		spinBox->setSingleStep(0.01);
		button = new QPushButton("OK", this);
		QVBoxLayout *layout = new QVBoxLayout(this);

		layout->addWidget(spinBox, 0, Qt::AlignHCenter);
		layout->addWidget(button, 0, Qt::AlignHCenter);
		setLayout(layout);
	}
};

class HelloUtil : public UtilityObj, public QObject
{
private:
	INode *target_node;
	PluginUI *UI;

public:
	void BeginEditParams(Interface *ip, IUtil *iu);
	void EndEditParams(Interface *ip, IUtil *iu);
	void DeleteThis() {}
	void onButtonClicked()
	{
		float value = UI->spinBox->value();
		QMessageBox::information(UI, "", QString("Value: %1").arg(value));
	}
};