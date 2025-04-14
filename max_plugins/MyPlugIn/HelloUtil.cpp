#include "HelloUtil.h"
#include "Geom/matrix3.h"
#include <simpobj.h>

void HelloUtil::BeginEditParams(Interface *ip, IUtil *iu)
{
    GenSphere *gs = (GenSphere *)ip->CreateInstance(GEOMOBJECT_CLASS_ID, Class_ID(SPHERE_CLASS_ID, 0));
    gs->SetParams(10.0f, 240);
    INode *pNode = ip->CreateObjectNode(gs);

    UI = new PluginUI();
    QObject::connect(UI->button, &QPushButton::clicked, this, &HelloUtil::onButtonClicked);
    ip->AddRollupPage(*UI, L"HiScale");
}

void HelloUtil::EndEditParams(Interface *ip, IUtil *iu)
{
    ip->DeleteRollupPage(*UI);
}