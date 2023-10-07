#include <boost/python.hpp>
 
using namespace boost::python;
 
int main( int argc, char ** argv ) {
  try {
    Py_Initialize();
 
    object ignored = exec("print(\"Hello, World\")");
    
    Py_Finalize();
  } catch( error_already_set ) {
    PyErr_Print();
  }
}