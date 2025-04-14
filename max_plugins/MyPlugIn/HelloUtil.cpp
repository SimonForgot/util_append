#include "HelloUtil.h"
#include "Geom/matrix3.h"
#include <simpobj.h>
#include <QtWidgets/QMessageBox>

void HelloUtil::BeginEditParams(Interface *ip, IUtil *iu)
{
    UI = new PluginUI();
    QObject::connect(UI->button, &QPushButton::clicked, this, &HelloUtil::onButtonClicked);
    ip->AddRollupPage(*UI, L"HiScale");
}

void HelloUtil::EndEditParams(Interface *ip, IUtil *iu)
{
    ip->DeleteRollupPage(*UI);
}

void HelloUtil::onButtonClicked()
{
    float value = UI->spinBox->value();

    Interface17* ip = GetCOREInterface17();
    GenSphere *gs = (GenSphere *)ip->CreateInstance(GEOMOBJECT_CLASS_ID, Class_ID(SPHERE_CLASS_ID, 0));
    gs->SetParams(value, 240);
    INode *pNode = ip->CreateObjectNode(gs, L"Sphere");

    QMessageBox::information(UI, "SpinBox Value", QString("Value: %1").arg(value));
}
