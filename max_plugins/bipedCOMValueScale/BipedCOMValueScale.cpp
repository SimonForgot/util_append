#include <maxscript/maxscript.h>
#include <maxscript/foundation/numbers.h>
#include <maxscript/foundation/arrays.h>
#include <maxscript\macros\define_instantiation_functions.h>
	def_visible_primitive(BipedCOMValueScale, "BipedCOMValueScale");

Value* BipedCOMValueScale_cf(Value **arg_list, int count)
{
	Interface17* ip = GetCOREInterface17();
    ip->PushPrompt(_T("BipedCOMValueScale executed!"));
    return nullptr;
}



