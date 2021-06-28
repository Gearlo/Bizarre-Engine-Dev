/////////////////////////////////////////////////////////////////////////////////////////////////////////
// BCore
// BScriptContext.h
/////////////////////////////////////////////////////////////////////////////////////////////////////////

//========================================================================
// Copyright (c) 2003-2011 Anael Seghezzi <www.maratis3d.com>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================


#ifndef _M_SCRIPT_CONTEXT_H
#define _M_SCRIPT_CONTEXT_H

#include <Python.h>


#include <iostream> 
#include <cstring> 
#include <cstdarg>



typedef PyObject BScript;
typedef PyObject BSObject;


class M_CORE_EXPORT BScriptContext
{
private:
	BScript * BizarreModule;

public :
	BScriptContext(void){
		Py_Initialize();
	}

	// destructor
	virtual ~BScriptContext(void){ finalizeContext(); }

public:
	void initializeContext( void );	
    void finalizeContext(void){ Py_Finalize(); }

	inline static BScriptContext* getInstance(){ static BScriptContext instance; return &instance; }



public:    

    inline BSObject * getAtributte(BScript * object, const char* name){
      return PyObject_GetAttrString(object, name);  
    }
    
    inline BScript * import_script(const char * name){
        PyObject * p_script = PyImport_ImportModule(name);
		if ( PyErr_Occurred() )
                    PyErr_Print();
        return p_script;
    }
    
    inline void decRef(BScript * script){ Py_DECREF(script); }


public:


    inline void run_file(const char * filename, const char * name = ""){
        FILE* exp_file = fopen(filename, "r");
        PyRun_SimpleFile(exp_file, name);
		if ( PyErr_Occurred() )
                    PyErr_Print();
    }
    
    inline BSObject * run_function(BScript * function, const char* argsFormat, ...){
        PyObject * args = PyTuple_New( strlen(argsFormat) );
        
        va_list argsList;
        va_start(argsList, argsFormat);
        for(unsigned int i = 0u; i < strlen(argsFormat); i++) {
           switch(argsFormat[i]){
               case 's':
                   PyTuple_SetItem(args, i, PyString_FromString(va_arg(argsList, char*)) );
                   break;
               
               case 'i':
                   PyTuple_SetItem(args, i, PyInt_FromLong(va_arg(argsList, int)) );
                   break;
                   
               case 'l':
                   PyTuple_SetItem(args, i, PyLong_FromLong(va_arg(argsList, long)) );
                   break;
                   
               case 'L':
                   PyTuple_SetItem(args, i, PyLong_FromUnsignedLong(va_arg(argsList, unsigned long)) );
                   break;
               
               case 'f':
                   PyTuple_SetItem(args, i, PyFloat_FromDouble(va_arg(argsList, double)) );
                   break;    
                   
               case 'b':
                   PyTuple_SetItem(args, i, PyBool_FromLong(va_arg(argsList, int)) ); 
                   break;
                   
               case 'o':
                   PyTuple_SetItem(args, i, va_arg(argsList, PyObject *) );
                   break;   
                   
           }
        }
        va_end(argsList);
        
        PyObject * r = NULL;
        
        
        if ( function && PyCallable_Check(function) ){
            r = PyObject_CallObject(function, args);
            if (PyErr_Occurred())
                PyErr_Print();
            Py_DECREF(function);
        }else{
            std::cout << "error al ejecutar funcion" << std::endl;
        }
        
        Py_DECREF((PyObject*)args);
        //Py_DECREF((PyObject*)argsList);
        return r;
    }
    
    inline static BSObject * run_method2(BScript * script, const char* name, const char* argsFormat = "", ...){
        PyObject * args = PyTuple_New( strlen(argsFormat) );
        
        va_list argsList;
        va_start(argsList, argsFormat);
        for(unsigned int i = 0u; i < strlen(argsFormat); i++) {
           switch(argsFormat[i]){
               case 's':
                   PyTuple_SetItem(args, i, PyString_FromString(va_arg(argsList, char*)) );
                   break;
               
               case 'i':
                   PyTuple_SetItem(args, i, PyInt_FromLong(va_arg(argsList, int)) );
                   break;
                   
               case 'l':
                   PyTuple_SetItem(args, i, PyLong_FromLong(va_arg(argsList, long)) );
                   break;
                   
               case 'L':
                   PyTuple_SetItem(args, i, PyLong_FromUnsignedLong(va_arg(argsList, unsigned long)) );
                   break;
               
               case 'f':
                   PyTuple_SetItem(args, i, PyFloat_FromDouble(va_arg(argsList, double)) );
                   break;    
                   
               case 'b':
                   PyTuple_SetItem(args, i, PyBool_FromLong(va_arg(argsList, int)) ); 
                   break;
                   
               case 'o':
                   PyTuple_SetItem(args, i, va_arg(argsList, PyObject *) );
                   break;   
                   
           }
        }
        va_end(argsList);
        
        PyObject * r = NULL;
        
        if(script){
            PyObject* method = PyObject_GetAttrString(script, name);
            if ( method && PyCallable_Check(method) ){
                r = PyObject_CallObject(method, args);
                if (PyErr_Occurred())
                    PyErr_Print();
            }else{
                std::cout << "error al ejecutar funcion" << std::endl;
            }
            Py_DECREF(method);
        }
        
        Py_DECREF((PyObject*)args);
        //Py_DECREF((PyObject*)argsList);
        return r;
    }


    inline static void run_method(BScript * script, const char* name, const char* argsFormat = "", ...){
        PyObject * args = PyTuple_New( strlen(argsFormat) );
        
        va_list argsList;
        va_start(argsList, argsFormat);
        for(unsigned int i = 0u; i < strlen(argsFormat); i++) {
           switch(argsFormat[i]){
               case 's':
                   PyTuple_SetItem(args, i, PyString_FromString(va_arg(argsList, char*)) );
                   break;
               
               case 'i':
                   PyTuple_SetItem(args, i, PyInt_FromLong(va_arg(argsList, int)) );
                   break;
                   
               case 'l':
                   PyTuple_SetItem(args, i, PyLong_FromLong(va_arg(argsList, long)) );
                   break;
                   
               case 'L':
                   PyTuple_SetItem(args, i, PyLong_FromUnsignedLong(va_arg(argsList, unsigned long)) );
                   break;
               
               case 'f':
                   PyTuple_SetItem(args, i, PyFloat_FromDouble(va_arg(argsList, double)) );
                   break;    
                   
               case 'b':
                   PyTuple_SetItem(args, i, PyBool_FromLong(va_arg(argsList, int)) ); 
                   break;
                   
               case 'o':
                   PyTuple_SetItem(args, i, va_arg(argsList, PyObject *) );
                   break;   
                   
           }
        }
        va_end(argsList);
        
        PyObject * r = NULL;
        
        if(script){
            PyObject* method = PyObject_GetAttrString(script, name);
            if ( method && PyCallable_Check(method) ){
                r = PyObject_CallObject(method, args);
                if (PyErr_Occurred())
                    PyErr_Print();
            }else{
                std::cout << "error al ejecutar funcion" << std::endl;
            }
            Py_DECREF(method);
        }
        
        Py_DECREF((PyObject*)args);
        //Py_DECREF((PyObject*)argsList);
        Py_DECREF((PyObject*)r);
    }
    
    
    inline void run_string(const char* script){
        PyRun_SimpleString(script);
		if ( PyErr_Occurred() )
                    PyErr_Print();
    }
    

};

#endif
