
#include <maxscript/maxscript.h>
#include <maxscript/foundation/numbers.h>
#include <CS/Biped12Api.h>
#include <maxscript\macros\define_instantiation_functions.h>
def_visible_primitive(BipedCOMValueScale, "BipedCOMValueScale");

Value *BipedCOMValueScale_cf(Value **arg_list, int count)
{
    check_arg_count(BipedCOMValueScale, 2, count);
    Value *pbip_ctrl = arg_list[0];
    Control *ctrl = pbip_ctrl->to_controller();
    if (!ctrl)
        throw RuntimeError(_T("Expected a valid controller."));
    IBipDriver12 *bipDriver = IBipDriver12::GetBipDriver12Interface(*ctrl);
    if (!bipDriver)
        throw RuntimeError(_T("The controller is not a valid IBipDriver."));

    Value *pfactor = arg_list[1];
    float_type_check(pfactor, _T("Expected an float for the factor" ));
    float factor = pfactor->to_float();

    Control *verticalControl = bipDriver->GetVerticalControl();
    int keycount = verticalControl->NumKeys();
    INode *pnode = bipDriver->GetNode(13);
    bipDriver->StartSettingBipedKeys();
    for (int i = 0; i < keycount; i++)
    {
        TimeValue time = verticalControl->GetKeyTime(i);
        Matrix3 mat = pnode->GetNodeTM(time);
        mat.Scale(Point3(factor, factor, factor), true);
        bipDriver->SetBipedTM(time, mat, 13, 0);
    }
    bipDriver->StopSettingBipedKeys();
    return nullptr;
}
