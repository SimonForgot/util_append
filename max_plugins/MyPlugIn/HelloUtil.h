#include <max.h>
#include "utilapi.h"
#include <Qt/QmaxRollupContainer.h>
#include <Qt/QmaxSpinBox.h>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QLabel>

class PluginUI : public MaxSDK::QmaxRollupContainer
{
public:
	QLabel *label;
	MaxSDK::QmaxDoubleSpinBox *spinBox;
	QPushButton *button;
	PluginUI() : MaxSDK::QmaxRollupContainer()
	{
		label = new QLabel("No Node Selected", this);
		spinBox = new MaxSDK::QmaxDoubleSpinBox(this);
		spinBox->setRange(0.0, 100.0);
		spinBox->setValue(1.0);
		spinBox->setSingleStep(0.01);
		button = new QPushButton("OK", this);
		QVBoxLayout *layout = new QVBoxLayout(this);

		layout->addWidget(label, 0, Qt::AlignHCenter);
		layout->addWidget(spinBox, 0, Qt::AlignHCenter);
		layout->addWidget(button, 0, Qt::AlignHCenter);
		setLayout(layout);
	}
};

class HelloUtil : public UtilityObj, public QObject, public ReferenceMaker
{
private:
	INode *target_node = nullptr;
	PluginUI *UI;
	void SetReference(int i, ReferenceTarget *pTarget);
public:
	~HelloUtil() { DeleteAllRefsFromMe(); };
	void BeginEditParams(Interface *ip, IUtil *iu);
	void EndEditParams(Interface *ip, IUtil *iu);
	void DeleteThis() {}
	void onButtonClicked();

	void SelectionSetChanged(Interface *ip, IUtil *iu) override;

	int NumRefs() override { return 1; }
	ReferenceTarget *GetReference(int i) { return target_node; }
	RefResult NotifyRefChanged(const Interval &changeInt, RefTargetHandle hTarget, PartID &partID, RefMessage message, BOOL propagate);
};