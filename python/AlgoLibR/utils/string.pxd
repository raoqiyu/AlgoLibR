
'''
Author: raoqiyu@gmail.com
Date: 2020-05-24 17:45:54
FilePath: /AlgoLibR/python/AlgoLibR/utils/string.pxd
Description: 
'''
cimport cython
from libc.stddef cimport wchar_t
from cpython.ref cimport PyObject

cdef extern from "<string>" namespace 'std':
    cdef cppclass wstring:
        cppclass iterator:
            iterator()
            char& operator*()
            iterator(iterator &)
            iterator operator++()
            iterator operator--()
            bint operator==(iterator)
            bint operator!=(iterator)
        cppclass const_iterator(iterator):
            pass

        wstring() except +
        wstring(const wchar_t *) except +
        wstring(const wchar_t *, size_t) except +
        wstring(const wstring&) except +
        wstring(size_t, wchar_t) except +
        size_t length()
        # const wchar_t* data()

        iterator begin()
        const_iterator const_begin "begin"()
        iterator end()
        const_iterator const_end "end"()

        const wchar_t* c_str()
        const wchar_t* data()
        wchar_t& at(size_t)
        wchar_t& operator[](size_t)


cdef extern from "Python.h":
    # https://docs.python.org/3/c-api/unicode.html#c.PyUnicode_FromWideChar
    PyObject* PyUnicode_FromWideChar(const wchar_t *w, Py_ssize_t size)
    
    # https://docs.python.org/3/c-api/unicode.html#c.PyUnicode_AsWideChar
    Py_ssize_t PyUnicode_AsWideChar(object o, wchar_t *w, Py_ssize_t size) except -1

    #  # https://docs.python.org/3/c-api/unicode.html#c.PyUnicode_AsWideCharString
    wchar_t* PyUnicode_AsWideCharString(PyObject *unicode, Py_ssize_t *size)

# conversion function
cdef inline wstring to_wstring(s):
    # create 0-filled output
    cdef wstring out = wstring(len(s),0)
    PyUnicode_AsWideChar(s, <wchar_t*>out.data(),len(s)) # note cast to remove const 
    return out

cdef inline wchar_t* to_wchar_t(s):
    cdef wchar_t* out
    cdef Py_ssize_t size = len(s)
    out = PyUnicode_AsWideCharString(<PyObject *>s, &size)
    return out

cdef inline str from_wstring(wstring s):
    cdef PyObject* out
    cdef Py_ssize_t size = s.length()
    out = PyUnicode_FromWideChar(<wchar_t*>s.data(), size)
    return <object>out


