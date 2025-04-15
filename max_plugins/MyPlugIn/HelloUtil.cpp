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

    Interface17 *ip = GetCOREInterface17();
    GenSphere *gs = (GenSphere *)ip->CreateInstance(GEOMOBJECT_CLASS_ID, Class_ID(SPHERE_CLASS_ID, 0));
    gs->SetParams(value, 240);
    INode *pNode = ip->CreateObjectNode(gs, L"Sphere");
    ip->RedrawViews(0);

    QMessageBox::information(UI, "SpinBox Value", QString("Value: %1").arg(value));
}

void HelloUtil::SelectionSetChanged(Interface *ip, IUtil *iu)
{
    if (ip->GetSelNodeCount() > 0)
    {
        ReplaceReference(0, ip->GetSelNode(0));
    }
    else
    {
        ReplaceReference(0, NULL);
    }
}

void HelloUtil::SetReference(int i, ReferenceTarget *pTarget)
{
    switch (i)
    {
    case 0: // we have only one reference in this plug-in
    {
        INode *tmp = dynamic_cast<INode *>(pTarget);
        if (tmp)
        {
            target_node = tmp;
            MSTR s(tmp->GetName());
            UI->label->setText(s);
        }
        else{
            target_node = nullptr;
            UI->label->setText("No Node Selected");
        }
    }
    break;
    }
}

RefResult HelloUtil::NotifyRefChanged(const Interval &changeInt, RefTargetHandle hTarget, PartID &partID, RefMessage message, BOOL propagate)
{
    return REF_SUCCEED;
}