%module deformerDetector

%include "std_string.i"
%include "std_vector.i"

%{    
    #include "header.h"       
%}

namespace std {
  %template(StringVector) vector<string>;
}

%include "header.h"
